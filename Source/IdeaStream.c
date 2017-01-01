//
//  IdeaStream.c
//  IDEA
//
//  Created by ivan sarno on 22/03/16.
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

#include "IdeaLib.h"
#include "KeyCreation.h"
#include <stdlib.h>


typedef struct
{
    uint16_t subKey[56];
    uint64_t nonce;
}   StreamInternalStatus;

IdeaStreamStatus IdeaStreamEncryptionInit(uint64_t *key, uint64_t nonce)
{
    if(!key)
        return NULL;
    if(!KeyCheck(key))
        return NULL;
    
    StreamInternalStatus *status = (StreamInternalStatus *) malloc(sizeof(StreamInternalStatus));
    EncryptKeyCreate(key, (uint64_t *)status->subKey);
    status->nonce = nonce;
    return status;
}

IdeaStreamStatus IdeaStreamDecryptionInit(uint64_t *key, uint64_t nonce)
{
    if(!key)
        return NULL;
    if(!KeyCheck(key))
        return NULL;
    
    StreamInternalStatus *status = (StreamInternalStatus *) malloc(sizeof(StreamInternalStatus));
    DecryptKeyCreate(key, status->subKey);
    status->nonce = nonce;
    return status;
}

void IdeaStreamStatusDelete(IdeaStreamStatus status)
{
    SecureMemoryWipe(status, sizeof(StreamInternalStatus));
    free(status);
}

void IdeaStreamCBCEncrypt(uint64_t *message, IdeaStreamStatus status)
{
    StreamInternalStatus *iStatus = (StreamInternalStatus *) status;
    *message ^= iStatus->nonce;
    IdeaRoutine((uint16_t *) message, iStatus->subKey);
    iStatus->nonce = *message;
}

void IdeaStreamCBCDecrypt(uint64_t *message, IdeaStreamStatus status)
{
    StreamInternalStatus *iStatus = (StreamInternalStatus *) status;
    uint64_t temp = *message;
    IdeaRoutine((uint16_t *) message, iStatus->subKey);
    *message ^= iStatus->nonce;
    iStatus->nonce = temp;
}

void IdeaStreamPCBCEncrypt(uint64_t *message, IdeaStreamStatus status)
{
    StreamInternalStatus *iStatus = (StreamInternalStatus *) status;
    uint64_t temp = *message;
    *message ^= iStatus->nonce;
    IdeaRoutine((uint16_t *) message, iStatus->subKey);
    iStatus->nonce = *message ^ temp;
}

void IdeaStreamPCBCDecrypt(uint64_t *message, IdeaStreamStatus status)
{
    StreamInternalStatus *iStatus = (StreamInternalStatus *) status;
    uint64_t temp = *message;
    IdeaRoutine((uint16_t *) message, iStatus->subKey);
    *message ^= iStatus->nonce;
    iStatus->nonce = temp ^ *message;
}

void IdeaStreamCFBEncrypt(uint64_t *message, IdeaStreamStatus status)
{
    StreamInternalStatus *iStatus = (StreamInternalStatus *) status;
    IdeaRoutine((uint16_t *) &(iStatus->nonce), iStatus->subKey);
    *message ^= iStatus->nonce;
    iStatus->nonce = *message;
}

void IdeaStreamCFBDecrypt(uint64_t *message, IdeaStreamStatus status)
{
    StreamInternalStatus *iStatus = (StreamInternalStatus *) status;
    IdeaRoutine((uint16_t *) &(iStatus->nonce), iStatus->subKey);
    uint64_t temp = *message ^ iStatus->nonce;
    iStatus->nonce = *message;
    *message = temp;
}

void IdeaStreamOFB(uint64_t *message, IdeaStreamStatus status)
{
    StreamInternalStatus *iStatus = (StreamInternalStatus *) status;
    IdeaRoutine((uint16_t *) &(iStatus->nonce), iStatus->subKey);
    *message ^= iStatus->nonce;
}

void IdeaStreamCTR(uint64_t *message, IdeaStreamStatus status)
{
    StreamInternalStatus *iStatus = (StreamInternalStatus *) status;
    IdeaRoutine((uint16_t *) &(iStatus->nonce), iStatus->subKey);
    *message ^= iStatus->nonce;
    iStatus->nonce++;
}
