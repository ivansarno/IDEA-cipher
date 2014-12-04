//
//  Round.c
//  IDEA
//
//  Created by ivan sarno on 02/12/14.
//  Copyright (c) 2014 ivan sarno. All rights reserved.
//

#include "Round.h"


void Round(typeint *message,typeint *key)
{
    typeint temp[2];
    
    step1(message,key);
    step2(message,temp);
    step3(temp,key);
    step4(temp,key);
    step5(message,temp);
    step6(message,temp);
    step7(message);
    
}


void Finalround(typeint *message,typeint *key)
{
    typeint temp[2];
    
    step1(message,key);
    step2(message,temp);
    step3(temp,key);
    step4(temp,key);
    step5(message,temp);
    step6(message,temp);
    step8(message,key);
    
}


typeint mul(typeint3 a, typeint3 b)
{
    if(a==0)
        a=mod;
    if(b==0)
        b=mod;
    return (typeint) ((a*b)%mulmod)addmod;
}


void step1(typeint *message,typeint *key)
{
    message[0]=mul(message[0],key[0]);
    message[1]=(message[1]+key[1]) addmod;
    message[2]=(message[2]+key[2]) addmod;
    message[3]=mul(message[3],key[3]);
}

void step2(typeint *message, typeint *temp)
{
    temp[0]= (message[0]^message[2])xormod;
    temp[1]= (message[1]^message[3])xormod;
}

void step3(typeint *temp, typeint *key)
{
    temp[0]= mul(temp[0],key[4]);
    temp[1]= (temp[1]+temp[0])addmod;
}

void step4(typeint *temp, typeint *key)
{
    temp[1]= mul(temp[1],key[5]);
    temp[0]= (temp[1]+temp[0])addmod;
}

void step5(typeint *message,typeint *temp)
{
    message[0]=(message[0]^temp[1])xormod;
    message[2]=(message[2]^temp[1])xormod;
}

void step6(typeint *message,typeint *temp)
{
    message[1]=(message[1]^temp[0])xormod;
    message[3]=(message[3]^temp[0])xormod;
}

void step7(typeint *message)
{
    typeint aus=message[1];
    message[1]=message[2];
    message[2]=aus;
}

void step8(typeint *message,typeint *key)
{
    message[0]=mul(message[0],key[6]);
    message[1]=(message[1]+key[7]) addmod;
    message[2]=(message[2]+key[8]) addmod;
    message[3]=mul(message[3],key[9]);
}