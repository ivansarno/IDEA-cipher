//
//  Keycreate.h
//  IDEA
//
//  Created by ivan sarno on 02/12/14.
//  Copyright (c) 2014 ivan sarno. All rights reserved.
//

#ifndef __IDEA__Keycreate__
#define __IDEA__Keycreate__
#include "define.h"
#include "ExtendedEuclide.h"

void keyrotate(uint16_t *key);
void keycreate(uint16_t *key, uint16_t *subkey);
void deckey(uint16_t *key,uint16_t *subkey);
uint16_t inv(unsigned long long a);


#endif /* defined(__IDEA__Keycreate__) */
