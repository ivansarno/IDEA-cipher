//
//  IDEA.h
//  IDEA
//
//  Created by ivan sarno on 02/12/14.
//  Copyright (c) 2014 ivan sarno. All rights reserved.
//

#ifndef __IDEA__IDEA__
#define __IDEA__IDEA__

#include "Round.h"
#include "Keycreate.h"
void IDEA_single_encrypt(typeint *message,typeint2 *key);
void IDEA_single_decrypt(typeint *message, typeint2 *key);
void IDEA_crypt(typeint *message, typeint2 *subkey);
void IDEA_multi_encrypt(typeint *message, typeint2 *key, int num);
void IDEA_multi_decrypt(typeint *message, typeint2 *key, int num);

#endif /* defined(__IDEA__IDEA__) */
