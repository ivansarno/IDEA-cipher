//
//  Test.c
//  IDEA
//
//  Created by ivan sarno on 23/02/16.
//  Copyright © 2016 ivan sarno. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "IDEA.h"
#include <time.h>

const int messageLength = 15;
const int testPrecision = 25;

int main()
{
    srand((unsigned int)time(NULL));
    uint64_t message[messageLength];
    uint64_t messageCopy[messageLength];
    uint64_t multiNonce[messageLength];
    int i,j;
    uint32_t keyInit[4];
    uint64_t nonce;
    uint64_t *key=(uint64_t *)keyInit;
    
    keyInit[0] = rand();
    keyInit[1] = rand();
    keyInit[2] = rand();
    keyInit[3] = rand();

    
    for(j=0; j<messageLength; j++)
        multiNonce[j] = rand();
    
    for(i=0; i<testPrecision; i++)
    {
        message[0] = rand()*rand();
        messageCopy[0] = message[0];
        IdeaEncrypt(message, key);
        IdeaDecrypt(message, key);
        if(message[0] != messageCopy[0])
        {
            printf("Single ERROR\n");
            return 1;
        }
    }
    printf("Single Encription OK\n");
    
    for(i=0; i<testPrecision; i++)
    {
        for(j=0; j<messageLength; j++)
            message[j]= messageCopy[j] = rand()*rand();
        nonce = rand();
        IdeaCBCEncrypt(message, key, nonce, messageLength);
        IdeaCBCDecrypt(message, key, nonce, messageLength);
        if(message[0] != messageCopy[0])
        {
            printf("CBC ERROR\n");
            return 1;
        }
    }
    printf("CBC Encription OK\n");
    
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
                printf("PCBC ERROR\n");
                return 1;
            }
    }
    printf("PCBC Encription OK\n");
    
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
                printf("CFB ERROR\n");
                return 1;
            }
    }
    printf("CFB Encription OK\n");
    
    for(i=0; i<testPrecision; i++)
    {
        for(j=0; j<messageLength; j++)
            message[j]= messageCopy[j] = rand()*rand();
        nonce = rand()*rand();
        IdeaOFBEncrypt(message, key, nonce, messageLength);
        IdeaOFBDecrypt(message, key, nonce, messageLength);
        for(j=0; j<messageLength; j++)
            if(message[0] != messageCopy[0])
            {
                printf("OFB ERROR\n");
                return 1;
            }
    }
    printf("OFB Encription OK\n");
    
    for(i=0; i<testPrecision; i++)
    {
        for(j=0; j<messageLength; j++)
            message[j]= messageCopy[j] = rand()*rand();
        
        IdeaCTREncrypt(message, key, multiNonce, messageLength);
        IdeaCTRDecrypt(message, key, multiNonce, messageLength);
        for(j=0; j<messageLength; j++)
            if(message[0] != messageCopy[0])
            {
                printf("CTR ERROR\n");
                return 1;
            }
    }
    printf("CTR Encription OK\n");
    
    return 0;
}












