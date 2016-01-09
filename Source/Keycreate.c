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
//Version V.1.3
/*
implementation of key shedule of IDEA, subkey array is allocated in the caller function.
See official algorithm reference for more details
*/

#include "Keycreate.h"
#define mulmod 65537
#define mod 65536


/*
the rotation of 25 bits of the key is implemented by copying elements of the array for the first 16 bits,
shift the last 9 bits and adding the remaining digits to next element
*/


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

    key[7]=(key[7]<<9)+temp;

}

//add inverse operator
uint16_t add_inverse(uint16_t a)
{

    return (uint16_t) mod-a;
}

//mul inverse operator
uint16_t mul_inverse(uint16_t number, uint32_t modulus)
{
    if (modulus == 0)
    {
        return 0;
    }
    
    
    int j = 1;
    int64_t result, temp, intermediate;
    int64_t buffer[35];
    
    buffer[0] = number;
    buffer[1] = modulus;
    
    while(buffer[j] > 0) //find intermediate values of greatest common divisor
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
    else return (uint16_t) (modulus + result);
}


void keycreate(uint16_t *key, uint16_t *subkey)
{
    int i,j;
    for(i=0;i<=48;i+=8)
    {
        for(j=0;j<8;j++)
            subkey[i+j]=key[j];
        keyrotate(key);
    }
}

//decryption subkey generator
void decrypt_keycreate(uint16_t *key,uint16_t *subkey)
{
    uint16_t tempkey[56];
    int i;

    keycreate(key,tempkey);
    subkey[0]=mul_inverse(tempkey[48],mulmod);
    subkey[1]=add_inverse(tempkey[49]);
    subkey[2]=add_inverse(tempkey[50]);
    subkey[3]=mul_inverse(tempkey[51],mulmod);

    //preswapped for final operation
    uint16_t t=tempkey[1];
    tempkey[1]=tempkey[2];
    tempkey[2]=t;


    for(i=0;i<48;i+=6)
    {
        subkey[4+i]=tempkey[46-i];
        subkey[5+i]=tempkey[47-i];
        subkey[6+i]=mul_inverse(tempkey[42-i],mulmod);
        subkey[7+i]=add_inverse(tempkey[44-i]);
        subkey[8+i]=add_inverse(tempkey[43-i]);
        subkey[9+i]=mul_inverse(tempkey[45-i],mulmod);
    }
}



