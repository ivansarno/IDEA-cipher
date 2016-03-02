//
//  IdeaLib.h
//  IdeaLib
//
//  Created by ivan sarno on 02/12/14.
//  Copyright (c) 2014 ivan sarno.
/*
 This file is part of IdeaCipher library
 IdeaCipher  is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 IdeaCipher  is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with IdeaCipher ; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
 USA
 */
//Version V.2.0
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


#endif /* defined(__IdeaLib__IdeaLib__) */
