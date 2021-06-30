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
    miracl *mip=mirsys(1000,0);
    int Xi_D=-1;
    big sks;
    big Bi,Ci,Di,Ei,HPID,PKs,ski,ID,PW,tmpPoint;
    big xi,CPID,PID,HPW,ai,Ei_,Xi,zi,AUTH,T1;
    epoint *g,*EPKs,*tmpResult; 
    big a,b,p,y,gx,gy;
    irand(seed);
    sks=mirvar(0);
    xi=mirvar(0);
    CPID=mirvar(0);
    HPID=mirvar(0);
    PID=mirvar(0);
    ID=mirvar(0);
    PW=mirvar(0);
    HPW=mirvar(0);
    PKs=mirvar(0);
    AUTH = mirvar(0);
    tmpPoint=mirvar(0);
    Xi = mirvar(0);
    ai = mirvar(0);
    ski = mirvar(0);
    Bi = mirvar(0);
    Ci = mirvar(0);
    Di = mirvar(0);
    Ei = mirvar(0);
    Ei_ = mirvar(0);
    T1 = mirvar(0);

    //ECC 설정 
    a=mirvar(0);
    b=mirvar(0);
    p=mirvar(0);
    gx=mirvar(0);
    gy=mirvar(0);
    y=mirvar(0);
    zi=mirvar(0);
    mip->IOBASE=16;
    // argv 값 넣어주기
    cinstr(ski, argv[1]);
    bytes_to_big(strlen(argv[2]),argv[2],ID);
    bytes_to_big(strlen(argv[3]),argv[3],PW);
    cinstr(Bi,argv[4]);
    cinstr(Ci,argv[5]);
    cinstr(Di,argv[6]);
    cinstr(Ei,argv[7]);
    cinstr(HPID,argv[8]);
    cinstr(PKs,"999A48ADD10173A41BCCF88D407626D57867F164D84AB712");
    cinstr(sks,"5A1ADFD946AD2ECB15F00518D7861FF861A4D88E");
    // char requst[] = "3430주 10";


    //ECC 설정 
    convert(-3,a);
    cinstr(b,ecb);
    cinstr(gx,egx);
    cinstr(gy,egy);
    cinstr(p,ecp);

    
    ecurve_init(a,b,p,MR_BEST);
    g=epoint_init();
    tmpResult=epoint_init();
    EPKs=epoint_init();
    epoint_set(PKs,PKs,0,EPKs); //ECC 설정완료
    epoint_set(gx,gy,0,g); //ECC 설정완료

    ai = XOR(hashing1(concat(ID,PW)),Bi);
    HPW = hashing1(concat(PW,ai));
    ski = XOR(hashing1(concat(hashing1(concat(ID,ai)),HPW)),Ci);
    zi = XOR(hashing1(concat(ski,ai)),Di);
    Ei_ = hashing1(concat(concat(ski,zi),ai));

    if(mr_compare(Ei,Ei_)!=0){
        printf("ID miss match");
        return 0;
    }
    time_t T;
    time(&T);
    convert(T,T1);

    bigdig(40,16,xi);

    ecurve_mult(xi,g,tmpResult);
    Xi_D=epoint_get(tmpResult,Xi,Xi);
    PID = XOR(HPID,HPW);
    // printf("PID : ");
    // cotnum(PID,stdout);
    ecurve_mult(xi,EPKs,tmpResult);
    epoint_get(tmpResult,tmpPoint,tmpPoint);
    CPID = XOR(PID,hashing1(tmpPoint));

    AUTH = hashing1(concat(concat(concat(PID,Xi),hashing2(argv[9])),T1));
    multiply(AUTH,ski,AUTH);
    add(xi,AUTH,AUTH);

    // printf("xi:");
    // cotnum(xi,stdout);

    // printf("Xi : ");
    cotnum(Xi,stdout);
    printf("%d\n",Xi_D);

    // printf("CPID : ");
    cotnum(CPID,stdout);

    // printf("AUTH : ");
    cotnum(AUTH,stdout);

    // printf("T1 : ");
    cotnum(T1,stdout);

    printf("%s",argv[9]);

    return 0;
}

