//
//  IDEA.c
//  IDEA
//
//  Created by ivan sarno on 02/12/14.
//  Copyright (c) 2014 ivan sarno. All rights reserved.
//
//Version V.1.1

#include "IDEA.h"

//single instance encrypt fun, return 0 in case of error
int IDEA_single_encrypt(uint16_t *message, uint16_t *key)
{
	if(!message || !key)
		return 0;
	
    uint16_t subkey[56];
    keycreate(key,subkey);
    int i;
    for(i=0;i<7;i++)
        Round(message, subkey+(6*i));
    Finalround(message, subkey+(6*i));
	
	return 1;
}

//single instance decrypt fun, return 0 in case of error
int IDEA_single_decrypt(uint16_t *message, uint16_t *key)
{
	if(!message || !key)
		return 0;
	
    uint16_t subkey[56];
    deckey(key,subkey);
    int i;
    for(i=0;i<7;i++)
        Round(message, subkey+(6*i));
    Finalround(message, subkey+(6*i));
	
	return 1;
}

//single instance encrypt or decript fun with extern generation of subkey, to reuse the same
void IDEA_crypt(uint16_t *message, uint16_t *subkey)
{
	
	int i;
	for (i = 0; i<7; i++)
		Round(message, subkey + (6 * i));
	Finalround(message, subkey + (6 * i));

}

//multi inscance encrypt fun to process for block with same key, return number of iterations performed successfully
void IDEA_multi_encrypt(uint16_t *message, uint16_t *key, const int num)
{
	if(!message || !key || num < 1)
		return 0;
	
	uint16_t subkey[56];
	keycreate(key, subkey);
	int i;
	for (i = 0; i < num; i += 4)
		IDEA_crypt(message + i, subkey);
	
	return i / 4 - 1;
}


//multi inscance decrypt fun to process for block with same key
void IDEA_multi_decrypt(uint16_t *message, uint16_t *key,const int num)
{
	if(!message || !key || num < 1)
		return 0;
	
	uint16_t subkey[56];
	deckey(key, subkey);
	int i;
	for (i = 0; i < num ; i += 4)
		IDEA_crypt(message + i, subkey);
	
	return i / 4 - 1;
}