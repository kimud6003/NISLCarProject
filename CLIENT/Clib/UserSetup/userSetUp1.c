#include "miracl.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>

char *ecp="FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFFFFFFFFFFFF";

char *ecb="64210519E59C80E70FA7E9AB72243049FEB8DEECC146B9B1";
char *ecx="188DA80EB03090F67CBF20EB43A18800F4FF0AFD82FF1012";
char *ecy="07192B95FFC8DA78631011ED6B24CDD573F977A11E794811";

int main(int argc, char const *argv[])
{
    int tmp=0, driveLicense = 0;
    srand(time(NULL));
    long seed = rand()%100;
    miracl *mip=mirsys(500,0);
    epoint *g,*PK,*test;
    big ai,ski;
    big a,b,p,x,y,PKX;
    int PKi_D;
    mip->IOBASE=16;
    irand(seed);

    a=mirvar(0);
    b=mirvar(0);
    p=mirvar(0);
    x=mirvar(0);
    y=mirvar(0);
    PKX=mirvar(0);
    ski=mirvar(0);
    ai=mirvar(0);

    convert(-3,a);
    cinstr(b,ecb);
    cinstr(x,ecx);
    cinstr(y,ecy);
    cinstr(p,ecp);
    bigrand(p,ai);

    //  y2 = x3 + Ax + B (mod p) 의형태로 진행
    ecurve_init(a,b,p,MR_BEST);
    g=epoint_init();
    PK=epoint_init();
    test=epoint_init();
    bigdig(40,16,ski);
    bigdig(40,16,ai);
    epoint_set(x,y,0,g);

    ecurve_mult(ski,g,PK);
    PKi_D = epoint_get(PK,PKX,PKX);
    // printf("ski : ");
    cotnum(ski,stdout);
    // printf("ai : ");
    cotnum(ai,stdout);
    // printf("PKi : ");
    cotnum(PKX,stdout);
    printf("%d",PKi_D);

    
    return 0;
}
