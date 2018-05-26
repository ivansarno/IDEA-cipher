//
//  IdeaCore.h
//  IDEA
//
//  Created by ivan sarno on 23/02/17.
//  Copyright © 2014 ivan sarno.
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
//This file contains the core functionalities of IdeaLib
#ifndef IdeaCore_h
#define IdeaCore_h
#include <stdint.h>

//key generation fun, generate subkeys from the key
void EncryptKeyCreate(uint64_t *key, uint16_t *subKey);
void DecryptKeyCreate(uint64_t *key, uint16_t *subKey);

//single encryption, return 0 in case of error
int IdeaEncrypt(uint64_t *message,uint64_t *key);

//single decryption, return 0 in case of error
int IdeaDecrypt(uint64_t *message, uint64_t *key);

//process single block of data, use encryption subkey to encrypt or decryption subkey to decrypt
void IdeaRoutine(uint16_t *message, uint16_t *subKey);

//aux fun to clean sensitive information, take size in bytes;
void SecureMemoryWipe(void *pointer, uint64_t size);

//return 1 if the key is a valid key to be used with IDEA
int KeyCheck(uint64_t *key);


#endif /* IdeaCore_h */
