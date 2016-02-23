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

void IdeaRoutine(uint16_t *message, uint16_t *subkey)
{
    
    for (int i = 0; i<7; i++)
    {
        Round(message, subkey);
        subkey += 6;
    }
    FinalRound(message, subkey);
    
}

//single instance encrypt fun, return 0 in case of error
int IdeaEncrypt(uint64_t *message, uint64_t *key)
{
	if(!message || !key)
		return 0;
    
    uint16_t subkey[56];
    EncryptKeyCreate(key, subkey);
    IdeaRoutine((uint16_t *) message, subkey);
    

	return 1;
}

//single instance decrypt fun, return 0 in case of error
int IdeaDecrypt(uint64_t *message, uint64_t *key)
{
	if(!message || !key)
		return 0;

    uint16_t subkey[56];
    DecryptKeyCreate(key,subkey);
    IdeaRoutine((uint16_t *) message, subkey);

	return 1;
}



