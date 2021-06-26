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
    cinstr(ski,"D4C71685B73F4ECDB6665088F589CDCD9210365E");
    cinstr(ai,"4EDBEEC9A79133209090CD5DBAA5A9CD10E6259D");
    cinstr(PID,"686C2E403939827CCA8229EAD437D6F5D126F068");
    cinstr(Ri,"95C02223361E60ECD0D52437109C02099EE15BB08DC461CC");
    cinstr(zi,"7D467858F310FB2CDF1276CC0FCFD5690B5773820C31E510");

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

    return 0;
}

