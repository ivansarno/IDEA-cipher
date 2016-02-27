//
//  Keycreate.c
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

#include "Keycreate.h"

//add inverse operator
uint16_t AddInverse(uint16_t number)
{
    const uint32_t addModulus = 65536;
    return (uint16_t) addModulus-number;
}

//mul inverse operator
uint16_t MulInverse(uint16_t number)
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

void EncryptKeyCreate(uint64_t *key, uint16_t *subKey)
{

    uint64_t *temp = (uint64_t *) subKey;
    int i;
    temp[0] = key[0];
    temp[1] = key[1];
    for(i = 3; i < 14; i+=2)//25 bit left shift
    {
        temp[i-1] = ((temp[i-3]<<25)) | ((temp[i-2]>>39));
        temp[i] = ((temp[i-2]<<25)) | ((temp[i-3]>>39));
    }

}

//decryption subkey generator
void DecryptKeyCreate(uint64_t *key,uint16_t *subKey)
{
    uint16_t tempKey[56];
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


    for(i=0;i<48;i+=6)
    {
        subKey[4+i]=tempKey[46-i];
        subKey[5+i]=tempKey[47-i];
        subKey[6+i]=MulInverse(tempKey[42-i]);
        subKey[7+i]=AddInverse(tempKey[44-i]);
        subKey[8+i]=AddInverse(tempKey[43-i]);
        subKey[9+i]=MulInverse(tempKey[45-i]);
    }
}

