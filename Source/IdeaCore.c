//
//  IdeaCore.c
//  IDEA
//
//  Created by ivan sarno on 23/02/17.
//  Copyright © 2017 ivan sarno.
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
//Version V.3.1
//This file implements the core functionalities of IdeaLib

#include "IdeaCore.h"
#include <stddef.h>

#define mulModulus 65537
#define addModulus 65536
#define roundNumber 7
#define subKeyNumber 56

/*
 Implementation of round of IDEA algorithm, divided in steps for clarity and simplicity, multiplication operation is ad hoc for the algorithm.
 See official algorithm reference for more details
 */

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

static inline void step2(const uint16_t *message, uint16_t *temp)
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

static inline void step5(uint16_t *message, const uint16_t *temp)
{
    message[0]=(message[0]^temp[1]);
    message[2]=(message[2]^temp[1]);
}

static inline void step6(uint16_t *message, const uint16_t *temp)
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


static void Round(uint16_t *message,uint16_t *key)
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


static void FinalRound(uint16_t *message,uint16_t *key)
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

/*
 implementation of key schedule of IDEA, subkey array is allocated in the caller function.
 See official algorithm reference for more details
 */


//add inverse operator
static inline uint16_t AddInverse(uint16_t number)
{
    return (uint16_t) addModulus-number;
}

//mul inverse operator
static uint16_t MulInverse(uint16_t number)
{
    int j = 1;
    int64_t result, temp, intermediate;
    int64_t buffer[35];//35 is an upper bound for intermediate result of a inversion of a 16 bits integer
    
    buffer[0] = number;
    buffer[1] = mulModulus;
    
    while(buffer[j] != 0) //find intermediate values of greatest common divisor
    {
        j++;
        buffer[j] = buffer[j-2] % buffer[j-1];
    }
    
    result = 1;
    intermediate = 1;
    temp = 0;
    
    while(j > 1) //inverse calculation from intermediates values
    {
        
        j--;
        result = temp;
        temp = intermediate - ((buffer[j-1] / buffer[j]) * temp);
        intermediate = result;
    }
    
    if(result > 0)
        return (uint16_t) result;
    else return (uint16_t) (mulModulus + result);
}

//25 bit left shift
static inline void keyrotate(uint64_t *key)
{
    uint64_t temp;
    temp = (key[0] << 25u) + (key[1] >> 39u);
    key[1] = (key[1] << 25u) + (key[0] >> 39u);
    key[0] = temp;
}

void EncryptKeyCreate(uint64_t *key, uint16_t *subKey)
{
    uint64_t *subKeyp = (uint64_t*)subKey;
    uint64_t keyc[2];//key local copy
    keyc[0] = key[0];
    keyc[1] = key[1];
    
    for(int i=0, j=0; i<roundNumber; i++, j+=2)
    {
        subKeyp[j]=keyc[0];
        subKeyp[j+1] = keyc[1];
        keyrotate(keyc);
    }
}

//decryption subkey generator
void DecryptKeyCreate(uint64_t *key,uint16_t *subKey)
{
    uint16_t tempKey[subKeyNumber];
    int i;
    
    EncryptKeyCreate(key,tempKey);
    subKey[0]=MulInverse(tempKey[48]);
    subKey[1]=AddInverse(tempKey[49]);
    subKey[2]=AddInverse(tempKey[50]);
    subKey[3]=MulInverse(tempKey[51]);
    
    //preswapped for final operation
    uint16_t t=tempKey[1];
    tempKey[1]=tempKey[2];
    tempKey[2]=t;
    
    //set remaining subkeys
    for(i=0;i<48;i+=6)
    {
        subKey[4+i]=tempKey[46-i];
        subKey[5+i]=tempKey[47-i];
        subKey[6+i]=MulInverse(tempKey[42-i]);
        subKey[7+i]=AddInverse(tempKey[44-i]);
        subKey[8+i]=AddInverse(tempKey[43-i]);
        subKey[9+i]=MulInverse(tempKey[45-i]);
    }
    
    SecureMemoryWipe((void *) tempKey, subKeyNumber * sizeof(uint16_t));
}

//aux fun to clean sensitive information;
void SecureMemoryWipe(void *pointer, uint64_t size)
{
    volatile uint8_t *temp = (volatile uint8_t *)pointer;
    uint64_t i;
    for(i=0; i<size; i++)
    {
        temp[i] = 0;
    }
}


int KeyCheck(uint64_t *key)
{
    if(key == NULL)
        return 0;
    
    uint16_t *temp = (uint16_t *)key;
    for(int i=0; i<8; i++)
        if(temp[i] == 0)
            return 0;
    return 1;
}


void IdeaRoutine(uint16_t *message, uint16_t *subKey)
{
    for (int i = 0; i<roundNumber; i++)
    {
        Round(message, subKey);
        subKey += 6;
    }
    FinalRound(message, subKey);
    
}


//single encryption, return 0 in case of error
int IdeaEncrypt(uint64_t *message, uint64_t *key)
{
    if(!message || !key)
        return 0;
    
    uint16_t subKey[subKeyNumber];
    EncryptKeyCreate(key, subKey);
    IdeaRoutine((uint16_t *) message, subKey);
    
    SecureMemoryWipe((void *)subKey, subKeyNumber*sizeof(uint16_t));
    return 1;
}

//single decryption, return 0 in case of error
int IdeaDecrypt(uint64_t *message, uint64_t *key)
{
    if(!message || !key)
        return 0;
    
    uint16_t subKey[subKeyNumber];
    DecryptKeyCreate(key,subKey);
    IdeaRoutine((uint16_t *) message, subKey);
    
    SecureMemoryWipe((void *)subKey, subKeyNumber*sizeof(uint16_t));
    return 1;
}
