//
//  IDEA.c
//  IDEA
//
//  Created by ivan sarno on 02/12/14.
//  Copyright (c) 2014 ivan sarno. All rights reserved.
//

#include "IDEA.h"

void IDEAencrypt(typeint *message,typeint2 *key)
{
    typeint subkey[56];
    keycreate(key,subkey);
    int i;
    for(i=0;i<7;i++)
        Round(message, subkey+(6*i));
    Finalround(message, subkey+(6*i));
}


void IDEAdecrypt(typeint *message, typeint2 *key)
{
    typeint subkey[56];
    deckey(key,subkey);
    int i;
    for(i=0;i<7;i++)
        Round(message, subkey+(6*i));
    Finalround(message, subkey+(6*i));
}