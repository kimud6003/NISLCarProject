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
    miracl *mip=mirsys(500,0);
    big sks;
    big PKi,Bi,Ci,Di,Ei,HPID,PKs,ski,ID,PW,tmpPoint;
    big xi,CPID,PID,HPW,ai,Ei_,Xi,zi,AUTH,T;
    epoint *g,*Eski, *EPKs,*tmpResult, *ESKs; 
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
    PKi=mirvar(0);
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
    cinstr(ski,"D4C71685B73F4ECDB6665088F589CDCD9210365E");
    cinstr(PKi,"BD1BD462D74564636BDCF08EC6ED56BD350E0E903496772F");
    bytes_to_big(strlen("kimud6003"),"kimud6003",ID);
    bytes_to_big(strlen("1q2w3e"),"1q2w3e",PW);
    cinstr(Bi,"3AFCB91F848BC6237403F891F06616872F018EC4");
    cinstr(Ci,"FE60D24B0101681B61143E5EE77F28B0933487B1");
    cinstr(Di,"7D467858681F362EACA9B35F446885A009EC90B66AE4127F");
    cinstr(Ei,"2C2F392554DD59E175D6EEB5A752B9CE513F017");
    cinstr(HPID,"F3607136FF16157C48D3271C6DB40462B5FC5437");
    cinstr(PKs,"999A48ADD10173A41BCCF88D407626D57867F164D84AB712");
    cinstr(sks,"5A1ADFD946AD2ECB15F00518D7861FF861A4D88E");
    char requst[] = "3430주 10";


    //ECC 설정 
    convert(-3,a);
    cinstr(b,ecb);
    cinstr(gx,egx);
    cinstr(gy,egy);
    cinstr(p,ecp);

    ecurve_init(a,b,p,MR_BEST);
    g=epoint_init();
    tmpResult=epoint_init();
    Eski=epoint_init();
    EPKs=epoint_init();
    epoint_set(ski,ski,0,Eski); //ECC 설정완료
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
    time_t T1;
    time(&T1);
    convert(T1,T);

    bigdig(40,16,xi);

    ecurve_mult(xi,g,tmpResult);
    epoint_get(tmpResult,Xi,Xi);
    PID = XOR(HPID,HPW);
    printf("PID : ");
    cotnum(PID,stdout);
    ecurve_mult(xi,EPKs,tmpResult);
    epoint_get(tmpResult,tmpPoint,tmpPoint);
    CPID = XOR(PID,hashing1(tmpPoint));
// 삭제
    // ESKs = epoint_init();
    // epoint_set(Xi,Xi,0,ESKs);
    // ecurve_mult(sks,ESKs,tmpResult);
    // epoint_get(tmpResult,tmpPoint,tmpPoint);
    // printf("2 : ");
    // cotnum(tmpPoint,stdout);

// 삭제 

    AUTH = hashing1(concat(concat(concat(PID,Xi),hashing2(requst)),T));
    // printf("Ecurve mult : ");
    // cotnum(AUTH,stdout);
    // ecurve_mult(AUTH,Eski,tmpResult);
    // epoint_get(tmpResult,AUTH,AUTH);
    multiply(AUTH,ski,AUTH);
    add(xi,AUTH,AUTH);
    printf("xi:");
    cotnum(xi,stdout);

    printf("Xi : ");
    cotnum(Xi,stdout);

    printf("CPID : ");
    cotnum(CPID,stdout);

    printf("AUTH : ");
    cotnum(AUTH,stdout);

    printf("T : ");
    cotnum(T,stdout);

    return 0;
}

