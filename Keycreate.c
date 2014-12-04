//
//  Keycreate.c
//  IDEA
//
//  Created by ivan sarno on 02/12/14.
//  Copyright (c) 2014 ivan sarno. All rights reserved.
//

#include "Keycreate.h"


void keycreate(typeint2 *key, typeint *subkey)
{
    int i,j;
    for(i=0;i<50;i+=8)
    {
        for(j=0;j<8;j++)
            subkey[i+j]=key[j];
        keyrotate(key);
    }
}

void keyrotate(uint16_t *key)
{
    int i;
    uint16_t temp=key[0];
    for(i=0;i<7;i++)
        key[i]=key[i+1];
    key[7]=temp;
    
    temp=key[0]/128;
    for(i=0;i<7;i++)
        key[i]=(key[i]<<9)+(key[i+1]/128);
    
    key[7]=(key[7]<<9)+temp;
    
}

void deckey(typeint2 *key,typeint *subkey)
{
    typeint tempkey[56];
    int i;
    keycreate(key,tempkey);
    subkey[0]=inverso(tempkey[48],mulmod);
    subkey[1]=mod-(tempkey[49]);
    subkey[2]=mod-(tempkey[50]);
    subkey[3]=inverso(tempkey[51],mulmod);
    
    for(i=0;i<50;i+=6)
    {
        subkey[4+i]=tempkey[46-i];
        subkey[5+i]=tempkey[47-i];
        subkey[6+i]=inverso(tempkey[42-i],mulmod);
        subkey[7+i]=mod-(tempkey[44-i]);
        subkey[8+i]=mod-(tempkey[43-i]);
        subkey[9+i]=inverso(tempkey[45-i],mulmod);
    }
        
    
}