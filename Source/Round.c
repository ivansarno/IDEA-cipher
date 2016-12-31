//
//  Round.c
//  IdeaLib
//
//  Created by ivan sarno on 02/12/14.
//  Copyright (c) 2014 ivan sarno.
/*
 This file is part of IdeaLib library
 IdeaLib  is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 IdeaLib  is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with IdeaLib ; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
 USA
 */
//Version V.2.4
/*
Implementation of round of IDEA algorithm, divided in steps for clarity and simplicity, multiplication operation is ad hoc for the algorithm.
See official algorithm reference for more details
*/

#include "Round.h"

#define mulModulus 65537
#define addModulus 65536

static inline uint16_t IdeaMultiplication(uint32_t a, uint32_t b)
{
    if(a==0)
        a=addModulus;
    if(b==0)
        b=addModulus;
    return (uint16_t) ((a*b)%mulModulus);
}


static inline void step1(uint16_t *message, uint16_t *key)
{
    message[0]=IdeaMultiplication(message[0],key[0]);
    message[1]=(message[1]+key[1]) ;
    message[2]=(message[2]+key[2]) ;
    message[3]=IdeaMultiplication(message[3],key[3]);
}

static inline void step2(uint16_t *message, uint16_t *temp)
{
    temp[0]= (message[0]^message[2]);
    temp[1]= (message[1]^message[3]);
}

static inline void step3(uint16_t *temp, uint16_t *key)
{
    temp[0]= IdeaMultiplication(temp[0],key[4]);
    temp[1]= (temp[1]+temp[0]);
}

static inline void step4(uint16_t *temp, uint16_t *key)
{
    temp[1]= IdeaMultiplication(temp[1],key[5]);
    temp[0]= temp[1] + temp[0];
}

static inline void step5(uint16_t *message,uint16_t *temp)
{
    message[0]=(message[0]^temp[1]);
    message[2]=(message[2]^temp[1]);
}

static inline void step6(uint16_t *message,uint16_t *temp)
{
    message[1]=(message[1]^temp[0]);
    message[3]=(message[3]^temp[0]);
}

static inline void step7(uint16_t *message)
{
    uint16_t aus=message[1];
    message[1]=message[2];
    message[2]=aus;
}

static inline void step8(uint16_t *message, uint16_t *key)
{
    message[0]=IdeaMultiplication(message[0],key[6]);
    message[1]=(message[1]+key[7]);
    message[2]=(message[2]+key[8]);
    message[3]=IdeaMultiplication(message[3],key[9]);
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


void FinalRound(uint16_t *message,uint16_t *key)
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
