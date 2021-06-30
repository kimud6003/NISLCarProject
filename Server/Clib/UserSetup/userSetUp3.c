#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "miracl.h"
#include "setup.h"
#include <time.h>


int main(int argc, char const *argv[])
{
    // if(argc!=2){
    //     perror("argument is not found\n");
    //     return 0;
    // }
    long seed = rand()%100;
    int Ri_D=-1;
    miracl *mip=mirsys(500,0);
    big Bi,Ci,Di,Ei,HPID, tmp;
    big ai,ID,PW,HPW,ski,PID,hashing_result,Ri,zi;
    irand(seed);
    Bi=mirvar(0);
    Ci=mirvar(0);
    Di=mirvar(0);
    Ei=mirvar(0);
    ai=mirvar(0);
    ID=mirvar(0);
    PW=mirvar(0);
    HPW=mirvar(0);
    ski=mirvar(0);
    PID=mirvar(0);
    hashing_result=mirvar(0);
    Ri=mirvar(0);
    zi=mirvar(0);
    tmp = mirvar(0);
    mip->IOBASE=16;

    
    // argv 입력값
    bytes_to_big(strlen("kimud6003"),"kimud6003",ID);
    bytes_to_big(strlen("1q2w3e"),"1q2w3e",PW);
    cinstr(ski,"2A98E2DAC9176641F4DCDD7233006991016AEFD2");
    cinstr(ai,"80A7F68FF5B6B3F94D4084D0428C5062FB366C50");
    cinstr(PID,"A54A9FB5C7FBD2592D8D5D1D1A9846F7C018DB09");
    cinstr(Ri,"331921FB991C6DC47BB5ED0C750072AF281D74A4C97ED08F");
    Ri_D = 0;
    cinstr(zi,"6E605C742C7E206402C00EC5794FCAFD90DE5707374CE53ECFB125DFD634608DC3CDF55E4FBBC63");

    HPW = hashing1(concat(PW,ai));
    Bi = XOR(hashing1(concat(ID,PW)),ai);
    Ci = XOR(hashing1(concat(hashing1(concat(ID,ai)),HPW)),ski);
    Di = XOR(hashing1(concat(ski,ai)),zi);
    Ei = hashing1(concat(concat(ski,zi),ai));
    HPID = XOR(PID,HPW);

    printf("Bi : ");
    cotnum(Bi,stdout);
    printf("Ci :");
    cotnum(Ci,stdout);
    printf("Di : ");
    cotnum(Di,stdout);
    printf("Ei : ");
    cotnum(Ei,stdout);
    printf("HPID : ");
    cotnum(HPID,stdout);
    printf("Ri : ");
    cotnum(Ri,stdout);
    printf("Ri_D : %d\n",Ri_D);

    return 0;
}

