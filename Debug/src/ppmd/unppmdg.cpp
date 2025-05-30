// modified by Luigi Auriemma (mem2mem decompression only)
/****************************************************************************
 *  This file is part of PPMd project                                       *
 *  Written and distributed to public domain by Dmitry Shkarin 1997,        *
 *  1999-2000                                                               *
 *  Contents: model description and encoding/decoding routines              *
 ****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define _FASTCALL
#define _STDCALL
#define CLK_TCK 1
static unsigned char   *EncodedFile  = NULL;
static unsigned char   *EncodedFilel = NULL;
static unsigned char   *DecodedFile  = NULL;
static unsigned char   *DecodedFilel = NULL;
static int xgetc(void *X) {
    if(EncodedFile >= EncodedFilel) return(-1);
    return(*EncodedFile++);
}
static int xputc(int chr, void *X) {
    if(DecodedFile >= DecodedFilel) return(-1);
    *DecodedFile++ = chr;
    return(chr);
}
static void PrintInfo(void *a, void *b, int c) {}
#include "unppmdg_internal.h"


//#include "PPMd.h"
//#include "SubAlloc.h"
#pragma hdrstop
//#include "Coder.hpp"

const int INT_BITS=7, PERIOD_BITS=7, MAX_FREQ=124;
const int INTERVAL=1 << INT_BITS, BIN_SCALE=INTERVAL << PERIOD_BITS;

#pragma pack(1)
static struct SEE2_CONTEXT { // SEE-contexts for PPM-contexts with masked symbols
    WORD Summ;
    BYTE Shift, Count;
    void init(int InitVal) { Summ=InitVal << (Shift=PERIOD_BITS-4); Count=3; }
    UINT getMean() {
        UINT RetVal=Summ >> Shift;          Summ -= RetVal;
        RetVal &= 0x03FF;                   return RetVal+(RetVal == 0);
    }
    void update() {
        if (Shift < PERIOD_BITS && --Count == 0) {
            Summ += Summ;                   Count=3 << Shift++;
        }
    }
} _PACK_ATTR SEE2Cont[44][8];
static struct PPM_CONTEXT {
    WORD NumStats,SummFreq;                     // sizeof(WORD) > sizeof(BYTE)
    struct STATE { BYTE Symbol, Freq; PPM_CONTEXT* Successor; } _PACK_ATTR * Stats;
    PPM_CONTEXT* Suffix;
    inline PPM_CONTEXT(STATE* pStats, PPM_CONTEXT* ShorterContext);
    inline PPM_CONTEXT();
    inline void encodeBinSymbol(int symbol);    // MaxOrder:
    inline void   encodeSymbol1(int symbol);    //  ABCD    context
    inline void   encodeSymbol2(int symbol);    //   BCD    suffix
    inline void           decodeBinSymbol();    //   BCDE   successor
    inline void             decodeSymbol1();    // other orders:
    inline void             decodeSymbol2();    //   BCD    context
    inline void           update1(STATE* p);    //    CD    suffix
    inline void           update2(STATE* p);    //   BCDE   successor
    void                          rescale();
    inline SEE2_CONTEXT* makeEscFreq2(int Diff);
    void* operator new(size_t ) { return AllocContext(); }
    STATE& oneState() const { return (STATE&) SummFreq; }
} _PACK_ATTR * MinContext, * MedContext, * MaxContext;
#pragma pack()

static PPM_CONTEXT::STATE* FoundState;      // found next state transition
static int NumMasked, InitEsc, OrderFall, MaxOrder;
static BYTE CharMask[256], NS2Indx[256], NS2BSIndx[256];
static BYTE EscCount, PrintCount, PrevSuccess;
static WORD BinSumm[128][16];               // binary SEE-contexts

inline PPM_CONTEXT::PPM_CONTEXT(STATE* pStats,PPM_CONTEXT* ShorterContext):
        NumStats(1), Suffix(ShorterContext) { pStats->Successor=this; }
inline PPM_CONTEXT::PPM_CONTEXT(): NumStats(0) {}
static clock_t StartModel()
{
    int i, k;
    InitSubAllocator();
    MaxContext = new PPM_CONTEXT();         MaxContext->Suffix=NULL;
    MaxContext->SummFreq=(MaxContext->NumStats=256)+1;
    MaxContext->Stats = (PPM_CONTEXT::STATE*) AllocUnitsRare(256/2);
    for (PrevSuccess=i=0;i < 256;i++) {
        MaxContext->Stats[i].Symbol=i;      MaxContext->Stats[i].Freq=1;
        MaxContext->Stats[i].Successor=NULL;
    }
    PPM_CONTEXT::STATE* p=MaxContext->Stats;
    for (OrderFall=i=1; ;i++) {
        MaxContext = new PPM_CONTEXT(p,MaxContext);
        if (i == MaxOrder)                  break;
        p=&(MaxContext->oneState());
        p->Symbol = 0;                      p->Freq = 1;
    }
    MaxContext->NumStats=0;                 MedContext=MinContext=MaxContext->Suffix;
static const WORD InitBinEsc[16] = {
                0x3CDD,0x1F3F,0x59BF,0x48F3,0x5FFB,0x5545,0x63D1,0x5D9D,
                0x64A1,0x5ABC,0x6632,0x6051,0x68F6,0x549B,0x6BCA,0x3AB0, };
    for (i=0;i < 128;i++)
        for (k=0;k < 16;k++)
            BinSumm[i][k]=BIN_SCALE-InitBinEsc[k]/(i+2);
    for (i=0;i <   6;i++)                   NS2BSIndx[i]=2*i;
    for (   ;i <  50;i++)                   NS2BSIndx[i]=12;
    for (   ;i < 256;i++)                   NS2BSIndx[i]=14;
    for (i=0;i < 43;i++)
            for (k=0;k < 8;k++)             SEE2Cont[i][k].init(4*i+10);
    SEE2Cont[i][0].Shift=PERIOD_BITS;
    for (i=0;i < 4;i++)                     NS2Indx[i]=i;
    for ( ;i < 4+8;i++)                     NS2Indx[i]=4+((i-4) >> 1);
    for ( ;i < 4+8+32;i++)                  NS2Indx[i]=4+4+((i-4-8) >> 2);
    for ( ;i < 256;i++)                     NS2Indx[i]=4+4+8+((i-4-8-32) >> 3);
    memset(CharMask,0,sizeof(CharMask));    EscCount=PrintCount=1;
    return clock();
}
inline void StopModel() {}
inline void PPM_CONTEXT::rescale()
{
    int OldNS=NumStats, i=NumStats-1, Adder, EscFreq;
    STATE* p1, * p;
    for (p=FoundState;p != Stats;p--)       SWAP(p[0],p[-1]);
    Stats->Freq += 4;                       SummFreq += 4;
    EscFreq=SummFreq-p->Freq;               Adder=(OrderFall != 0);
    SummFreq = (p->Freq=(p->Freq+Adder) >> 1);
    do {
        EscFreq -= (++p)->Freq;
        SummFreq += (p->Freq=(p->Freq+Adder) >> 1);
        if (p[0].Freq > p[-1].Freq) {
            STATE tmp=*(p1=p);
            do { p1[0]=p1[-1]; } while (--p1 != Stats && tmp.Freq > p1[-1].Freq);
            *p1=tmp;
        }
    } while ( --i );
    if (p->Freq == 0) {
        do { i++; } while ((--p)->Freq == 0);
        EscFreq += i;
        if ((NumStats -= i) == 1) {
            STATE tmp=*Stats;
            do { tmp.Freq-=(tmp.Freq >> 1); EscFreq>>=1; } while (EscFreq > 1);
            FreeUnits(Stats,(OldNS+1) >> 1);
            *(FoundState=&oneState())=tmp;  return;
        }
    }
    SummFreq += (EscFreq -= (EscFreq >> 1));
    int n0=(OldNS+1) >> 1, n1=(NumStats+1) >> 1;
    if (n0 != n1)
            Stats=(STATE*)ShrinkUnits(Stats,n0,n1);
    FoundState=Stats;
}
static BOOL MakeRoot(UINT SkipCount,PPM_CONTEXT::STATE* p1)
{
    PPM_CONTEXT* pc=MinContext, * UpBranch=FoundState->Successor;
    PPM_CONTEXT::STATE* p, * ps[MAX_O], ** pps=ps;
    if (SkipCount == 0) {
        *pps++ = FoundState;
        if ( !pc->Suffix )                  goto NO_LOOP;
    } else if (SkipCount == 2)              pc=pc->Suffix;
    if ( p1 ) {
        p=p1;                               pc=pc->Suffix;
        goto LOOP_ENTRY;
    }
    do {
        pc=pc->Suffix;
        if (pc->NumStats != 1) {
            if ((p=pc->Stats)->Symbol != FoundState->Symbol)
                do { p++; } while (p->Symbol != FoundState->Symbol);
        } else                              p=&(pc->oneState());
LOOP_ENTRY:
        if (p->Successor != UpBranch) {
            pc=p->Successor;                break;
        }
        *pps++ = p;
    } while ( pc->Suffix );
NO_LOOP:
    PPM_CONTEXT::STATE& UpState=UpBranch->oneState();
    if (pc->NumStats != 1) {
        UINT cf=UpState.Symbol;
        if ((p=pc->Stats)->Symbol != cf)
                do { p++; } while (p->Symbol != cf);
        UINT s0=pc->SummFreq-pc->NumStats-(cf=p->Freq-1);
        UpState.Freq=1+((2*cf <= s0)?(5*cf > s0):((2*cf+3*s0-1)/(2*s0)));
    } else                                  UpState.Freq=pc->oneState().Freq;
    while (--pps >= ps) {
        pc = new PPM_CONTEXT(*pps,pc);
        if ( !pc )                          return FALSE;
        pc->oneState()=UpState;
    }
    if ( !OrderFall ) {
        UpBranch->NumStats=1;               UpBranch->Suffix=pc;
    }
    return TRUE;
}
static void UpdateModel()
{
    PPM_CONTEXT::STATE fs=*FoundState, * p, *p1=NULL;
    PPM_CONTEXT* pc, * Successor;
    UINT ns1, ns, cf, sf, s0, SkipCount=0;
    if (fs.Freq < MAX_FREQ/4 && (pc=MinContext->Suffix) != NULL) {
        if (pc->NumStats != 1) {
            if ((p1=pc->Stats)->Symbol != fs.Symbol) {
                do { p1++; } while (p1->Symbol != fs.Symbol);
                if (p1[0].Freq >= p1[-1].Freq) {
                    SWAP(p1[0],p1[-1]);     p1--;
                }
            }
            if (p1->Freq < 7*MAX_FREQ/8) {
                p1->Freq += 2;              pc->SummFreq += 2;
            }
        } else {
            p1=&(pc->oneState());           p1->Freq += (p1->Freq < 32);
        }
    }
    if (OrderFall == 0) {
        if ( !MakeRoot(2,NULL) )            goto RESTART_MODEL;
        MinContext=MedContext=fs.Successor; return;
    } else if (--OrderFall == 0) {
        Successor=fs.Successor;             SkipCount=1;
    } else if ((Successor = new PPM_CONTEXT()) == NULL)
            goto RESTART_MODEL;
    if ( !MaxContext->NumStats ) {
        MaxContext->oneState().Symbol = fs.Symbol;
        MaxContext->oneState().Successor = Successor;
    }
    s0=MinContext->SummFreq-(ns=MinContext->NumStats)-(fs.Freq-1);
    for (pc=MedContext;pc != MinContext;pc=pc->Suffix) {
        if ((ns1=pc->NumStats) != 1) {
            if ((ns1 & 1) == 0) {
                pc->Stats=(PPM_CONTEXT::STATE*) ExpandUnits(pc->Stats,ns1 >> 1);
                if ( !pc->Stats )           goto RESTART_MODEL;
            }
            pc->SummFreq += (2*ns1 < ns)+2*((4*ns1 <= ns) &
                    (pc->SummFreq <= 8*ns1));
        } else {
            p=(PPM_CONTEXT::STATE*) AllocUnitsRare(1);
            if ( !p )                       goto RESTART_MODEL;
            *p=pc->oneState();              pc->Stats=p;
            if (p->Freq < MAX_FREQ/4-1)     p->Freq += p->Freq;
            else                            p->Freq  = MAX_FREQ-4;
            pc->SummFreq=p->Freq+InitEsc+(ns > 3);
        }
        cf=2*fs.Freq*(pc->SummFreq+6);      sf=s0+pc->SummFreq;
        if (cf < 6*sf) {
            cf=1+(cf > sf)+(cf >= 4*sf);
            pc->SummFreq += 3;
        } else {
            cf=4+(cf >= 9*sf)+(cf >= 12*sf)+(cf >= 15*sf);
            pc->SummFreq += cf;
        }
        p=pc->Stats+ns1;                    p->Successor=Successor;
        p->Symbol = fs.Symbol;              p->Freq = cf;
        pc->NumStats=++ns1;
    }
    if ( fs.Successor ) {
        if (!fs.Successor->NumStats && !MakeRoot(SkipCount,p1))
                goto RESTART_MODEL;
        MinContext=FoundState->Successor;
    } else {
        FoundState->Successor=Successor;    OrderFall++;
    }
    MedContext=MinContext;                  MaxContext=Successor;
    return;
RESTART_MODEL:
    StartModel();
    EscCount=0;                             PrintCount=0xFF;
}
// Tabulated escapes for exponential symbol distribution
static const BYTE ExpEscape[16]={ 25,14, 9, 7, 5, 5, 4, 4, 4, 3, 3, 3, 2, 2, 2, 2 };
#define GET_MEAN(SUMM,SHIFT,ROUND) ((SUMM+(1 << (SHIFT-ROUND))) >> (SHIFT))
inline void PPM_CONTEXT::encodeBinSymbol(int symbol)
{
    STATE& rs=oneState();
    WORD& bs=BinSumm[rs.Freq-1][PrevSuccess+NS2BSIndx[Suffix->NumStats-1]];
    if (rs.Symbol == symbol) {
        FoundState=&rs;                     rs.Freq += (rs.Freq < 128);
        SubRange.LowCount=0;                SubRange.HighCount=bs;
        bs += INTERVAL-GET_MEAN(bs,PERIOD_BITS,2);
        PrevSuccess=1;
    } else {
        SubRange.LowCount=bs;               bs -= GET_MEAN(bs,PERIOD_BITS,2);
        SubRange.HighCount=BIN_SCALE;       InitEsc=ExpEscape[bs >> 10];
        NumMasked=1;                        CharMask[rs.Symbol]=EscCount;
        PrevSuccess=0;                      FoundState=NULL;
    }
}
inline void PPM_CONTEXT::decodeBinSymbol()
{
    STATE& rs=oneState();
    WORD& bs=BinSumm[rs.Freq-1][PrevSuccess+NS2BSIndx[Suffix->NumStats-1]];
    if (ariGetCurrentShiftCount(INT_BITS+PERIOD_BITS) < bs) {
        FoundState=&rs;                     rs.Freq += (rs.Freq < 128);
        SubRange.LowCount=0;                SubRange.HighCount=bs;
        bs += INTERVAL-GET_MEAN(bs,PERIOD_BITS,2);
        PrevSuccess=1;
    } else {
        SubRange.LowCount=bs;               bs -= GET_MEAN(bs,PERIOD_BITS,2);
        SubRange.HighCount=BIN_SCALE;       InitEsc=ExpEscape[bs >> 10];
        NumMasked=1;                        CharMask[rs.Symbol]=EscCount;
        PrevSuccess=0;                      FoundState=NULL;
    }
}
inline void PPM_CONTEXT::update1(STATE* p)
{
    (FoundState=p)->Freq += 4;              SummFreq += 4;
    if (p[0].Freq > p[-1].Freq) {
        SWAP(p[0],p[-1]);                   FoundState=--p;
        if (p->Freq > MAX_FREQ)             rescale();
    }
}
inline void PPM_CONTEXT::encodeSymbol1(int symbol)
{
    SubRange.scale=SummFreq;
    STATE* p=Stats;
    if (p->Symbol == symbol) {
        PrevSuccess=(2*(SubRange.HighCount=p->Freq) > SubRange.scale);
        (FoundState=p)->Freq += 4;          SummFreq += 4;
        if (p->Freq > MAX_FREQ)             rescale();
        SubRange.LowCount=0;                return;
    }
    PrevSuccess=0;
    int LoCnt=p->Freq, i=NumStats-1;
    while ((++p)->Symbol != symbol) {
        LoCnt += p->Freq;
        if (--i == 0) {
            SubRange.LowCount=LoCnt;        CharMask[p->Symbol]=EscCount;
            i=(NumMasked=NumStats)-1;       FoundState=NULL;
            do { CharMask[(--p)->Symbol]=EscCount; } while ( --i );
            SubRange.HighCount=SubRange.scale;
            return;
        }
    }
    SubRange.HighCount=(SubRange.LowCount=LoCnt)+p->Freq;
    update1(p);
}
inline void PPM_CONTEXT::decodeSymbol1()
{
    SubRange.scale=SummFreq;
    STATE* p=Stats;
    int i, count, HiCnt;
    if ((count=ariGetCurrentCount()) < (HiCnt=p->Freq)) {
        PrevSuccess=(2*(SubRange.HighCount=HiCnt) > SubRange.scale);
        (FoundState=p)->Freq=(HiCnt += 4);  SummFreq += 4;
        if (HiCnt > MAX_FREQ)               rescale();
        SubRange.LowCount=0;                return;
    }
    PrevSuccess=0;                          i=NumStats-1;
    while ((HiCnt += (++p)->Freq) <= count)
            if (--i == 0) {
                SubRange.LowCount=HiCnt;    CharMask[p->Symbol]=EscCount;
                i=(NumMasked=NumStats)-1;   FoundState=NULL;
                do { CharMask[(--p)->Symbol]=EscCount; } while ( --i );
                SubRange.HighCount=SubRange.scale;
                return;
            }
    SubRange.LowCount=(SubRange.HighCount=HiCnt)-p->Freq;
    update1(p);
}
inline void PPM_CONTEXT::update2(STATE* p)
{
    (FoundState=p)->Freq += 4;              SummFreq += 4;
    if (p->Freq > MAX_FREQ)                 rescale();
    EscCount++;
}
inline SEE2_CONTEXT* PPM_CONTEXT::makeEscFreq2(int Diff)
{
    SEE2_CONTEXT* psee2c;
    if (NumStats != 256) {
        psee2c=SEE2Cont[NS2Indx[Diff-1]]+(Diff < Suffix->NumStats-NumStats)+
                2*(SummFreq < 11*NumStats)+4*(NumMasked > Diff);
        SubRange.scale=psee2c->getMean();
    } else {
        psee2c=SEE2Cont[43];                SubRange.scale=1;
    }
    return psee2c;
}
inline void PPM_CONTEXT::encodeSymbol2(int symbol)
{
    int HiCnt, i=NumStats-NumMasked;
    SEE2_CONTEXT* psee2c=makeEscFreq2(i);
    STATE* p=Stats-1;                       HiCnt=0;
    do {
        do { p++; } while (CharMask[p->Symbol] == EscCount);
        HiCnt += p->Freq;
        if (p->Symbol == symbol)            goto SYMBOL_FOUND;
        CharMask[p->Symbol]=EscCount;
    } while ( --i );
    SubRange.HighCount=(SubRange.scale += (SubRange.LowCount=HiCnt));
    psee2c->Summ += SubRange.scale;         NumMasked = NumStats;
    return;
SYMBOL_FOUND:
    SubRange.LowCount = (SubRange.HighCount=HiCnt)-p->Freq;
    if ( --i ) {
        STATE* p1=p;
        do {
            do { p1++; } while (CharMask[p1->Symbol] == EscCount);
            HiCnt += p1->Freq;
        } while ( --i );
    }
    SubRange.scale += HiCnt;
    psee2c->update();                       update2(p);
}
inline void PPM_CONTEXT::decodeSymbol2()
{
    int count, HiCnt, i=NumStats-NumMasked;
    SEE2_CONTEXT* psee2c=makeEscFreq2(i);
    STATE* ps[256], ** pps=ps, * p=Stats-1;
    HiCnt=0;
    do {
        do { p++; } while (CharMask[p->Symbol] == EscCount);
        HiCnt += p->Freq;                   *pps++ = p;
    } while ( --i );
    SubRange.scale += HiCnt;                count=ariGetCurrentCount();
    p=*(pps=ps);
    if (count < HiCnt) {
        HiCnt=0;
        while ((HiCnt += p->Freq) <= count) p=*++pps;
        SubRange.LowCount = (SubRange.HighCount=HiCnt)-p->Freq;
        psee2c->update();                   update2(p);
    } else {
        SubRange.LowCount=HiCnt;            SubRange.HighCount=SubRange.scale;
        i=NumStats-NumMasked;               pps--;
        do { CharMask[(*++pps)->Symbol]=EscCount; } while ( --i );
        psee2c->Summ += SubRange.scale;     NumMasked = NumStats;
    }
}
inline void ClearMask(unsigned char* EncodedFile,unsigned char* DecodedFile,clock_t StartClock)
{
    EscCount=1;                             memset(CharMask,0,sizeof(CharMask));
    if (++PrintCount == 0)
        PrintInfo(DecodedFile,EncodedFile,((clock()-StartClock) << 10)/int(CLK_TCK));
}
void _STDCALL EncodeFile(unsigned char* EncodedFile,unsigned char* DecodedFile,int MaxOrder)
{
    ariInitEncoder(EncodedFile);            ::MaxOrder=MaxOrder;
    clock_t StartClock=StartModel();
    for ( ; ; ) {
        int c = xgetc(DecodedFile);
        if (MinContext->NumStats != 1) {
            MinContext->encodeSymbol1(c);
            ariEncodeSymbol();
        } else {
            MinContext->encodeBinSymbol(c);
            ariShiftEncodeSymbol(INT_BITS+PERIOD_BITS);
        }
        while ( !FoundState ) {
            ARI_ENC_NORMALIZE(EncodedFile);
            do {
                OrderFall++;                MinContext=MinContext->Suffix;
                if ( !MinContext )          goto STOP_ENCODING;
            } while (MinContext->NumStats == NumMasked);
            MinContext->encodeSymbol2(c);   ariEncodeSymbol();
        }
        if (!OrderFall && FoundState->Successor->NumStats)
                MinContext=MedContext=FoundState->Successor;
        else {
            UpdateModel();
            if (EscCount == 0)
                    ClearMask(EncodedFile,DecodedFile,StartClock);
        }
        ARI_ENC_NORMALIZE(EncodedFile);
    }
STOP_ENCODING:
    StopModel();
    ARI_FLUSH_ENCODER(EncodedFile);
    PrintInfo(DecodedFile,EncodedFile,((clock()-StartClock) << 10)/int(CLK_TCK));
}
void _STDCALL DecodeFile(unsigned char* DecodedFile,unsigned char* EncodedFile,int MaxOrder)
{
    ARI_INIT_DECODER(EncodedFile);          ::MaxOrder=MaxOrder;
    clock_t StartClock=StartModel();
    for ( ; ; ) {
        if (MinContext->NumStats != 1)      MinContext->decodeSymbol1();
        else                                MinContext->decodeBinSymbol();
        ariRemoveSubrange();
        while ( !FoundState ) {
            ARI_DEC_NORMALIZE(EncodedFile);
            do {
                OrderFall++;                MinContext=MinContext->Suffix;
                if ( !MinContext )          goto STOP_DECODING;
            } while (MinContext->NumStats == NumMasked);
            MinContext->decodeSymbol2();    ariRemoveSubrange();
        }
        xputc(FoundState->Symbol,DecodedFile);
        if (!OrderFall && FoundState->Successor->NumStats)
                MinContext=MedContext=FoundState->Successor;
        else {
            UpdateModel();
            if (EscCount == 0)
                    ClearMask(EncodedFile,DecodedFile,StartClock);
        }
        ARI_DEC_NORMALIZE(EncodedFile);
    }
STOP_DECODING:
    StopModel();
    PrintInfo(DecodedFile,EncodedFile,((clock()-StartClock) << 10)/int(CLK_TCK));
}

/****************************************************************************
 *  This file is part of PPMd project                                       *
 *  Written and distributed to public domain by Dmitry Shkarin 1997,        *
 *  1999-2000                                                               *
 *  Contents: memory allocation routines                                    *
 ****************************************************************************/
