//
//  IdeaGenerators.c
//  IDEA
//
//  Created by ivan sarno on 05/03/16.
//  Copyright © 2016 ivan sarno.
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

#include <stdio.h>
#include <stdlib.h>
#include "IdeaLib.h"
#include "KeyCreation.h"


typedef struct
{
    uint64_t seed;
    uint64_t key[2];
    uint64_t keyUpdateCounter;
    uint64_t keyUpdatePeriod;
    uint8_t bytePositionCounter;
} InternalStatus;

IdeaGeneratorStatus IdeaGeneratorInit(uint64_t *key, uint64_t seed, uint64_t keyUpdatePeriod)
{
    if(keyUpdatePeriod == 0)
        return NULL;
    
    InternalStatus *status = (InternalStatus *) malloc(sizeof(InternalStatus));
    status->key[0] = key[0];
    status->key[1] = key[1];
    status->seed = seed;
    status->keyUpdatePeriod = keyUpdatePeriod;
    status->keyUpdateCounter = 0;
    status->bytePositionCounter = seed % 8;// select the position of the first output byte based on seed
    
    return (IdeaGeneratorStatus) status;
}

void IdeaGeneratorDelete(IdeaGeneratorStatus status)
{
    SecureMemoryWipe(status, sizeof(InternalStatus));
    free(status);
}

static inline void IterativeGenUpdateStatus(InternalStatus *status)
{
    IdeaEncrypt(&status->seed, status->key);
    status->keyUpdateCounter = (status->keyUpdateCounter+1) % status->keyUpdatePeriod;
    if (status->keyUpdateCounter % status->keyUpdatePeriod == 0)
    {
        status->key[0] ^= status->seed;
        status->key[1] ^= status->seed;
    }
}

static inline uint8_t IterativeGenOutput(InternalStatus *status)
{
    uint8_t* temp = (uint8_t*) &status->seed;
    status->bytePositionCounter = (status->bytePositionCounter + 1) % 8;
    return temp[status->bytePositionCounter];
}

uint64_t IdeaIterativeGenInteger(IdeaGeneratorStatus status)
{
    uint8_t result[8];
    for(int i=0; i<8; i++)
    {
        IterativeGenUpdateStatus(status);
        result[i] = IterativeGenOutput(status);
    }
    return *((uint64_t *) result);
}

uint64_t IdeaIterativeGenUnsafe(IdeaGeneratorStatus status)
{
    IterativeGenUpdateStatus(status);
    return ((InternalStatus *) status)->seed;
}

int IdeaIterativeGenFill(IdeaGeneratorStatus status, uint8_t *buffer, unsigned long long length)
{
    if(length == 0 || buffer == NULL)
        return 0;
    
    for(unsigned long long i=0; i<length; i++)
    {
        IterativeGenUpdateStatus(status);
        buffer[i] = IterativeGenOutput(status);
    }
    return 1;
}

static inline uint64_t CounterUpdate(InternalStatus *status)
{
    status->seed++;
    status->keyUpdateCounter = (status->keyUpdateCounter+1) % status->keyUpdatePeriod;
    if (status->keyUpdateCounter % status->keyUpdatePeriod == 0)
    {
        status->key[0] ^= status->seed;
        status->key[1] ^= status->seed;
    }
    
    uint64_t result = status->seed;
    IdeaEncrypt(&result, status->key);
    
    return result;
}

uint64_t IdeaCounterGenInteger(IdeaGeneratorStatus status)
{
    return CounterUpdate(status);
}

int IdeaCounterGenFill(IdeaGeneratorStatus status, uint64_t *buffer, unsigned long long length)
{
    if(length == 0 || buffer == NULL)
        return 0;
    
    for(unsigned long long i=0; i<length; i++)
    {
        IterativeGenUpdateStatus(status);
        buffer[i] = CounterUpdate(status);
    }
    return 1;
}







