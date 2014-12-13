//
//  IDEA.c
//  IDEA
//
//  Created by ivan sarno on 02/12/14.
//  Copyright (c) 2014 ivan sarno. All rights reserved.
//

#include "IDEA.h"

void IDEA_single_encrypt(typeint *message, typeint2 *key)
{
    typeint subkey[56];
    keycreate(key,subkey);
    int i;
    for(i=0;i<7;i++)
        Round(message, subkey+(6*i));
    Finalround(message, subkey+(6*i));
}


void IDEA_single_decrypt(typeint *message, typeint2 *key)
{
    typeint subkey[56];
    deckey(key,subkey);
    int i;
    for(i=0;i<7;i++)
        Round(message, subkey+(6*i));
    Finalround(message, subkey+(6*i));

}

void IDEA_crypt(typeint *message, typeint2 *subkey)
{
	
	int i;
	for (i = 0; i<7; i++)
		Round(message, subkey + (6 * i));
	Finalround(message, subkey + (6 * i));

}


void IDEA_multi_encrypt(typeint *message, typeint2 *key, int num)
{
	typeint subkey[56];
	keycreate(key, subkey);
	int i;
	for (i = 0; i < num; i += 4)
		IDEA_crypt(message + i, subkey);
}



void IDEA_multi_decrypt(typeint *message, typeint2 *key,int num)
{
	typeint subkey[56];
	deckey(key, subkey);
	int i;
	for (i = 0; i < num; i += 4)
		IDEA_crypt(message + i, subkey);

}