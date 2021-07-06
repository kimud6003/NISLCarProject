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
    int AUTH_P_D=-1,PKi_D=-1,Xi_D=-1,PKj_D=-1,QS_D=-1;
    miracl *mip=mirsys(1000,0);
    big Xi,CPID,AUTH,AUTH_P,AUTH_S,T1,sks,tmpPoint,checkPoint,PKj,SID;
    big PID,PID_,qs,Qs,T2,PKi,PKs,SM1;
    epoint *g,*EXi,*EPKj, *EPKi,*tmpResult; 
    big a,b,p,gx,gy;
    big ski,xi;
    epoint *ESKi; 
    irand(seed);
    tmpPoint=mirvar(0);
    AUTH_P=mirvar(0);
    AUTH_S=mirvar(0);
    CPID=mirvar(0);
    PID=mirvar(0);
    PID_=mirvar(0);
    PKi=mirvar(0);
    PKj=mirvar(0);
    PKs=mirvar(0);
    sks=mirvar(0);
    SM1=mirvar(0);
    AUTH = mirvar(0);
    checkPoint = mirvar(0);
    SID=mirvar(0);
    Xi = mirvar(0);
    qs = mirvar(0);
    Qs = mirvar(0);
    T1 = mirvar(0);
    T2 = mirvar(0);

    ski = mirvar(0);
    xi = mirvar(0);
    //ECC 설정 
    a=mirvar(0);
    b=mirvar(0);
    p=mirvar(0);
    gx=mirvar(0);
    gy=mirvar(0);
    mip->IOBASE=16;
    // argv 값 넣어주기
    cinstr(PID,argv[1]);
    cinstr(Xi,argv[2]);
    Xi_D=atoi(argv[3]);
    cinstr(CPID,argv[4]);
    cinstr(AUTH,argv[5]);
    cinstr(PKj,"B72B86B1B778E36906E87254C8B97EBC31F83211250567C8");
    PKj_D=0;
    cinstr(T1,argv[6]);
    cinstr(PKi,argv[8]);
    PKi_D=atoi(argv[9]);
    cinstr(sks,"5A1ADFD946AD2ECB15F00518D7861FF861A4D88E");
    cinstr(SID,"AAAA");

    // ECC 설정 
    convert(-3,a);
    cinstr(b,ecb);
    cinstr(gx,egx);
    cinstr(gy,egy);
    cinstr(p,ecp);

    ecurve_init(a,b,p,MR_BEST);
    g=epoint_init();
    tmpResult=epoint_init();
    EXi=epoint_init();
    EPKi=epoint_init();
    EPKj=epoint_init();
    ESKi=epoint_init();
    epoint_set(Xi,Xi,Xi_D,EXi); //ECC 설정완료
    epoint_set(PKi,PKi,PKi_D,EPKi); //ECC 설정완료
    epoint_set(PKj,PKj,PKj_D,EPKj); //ECC 설정완료
    epoint_set(gx,gy,0,g); //ECC 설정완료

    ecurve_mult(sks,EXi,tmpResult);
    epoint_get(tmpResult,tmpPoint,tmpPoint);
    PID_ = XOR(CPID,hashing1(tmpPoint));
    if(mr_compare(PID_,PID)!=0){
        printf("PID missmatch\n");
        return 0;
    }

    ecurve_mult(AUTH,g,tmpResult);
    epoint_get(tmpResult,AUTH_P,AUTH_P);

    checkPoint = hashing1(concat(concat(concat(PID_,Xi),hashing2(argv[7])),T1));
    ecurve_mult(checkPoint,EPKi,tmpResult);
    ecurve_add(EXi,tmpResult);
    epoint_get(tmpResult,tmpPoint,tmpPoint);
    
    if(mr_compare(AUTH_P,tmpPoint)!=0){
        printf("verified fail\n");
        return 0;
    }

    bigdig(40,16,qs);
    // printf("qs : ");

    ecurve_mult(qs,g,tmpResult);
    QS_D=epoint_get(tmpResult,Qs,Qs);

    ecurve_mult(qs,EPKj,tmpResult);
    epoint_get(tmpResult,tmpPoint,tmpPoint);
    SM1 = XOR(Xi,hashing1(tmpPoint));
    // printf("temp Point :");
    // cotnum(tmpPoint,stdout);

    time_t T;
    time(&T);
    convert(T,T2);

    tmpPoint = hashing1(concat(Xi,concat(SID,concat(Qs,T2))));
    multiply(tmpPoint,sks,tmpPoint);
    add(qs,tmpPoint,AUTH_S);


    // printf("QS : ");
    cotnum(Qs,stdout);
    // printf("QS_D : %d\n",QS_D);
    printf("%d\n",QS_D);

    
    // printf("SID : ");
    cotnum(SID,stdout);

    // printf("AUTH_S : ");
    cotnum(AUTH_S,stdout);

    // printf("T2 : ");
    cotnum(T2,stdout);

    // printf("SM1 : ");
    cotnum(SM1,stdout);

    cotnum(qs,stdout);
    return 0;
}

