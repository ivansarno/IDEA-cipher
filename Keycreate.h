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
void keycreate(typeint2 *key, typeint *subkey);
void deckey(typeint2 *key,typeint *subkey);
typeint inv(typeint3 a);


#endif /* defined(__IDEA__Keycreate__) */
