//
//  Round.h
//  IDEA
//
//  Created by ivan sarno on 02/12/14.
//  Copyright (c) 2014 ivan sarno. All rights reserved.
//
/*
 Implementation of round of IDEA algorithm, divided in steps for clarity and simplicity, mul operation is ad hoc for the algorithm.
 See official algorithm reference for more details
 */

#ifndef __IDEA__Round__
#define __IDEA__Round__

#include "define.h"
uint16_t mul(unsigned long long a, unsigned long long b);
void step1(uint16_t *message,uint16_t *key);
void step2(uint16_t *message, uint16_t *temp);
void step3(uint16_t *temp, uint16_t *key);
void step4(uint16_t *temp, uint16_t *key);
void step5(uint16_t *message,uint16_t *temp);
void step6(uint16_t *message,uint16_t *temp);
void step7(uint16_t *message);
void Round(uint16_t *message,uint16_t *key);
void Finalround(uint16_t *message,uint16_t *key);
void step8(uint16_t *message,uint16_t *key);



#endif /* defined(__IDEA__Round__) */
