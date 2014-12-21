//
//  IDEA.h
//  IDEA
//
//  Created by ivan sarno on 02/12/14.
//  Copyright (c) 2014 ivan sarno. All rights reserved.
//
//complete set of fun to implement IDEA, detail in IDEA.c file

#ifndef __IDEA__IDEA__
#define __IDEA__IDEA__

#include "Round.h"
#include "Keycreate.h"
void IDEA_single_encrypt(uint16_t *message,uint16_t *key);
void IDEA_single_decrypt(uint16_t *message, uint16_t *key);
void IDEA_crypt(uint16_t *message, uint16_t *subkey);
void IDEA_multi_encrypt(uint16_t *message, uint16_t *key, const int num);
void IDEA_multi_decrypt(uint16_t *message, uint16_t *key, const int num);

#endif /* defined(__IDEA__IDEA__) */
