//
//  KeyCreation.c
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
//Version V.2.0
/*
implementation of key schedule of IDEA, subkey array is allocated in the caller function.
See official algorithm reference for more details
*/

#include "KeyCreation.h"

//add inverse operator
static inline uint16_t AddInverse(uint16_t number)
{
    const uint32_t addModulus = 65536;
    return (uint16_t) addModulus-number;
}

//mul inverse operator
static uint16_t MulInverse(uint16_t number)
{
    const uint32_t mulModulus = 65537;
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

//eliminare
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
    
    key[7]=(key[7]<<9)+temp;/*
    uint64_t temp1=key[0];
    uint64_t temp2=key[1];
    key[0] = (temp1<<25) | temp2>>39;
    key[1] = (temp2<<25) | temp1>>39;*/
    
}

void EncryptKeyCreate(uint64_t *key, uint64_t *subKey)
{
    uint64_t keyc[2];
    keyc[0] = key[0];
    keyc[1] = key[1];
    
    for(int i=0, j=0; i<7; i++, j+=2)
    {
        subKey[j]=keyc[0];
        subKey[j+1] = keyc[1];
        keyrotate((uint16_t *)keyc);
    }
}

//decryption subkey generator
void DecryptKeyCreate(uint64_t *key,uint16_t *subKey)
{
    uint16_t tempKey[56];
    int i;

    EncryptKeyCreate(key,(uint64_t *)tempKey);
    subKey[0]=MulInverse(tempKey[48]);
    subKey[1]=AddInverse(tempKey[49]);
    subKey[2]=AddInverse(tempKey[50]);
    subKey[3]=MulInverse(tempKey[51]);

    //preswapped for final operation
    uint16_t t=tempKey[1];
    tempKey[1]=tempKey[2];
    tempKey[2]=t;


    for(i=0;i<48;i+=6)
    {
        subKey[4+i]=tempKey[46-i];
        subKey[5+i]=tempKey[47-i];
        subKey[6+i]=MulInverse(tempKey[42-i]);
        subKey[7+i]=AddInverse(tempKey[44-i]);
        subKey[8+i]=AddInverse(tempKey[43-i]);
        subKey[9+i]=MulInverse(tempKey[45-i]);
    }

    SecureMemoryWipe((void *) tempKey, 112);
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
