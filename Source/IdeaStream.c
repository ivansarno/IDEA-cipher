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
//Version V.3.0

#include "IdeaStream.h"
#include <stdlib.h>
#include "IdeaCore.h"


typedef struct
{
    uint16_t subKey[56];
    uint64_t nonce;
}   StreamInternalStatus;

IdeaEncryptStreamStatus IdeaStreamEncryptInit(uint64_t *key, uint64_t nonce)
{
    StreamInternalStatus *status = (StreamInternalStatus *) malloc(sizeof(StreamInternalStatus));
    EncryptKeyCreate(key, status->subKey);
    status->nonce = nonce;
    IdeaEncryptStreamStatus s = {.privateData = status};
    return s;
}

IdeaDecryptStreamStatus IdeaStreamDecryptInit(uint64_t *key, uint64_t nonce)
{
    StreamInternalStatus *status = (StreamInternalStatus *) malloc(sizeof(StreamInternalStatus));
    DecryptKeyCreate(key, status->subKey);
    status->nonce = nonce;
    IdeaDecryptStreamStatus s = {.privateData = status};
    return s;
}

void IdeaStreamEncryptDelete(IdeaEncryptStreamStatus status)
{
    SecureMemoryWipe(status.privateData, sizeof(StreamInternalStatus));
    free(status.privateData);
}

void IdeaStreamDecryptDelete(IdeaDecryptStreamStatus status)
{
    SecureMemoryWipe(status.privateData, sizeof(StreamInternalStatus));
    free(status.privateData);
}

void IdeaStreamCBCEncrypt(uint64_t *message, IdeaEncryptStreamStatus status)
{
    StreamInternalStatus *iStatus = (StreamInternalStatus *) status.privateData;
    *message ^= iStatus->nonce;
    IdeaRoutine((uint16_t *) message, iStatus->subKey);
    iStatus->nonce = *message;
}

void IdeaStreamCBCDecrypt(uint64_t *message, IdeaDecryptStreamStatus status)
{
    StreamInternalStatus *iStatus = (StreamInternalStatus *) status.privateData;
    uint64_t temp = *message;
    IdeaRoutine((uint16_t *) message, iStatus->subKey);
    *message ^= iStatus->nonce;
    iStatus->nonce = temp;
}

void IdeaStreamPCBCEncrypt(uint64_t *message, IdeaEncryptStreamStatus status)
{
    StreamInternalStatus *iStatus = (StreamInternalStatus *) status.privateData;
    uint64_t temp = *message;
    *message ^= iStatus->nonce;
    IdeaRoutine((uint16_t *) message, iStatus->subKey);
    iStatus->nonce = *message ^ temp;
}

void IdeaStreamPCBCDecrypt(uint64_t *message, IdeaDecryptStreamStatus status)
{
    StreamInternalStatus *iStatus = (StreamInternalStatus *) status.privateData;
    uint64_t temp = *message;
    IdeaRoutine((uint16_t *) message, iStatus->subKey);
    *message ^= iStatus->nonce;
    iStatus->nonce = temp ^ *message;
}

void IdeaStreamCFBEncrypt(uint64_t *message, IdeaEncryptStreamStatus status)
{
    StreamInternalStatus *iStatus = (StreamInternalStatus *) status.privateData;
    IdeaRoutine((uint16_t *) &(iStatus->nonce), iStatus->subKey);
    *message ^= iStatus->nonce;
    iStatus->nonce = *message;
}

void IdeaStreamCFBDecrypt(uint64_t *message, IdeaEncryptStreamStatus status)
{
    StreamInternalStatus *iStatus = (StreamInternalStatus *) status.privateData;
    IdeaRoutine((uint16_t *) &(iStatus->nonce), iStatus->subKey);
    uint64_t temp = *message ^ iStatus->nonce;
    iStatus->nonce = *message;
    *message = temp;
}

void IdeaStreamOFB(uint64_t *message, IdeaEncryptStreamStatus status)
{
    StreamInternalStatus *iStatus = (StreamInternalStatus *) status.privateData;
    IdeaRoutine((uint16_t *) &(iStatus->nonce), iStatus->subKey);
    *message ^= iStatus->nonce;
}

void IdeaStreamCTR(uint64_t *message, IdeaEncryptStreamStatus status)
{
    StreamInternalStatus *iStatus = (StreamInternalStatus *) status.privateData;
    IdeaRoutine((uint16_t *) &(iStatus->nonce), iStatus->subKey);
    *message ^= iStatus->nonce;
    iStatus->nonce++;
}
