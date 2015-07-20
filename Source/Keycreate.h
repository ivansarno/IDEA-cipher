//
//  Keycreate.h
//  IDEA
//
//  Created by ivan sarno on 02/12/14.
//  Copyright (c) 2014 ivan sarno. All rights reserved.
//
//Version V.1.2
/*
implementation of key schedule of IDEA, subkey array is allocated in the caller function.
See official algorithm reference for more details
*/

#ifndef __IDEA__Keycreate__
#define __IDEA__Keycreate__
#include "define.h"
#include "ExtendedEuclide.h"

void keyrotate(uint16_t *key);
void keycreate(uint16_t *key, uint16_t *subkey);
void deckey(uint16_t *key,uint16_t *subkey);
uint16_t inv(uint16_t a);


#endif /* defined(__IDEA__Keycreate__) */
