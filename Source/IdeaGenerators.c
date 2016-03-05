//
//  IdeaGenerators.c
//  IDEA
//
//  Created by ivan sarno on 05/03/16.
//  Copyright © 2016 ivan sarno. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "IdeaLib.h"
#include "KeyCreation.h"


typedef struct
{
    uint64_t seed;
    uint64_t key[2];
    uint64_t keyUpdateCounter;
    uint64_t keyUpdateMod;
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
    status->keyUpdateMod = keyUpdatePeriod;
    status->keyUpdateCounter = 0;
    status->bytePositionCounter = seed % 8;
    
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
    status->keyUpdateCounter = (status->keyUpdateCounter+1) % status->keyUpdateMod;
    if (status->keyUpdateCounter % status->keyUpdateMod == 0)
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
        return 1;
    
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
    status->keyUpdateCounter = (status->keyUpdateCounter+1) % status->keyUpdateMod;
    if (status->keyUpdateCounter % status->keyUpdateMod == 0)
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
        return 1;
    
    for(unsigned long long i=0; i<length; i++)
    {
        IterativeGenUpdateStatus(status);
        buffer[i] = CounterUpdate(status);
    }
    return 1;
}







