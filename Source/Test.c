//
//  Test.c
//  IdeaLib
//
//  Created by ivan sarno on 23/02/16.
//  Copyright © 2016 ivan sarno. All rights reserved.
//
//V.2.0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "IdeaLib.h"
#include <time.h>

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define COLOR_RESET   "\x1b[0m"

const int messageLength = 15;
const int testPrecision = 25;

int main()
{
    srand((unsigned int)time(NULL));
    uint64_t message[messageLength];
    uint64_t messageCopy[messageLength];
    int i,j;
    uint32_t keyInit[4];
    uint64_t nonce;
    uint64_t *key=(uint64_t *)keyInit;

    keyInit[0] = rand();
    keyInit[1] = rand();
    keyInit[2] = rand();
    keyInit[3] = rand();


    for(i=0; i<testPrecision; i++)
    {
        message[0] = rand()*rand();
        messageCopy[0] = message[0];
        IdeaEncrypt(message, key);
        IdeaDecrypt(message, key);
        if(message[0] != messageCopy[0])
        {
            printf(RED "Single ERROR\n" COLOR_RESET);
            return 1;
        }
    }
    printf(GREEN "Single Encription OK\n" COLOR_RESET);

    keyInit[0] = rand();
    keyInit[1] = rand();
    keyInit[2] = rand();
    keyInit[3] = rand();

    for(i=0; i<testPrecision; i++)
    {
        for(j=0; j<messageLength; j++)
            message[j]= messageCopy[j] = rand()*rand();
        nonce = rand();
        IdeaCBCEncrypt(message, key, nonce, messageLength);
        IdeaCBCDecrypt(message, key, nonce, messageLength);
        if(message[0] != messageCopy[0])
        {
            printf(RED "CBC ERROR\n" COLOR_RESET);
            return 1;
        }
    }
    printf(GREEN "CBC Encription OK\n" COLOR_RESET);

    keyInit[0] = rand();
    keyInit[1] = rand();
    keyInit[2] = rand();
    keyInit[3] = rand();

    for(i=0; i<testPrecision; i++)
    {
        for(j=0; j<messageLength; j++)
            message[j]= messageCopy[j] = rand()*rand();
        nonce = rand();
        IdeaPCBCEncrypt(message, key, nonce, messageLength);
        IdeaPCBCDecrypt(message, key, nonce, messageLength);
        for(j=0; j<messageLength; j++)
            if(message[0] != messageCopy[0])
            {
                printf(RED "PCBC ERROR\n" COLOR_RESET);
                return 1;
            }
    }
    printf(GREEN "PCBC Encription OK\n" COLOR_RESET);

    keyInit[0] = rand();
    keyInit[1] = rand();
    keyInit[2] = rand();
    keyInit[3] = rand();

    for(i=0; i<testPrecision; i++)
    {
        for(j=0; j<messageLength; j++)
            message[j]= messageCopy[j] = rand()*rand();
        nonce = rand()*rand();
        uint64_t nonceb = nonce;
        IdeaCFBEncrypt(message, key, nonce, messageLength);
        IdeaCFBDecrypt(message, key, nonceb, messageLength);
        for(j=0; j<messageLength; j++)
            if(message[0] != messageCopy[0])
            {
                printf(RED "CFB ERROR\n" COLOR_RESET);
                return 1;
            }
    }
    printf(GREEN "CFB Encription OK\n" COLOR_RESET);

    keyInit[0] = rand();
    keyInit[1] = rand();
    keyInit[2] = rand();
    keyInit[3] = rand();

    for(i=0; i<testPrecision; i++)
    {
        for(j=0; j<messageLength; j++)
            message[j]= messageCopy[j] = rand()*rand();
        nonce = rand()*rand();
        IdeaOFB(message, key, nonce, messageLength);
        IdeaOFB(message, key, nonce, messageLength);
        for(j=0; j<messageLength; j++)
            if(message[0] != messageCopy[0])
            {
                printf(RED  "OFB ERROR\n" COLOR_RESET);
                return 1;
            }
    }
    printf(GREEN "OFB Encription OK\n" COLOR_RESET);

    keyInit[0] = rand();
    keyInit[1] = rand();
    keyInit[2] = rand();
    keyInit[3] = rand();

    for(i=0; i<testPrecision; i++)
    {
        for(j=0; j<messageLength; j++)
            message[j]= messageCopy[j] = rand()*rand();
        nonce =rand();
        IdeaCTR(message, key, nonce, messageLength);
        IdeaCTR(message, key, nonce, messageLength);
        for(j=0; j<messageLength; j++)
            if(message[0] != messageCopy[0])
            {
                printf(RED "CTR ERROR\n" COLOR_RESET);
                return 1;
            }
    }
    printf(GREEN "CTR Encription OK\n" COLOR_RESET);

    return 0;
}
