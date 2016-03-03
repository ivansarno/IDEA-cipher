//
//  Round.h
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
//Version V.2.0

//Implementation of round of IDEA algorithm. See official algorithm reference for more details


#ifndef __IdeaLib__Round__
#define __IdeaLib__Round__
#include <stdint.h>

void Round(uint16_t *message, uint16_t *key);
void FinalRound(uint16_t *message, uint16_t *key);

#endif /* defined(__IdeaLib__Round__) */
