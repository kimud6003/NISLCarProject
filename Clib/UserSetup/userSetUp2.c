#include "miracl.h"
#include "setup.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <time.h>

char *ecp="FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFFFFFFFFFFFF";
char *skTAString= "E2AC3E2032159FA6A804BA5F9640DEF4EBDE357202FE025B";
char *PKTAString="AB072A1C611A0B363D4937540FB9EACBC0AD1A82EF2F2647";

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
    big ri,PID,ID,hashing_result,Ri,zi,PKi;
    epoint *g,*PKTA, *tmpResult, *SKTA;
    big a,b,p,PKx,y,gx,gy,SKx;
    irand(seed);
    ri=mirvar(0);
    PID=mirvar(0);
    ID=mirvar(0);
    PKi=mirvar(0);
    //ECC 설정 
    a=mirvar(0);
    b=mirvar(0);
    p=mirvar(0);
    PKx=mirvar(0);
    SKx=mirvar(0);
    gx=mirvar(0);
    gy=mirvar(0);
    y=mirvar(0);
    zi=mirvar(0);
    Ri=mirvar(0);
    mip->IOBASE=16;
    // argv 값 넣어주기
    cinstr(PKi,"BD1BD462D74564636BDCF08EC6ED56BD350E0E903496772F");
    bytes_to_big(strlen("kimud6003"),"kimud6003",ID);

    //ECC 설정 
    convert(-3,a);
    cinstr(b,ecb);
    cinstr(PKx,PKTAString);
    cinstr(SKx,skTAString);
    cinstr(gx,egx);
    cinstr(gy,egy);
    cinstr(p,ecp);

    ecurve_init(a,b,p,MR_BEST);
    g=epoint_init();
    tmpResult=epoint_init();
    PKTA=epoint_init();
    SKTA=epoint_init();
    epoint_set(PKx,PKx,0,PKTA); //ECC 설정완료
    epoint_set(SKx,SKx,0,SKTA); //ECC 설정완료
    epoint_set(gx,gy,0,g); //ECC 설정완료

    bigdig(40,16,ri);
    ecurve_mult(ri,PKTA,tmpResult);
    epoint_get(tmpResult,y,y);
    PID=XOR(ID,hashing1(y));
    printf("PID : ");
    cotnum(PID,stdout);

    ecurve_mult(ri,g,tmpResult);
    epoint_get(tmpResult,Ri,Ri);
    printf("Ri : ");
    cotnum(Ri,stdout);

    ecurve_mult(hashing1(concat(concat(PID,Ri),PKi)),SKTA,tmpResult);
    epoint_get(tmpResult,y,y);
    add(ri,y,zi);
    printf("zi : ");
    cotnum(zi,stdout);


    return 0;
}

