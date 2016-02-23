//
//  Keycreate.h
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
//Version V.1.4
/*
implementation of key schedule of IDEA, subkey array is allocated in the caller function.
See official algorithm reference for more details
*/

#ifndef __IDEA__Keycreate__
#define __IDEA__Keycreate__
#include <stdint.h>

void EncryptKeyCreate(uint64_t *keyp, uint16_t *subKey);
void DecryptKeyCreate(uint64_t *key,uint16_t *subKey);

#endif /* defined(__IDEA__Keycreate__) */
