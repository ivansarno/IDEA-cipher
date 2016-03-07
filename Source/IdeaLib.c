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
//Version V.2.2

#include "IdeaLib.h"
#include "Round.h"
#include "KeyCreation.h"

static const int roundNumber = 7;
static const int subKeyNumber = 56;

static inline void IdeaRoutine(uint16_t *message, uint16_t *subKey)
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
    EncryptKeyCreate(key, (uint64_t *) subKey);
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

//return number of block processed
uint64_t IdeaCBCEncrypt(uint64_t *message, uint64_t *key, uint64_t nonce, uint64_t messageLength)
{
    if(!message || !key)
        return 0;

    uint16_t subKey[subKeyNumber];
    EncryptKeyCreate(key, (uint64_t *) subKey);

    message[0] ^= nonce;
    IdeaRoutine((uint16_t *) message, subKey);

    uint64_t i;

    for(i=1; i<messageLength; i++)
    {
        message[i] ^= message[i-1];
        IdeaRoutine((uint16_t *) (message+i), subKey);
    }
    
    SecureMemoryWipe((void *)subKey, subKeyNumber*sizeof(uint16_t));
    return i;
}

//return number of block processed
uint64_t IdeaCBCDecrypt(uint64_t *message, uint64_t *key, uint64_t nonce, uint64_t messageLength)
{
    {
        if(!message || !key)
            return 0;

        uint64_t temp;
        uint16_t subKey[subKeyNumber];
        DecryptKeyCreate(key, subKey);


        uint64_t i;

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
uint64_t IdeaPCBCEncrypt(uint64_t *message, uint64_t *key, uint64_t nonce, uint64_t messageLength)
{
    if(!message || !key)
        return 0;

    uint64_t temp;
    uint16_t subKey[subKeyNumber];
    EncryptKeyCreate(key, (uint64_t *)subKey);


    uint64_t i;

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
uint64_t IdeaPCBCDecrypt(uint64_t *message, uint64_t *key, uint64_t nonce, uint64_t messageLength)
{
    {
        if(!message || !key)
            return 0;

        uint64_t temp;
        uint16_t subKey[subKeyNumber];
        DecryptKeyCreate(key, subKey);


        uint64_t i=0;

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
uint64_t IdeaCFBEncrypt(uint64_t *message, uint64_t *key, uint64_t nonce, uint64_t messageLength)
{
    if(!message || !key)
        return 0;

    uint16_t subKey[subKeyNumber];
    EncryptKeyCreate(key, (uint64_t *)subKey);


    IdeaRoutine((uint16_t *) &nonce, subKey);
    message[0] ^= nonce;

    uint64_t i;

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
uint64_t IdeaCFBDecrypt(uint64_t *message, uint64_t *key, uint64_t nonce, uint64_t messageLength)
{
    {
        if(!message || !key)
            return 0;

        uint64_t temp;
        uint16_t subKey[subKeyNumber];
        EncryptKeyCreate(key, (uint64_t *)subKey);


        uint64_t i;

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
uint64_t IdeaOFB(uint64_t *message, uint64_t *key, uint64_t nonce, uint64_t messageLength)
{
    if(!message || !key)
        return 0;

    uint16_t subKey[subKeyNumber];
    EncryptKeyCreate(key, (uint64_t *)subKey);


    uint64_t i;

    for(i=0; i<messageLength; i++)
    {
        IdeaRoutine((uint16_t *) &nonce, subKey);
        message[i] ^= nonce;
    }

    SecureMemoryWipe((void *)subKey, subKeyNumber*sizeof(uint16_t));
    return i;
}


//return number of block processed
uint64_t IdeaCTR(uint64_t *message, uint64_t *key, uint64_t nonce, uint64_t messageLength)
{
    if(!message || !key)
        return 0;

    uint16_t subKey[subKeyNumber];
    EncryptKeyCreate(key, (uint64_t *)subKey);
    uint64_t tempNonce;

    uint64_t i;

    for(i=0; i<messageLength; i++)
    {
        tempNonce = nonce;
        IdeaRoutine((uint16_t *) &tempNonce, subKey);
        *message ^= tempNonce;
        message++;
        nonce++;
    }

    SecureMemoryWipe((void *)subKey, subKeyNumber*sizeof(uint16_t));
    return i;
}

int KeyCheck(uint64_t *key)
{
    uint16_t *temp = (uint16_t *)key;
    for(int i=0; i<8; i++)
        if(temp[i] == 0)
            return 0;
    return 1;
}




























