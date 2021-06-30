#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "miracl.h"
#include <time.h>

char *ecp="FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFFFFFFFFFFFF";
char *IDString="kimud6003";
char *PWString="1q2w3e";
char *skTAString= "E2AC3E2032159FA6A804BA5F9640DEF4EBDE357202FE025B";
char *PKTAString="AB072A1C611A0B363D4937540FB9EACBC0AD1A82EF2F2647";
char *ecb="64210519E59C80E70FA7E9AB72243049FEB8DEECC146B9B1";
char *ecx="3B5EFCFF203B1934E7CD717CD186AB00F79058E8831BDC73";

char *egx="188DA80EB03090F67CBF20EB43A18800F4FF0AFD82FF1012";
char *egy="07192B95FFC8DA78631011ED6B24CDD573F977A11E794811";

static big concat(big input1, big input2) {
    char inputChar1[100]="";
    char inputChar2[100]="";
    big ouput;
    ouput=mirvar(0);
    cotstr(input1,inputChar1);
    cotstr(input2,inputChar2);
    char *outputChar = malloc(strlen(inputChar1) + strlen(inputChar2) + 1);
    strcpy(outputChar, inputChar1);
    strcat(outputChar, inputChar2);
    cinstr(ouput,outputChar);
    // printf("concat\n");
    // cotnum(ouput,stdout);
    return ouput;
}
static big hashing1(big input){ 
    sha sh;
    big o;
    o = mirvar(0);
    char inputChar[100]="";
    char outputChar[100]="";
    cotstr(input,inputChar);
    shs256_init(&sh);
    int loop= strlen(inputChar);
    for(int i=0; i<loop; i++){
        shs256_process(&sh,inputChar[i]);
    }
    shs256_hash(&sh,outputChar);
    bytes_to_big(strlen(outputChar),outputChar,o);
    // printf("Hashing output\n");
    // cotnum(o,stdout);
    return o;
}
static big hashing2(big input){ 
    sha sh;
    big o;
    o = mirvar(0);
    char inputChar[100]="";
    char outputChar[100]="";
    cotstr(input,inputChar);
    shs_init(&sh);
    int loop= strlen(inputChar);
    for(int i=0; i<loop; i++){
        shs_process(&sh,inputChar[i]);
    }
    shs_hash(&sh,outputChar);
    bytes_to_big(strlen(outputChar),outputChar,o);
    // printf("Hashing output\n");
    // cotnum(o,stdout);
    return o;
}

// //XOR
static big XOR(big input1,big input2){
    int len = 0;
    char inputChar1[100]="";
    char inputChar2[100]="";
    char outputChar[100]="";
    big o;
    o = mirvar(0);
    cotstr(input1,inputChar1);
    cotstr(input2,inputChar2);
    (strlen(inputChar1)>strlen(inputChar2)) ? (len =strlen(inputChar1)) :(len = strlen(inputChar2));
    for(int i =0; i<len; i++)
        outputChar[i]=(inputChar1[i])^(inputChar2[i]);

    bytes_to_big(strlen(len),outputChar,o);
    // printf("Xor output\n");
    // cotnum(o,stdout);
    return o;
}

int main(int argc, char const *argv[])
{
    // if(argc!=2){
    //     perror("argument is not found\n");
    //     return 0;
    // }
    long seed = 12346;
    miracl *mip=mirsys(500,0);
    big ri,ID,PW,tmpBig,zi;
    epoint *P, *tmpResult ;
    big a,b,p,ai,Bi,Ci,Di,Ei,Ei_,Xi,xi,HPW,HPID,PID,CPID,ski,PKS,Auth,Requset,Ti,  y,px,py,SKx,PKx;
    irand(seed);
    ri=mirvar(0);
    PID=mirvar(0);
    ID=mirvar(0);
    PW=mirvar(0);
    //ECC 설정 
    a=mirvar(0);
    b=mirvar(0);
    p=mirvar(0);
    ai=mirvar(0);
    Bi=mirvar(0);
    Ci=mirvar(0);
    Di=mirvar(0);
    Ei=mirvar(0);
    Ei_=mirvar(0);
    xi=mirvar(0);
    Xi=mirvar(0);
    HPW=mirvar(0);
    HPID=mirvar(0);
    PID=mirvar(0);
    CPID=mirvar(0);
    ski=mirvar(0);
    PKS=mirvar(0);
    Requset=mirvar(0);
    px=mirvar(0);
    py=mirvar(0);

    PKx=mirvar(0);
    SKx=mirvar(0);
    y=mirvar(0);
    mip->IOBASE=16;

    bytes_to_big(strlen(IDString),IDString,ID);
    bytes_to_big(strlen(PWString),PWString,PW);
    //ECC 설정 
    convert(-3,a);
    cinstr(b,ecb);
    cinstr(PKx,PKTAString);
    cinstr(SKx,skTAString);
    cinstr(px,egx);
    cinstr(py,egy);
    cinstr(p,ecp);
    
    //변수로 받아와야하는것
    // cinstr(Bi,);
    // cinstr(Ci,);
    // cinstr(Di,);
    // cinstr(Ei,);
    // cinstr(HPID,);
    // cinstr(PKS,);
    // cinstr(Request,);

    ai = XOR(hashing1(concat(ID,PW)),Bi);
    HPW = hashing1(concat(PW,ai));
    ski = XOR(hashing1(concat(hashing1(concat(ID,ai)),HPW)),Ci);
    zi = XOR(hashing1(concat(ski,ai)),Di);
    Ei_ = hashing1(concat(concat(ski,zi),ai));
    if(Ei!=Ei_){
        exit(0);
    }
    bigrand(p,xi);
    P=epoint_init();
    tmpResult=epoint_init();
    epoint_set(px,py,0,P);
    ecurve_mult(xi,P,tmpResult);
    epoint_get(tmpResult,Xi,Xi);
    PID=XOR(HPID,HPW);
    CPID = XOR(PID,hashing1(concat(xi,PKS)));
    Auth = hashing2(concat(concat(concat(PID,Xi),hashing1(Requset)),Ti));
    ecurve_mult(Auth,ski,tmpResult);
    epoint_get(tmpResult,tmpBig,tmpBig);

    return 0;
}

