// original code by ilia muraviev
// modifications for implementing it as memory2memory decompression only by Luigi Auriemma

// balz.cpp is in the public domain
#define _CRT_DISABLE_PERFCRIT_LOCKS // for vc8 and later
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// common data types
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef long long LONGLONG;

static unsigned char    *in   = NULL;
static unsigned char    *out  = NULL;
static unsigned char    *inl  = NULL;
static unsigned char    *outl = NULL;

//static FILE *in; // input file stream
//static FILE *out; // output file stream
static int xgetc(void *X) {
    if(in >= inl) return(-1);
    return(*in++);
}
static int xwrite(void *buff, int a, int b, void *X) {
    int     len,
            outlen;

    len = a * b;
    outlen = (outl - out);
    if(len > outlen) len = outlen;
    memcpy(out, buff, len);
    out += len;
    return(len);
}

// a predictor estimates the probability of bit 1
// we keep two probabilities:
// one with fast update and one with slow update
// the final probability is a sum of both
class TPredictor {
private:
  WORD p1;
  WORD p2;

public:
  TPredictor(): p1(1<<15), p2(1<<15) {} // initially, p1 and p2 = 0.5

  int P() const {
    return (p1+p2); // combine two probabilities
  }

  void Update(int y) { // update p1 and p2, according to bit y
    if (y) {
      p1+=(WORD(~p1)>>3); // fast update
      p2+=(WORD(~p2)>>6); // slow update
    }
    else {
      p1-=(p1>>3); // fast update
      p2-=(p2>>6); // slow update
    }
  }
};

class TDecoder {
private:
  DWORD x1;
  DWORD x2;
  DWORD x;

public:
  TDecoder(): x1(0), x2(-1) {} // range, initially [0, 1]

  void Init() { // initialize the decoder
    for (int i=0; i<4; i++)
      x=(x<<8)+xgetc(in);
  }

  int Decode(TPredictor &predictor) { // decode one bit
    // calculate subrange with 64-bit precision
    const DWORD xmid=x1+((LONGLONG(x2-x1)*predictor.P())>>17);

    // update the range
    int y=(x<=xmid);
    if (y)
      x2=xmid;
    else
      x1=xmid+1;

    predictor.Update(y); // update the predictor

    // write leading bytes of the range as they become known
    while ((x1^x2)<(1<<24)) { 
      x1<<=8;
      x2=(x2<<8)+255;
      x=(x<<8)+xgetc(in);
    }

    return (y);
  }
};

#define TABBITS 7
#define TABSIZE (1<<TABBITS) // table size

// ppm - a special class for lz-output encoding
static class TPPM {
private:
  TPredictor p1[256][512];
  TPredictor p2[256][TABSIZE];

public:
  TDecoder decoder;

  int Decode(int c) { // decode literal/match length
    int s=1;
    while ((s+=(s+decoder.Decode(p1[c][s])))<512);

    return (s-512);
  }

  int DecodeIndex(int c) { // decode match index
    int x=1;
    while ((x+=(x+decoder.Decode(p2[c][x])))<TABSIZE);

    return (x-TABSIZE);
  }
} ppm;

#define MINMATCH 3 // smallest allowable match length
#define MAXMATCH (255+MINMATCH) // largest allowable match length

#define BUFBITS 25
#define BUFSIZE (1<<BUFBITS) // buffer size

static BYTE buf[BUFSIZE+MAXMATCH]; // data buffer
static DWORD tab[1<<16][TABSIZE]; // offset table

#define IDENT 0xba // identification byte

// perform a special transformation for executable data
static void exetransform(int y, int n) {
  const int end=n-8;
  int i=0;
  // search for pe file header
  while ((*(int *)(buf + i)!=0x4550)&&(++i<end));

  // perform call/jmp address translation
  while (i<end) {
    if ((buf[i++]&254)==0xe8) {
      int addr=*(int *)(buf + i);
      if (y) {
        if ((addr>=-i)&&(addr<(n-i)))
          addr+=i;
        else if ((addr>0)&&(addr<n))
          addr-=n;
      }
      else {
        if (addr<0) {
          if ((addr+i)>=0)
            addr+=n;
        }
        else if (addr<n)
          addr-=i;
      }
      i+=4;
    }
  }
}

// decode in to out
static void decode() {
  BYTE cnt[1<<16]; // count for each context

  // check identification byte
  //if (xgetc(in)!=IDENT) {
    //fprintf(stderr, "bad file format\n");
    //exit(1);
  //}

  // read uncompressed size
  LONGLONG size=-1;
  //fread(&size, 1, sizeof(size), in);
  //if (size<0) {
    //fprintf(stderr, "size error\n");
    //exit(1);
  //}
  size = outl - out;

  //printf("decoding...\n");

  ppm.decoder.Init(); // initialize the decoder

  while (size>0) {
    int i=0;
    while ((i<2)&&(i<size)) { // decode two raw literals
      const int s=ppm.Decode(0);
      // raw literals cannot be larger than 255
      if (s>=256) {
        //fprintf(stderr, "data error\n");
        //exit(1);
        return;
      }
      buf[i++]=s;
    }

    while ((i<BUFSIZE)&&(i<size)) {
      const int c=*(WORD *)(buf + (i-2)); // rolz context
      const int j=i; // keep current buffer offset
      const int s=ppm.Decode(buf[i-1]); // decode literal/match length

      if (s>=256) { // match
        int len=BYTE(s);
        // get the buffer offset from the offset table
        int p=tab[c][(cnt[c]-ppm.DecodeIndex(buf[i-2]))&(TABSIZE-1)];
        buf[i++]=buf[p++]; // partially unrolled loop
        buf[i++]=buf[p++];
        buf[i++]=buf[p++];
        while (len--) // copy the rest of a match
          buf[i++]=buf[p++];
      }
      else // literal
        buf[i++]=s;

      tab[c][++cnt[c]&(TABSIZE-1)]=j; // add a new offset
    }

    exetransform(0, i); // perform a special exe untransformation

    xwrite(&buf, 1, i, out); // write just decoded buffer
    size-=i;
  }
}

extern "C" int unbalz(unsigned char *src, int srcsz, unsigned char *dst, int dstsz) {
    in   = src;
    inl  = src + srcsz;
    out  = dst;
    outl = dst + dstsz;
    decode();
    return(out - dst);
}
