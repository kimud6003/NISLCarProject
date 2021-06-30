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

//TODO
    
    // argv 입력값
    bytes_to_big(strlen(argv[1]),argv[1],ID);
    bytes_to_big(strlen(argv[2]),argv[2],PW);
    cinstr(ski,argv[3]);
    cinstr(ai,argv[4]);
    cinstr(PID,argv[5]);
    cinstr(Ri,argv[6]);
    cinstr(zi,argv[7]);


    HPW = hashing1(concat(PW,ai));
    Bi = XOR(hashing1(concat(ID,PW)),ai);
    Ci = XOR(hashing1(concat(hashing1(concat(ID,ai)),HPW)),ski);
    Di = XOR(hashing1(concat(ski,ai)),zi);
    Ei = hashing1(concat(concat(ski,zi),ai));
    HPID = XOR(PID,HPW);

    // printf("Bi : ");
    cotnum(Bi,stdout);
    // printf("Ci :");
    cotnum(Ci,stdout);
    // printf("Di : ");
    cotnum(Di,stdout);
    // printf("Ei : ");
    cotnum(Ei,stdout);
    // printf("HPID : ");
    cotnum(HPID,stdout);
    // printf("Ri : ");
    cotnum(Ri,stdout);

    return 0;
}