#include <stdlib.h>
#include <string.h>
//#include "PPMd.h"
//#include "SubAlloc.h"

const UINT N1=4, N2=4, N3=4, N4=(128+3-1*N1-2*N2-3*N3)/4;
const UINT UNIT_SIZE=12, N_INDEXES=N1+N2+N3+N4;

static long SubAllocatorSize=0;
static BYTE Indx2Units[N_INDEXES], Units2Indx[128];
static BYTE* HeapStart, * LoUnit, * HiUnit, * LastBreath;
static struct NODE { NODE* next; } FreeList[N_INDEXES];

inline void InsertNode(void* p,int indx) {
    ((NODE*) p)->next=FreeList[indx].next;  FreeList[indx].next=(NODE*) p;
}
inline void* RemoveNode(int indx) {
    NODE* RetVal=FreeList[indx].next;       FreeList[indx].next=RetVal->next;
    return RetVal;
}
inline UINT I2B(int indx) { return UNIT_SIZE*Indx2Units[indx]; }
inline void SplitBlock(void* pv,int OldIndx,int NewIndx)
{
    int i, UDiff=Indx2Units[OldIndx]-Indx2Units[NewIndx];
    BYTE* p=((BYTE*) pv)+I2B(NewIndx);
    if (Indx2Units[i=Units2Indx[UDiff-1]] != UDiff) {
        InsertNode(p,--i);                  p += I2B(i);
        UDiff -= Indx2Units[i];
    }
    InsertNode(p,Units2Indx[UDiff-1]);
}

