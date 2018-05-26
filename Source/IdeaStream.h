//
//  IdeaStream.h
//  IDEA
//
//  Created by ivan sarno on 23/02/17.
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
//Version V.3.1

#ifndef IdeaStream_h
#define IdeaStream_h

#include <stdint.h>
/*These functions provides the encryption modes on singles blocks from a stream*/

//Internal status of the stream processor
typedef struct {void* privateData;} IdeaEncryptStreamStatus;
typedef struct {void* privateData;} IdeaDecryptStreamStatus;


IdeaEncryptStreamStatus IdeaStreamEncryptInit(uint64_t *key, uint64_t nonce);

IdeaDecryptStreamStatus IdeaStreamDecryptInit(uint64_t *key, uint64_t nonce);

//initializes a stream status for CTR mode to start from a block != 0
IdeaEncryptStreamStatus IdeaStreamCTRRandomAccessInit(uint64_t *key, uint64_t nonce, uint64_t position);

void IdeaStreamEncryptDelete(IdeaEncryptStreamStatus status);
void IdeaStreamDecryptDelete(IdeaDecryptStreamStatus status);

void IdeaStreamCBCEncrypt(uint64_t *message, IdeaEncryptStreamStatus status);

void IdeaStreamCBCDecrypt(uint64_t *message, IdeaDecryptStreamStatus status);

void IdeaStreamPCBCEncrypt(uint64_t *message, IdeaEncryptStreamStatus status);

void IdeaStreamPCBCDecrypt(uint64_t *message, IdeaDecryptStreamStatus status);

void IdeaStreamCFBEncrypt(uint64_t *message, IdeaEncryptStreamStatus status);

void IdeaStreamCFBDecrypt(uint64_t *message, IdeaEncryptStreamStatus status);

void IdeaStreamOFB(uint64_t *message, IdeaEncryptStreamStatus status);

void IdeaStreamCTR(uint64_t *message, IdeaEncryptStreamStatus status);


#endif /* IdeaStream_h */
