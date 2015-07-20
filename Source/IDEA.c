//
//  IDEA.c
//  IDEA
//
//  Created by ivan sarno on 02/12/14.
//  Copyright (c) 2014 ivan sarno. All rights reserved.
//
//Version V.1.2

#include "IDEA.h"

//AAA this functions destroies the key

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

//multi instance encrypt fun to process more blocks with same key, return number of blocks processed successfully
int IDEA_multi_encrypt(uint16_t *message, uint16_t *key, const int blocks)
{
	if(!message || !key || blocks < 1)
		return 0;

	uint16_t subkey[56];
	keycreate(key, subkey);
	int i;
	for (i = 0; i < blocks; i += 4)
		IDEA_crypt(message + i, subkey);

	return i;
}


//multi instance decrypt fun to process more blocks with same key, return number of blocks processed successfully
int IDEA_multi_decrypt(uint16_t *message, uint16_t *key,const int blocks)
{
	if(!message || !key || blocks < 1)
		return 0;

	uint16_t subkey[56];
	deckey(key, subkey);
	int i;
	for (i = 0; i < blocks ; i += 4)
		IDEA_crypt(message + i, subkey);

	return i;
}