inline DWORD _STDCALL GetUsedMemory()
{
    DWORD i, k, RetVal=SubAllocatorSize-(HiUnit-LoUnit);
    for (k=i=0;i < N_INDEXES;i++, k=0) {
        for (NODE* pn=FreeList+i;(pn=pn->next) != NULL;k++)
                ;
        RetVal -= UNIT_SIZE*Indx2Units[i]*k;
    }
    if ( LastBreath )                       RetVal -= 128*128*UNIT_SIZE;
    return (RetVal >> 2);
}
inline void _STDCALL StopSubAllocator() {
    if ( SubAllocatorSize ) {
        SubAllocatorSize=0;                 delete[] HeapStart;
    }
}
inline BOOL _STDCALL StartSubAllocator(int SASize)
{
    DWORD t=SASize << 20;
    if (SubAllocatorSize == t)              return TRUE;
    StopSubAllocator();
    if ((HeapStart=new BYTE[t]) == NULL)    return FALSE;
    SubAllocatorSize=t;                     return TRUE;
}
inline void InitSubAllocator()
{
    int i, k;
    memset(FreeList,0,sizeof(FreeList));
    HiUnit=(LoUnit=HeapStart)+UNIT_SIZE*(SubAllocatorSize/UNIT_SIZE);
    LastBreath=LoUnit;                      LoUnit += 128*128*UNIT_SIZE;
    for (i=0,k=1;i < N1     ;i++,k += 1)    Indx2Units[i]=k;
    for (k++;i < N1+N2      ;i++,k += 2)    Indx2Units[i]=k;
    for (k++;i < N1+N2+N3   ;i++,k += 3)    Indx2Units[i]=k;
    for (k++;i < N1+N2+N3+N4;i++,k += 4)    Indx2Units[i]=k;
    for (k=i=0;k < 128;k++) {
        i += (Indx2Units[i] < k+1);         Units2Indx[k]=i;
    }
}
inline void* _FASTCALL AllocUnitsRare(int NU)
{
    int i, indx=Units2Indx[NU-1];
    if ( FreeList[indx].next )              return RemoveNode(indx);
    void* RetVal=LoUnit;                    LoUnit += I2B(indx);
    if (LoUnit <= HiUnit)                   return RetVal;
    if ( LastBreath ) {
        for (i=0;i < 128;i++) {
            InsertNode(LastBreath,N_INDEXES-1);
            LastBreath += 128*UNIT_SIZE;
        }
        LastBreath=NULL;
    }
    LoUnit -= I2B(indx);                    i=indx;
    do {
        if (++i == N_INDEXES)               return NULL;
    } while ( !FreeList[i].next );
    SplitBlock(RetVal=RemoveNode(i),i,indx);
    return RetVal;
}
inline void* AllocContext()
{
    if (HiUnit != LoUnit)                   return (HiUnit -= UNIT_SIZE);
    return AllocUnitsRare(1);
}
inline void* _FASTCALL ExpandUnits(void* OldPtr,int OldNU)
{
    int i0=Units2Indx[OldNU-1], i1=Units2Indx[OldNU-1+1];
    if (i0 == i1)                           return OldPtr;
    void* ptr=AllocUnitsRare(OldNU+1);
    if ( ptr ) {
        memcpy(ptr,OldPtr,I2B(i0));         InsertNode(OldPtr,i0);
    }
    return ptr;
}
inline void* _FASTCALL ShrinkUnits(void* OldPtr,int OldNU,int NewNU)
{
    int i0=Units2Indx[OldNU-1], i1=Units2Indx[NewNU-1];
    if (i0 == i1)                           return OldPtr;
    if ( FreeList[i1].next ) {
        void* ptr=RemoveNode(i1);           memcpy(ptr,OldPtr,I2B(i1));
        InsertNode(OldPtr,i0);              return ptr;
    } else {
        SplitBlock(OldPtr,i0,i1);           return OldPtr;
    }
}
inline void _FASTCALL FreeUnits(void* ptr,int OldNU)
{
    InsertNode(ptr,Units2Indx[OldNU-1]);
}


