//
//  IDEA.c
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

#include "IDEA.h"
#include "Round.h"
#include "Keycreate.h"


void IdeaRoutine(uint16_t *message, uint16_t *subkey)
{

    for (int i = 0; i<7; i++)
    {
        Round(message, subkey);
        subkey += 6;
    }
    FinalRound(message, subkey);

}

//single encryption, return 0 in case of error
int IdeaEncrypt(uint64_t *message, uint64_t *key)
{
    if(!message || !key)
        return 0;

    uint16_t subkey[56];
    EncryptKeyCreate(key, subkey);
    IdeaRoutine((uint16_t *) message, subkey);


    return 1;
}

//single decryption, return 0 in case of error
int IdeaDecrypt(uint64_t *message, uint64_t *key)
{
    if(!message || !key)
        return 0;

    uint16_t subkey[56];
    DecryptKeyCreate(key,subkey);
    IdeaRoutine((uint16_t *) message, subkey);

    return 1;
}

//return number of block processed
uint64_t IdeaCBCEncrypt(uint64_t *message, uint64_t *key, const uint64_t nonce, const uint64_t messageLength)
{
    if(!message || !key)
        return 0;

    uint16_t subkey[56];
    EncryptKeyCreate(key, subkey);

    message[0] ^= nonce;
    IdeaRoutine((uint16_t *) message, subkey);

    uint64_t i=1;

    for(; i<messageLength; i++)
    {
        message[i] ^= message[i-1];
        IdeaRoutine((uint16_t *) (message+i), subkey);
    }

    return i;
}

//return number of block processed
uint64_t IdeaCBCDecrypt(uint64_t *message, uint64_t *key, uint64_t nonce, const uint64_t messageLength)
{
    {
        if(!message || !key)
            return 0;

        uint64_t temp;
        uint16_t subkey[56];
        DecryptKeyCreate(key, subkey);


        uint64_t i=0;

        for(; i<messageLength; i++)
        {
            temp = message[i];
            IdeaRoutine((uint16_t *) (message+i), subkey);
            message[i] ^= nonce;
            nonce = temp;
        }

        return i;
    }
}


//return number of block processed
uint64_t IdeaPCBCEncrypt(uint64_t *message, uint64_t *key, uint64_t nonce, const uint64_t messageLength)
{
    if(!message || !key)
        return 0;

    uint64_t temp;
    uint16_t subkey[56];
    EncryptKeyCreate(key, subkey);


    uint64_t i=0;

    for(; i<messageLength; i++)
    {
        temp = message[i];
        message[i] ^= message[i-1];
        IdeaRoutine((uint16_t *) (message+i), subkey);
        nonce = temp ^ message[i];
    }

    return i;
}

//return number of block processed
uint64_t IdeaPCBCDecrypt(uint64_t *message, uint64_t *key, uint64_t nonce, const uint64_t messageLength)
{
    {
        if(!message || !key)
            return 0;

        uint64_t temp;
        uint16_t subkey[56];
        DecryptKeyCreate(key, subkey);


        uint64_t i=0;

        for(; i<messageLength; i++)
        {
            temp = message[i];
            IdeaRoutine((uint16_t *) (message+i), subkey);
            message[i] ^= message[i-1];
            nonce = temp ^ message[i];
        }

        return i;
    }
}


//return number of block processed
uint64_t IdeaCFBEncrypt(uint64_t *message, uint64_t *key, uint64_t nonce, uint64_t messageLength)
{
    if(!message || !key)
        return 0;

    uint16_t subkey[56];
    EncryptKeyCreate(key, subkey);


    IdeaRoutine((uint16_t *) &nonce, subkey);
    message[0] ^= nonce;

    uint64_t i=1;

    for(; i<messageLength; i++)
    {
        nonce = message[i-1];
        IdeaRoutine((uint16_t *) &nonce, subkey);
        message[i] ^= nonce;
    }

    return i;
}

//return number of block processed
uint64_t IdeaCFBDecrypt(uint64_t *message, uint64_t *key, uint64_t nonce, const uint64_t messageLength)
{
    {
        if(!message || !key)
            return 0;

        uint64_t temp;
        uint16_t subkey[56];
        DecryptKeyCreate(key, subkey);


        uint64_t i=0;

        for(; i<messageLength; i++)
        {
            IdeaRoutine((uint16_t *) &nonce, subkey);
            temp = message[i];
            message[i] = nonce;
            nonce = temp;
        }

        return i;
    }
}


//return number of block processed
uint64_t IdeaOFBEncrypt(uint64_t *message, uint64_t *key, uint64_t nonce, uint64_t messageLength)
{
    if(!message || !key)
        return 0;

    uint16_t subkey[56];
    EncryptKeyCreate(key, subkey);


    IdeaRoutine((uint16_t *) &nonce, subkey);
    message[0] ^= nonce;

    uint64_t i=1;

    for(; i<messageLength; i++)
    {
        IdeaRoutine((uint16_t *) &nonce, subkey);
        message[i] ^= nonce;
    }

    return i;
}

//return number of block processed
uint64_t IdeaOFBDecrypt(uint64_t *message, uint64_t *key, uint64_t nonce, const uint64_t messageLength)
{
    if(!message || !key)
        return 0;

    uint16_t subkey[56];
    DecryptKeyCreate(key, subkey);


    IdeaRoutine((uint16_t *) &nonce, subkey);
    message[0] ^= nonce;

    uint64_t i=1;

    for(; i<messageLength; i++)
    {
        IdeaRoutine((uint16_t *) &nonce, subkey);
        message[i] ^= nonce;
    }

    return i;
}



//return number of block processed, destroy the nonce
uint64_t IdeaCTREncrypt(uint64_t *message, uint64_t *key, uint64_t *nonce, uint64_t messageLength)
{
    if(!message || !key)
        return 0;

    uint16_t subkey[56];
    EncryptKeyCreate(key, subkey);


    uint64_t i=0;

    for(; i<messageLength; i++)
    {
        IdeaRoutine((uint16_t *) nonce, subkey);
        message[i] ^= nonce[i];
        message++;
        nonce++;
    }

    return i;
}

//return number of block processed, destroy the nonce
uint64_t IdeaCTRDecrypt(uint64_t *message, uint64_t *key, uint64_t *nonce, const uint64_t messageLength)
{
    if(!message || !key)
        return 0;

    uint16_t subkey[56];
    DecryptKeyCreate(key, subkey);


    uint64_t i=0;

    for(; i<messageLength; i++)
    {
        IdeaRoutine((uint16_t *) nonce, subkey);
        message[i] ^= nonce[i];
        message++;
        nonce++;
    }

    return i;
}



























