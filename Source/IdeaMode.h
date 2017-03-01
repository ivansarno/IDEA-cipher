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
//Version V.3.0
////This file contains the implementation of the block encryption modes for IDEA

#ifndef __IdeaLib__IdeaLib__
#define __IdeaLib__IdeaLib__
#include <stdint.h>
#include <stddef.h>


//return number of block processed
size_t IdeaCBCEncrypt(uint64_t *message, uint64_t *key, uint64_t nonce, size_t messageLength);

//return number of block processed
size_t IdeaCBCDecrypt(uint64_t *message, uint64_t *key, uint64_t nonce, size_t messageLength);

//return number of block processed
size_t IdeaPCBCEncrypt(uint64_t *message, uint64_t *key, uint64_t nonce, size_t messageLength);

//return number of block processed
size_t IdeaPCBCDecrypt(uint64_t *message, uint64_t *key, uint64_t nonce, size_t messageLength);

//return number of block processed
size_t IdeaCFBEncrypt(uint64_t *message, uint64_t *key, uint64_t nonce, size_t messageLength);

//return number of block processed
size_t IdeaCFBDecrypt(uint64_t *message, uint64_t *key, uint64_t nonce, size_t messageLength);

//return number of block processed
size_t IdeaOFB(uint64_t *message, uint64_t *key, uint64_t nonce, size_t messageLength);

//return number of block processed
size_t IdeaCTR(uint64_t *message, uint64_t *key, uint64_t nonce, size_t messageLength);

#endif /* defined(__IdeaLib__IdeaLib__) */