extern "C" int unppmdg_raw(unsigned char *in, int insz, unsigned char *out, int outsz, int SaSize, int MaxOrder) {
    EncodedFile  = in;
    EncodedFilel = in + insz;
    DecodedFile  = out;
    DecodedFilel = out + outsz;

    if(!SaSize)   SaSize   = 10;
    if(!MaxOrder) MaxOrder = 4;

    ARI_INIT_DECODER(EncodedFile);          ::MaxOrder=MaxOrder;
    clock_t StartClock=StartModel();
    for ( ; ; ) {
        if (MinContext->NumStats != 1)      MinContext->decodeSymbol1();
        else                                MinContext->decodeBinSymbol();
        ariRemoveSubrange();
        while ( !FoundState ) {
            ARI_DEC_NORMALIZE(EncodedFile);
            do {
                OrderFall++;                MinContext=MinContext->Suffix;
                if ( !MinContext )          goto STOP_DECODING;
            } while (MinContext->NumStats == NumMasked);
            MinContext->decodeSymbol2();    ariRemoveSubrange();
        }
        xputc(FoundState->Symbol,DecodedFile);
        if (!OrderFall && FoundState->Successor->NumStats)
                MinContext=MedContext=FoundState->Successor;
        else {
            UpdateModel();
            if (EscCount == 0)
                    ClearMask(EncodedFile,DecodedFile,StartClock);
        }
        ARI_DEC_NORMALIZE(EncodedFile);
    }
STOP_DECODING:
    StopModel();
    PrintInfo(DecodedFile,EncodedFile,((clock()-StartClock) << 10)/int(CLK_TCK));
    return(DecodedFile - out);
}



extern "C" int unppmdg(unsigned char *in, int insz, unsigned char *out, int outsz) {
    if(insz < 2) return(-1);
    int         parameters = in[0] | (in[1] << 8);
    int         MaxOrder = (parameters & 0x0f) + 1;
    int         SaSize   = ((parameters >> 4) & 0xFF) + 1;
    return(unppmdg_raw(in + 2, insz - 2, out, outsz, SaSize, MaxOrder));
}

