//
//  Round.c
//  IDEA
//
//  Created by ivan sarno on 02/12/14.
//  Copyright (c) 2014 ivan sarno. All rights reserved.
//
//Version V.1.1
/*
Implementation of round of IDEA algorithm, divided in steps for clarity and simplicity, mul operation is ad hoc for the algorithm.
See official algorithm reference for more details
*/

#include "Round.h"


void Round(uint16_t *message,uint16_t *key)
{
    uint16_t temp[2];
    
    step1(message,key);
    step2(message,temp);
    step3(temp,key);
    step4(temp,key);
    step5(message,temp);
    step6(message,temp);
    step7(message);
    
}


void Finalround(uint16_t *message,uint16_t *key)
{
    uint16_t temp[2];
    
    step1(message,key);
    step2(message,temp);
    step3(temp,key);
    step4(temp,key);
    step5(message,temp);
    step6(message,temp);
    step8(message,key);
    
}




uint16_t mul(unsigned long long a, unsigned long long b)
{
    if(a==0)
        a=mod;
    if(b==0)
        b=mod;
    return (uint16_t) ((a*b)%mulmod)addmod;
}


void step1(uint16_t *message,uint16_t *key)
{
    message[0]=mul(message[0],key[0]);
    message[1]=(message[1]+key[1]) addmod;
    message[2]=(message[2]+key[2]) addmod;
    message[3]=mul(message[3],key[3]);
}

void step2(uint16_t *message, uint16_t *temp)
{
    temp[0]= (message[0]^message[2]);
    temp[1]= (message[1]^message[3]);
}

void step3(uint16_t *temp, uint16_t *key)
{
    temp[0]= mul(temp[0],key[4]);
    temp[1]= (temp[1]+temp[0])addmod;
}

void step4(uint16_t *temp, uint16_t *key)
{
    temp[1]= mul(temp[1],key[5]);
    temp[0]= (temp[1]+temp[0])addmod;
}

void step5(uint16_t *message,uint16_t *temp)
{
    message[0]=(message[0]^temp[1]);
    message[2]=(message[2]^temp[1]);
}

void step6(uint16_t *message,uint16_t *temp)
{
    message[1]=(message[1]^temp[0]);
    message[3]=(message[3]^temp[0]);
}

void step7(uint16_t *message)
{
    uint16_t aus=message[1];
    message[1]=message[2];
    message[2]=aus;
}

void step8(uint16_t *message,uint16_t *key)
{
    message[0]=mul(message[0],key[6]);
    message[1]=(message[1]+key[7]) addmod;
    message[2]=(message[2]+key[8]) addmod;
    message[3]=mul(message[3],key[9]);
}


