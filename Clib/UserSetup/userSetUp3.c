#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "miracl.h"
#include "setup.h"
#include <time.h>

char *PIDString = "477740C040172770707";
char *RiString = "3B5EFCFF203B1934E7CD717CD186AB00F79058E8831BDC73";
char *ziString = "B86347E4A35B7AF7D416725E83E37D04665A5C19BA9239C1";

char *IDString="kimud6003";
char *PWString="1q2w3e";

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
    cinstr(ski,"3934A2306A37E7BDD19E7141839751B3EA77E0B3");
    cinstr(PID,"6CC4B5543C20229B1EE43F5B95EC5BEE46C45D56");
    cinstr(Ri,"2398D6DC54F50DCC0674C25E30D005FBDE0B72571C57995F");
    cinstr(ai,"ADE64ABC45D3F9013D615D3A20A3236A9D9E852F");
    cinstr(zi,"8225AF8D75ABA54F7E5CAD1B33CE00F923FF3DBC509BC6E");

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

