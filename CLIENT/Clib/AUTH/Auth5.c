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
    big H1CODE,CM5_,SM2,SM3,tmpPoint,SID;
    big qs,CM1,CM2,Yj,T3,T4,sks,Xi,PKc;
    big xi,CODE,CM2_,TID_,PKs,SM3_;
    epoint *g, *tmpResult, *EYj, *EPKs; 
    big a,b,p,gx,gy;




    irand(seed);

    SID = mirvar(0);
    Xi = mirvar(0);
    sks = mirvar(0);
    PKc=mirvar(0);

    TID_=mirvar(0);
    qs=mirvar(0);
    H1CODE = mirvar(0);
    Yj=mirvar(0);
    T3 = mirvar(0);
    T4 = mirvar(0);
    CM1 = mirvar(0);
    CM2 = mirvar(0);
    SM2 = mirvar(0);
    SM3 = mirvar(0);
    
    //TODO 품 
    tmpPoint =mirvar(0);
    xi = mirvar(0);
    PKs = mirvar(0);
    CODE = mirvar(0);
    CM2_ = mirvar(0);
    SM3_ = mirvar(0);


    // ECC 설정
    a=mirvar(0);
    b=mirvar(0);
    p=mirvar(0);
    gx=mirvar(0);
    gy=mirvar(0);


    mip->IOBASE=16;
    // argv 값 넣어주기
    cinstr(PKs,"999A48ADD10173A41BCCF88D407626D57867F164D84AB712");
    cinstr(PKc,"B9E7FAB9D8ACF0E8CE7500678C679112B5AA15DBB1BC1A4F");
    cinstr(SID,"AAAA");

    cinstr(xi,argv[1]);
    cinstr(Yj,argv[2]);
    int Yj_D = atoi(argv[3]);
    cinstr(CM1,argv[4]);
    cinstr(CM2,argv[5]);
    cinstr(SM2,argv[6]);
    cinstr(SM3,argv[7]);
    cinstr(T3,argv[8]);
    cinstr(T4,argv[9]);


    // ECC 설정 
    convert(-3,a);
    cinstr(b,ecb);
    cinstr(gx,egx);
    cinstr(gy,egy);
    cinstr(p,ecp);

    ecurve_init(a,b,p,MR_BEST);
    g = epoint_init();
    tmpResult = epoint_init();
    EYj = epoint_init();
    EPKs = epoint_init();
    epoint_set(gx,gy,0,g); // ECC 설정 완료
    epoint_set(Yj,Yj,Yj_D,EYj); // ECC 설정 완료
    epoint_set(PKs,PKs,0,EPKs); // ECC 설정 완료

//TODO 시작 
    ecurve_mult(xi,EYj,tmpResult);
    epoint_get(tmpResult,tmpPoint,tmpPoint);
    CODE = XOR(CM1,hashing1(tmpPoint));
    CM2_ = hashing1(concat(concat(hashing1(CODE),tmpPoint),T3));


    if(mr_compare(CM2,CM2_)!=0){
        printf("CM verified fail2\n");
        return 0;
    }

    ecurve_mult(xi,EPKs,tmpResult);
    epoint_get(tmpResult,tmpPoint,tmpPoint);

    TID_ = XOR(SM2,hashing1(tmpPoint));
    SM3_ = hashing1(concat(concat(concat(concat(hashing1(CODE),TID_),Yj),T4),tmpPoint));
    if(mr_compare(SM3,SM3_)!=0){
        printf("SM verified fail\n");
        return 0;
    }

    cotnum(TID_,stdout);
    cotnum(CODE,stdout);
   


    return 0;
}

