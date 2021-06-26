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
    miracl *mip=mirsys(10000,0);
    big ski;
    big Xi,CPID,AUTH,T,SKs,tmpPoint,tmpPoint2,checkPoint,PKj,SID;
    big PKi,Bi,Ci,Di,Ei,HPID,PKs,ID,PW,SM1;
    big xi,PID,PID_,HPW,qs,Qs,Ei_,zi;
    epoint *g,*EXi,*EPKj, *EPKi,*ESKs,*tmpResult ; 
    big a,b,p,y,gx,gy;
    irand(seed);
    ski = mirvar(0);
    xi=mirvar(0);
    tmpPoint=mirvar(0);
    tmpPoint2=mirvar(0);
    CPID=mirvar(0);
    HPID=mirvar(0);
    PID=mirvar(0);
    PID_=mirvar(0);
    ID=mirvar(0);
    PW=mirvar(0);
    HPW=mirvar(0);
    PKi=mirvar(0);
    PKj=mirvar(0);
    PKs=mirvar(0);
    SKs=mirvar(0);
    SM1=mirvar(0);
    AUTH = mirvar(0);
    checkPoint = mirvar(0);
    SID=mirvar(0);
    Xi = mirvar(0);
    qs = mirvar(0);
    Qs = mirvar(0);
    Bi = mirvar(0);
    Ci = mirvar(0);
    Di = mirvar(0);
    Ei = mirvar(0);
    Ei_ = mirvar(0);
    T = mirvar(0);

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
    cinstr(PID,"686C2E403939827CCA8229EAD437D6F5D126F068");
    cinstr(Xi,"2");
    cinstr(CPID,"54128F722B0DFFE399A3731374D2BD936E8E75F3");
    cinstr(AUTH,"4");
    cinstr(PKi,"BD1BD462D74564636BDCF08EC6ED56BD350E0E903496772F");
    cinstr(SKs,"5A1ADFD946AD2ECB15F00518D7861FF861A4D88E");
    cinstr(SID,"AAAA");
    cinstr(T,"60D6DF21");
    cinstr(ski,"D4C71685B73F4ECDB6665088F589CDCD9210365E");
    cinstr(xi,"1");

    char requst[] = "3430주 10";

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
    ESKs=epoint_init();
    epoint_set(Xi,Xi,0,EXi); //ECC 설정완료
    epoint_set(PKi,PKi,0,EPKi); //ECC 설정완료
    epoint_set(PKj,PKj,0,EPKj); //ECC 설정완료
    epoint_set(gx,gy,0,g); //ECC 설정완료
    epoint_set(SKs,SKs,0,ESKs); //ECC 설정완료

    ecurve_mult(SKs,EXi,tmpResult);
    epoint_get(tmpResult,tmpPoint,tmpPoint);
    PID_ = XOR(CPID,hashing1(tmpPoint));


    printf("TEST - AUTH : ");
    cotnum(AUTH,stdout);
    ecurve_mult(AUTH,g,tmpResult);
    epoint_get(tmpResult,tmpPoint,tmpPoint); // tmpPoint == Auth X P
    
    printf("4 * P : ");
    cotnum(tmpPoint,stdout);

    ecurve_mult(Xi,g,tmpResult);
    epoint_get(tmpResult,tmpPoint,tmpPoint); // tmpPoint == Auth X P

    printf("2 * P : ");
    cotnum(tmpPoint,stdout);
    ecurve_add(tmpResult,tmpResult);
    epoint_get(tmpResult,tmpPoint,tmpPoint); // tmpPoint == Auth X P

    printf("4 * P : ");
    cotnum(tmpPoint,stdout);



    ecurve_mult(checkPoint,EPKi,tmpResult);
    epoint_get(tmpResult,checkPoint,checkPoint); // tmpPoint == Auth X P
    printf("AUTH * p  : ");
    cotnum(checkPoint,stdout);

    ecurve_mult(checkPoint,EPKi,tmpResult);
    epoint_get(tmpResult,checkPoint,checkPoint);
    cotnum(checkPoint,stdout);

    // ecurve_mult(checkPoint,EPKi,tmpResult);
    // epoint_get(tmpResult,checkPoint,checkPoint);
    add(Xi,checkPoint,checkPoint);
    // printf("AUTH * P : ");
    cotnum(checkPoint,stdout);
    
    if(mr_compare(tmpPoint,checkPoint)!=0){
        printf("verified fail\n");
        return 0;
    }

    bigdig(40,16,qs);
    ecurve_mult(qs,g,tmpResult);
    epoint_get(tmpResult,Qs,Qs); 

    ecurve_mult(qs,EPKj,tmpResult);
    epoint_get(tmpResult,tmpPoint,tmpPoint); 
    SM1 = XOR(Xi,hashing1(tmpPoint));

    checkPoint = hashing1(concat(concat(concat(Xi,SID),hashing2(requst)),T));
    ecurve_mult(checkPoint,ESKs,tmpResult);
    epoint_get(tmpResult,checkPoint,checkPoint);
    add(qs,checkPoint,checkPoint);

    return 0;
}

