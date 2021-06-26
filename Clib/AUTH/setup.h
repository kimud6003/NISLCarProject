#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "miracl.h"
#include <time.h>

static big concat(big input1, big input2) {
    char inputChar1[1000]="";
    char inputChar2[1000]="";
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
static big hashing2(char* input){ 
    sha sh;
    big o = mirvar(0);
    char outputChar[1000]="";
    shs_init(&sh);
    int loop= strlen(input);
    for(int i=0; i<loop; i++){
        shs_process(&sh,input[i]);
    }
    shs_hash(&sh,outputChar);
    bytes_to_big(20,outputChar,o);
    return o;
}
static big hashing1(big input){ 
    sha sh;
    big o = mirvar(0);
    char inputChar[1000]="";
    char outputChar[1000]="";
    cotstr(input,inputChar);
    shs_init(&sh);
    int loop= strlen(inputChar);
    for(int i=0; i<loop; i++){
        shs_process(&sh,inputChar[i]);
    }
    shs_hash(&sh,outputChar);
    bytes_to_big(20,outputChar,o);
    // printf("Hashing output\n");
    // cotnum(o,stdout);
    return o;
}
int hex2int(char ch)
{
    if (ch >= '0' && ch <= '9')
        return ch - '0';
    if (ch >= 'A' && ch <= 'F')
        return ch - 'A' + 10;
    if (ch >= 'a' && ch <= 'f')
        return ch - 'a' + 10;
    return -1;
}
char *strrev(char *str){
    char *p1, *p2;

    if (! str || ! *str)
        return str;
    for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
    {
        *p1 ^= *p2;
        *p2 ^= *p1;
        *p1 ^= *p2;
    }
    return str;
}

// //XOR
static big XOR(big input1,big input2){
    char inputChar1[1000]="",inputChar2[1000]="",outputChar[100]="";
    char tmp[1000]="",tmp2[1000]="";
    int input1L=0,input2L=0,len=0;
    big o;
    o = mirvar(0);
    cotstr(input1,inputChar1);
    cotstr(input2,inputChar2);
    input1L=strlen(inputChar1)-1;
    input2L=strlen(inputChar2)-1;

    if(input1L>input2L){
        strncpy(outputChar,inputChar1,input1L-input2L);
        len=input1L;
    }else if (input1L<input2L){
        strncpy(outputChar,inputChar2,input2L-input1L);
        len=input2L;
    }else{
        len=input2L;
    }
    while(input2L > -1 && input1L > -1){
        int number1 = 0;
        int number2 = 0;
        if(input1L > -1){
            number1 = hex2int(inputChar1[input1L--]);
        } 
        if(input2L > -1){
            number2 = hex2int(inputChar2[input2L--]);
        } 
        sprintf(tmp,"%X",number1^number2);
        strcat(tmp2,tmp);
    }
    strcat(outputChar, strrev(tmp2));

    cinstr(o,outputChar);
    // printf("Xor output\n");
    // cotnum(o,stdout);
    return o;
}