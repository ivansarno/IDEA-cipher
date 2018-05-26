//
//  IdeaLib.c
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
//Version V.3.1

#include "IdeaCore.h"
#include <stddef.h>
#include <stdlib.h>


#define roundNumber 7
#define subKeyNumber 56

//This file implements of the block encryption modes

//return number of block processed
size_t IdeaCBCEncrypt(uint64_t *message, uint64_t *key, uint64_t nonce, size_t messageLength)
{
    if(!message || !key)
        return 0;

    uint16_t subKey[subKeyNumber];
    EncryptKeyCreate(key, subKey);

    message[0] ^= nonce;
    IdeaRoutine((uint16_t *) message, subKey);

    size_t i;

    for(i=1; i<messageLength; i++)
    {
        message[i] ^= message[i-1];
        IdeaRoutine((uint16_t *) (message+i), subKey);
    }
    
    SecureMemoryWipe((void *)subKey, subKeyNumber*sizeof(uint16_t));
    return i;
}

//return number of block processed
size_t IdeaCBCDecrypt(uint64_t *message, uint64_t *key, uint64_t nonce, size_t messageLength)
{
    {
        if(!message || !key)
            return 0;

        uint64_t temp;
        uint16_t subKey[subKeyNumber];
        DecryptKeyCreate(key, subKey);


        size_t i;

        for(i=0; i<messageLength; i++)
        {
            temp = message[i];
            IdeaRoutine((uint16_t *) (message+i), subKey);
            message[i] ^= nonce;
            nonce = temp;
        }

        SecureMemoryWipe((void *)subKey, subKeyNumber*sizeof(uint16_t));
        return i;
    }
}


//return number of block processed
size_t IdeaPCBCEncrypt(uint64_t *message, uint64_t *key, uint64_t nonce, size_t messageLength)
{
    if(!message || !key)
        return 0;

    uint64_t temp;
    uint16_t subKey[subKeyNumber];
    EncryptKeyCreate(key, subKey);


    size_t i;

    for(i=0; i<messageLength; i++)
    {
        temp = message[i];
        message[i] ^= nonce;
        IdeaRoutine((uint16_t *) (message+i), subKey);
        nonce = temp ^ message[i];
    }

    SecureMemoryWipe((void *)subKey, subKeyNumber*sizeof(uint16_t));
    return i;
}

//return number of block processed
size_t IdeaPCBCDecrypt(uint64_t *message, uint64_t *key, uint64_t nonce, size_t messageLength)
{
    {
        if(!message || !key)
            return 0;

        uint64_t temp;
        uint16_t subKey[subKeyNumber];
        DecryptKeyCreate(key, subKey);


        size_t i=0;

        for(; i<messageLength; i++)
        {
            temp = message[i];
            IdeaRoutine((uint16_t *) (message+i), subKey);
            message[i] ^= nonce;
            nonce = temp ^ message[i];
        }

        SecureMemoryWipe((void *)subKey, subKeyNumber*sizeof(uint16_t));
        return i;
    }
}


//return number of block processed
size_t IdeaCFBEncrypt(uint64_t *message, uint64_t *key, uint64_t nonce, size_t messageLength)
{
    if(!message || !key)
        return 0;

    uint16_t subKey[subKeyNumber];
    EncryptKeyCreate(key, subKey);


    IdeaRoutine((uint16_t *) &nonce, subKey);
    message[0] ^= nonce;

    size_t i;

    for(i=1; i<messageLength; i++)
    {
        nonce = message[i-1];
        IdeaRoutine((uint16_t *) &nonce, subKey);
        message[i] ^= nonce;
    }

    SecureMemoryWipe((void *)subKey, subKeyNumber*sizeof(uint16_t));
    return i;
}

//return number of block processed
size_t IdeaCFBDecrypt(uint64_t *message, uint64_t *key, uint64_t nonce, size_t messageLength)
{
    {
        if(!message || !key)
            return 0;

        uint64_t temp;
        uint16_t subKey[subKeyNumber];
        EncryptKeyCreate(key, subKey);


        size_t i;

        for(i=0; i<messageLength; i++)
        {
            IdeaRoutine((uint16_t *) &nonce, subKey);
            temp = message[i];
            message[i] ^= nonce;
            nonce = temp;
        }

        SecureMemoryWipe((void *)subKey, subKeyNumber*sizeof(uint16_t));
        return i;
    }
}


//return number of block processed
size_t IdeaOFB(uint64_t *message, uint64_t *key, uint64_t nonce, size_t messageLength)
{
    if(!message || !key)
        return 0;

    uint16_t subKey[subKeyNumber];
    EncryptKeyCreate(key, subKey);


    size_t i;

    for(i=0; i<messageLength; i++)
    {
        IdeaRoutine((uint16_t *) &nonce, subKey);
        message[i] ^= nonce;
    }

    SecureMemoryWipe((void *)subKey, subKeyNumber*sizeof(uint16_t));
    return i;
}


//return number of block processed
size_t IdeaCTR(uint64_t *message, uint64_t *key, uint64_t nonce, size_t messageLength)
{
    if(!message || !key)
        return 1;
    
    uint16_t subKey[subKeyNumber];
    EncryptKeyCreate(key, subKey);
    
    
    #pragma omp parallel for
    for(size_t i=0; i<messageLength; i++)
    {
        uint64_t tempNonce = nonce + i;
        IdeaRoutine((uint16_t *) &tempNonce, subKey);
        *(message+i) ^= tempNonce;
    }
    
    SecureMemoryWipe((void *)subKey, subKeyNumber*sizeof(uint16_t));
    return messageLength;
}

//return a pointer to blocks processed or NULL
uint64_t* IdeaCTRRandomAccess(const uint64_t *ciphertext, uint64_t *key, uint64_t nonce, size_t position, size_t length)
{
    nonce += position;
    uint64_t *message = malloc(sizeof(uint64_t) * length);
    for(size_t i=0; i<length; i++)
        message[i] = i + nonce;
    if(IdeaCTR(message, key, nonce, length) != length)
    {
        free(message);
        return NULL;
    }
    
    for(size_t i=0; i<length; i++)
        message[i] ^= ciphertext[i+position];
    
    return message;
}

//return the block decrypted
uint64_t IdeaCTRRandomAccessSingle(const uint64_t *ciphertext, uint64_t *key, uint64_t nonce, size_t position)
{
    nonce += position;
    IdeaEncrypt(&nonce, key);
    return ciphertext[position] ^ nonce;
}




























