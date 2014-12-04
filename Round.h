//
//  Round.h
//  IDEA
//
//  Created by ivan sarno on 02/12/14.
//  Copyright (c) 2014 ivan sarno. All rights reserved.
//

#ifndef __IDEA__Round__
#define __IDEA__Round__

#include "define.h"
typeint mul(typeint3 a, typeint3 b);
void step1(typeint *message,typeint *key);
void step2(typeint *message, typeint *temp);
void step3(typeint *temp, typeint *key);
void step4(typeint *temp, typeint *key);
void step5(typeint *message,typeint *temp);
void step6(typeint *message,typeint *temp);
void step7(typeint *message);
void Round(typeint *message,typeint *key);
void Finalround(typeint *message,typeint *key);
void step8(typeint *message,typeint *key);

#endif /* defined(__IDEA__Round__) */
