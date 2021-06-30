#include "miracl.h"
#include "setup.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <time.h>

char *ecp="FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFFFFFFFFFFFF";

char *ecb="64210519E59C80E70FA7E9AB72243049FEB8DEECC146B9B1";
char *ecx="3B5EFCFF203B1934E7CD717CD186AB00F79058E8831BDC73";

char *egx="188DA80EB03090F67CBF20EB43A18800F4FF0AFD82FF1012";
char *egy="07192B95FFC8DA78631011ED6B24CDD573F977A11E794811";

int main(int argc, char const *argv[]){
    // if(argc!=2){
    //     perror("argument is not found\n");
    //     return 0;
    // }
    srand(time(NULL));
    long seed = rand()%100;
    miracl *mip=mirsys(100,0);

    big H1CODE,CM5_,SM2,SM3,SM4,TID,tmpPoint,SID;
    big qs,CM1,CM2,CM3,CM4,CM5,CM6,Yj,T3,T4,sks,Xi,PKc;
    epoint *g, *tmpResult; 
    big a,b,p,gx,gy;


    irand(seed);

    SID = mirvar(0);
    Xi = mirvar(0);
    sks = mirvar(0);
    PKc=mirvar(0);

    TID=mirvar(0);
    qs=mirvar(0);
    H1CODE = mirvar(0);
    Yj=mirvar(0);
    T3 = mirvar(0);
    T4 = mirvar(0);
    CM1 = mirvar(0);
    CM2 = mirvar(0);
    CM3 = mirvar(0);
    CM4 = mirvar(0);
    CM5 = mirvar(0);
    CM6 = mirvar(0);
    SM2 = mirvar(0);
    SM3 = mirvar(0);


    // ECC 설정
    a=mirvar(0);
    b=mirvar(0);
    p=mirvar(0);
    gx=mirvar(0);
    gy=mirvar(0);


    mip->IOBASE=16;
    // argv 값 넣어주기


    cinstr(sks,"5A1ADFD946AD2ECB15F00518D7861FF861A4D88E");
    cinstr(PKc,"B9E7FAB9D8ACF0E8CE7500678C679112B5AA15DBB1BC1A4F");

    cinstr(Xi,argv[1]);
    cinstr(qs,argv[2]);
    cinstr(SID,"AAAA");


    cinstr(Yj,argv[3]);
    cinstr(T3,argv[4]);
    cinstr(CM1,argv[5]);
    cinstr(CM2,argv[6]);
    cinstr(CM3,argv[7]);
    cinstr(CM4,argv[8]);
    cinstr(CM5,argv[9]);
    cinstr(CM6,argv[10]);

    // ECC 설정 
    convert(-3,a);
    cinstr(b,ecb);
    cinstr(gx,egx);
    cinstr(gy,egy);
    cinstr(p,ecp);

    ecurve_init(a,b,p,MR_BEST);
    g = epoint_init();
    tmpResult = epoint_init();
    epoint_set(gx,gy,0,g); // ECC 설정 완료

//TODO 시작 
    multiply(qs,Yj,tmpPoint);
    H1CODE = XOR(CM6,hashing1(tmpPoint));
    CM5_ = hashing1(concat(concat(concat(H1CODE,SID),tmpPoint),T3));

    if(mr_compare(CM5,CM5)!=0){
        printf("verified fail\n");
        return 0;
    }
   
    time_t T;
    time(&T);
    convert(T,T4);

    multiply(Xi,sks,tmpPoint);
    SM2 = XOR(TID,hashing1(tmpPoint));
    SM3 = hashing1(concat(concat(concat(concat(H1CODE,TID),Yj),T4),tmpPoint));
    multiply(PKc,sks,tmpPoint);
    SM4 = hashing1(concat(concat(concat(H1CODE,Yj),T4),tmpPoint));
    
    cotnum(CM1,stdout);

    cotnum(CM2,stdout);

    cotnum(SM2,stdout);
    
    cotnum(SM3,stdout);
    
    cotnum(T3,stdout);

    cotnum(T4,stdout);

    cotnum(Yj,stdout);

    return 0;
}

