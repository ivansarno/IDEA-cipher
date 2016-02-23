//
//  IDEA.h
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
//Version V.1.3
//complete set of fun to implement IDEA, detail in IDEA.c file

#ifndef __IDEA__IDEA__
#define __IDEA__IDEA__

#include "Round.h"
#include "Keycreate.h"


//single instance encrypt fun, return 0 in case of error
int IdeaEncrypt(uint64_t *message,uint64_t *key);

//single instance decrypt fun, return 0 in case of error
int IdeaDecrypt(uint64_t *message, uint64_t *key);


//details in IDEA.c file
#endif /* defined(__IDEA__IDEA__) */
