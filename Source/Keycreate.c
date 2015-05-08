 //
//  Keycreate.c
//  IDEA
//
//  Created by ivan sarno on 02/12/14.
//  Copyright (c) 2014 ivan sarno. All rights reserved.
//
//Version V.1.2
/*
implementation of key shedule of IDEA, subkey array is allocated in the calling function.
See official algorithm reference for more details
*/

#include "Keycreate.h"

void keycreate(uint16_t *key, uint16_t *subkey)
{
    int i,j;
    for(i=0;i<=48;i+=8)
    {
        for(j=0;j<8;j++)
            subkey[i+j]=key[j];
        keyrotate(key);
    }
}

/*  
the rotation of 25 bits of the key is implemented by copying elements of the array for the first 16 bits, and shift the remaining bits and adding the remaining digits to next element
*/
void keyrotate(uint16_t *key)
{
    int i;
    uint16_t temp=key[0];
    for(i=0;i<7;i++)
        key[i]=key[i+1];
    key[7]=temp;
    
    temp=key[0]>>7;
    for(i=0;i<7;i++)
        key[i]=(key[i]<<9)+(key[i+1]>>7);
    
    key[7]=(key[7]<<9)+temp;
    
}
//additive inverse operator
uint16_t inv(uint16_t a)
{
    
    return (uint16_t) mod-a;
}

//decryption subkey generator
void deckey(uint16_t *key,uint16_t *subkey)
{
    uint16_t tempkey[56];
    int i;
  
    keycreate(key,tempkey);
    subkey[0]=(uint16_t)inverse(tempkey[48],mulmod);
    subkey[1]=inv(tempkey[49]);
    subkey[2]=inv(tempkey[50]);
    subkey[3]=(uint16_t)inverse(tempkey[51],mulmod);

    //preswapped for final operation
    uint16_t t=tempkey[1];
    tempkey[1]=tempkey[2];
    tempkey[2]=t;
    
    
    for(i=0;i<48;i+=6)
    {
        subkey[4+i]=tempkey[46-i];
        subkey[5+i]=tempkey[47-i];
        subkey[6+i]=(uint16_t)inverse(tempkey[42-i],mulmod);
        subkey[7+i]=inv(tempkey[44-i]);
        subkey[8+i]=inv(tempkey[43-i]);
        subkey[9+i]=(uint16_t)inverse(tempkey[45-i],mulmod);
    }
}