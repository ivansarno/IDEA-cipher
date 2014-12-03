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