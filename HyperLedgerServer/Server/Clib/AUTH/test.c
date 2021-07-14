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
    big Qs,SID,AUTH_S,T2,SM1,skj,PKs, etc;
    big Xi_,tmpPoint,AUTH_S_P,checkPoint;
    epoint *g, *EQs, *tmpResult, *EPKs; 
    big a,b,p,gx,gy;

    big sks,qs,PKj,SKs;
    epoint *EPKj; 
    irand(seed);

    etc =mirvar(0);
    Qs = mirvar(0);
    SID = mirvar(0);
    AUTH_S = mirvar(0);
    AUTH_S_P = mirvar(0);
    T2 = mirvar(0);
    SM1 = mirvar(0);
    Xi_ = mirvar(0);
    PKs = mirvar(0);
    skj = mirvar(0);
    PKs = mirvar(0);
    sks = mirvar(0);
    SKs = mirvar(0);
    qs = mirvar(0);
    checkPoint = mirvar(0);
    tmpPoint = mirvar(0);

    PKj = mirvar(0);

    // ECC 설정
    a=mirvar(0);
    b=mirvar(0);
    p=mirvar(0);
    gx=mirvar(0);
    gy=mirvar(0);


    mip->IOBASE=16;
    // argv 값 넣어주기
    cinstr(sks,"2A98E2DAC9176641F4DCDD7233006991016AEFD2");
    cinstr(skj,"2F317ADAEB437FBF557873CF8BD03621F086C218");
    cinstr(Qs,"FFC326E82E95C5985B03845A133EA90CE8F7A497696E69F7");
    cinstr(SID,"AAAA");
    cinstr(AUTH_S,"5F59B423F60DDCC0C669E67F7EEC91CE9B5125130B2F3CAFFEFEC9EBB39892B2E9A0259DE670D94");
    cinstr(T2,"60D98FB3");
    cinstr(SM1,"FCCBCBA9B8A061D050B2C8B8D64BC7DB4EBF4C33E3B3F418");
    // test
    cinstr(SKs,"5A1ADFD946AD2ECB15F00518D7861FF861A4D88E");
    cinstr(PKj,"8FFBFDA5FCF8C72A230FDE4B49C310DA3DEB7D394CE85B3");
    cinstr(PKs,"FCCBCBA994CA225173EB394CEA882FDB5F06BC59932678E0");
    cinstr(qs,"7A7EA840AED4B7E0FF52D2F3413BECDF904BA5CA");
// tmpPoint = 9EB4C3F929BC04F2F4FCE60D02F8BC16B1073E3073CAC3AD
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
    EPKj = epoint_init();
    tmpResult = epoint_init();
    epoint_set(gx,gy,0,g); // ECC 설정 완료
    epoint_set(Qs,Qs,0,EQs); // ECC 설정 완료
    epoint_set(PKs,PKs,0,EPKs); //ECC 설정완료
    epoint_set(PKj,PKj,0,EPKj); //ECC 설정완료

// //SKS * g  PKs
//     ecurve_mult(SKs,g,tmpResult);
//     int c=epoint_get(tmpResult,tmpPoint,tmpPoint);
//     printf("*SKs_D : %d ",c);

// //qs * PKJ (qs * (skj * g))
//     ecurve_mult(qs,EPKj,tmpResult);
//     tmpPoint=XsetPoint(tmpResult);
//     printf("*tmpPoint : ");
//     cotnum(tmpPoint,stdout);

// //qs * g = QS
//     ecurve_mult(qs,g,tmpResult);
//     tmpPoint=XsetPoint(tmpResult);
//     printf("*QS : ");
//     cotnum(tmpPoint,stdout);

// skj * g = PKJ
    big t_1,t_2,t_3;
    epoint *t1E,*t2E,*t3E;
    int ts1,ts2,ts3; 
    t1E = epoint_init();
    t2E = epoint_init();
    t3E = epoint_init();
    t_1= mirvar(3);
    t_2= mirvar(-2);
    t_3= mirvar(6);
    printf("=================\n");
    ecurve_mult(t_1,g,tmpResult);
    ts1 = epoint_get(tmpResult,tmpPoint,tmpPoint);
    printf("t_1*g의 X 좌표 : ");
    cotnum(tmpPoint,stdout);
    epoint_set(tmpPoint,tmpPoint,ts1,t1E); // ECC 설정 완료


    ecurve_mult(t_2,g,tmpResult);
    ts2 = epoint_get(tmpResult,tmpPoint,tmpPoint);
    printf("t_2*g의 X 좌표 : ");
    cotnum(tmpPoint,stdout);
    epoint_set(tmpPoint,tmpPoint,0,t2E); // ECC 설정 완료
    

    ecurve_mult(t_2,t1E,tmpResult);
    epoint_get(tmpResult,tmpPoint,tmpPoint);
    printf("t_2*(t_1*g)의 X 좌표 : ");
    cotnum(tmpPoint,stdout);
    // epoint_set(tmpPoint,tmpPoint,ts1,t1E); // ECC 설정 완료


    ecurve_mult(t_1,t2E,tmpResult);
    epoint_get(tmpResult,tmpPoint,tmpPoint);
    printf("t_1*(t_2*g)의 X 좌표 : ");
    cotnum(tmpPoint,stdout);


    ecurve_mult(t_3,g,tmpResult);
    tmpPoint=XsetPoint(tmpResult);
    printf("t_3*g: ");
    cotnum(tmpPoint,stdout);

// //skj * Qs (skj * (qs * g))
//     ecurve_mult(skj,EQs,tmpResult);
//     tmpPoint= XsetPoint(tmpResult);
//     printf("SKJ * QS : ");
//     cotnum(tmpPoint,stdout);

//     Xi_ = hashing1(XOR(SM1,hashing1(tmpPoint)));
//     printf("Xi_ : ");
//     cotnum(Xi_,stdout);

//     ecurve_mult(AUTH_S,g,tmpResult);
//     AUTH_S_P = XsetPoint(tmpResult);
//     // subtract(AUTH_S,qs,AUTH_S);
//     // cotnum(AUTH_S,stdout);
//     // printf("test : ");
//     cotnum(AUTH_S,stdout);

//     checkPoint = hashing1(concat(Xi_,concat(SID,concat(Qs,T2))));
//     // multiply(checkPoint,sks,checkPoint);
//     // printf("test : ");
//     // cotnum(checkPoint,stdout);


//     ecurve_mult(checkPoint,EPKs,tmpResult);
//     XsetPoint(tmpResult);
//     ecurve_add(EQs,tmpResult);
//     cotnum(XsetPoint(tmpResult),stdout);

    return 0;
}

