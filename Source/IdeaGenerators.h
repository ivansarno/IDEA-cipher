//
//  IdeaGenerators.h
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

#ifndef IdeaGenerators_h
#define IdeaGenerators_h

#include <stdint.h>
#include <stddef.h>

//Internal status of IdeaCounterGen and IdeaIterativeGen random number generators.
//These generator are different, use a different instance of status for different generator;
typedef struct {void* privateData;} IdeaGeneratorStatus;

//initializes the status of the generator
//keyUpdatePeriod = number of iteration before key update
IdeaGeneratorStatus IdeaGeneratorInit(uint64_t *key, uint64_t seed, uint64_t keyUpdatePeriod);

void IdeaGeneratorDelete(IdeaGeneratorStatus status);

//Return a cryptography safe random 64 bit integer
uint64_t IdeaIterativeGenInteger(IdeaGeneratorStatus status);

//Return a random 64 bit integer, this function is more efficient of IdeaIterativeGenInteger but it exposes
//a part of internal state of the generator.
//Use it for statistic application, not for cryptography.
uint64_t IdeaIterativeGenUnsafe(IdeaGeneratorStatus status);

//Fill a buffer of cryptography safe random bytes. Returns the number of random number generated.
size_t IdeaIterativeGenFill(IdeaGeneratorStatus status, uint8_t *buffer, size_t length);

//Return a cryptography safe random 64 bit integer
uint64_t IdeaCounterGenInteger(IdeaGeneratorStatus status);

//Fill a buffer of cryptography safe random 64 bit integer. Returns the number of random number generated.
size_t IdeaCounterGenFill(IdeaGeneratorStatus status, uint64_t *buffer, size_t length);

#endif /* IdeaGenerators_h */
