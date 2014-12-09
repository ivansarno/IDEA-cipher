 //
//  Keycreate.c
//  IDEA
//
//  Created by ivan sarno on 02/12/14.
//  Copyright (c) 2014 ivan sarno. All rights reserved.
//

#include "Keycreate.h"
#include <assert.h>
//#include <stdio.h>


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

typeint inv(typeint3 a)
{
    //if (a)
        //a=-a;
    return (typeint) mod-a;
}

void deckey(typeint2 *key,typeint *subkey)
{
    typeint tempkey[56];
    int i;
   // unsigned long long y,z;
   // unsigned int h;
    keycreate(key,tempkey);
    subkey[0]=inverso(tempkey[48],mulmod);
    subkey[1]=inv(tempkey[49]);
    subkey[2]=inv(tempkey[50]);
    subkey[3]=inverso(tempkey[51],mulmod);
    assert(((subkey[3]*tempkey[51])%65537)==1);
    assert(((subkey[0]*tempkey[48])%65537)==1);
    assert((subkey[1]+tempkey[49])%mod==0);
    assert((subkey[2]+tempkey[50])%mod==0);
    
    ///
    typeint2 t=tempkey[1];
    tempkey[1]=tempkey[2];
    tempkey[2]=t;
    //////
    
    for(i=0;i<50;i+=6)
    {
        subkey[4+i]=tempkey[46-i];
        subkey[5+i]=tempkey[47-i];
        subkey[6+i]=inverso(tempkey[42-i],mulmod);
        subkey[7+i]=inv(tempkey[44-i]);
        subkey[8+i]=inv(tempkey[43-i]);
        subkey[9+i]=inverso(tempkey[45-i],mulmod);
        
        //if(i>18)
        assert(((subkey[9+i]*tempkey[45-i])%65537)==1);
        assert(((subkey[6+i]*tempkey[42-i])%65537)==1);
        assert((subkey[7+i]+tempkey[44-i])%mod==0);
        assert((subkey[8+i]+tempkey[43-i])%mod==0);
    }
    //y=subkey[27];z=tempkey[27];
    //h=(subkey[27]*tempkey[27]);
   // assert(h%mulmod==1);
   //  assert(((subkey[27]*tempkey[27])%65537)==1);
    
    //printf("%x\n",tempkey[2]);
    //printf("%x\n",tempkey[1]);
    //printf("%x\n",subkey[49]);
    //subkey[49]=65536-0x00c8;
    //subkey[50]=65536-0x012c;
  //  printf("%x\n",subkey[49]);
    
}