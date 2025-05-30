// modified by Luigi Auriemma
/* expand.c -- Byte Pair Encoding decompression */
/* Copyright 1996 Philip Gage */

/* Byte Pair Compression appeared in the September 1997
 * issue of C/C++ Users Journal. The original source code
 * may still be found at the web site of the magazine
 * (www.cuj.com).
 *
 * The decompressor has been modified by me (Thiadmer
 * Riemersma) to accept a string as input, instead of a
 * complete file.
 */
//#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
//#include "sc.h"

#define STACKSIZE 16

int strexpand(char *dest, unsigned char *source, int maxlen, unsigned char pairtable[128][2]) {
static const unsigned char mypairtable[128][2] = {
  {101,32}, {111,110}, {116,32}, {105,110}, {97,114}, {115,32}, {116,105}, {100,32}, {101,114}, {37,115}, {101,110}, {134,129}, {34,137}, {140,34}, {97,108}, {117,110},
  {114,101}, {110,111}, {97,116}, {115,105}, {121,32}, {97,110}, {111,114}, {109,98}, {115,116}, {32,141}, {100,101}, {41,10}, {109,138}, {145,130}, {101,135}, {139,32},
  {98,108}, {111,108}, {114,97}, {143,99}, {118,142}, {102,163}, {115,121}, {166,151}, {167,161}, {97,32}, {117,115}, {103,32}, {115,147}, {132,162}, {97,160}, {136,32},
  {150,32}, {99,104}, {103,117}, {105,135}, {178,156}, {164,179}, {132,180}, {111,102}, {116,104}, {101,120}, {165,159}, {131,181}, {101,100}, {101,133}, {105,133}, {168,153},
  {154,102}, {118,132}, {183,32}, {105,174}, {193,195}, {116,111}, {173,148}, {109,97}, {99,129}, {101,10}, {115,10}, {112,144}, {116,97}, {182,130}, {98,128}, {152,146},
  {44,32}, {132,97}, {192,131}, {170,130}, {153,10}, {109,146}, {191,155}, {109,211}, {40,214}, {104,97}, {196,128}, {34,32}, {129,32}, {142,32}, {105,99}, {117,108},
  {99,111}, {147,122}, {110,32}, {100,105}, {101,108}, {108,111}, {111,112}, {116,136}, {200,152}, {131,32}, {149,32}, {131,171}, {213,177}, {58,212}, {109,101}, {102,105},
  {100,111}, {97,115}, {108,128}, {118,128}, {230,136}, {232,149}, {204,171}, {203,172}, {215,206}, {119,105}, {109,112}, {110,117}, {185,247}, {165,139}, {251,151}
};
  unsigned char stack[STACKSIZE];
  short c, top = 0;
  int len = 0;

  if(!pairtable) pairtable = (void *)mypairtable;

  //assert(maxlen > 0);
  if(maxlen == 0) return(0);
  if(maxlen < 0) return(-1);
  //len = 1;              /* already 1 byte for '\0' */
  for (;;) {

    /* Pop byte from stack or read byte from the input string */
    if (top)
      c = stack[--top];
    else if ((c = *(unsigned char *)source++) == '\0')
      break;

    /* Push pair on stack or output byte to the output string */
    if (c > 127) {
      //assert(top+2 <= STACKSIZE);
      if(top+2 > STACKSIZE) return(-1);
      stack[top++] = pairtable[c-128][1];
      stack[top++] = pairtable[c-128][0];
    }
    else {
      if(len >= maxlen) return(-1);
      *dest++ = (char)c;
      len++;
      //if (maxlen > 1) { /* reserve one byte for the '\0' */
        //*dest++ = (char)c;
        //maxlen--;
      //}
    }
  }
  //*dest = '\0';
  return len;           /* return number of bytes decoded */
}

