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
    big H1CODE,CM5_,SM2,SM3,SM4,tmpPoint,SID;
    big qs,CM1,CM2,CM3,CM4,CM5,CM6,Yj,T3,T4,sks,Xi,PKc;

    big xi,CODE,CM2_,TID_,PKs,SM3_;
    epoint *g, *tmpResult; 
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
    CM3 = mirvar(0);
    CM4 = mirvar(0);
    CM5 = mirvar(0);
    CM6 = mirvar(0);
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
    cinstr(Xi,"A7977E3AC6474E9EDE709D390531F7066D27B1A3B07EA840");
    cinstr(qs,"6167D7999019CACB1CFDD4601C10447E9EF01C3A");
    cinstr(sks,"5A1ADFD946AD2ECB15F00518D7861FF861A4D88E");
    cinstr(SID,"AAAA");
    cinstr(Yj,"11540B076C5473A7A4C465B60163F856568D4AA03484EB35");
    cinstr(T3,"60D9E04E");
    cinstr(CM1,"8019D9F847C688EB7CE5ABF0698A9D4E3AAC1EDA");
    cinstr(CM2,"9BA4A6CF97832035565C5822E9BC0556CD0DECDF");
    cinstr(CM4,"2E750367F5A1B73D8EC8BB050209B0FCAFC556C");
    cinstr(CM5,"9F35D38783D5EA802E0FFC570A23968EA472E9F3");
    cinstr(CM6,"7E6351DADEC7C9756FA16297D5FDDAE693D9627");


    cinstr(xi,"D0963A3A7474D0F96C352D7A5C45F2A059D025F9");
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
    multiply(Yj,xi,tmpPoint);
    cotnum(tmpPoint,stdout);
    CODE = XOR(CM1,hashing1(tmpPoint));
    CM2_ = hashing1(concat(concat(hashing1(CODE),tmpPoint),T3));

    if(mr_compare(CM2,CM2_)!=0){
        printf("CM verified fail\n");
        return 0;
    }

    time_t T;
    time(&T);
    convert(T,T4);
    multiply(xi,PKs,tmpPoint);

    TID_ = XOR(SM2,hashing1(tmpPoint));
    SM3_ = hashing1(concat(concat(concat(concat(hashing1(CODE),TID_),Yj),T4),tmpPoint));


    if(mr_compare(SM3,SM3_)!=0){
        printf("SM verified fail\n");
        return 0;
    }
   


    return 0;
}

