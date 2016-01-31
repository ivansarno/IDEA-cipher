//
//  IDEA.c
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

#include "IDEA.h"
#include <string.h>



//single instance encrypt fun, return 0 in case of error
int IDEA_single_encrypt(uint16_t *message, uint16_t *key)
{
	if(!message || !key)
		return 0;

    uint16_t key2[8];
    memcpy(key2, key, 16);
    uint16_t subkey[56];
    keycreate(key2,subkey);
    int i;
    for(i=0;i<7;i++)
        Round(message, subkey+(6*i));
    Finalround(message, subkey+(6*i));

	return 1;
}

//single instance decrypt fun, return 0 in case of error
int IDEA_single_decrypt(uint16_t *message, uint16_t *key)
{
	if(!message || !key)
		return 0;

    uint16_t key2[8];
    memcpy(key2, key, 16);
    uint16_t subkey[56];
    decrypt_keycreate(key2,subkey);
    int i;
    for(i=0;i<7;i++)
        Round(message, subkey+(6*i));
    Finalround(message, subkey+(6*i));

	return 1;
}

//single instance encrypt or decript fun with extern generation of subkey, to reuse the same
void IDEA_crypt(uint16_t *message, uint16_t *subkey)
{

	int i;
	for (i = 0; i<7; i++)
		Round(message, subkey + (6 * i));
	Finalround(message, subkey + (6 * i));

}

//multi instance encrypt fun to process more blocks with same key, return number of blocks processed successfully, NO CBC
unsigned long IDEA_multi_encrypt(uint16_t *message, uint16_t *key, const unsigned long blocks)
{
	if(!message || !key || blocks < 1)
		return 0;

  uint16_t key2[8];
  memcpy(key2, key, 16);
  uint16_t subkey[56];
	keycreate(key2, subkey);
	unsigned long i;
	for (i = 0; i < blocks; i += 4)
		IDEA_crypt(message + i, subkey);

	return i;
}


//multi instance decrypt fun to process more blocks with same key, return number of blocks processed successfully, NO CBC
unsigned long IDEA_multi_decrypt(uint16_t *message, uint16_t *key,const unsigned long blocks)
{
	if(!message || !key || blocks < 1)
		return 0;

  uint16_t key2[8];
  memcpy(key2, key, 16);
  uint16_t subkey[56];
	decrypt_keycreate(key2, subkey);
	unsigned long i;
	for (i = 0; i < blocks ; i += 4)
		IDEA_crypt(message + i, subkey);

	return i;
}
