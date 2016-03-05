//
//  IdeaLib.h
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
//Version V.2.1
//complete set of fun that implement IDEA algorithm

#ifndef __IdeaLib__IdeaLib__
#define __IdeaLib__IdeaLib__
#include <stdint.h>

//single encryption, return 0 in case of error
int IdeaEncrypt(uint64_t *message,uint64_t *key);

//single decryption, return 0 in case of error
int IdeaDecrypt(uint64_t *message, uint64_t *key);

//return number of block processed
uint64_t IdeaCBCEncrypt(uint64_t *message, uint64_t *key, uint64_t nonce, uint64_t messageLength);

//return number of block processed
uint64_t IdeaCBCDecrypt(uint64_t *message, uint64_t *key, uint64_t nonce, uint64_t messageLength);

//return number of block processed
uint64_t IdeaPCBCEncrypt(uint64_t *message, uint64_t *key, uint64_t nonce, uint64_t messageLength);

//return number of block processed
uint64_t IdeaPCBCDecrypt(uint64_t *message, uint64_t *key, uint64_t nonce, uint64_t messageLength);

//return number of block processed
uint64_t IdeaCFBEncrypt(uint64_t *message, uint64_t *key, uint64_t nonce, uint64_t messageLength);

//return number of block processed
uint64_t IdeaCFBDecrypt(uint64_t *message, uint64_t *key, uint64_t nonce, uint64_t messageLength);

//return number of block processed
uint64_t IdeaOFB(uint64_t *message, uint64_t *key, uint64_t nonce, uint64_t messageLength);

//return number of block processed
uint64_t IdeaCTR(uint64_t *message, uint64_t *key, uint64_t nonce, uint64_t messageLength);

//return 1 if the key is a valid key to be used with IDEA
int KeyCheck(uint64_t *key);

//Internal status of IdeaCounterGen and IdeaIterativeGen random number generators.
//These generator are different, use a different instance of status for different generator;
typedef void* IdeaGeneratorStatus;

//initializes the satus of the generator
//keyUpdatePeriod = number of iteration before key update
//return NULL in case of error
IdeaGeneratorStatus IdeaGeneratorInit(uint64_t *key, uint64_t seed, uint64_t keyUpdatePeriod);

void IdeaGeneratorDelete(IdeaGeneratorStatus status);

//Return a cryptography safe random 64 bit integer
uint64_t IdeaIterativeGenInteger(IdeaGeneratorStatus status);

//Return a random 64 bit integer, this function is more efficient of IdeaIterativeGenInteger but it exposes
//a part of internal state of the generator.
//Use it for statistic application, not for cryptography.
uint64_t IdeaIterativeGenUnsafe(IdeaGeneratorStatus status);

//Fill a buffer of cryptography safe random bytes
int IdeaIterativeGenFill(IdeaGeneratorStatus status, uint8_t *buffer, unsigned long long length);

//Return a cryptography safe random 64 bit integer
uint64_t IdeaCounterGenInteger(IdeaGeneratorStatus status);

//Fill a buffer of cryptography safe random 64 bit integer.
int IdeaCounterGenFill(IdeaGeneratorStatus status, uint64_t *buffer, unsigned long long length);

#endif /* defined(__IdeaLib__IdeaLib__) */
