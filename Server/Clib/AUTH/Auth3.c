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
    int QS_D=-1,PKs_D=-1,Yj_D=-1;
    big Qs,SID,AUTH_S,T2,SM1,skj,PKs,CODE,yj,Yj;
    big Xi_,tmpPoint,AUTH_S_P,checkPoint,T3,PKc;
    big CM1,CM2,CM3,CM4,CM5,CM6;
    epoint *g, *EQs, *tmpResult, *EPKs; 
    big a,b,p,gx,gy;

    irand(seed);

    Qs = mirvar(0);
    SID = mirvar(0);
    AUTH_S = mirvar(0);
    AUTH_S_P = mirvar(0);
    T2 = mirvar(0);
    T3 = mirvar(0);
    SM1 = mirvar(0);
    Xi_ = mirvar(0);
    PKs = mirvar(0);
    skj = mirvar(0);
    PKs = mirvar(0);
    checkPoint = mirvar(0);
    tmpPoint = mirvar(0);
    CODE=mirvar(0);
    yj=mirvar(0);
    Yj=mirvar(0);
    PKc=mirvar(0);

    CM1 = mirvar(0);
    CM2 = mirvar(0);
    CM3 = mirvar(0);
    CM4 = mirvar(0);
    CM5 = mirvar(0);
    CM6 = mirvar(0);


    // ECC 설정
    a=mirvar(0);
    b=mirvar(0);
    p=mirvar(0);
    gx=mirvar(0);
    gy=mirvar(0);


    mip->IOBASE=16;
    // argv 값 넣어주기
    cinstr(skj,"A8522064E8B58B1846DECE8EB4C08F756583E454");
    cinstr(Qs,"59203ACB0FE0327B8FA9D369B7DCA6621672D0A0F62C5716");
    QS_D= 0;
    cinstr(SID,"AAAA");
    cinstr(AUTH_S,"3998C72B78D4860EEE80A147C647C47C37C12552363E0651757E129775AD20B8A590BE79D901BFA8");
    cinstr(T2,"60D9DFD4");
    cinstr(SM1,"A7977E3A231EB6EDFCD50466250012A925DAF7FE724E5C88");
    cinstr(PKs,"999A48ADD10173A41BCCF88D407626D57867F164D84AB712");
    cinstr(PKc,"B9E7FAB9D8ACF0E8CE7500678C679112B5AA15DBB1BC1A4F");
    PKs_D=1;


    // ECC 설정 
    convert(-3,a);
    cinstr(b,ecb);
    cinstr(gx,egx);
    cinstr(gy,egy);
    cinstr(p,ecp);

    ecurve_init(a,b,p,MR_BEST);
    g = epoint_init();
    EQs = epoint_init();
    EPKs = epoint_init();
    tmpResult = epoint_init();
    epoint_set(gx,gy,0,g); // ECC 설정 완료
    epoint_set(Qs,Qs,QS_D,EQs); // ECC 설정 완료
    epoint_set(PKs,PKs,PKs_D,EPKs); //ECC 설정완료

    ecurve_mult(skj,EQs,tmpResult);
    epoint_get(tmpResult,tmpPoint,tmpPoint);
    Xi_ = XOR(SM1,hashing1(tmpPoint));

    ecurve_mult(AUTH_S,g,tmpResult);
    epoint_get(tmpResult,AUTH_S,AUTH_S);
    
    checkPoint = hashing1(concat(Xi_,concat(SID,concat(Qs,T2))));
    ecurve_mult(checkPoint,EPKs,tmpResult);
    ecurve_add(EQs,tmpResult);
    epoint_get(tmpResult,tmpPoint,tmpPoint);

    if(mr_compare(AUTH_S,tmpPoint)!=0){
        printf("PID missmatch\n");
        return 0;
    }

    bigdig(40,16,CODE);
    bigdig(40,16,yj);

    ecurve_mult(yj,g,tmpResult);
    Yj_D=epoint_get(tmpResult,Yj,Yj);
    
    time_t T;
    time(&T);
    convert(T,T3);

    // ecurve_mult(yj,Xi_,tmpResult);
    multiply(yj,Xi_,tmpPoint);
    CM1 = XOR(CODE,hashing1(tmpPoint));
    CM2 = hashing1(concat(concat(hashing1(CODE),tmpPoint),T3));
    multiply(PKc,yj,tmpPoint);
    CM3=XOR(CODE,hashing1(tmpPoint));
    CM4 = hashing1(concat(concat(hashing1(CODE),tmpPoint),T3));
    multiply(Qs,yj,tmpPoint);
    CM5 = hashing1(concat(concat(concat(hashing1(CODE),SID),tmpPoint),T3));
    CM6 = XOR(hashing1(CODE),hashing1(tmpPoint));

    printf("Yj : ");
    cotnum(Yj,stdout);

    printf("Yj_D : %d\n",Yj_D);

    printf("CM1 : ");
    cotnum(CM1,stdout);

    printf("CM2 : ");
    cotnum(CM2,stdout);

    printf("CM3 : ");
    cotnum(CM3,stdout);

    printf("CM4 : ");
    cotnum(CM4,stdout);

    printf("CM5 : ");
    cotnum(CM5,stdout);

    printf("CM6 : ");
    cotnum(CM6,stdout);

    printf("T3 : ");
    cotnum(T3,stdout);

    return 0;
}

