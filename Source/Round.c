//
//  Round.c
//  IDEA
//
//  Created by ivan sarno on 02/12/14.
//  Copyright (c) 2014 ivan sarno.
/*
 This file is part of IDEA-cipher library
 IDEA-cipher  is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.
 
 IDEA-cipher  is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public
 License along with IDEA-cipher ; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
 USA
 */
//Version V.1.3
/*
Implementation of round of IDEA algorithm, divided in steps for clarity and simplicity, mul operation is ad hoc for the algorithm.
See official algorithm reference for more details
*/

#include "Round.h"
#define mulmod 65537
#define mod 65536


uint16_t mul(unsigned long long a, unsigned long long b)
{
    if(a==0)
        a=mod;
    if(b==0)
        b=mod;
    return (uint16_t) ((a*b)%mulmod);
}


void step1(uint16_t *message,uint16_t *key)
{
    message[0]=mul(message[0],key[0]);
    message[1]=(message[1]+key[1]) ;
    message[2]=(message[2]+key[2]) ;
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
    temp[1]= (temp[1]+temp[0]);
}

void step4(uint16_t *temp, uint16_t *key)
{
    temp[1]= mul(temp[1],key[5]);
    temp[0]= (temp[1]+temp[0]);
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
    message[1]=(message[1]+key[7]) ;
    message[2]=(message[2]+key[8]) ;
    message[3]=mul(message[3],key[9]);
}


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


