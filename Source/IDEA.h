//
//  IDEA.h
//  IDEA
//
//  Created by ivan sarno on 02/12/14.
//  Copyright (c) 2014 ivan sarno. All rights reserved.
//
//Version V.1.2
//complete set of fun to implement IDEA, detail in IDEA.c file

#ifndef __IDEA__IDEA__
#define __IDEA__IDEA__

#include "Round.h"
#include "Keycreate.h"

//AAA this functions destroies the key used

int IDEA_single_encrypt(uint16_t *message,uint16_t *key);
int IDEA_single_decrypt(uint16_t *message, uint16_t *key);
void IDEA_crypt(uint16_t *message, uint16_t *subkey);
int IDEA_multi_encrypt(uint16_t *message, uint16_t *key, const int blocks);
int IDEA_multi_decrypt(uint16_t *message, uint16_t *key, const int blocks);

//details in IDEA.c file
#endif /* defined(__IDEA__IDEA__) */
