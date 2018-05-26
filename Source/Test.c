//
//  Test.c
//  IdeaLib
//
//  Created by ivan sarno on 23/02/16.
//  Copyright © 2016 ivan sarno.
/*
 This file is part of IdeaLib library
 IdeaLib  is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.
 
 IdeaLib  is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public
 License along with IdeaLib ; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
 USA
 */
//Version V.3.1

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "IdeaLib.h"
#include <time.h>

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define COLOR_RESET   "\x1b[0m"

#define messageLength 15
#define testPrecision 25


static void MakeKey(uint16_t *key)
{
    do
    {
        key[0] = rand();
        key[1] = rand();
        key[2] = rand();
        key[3] = rand();
        key[4] = rand();
        key[5] = rand();
        key[6] = rand();
        key[7] = rand();
    } while (!KeyCheck((uint64_t *)key));
}

static int ModeTest()
{
    srand((unsigned int)time(NULL));
    uint64_t message[messageLength];
    uint64_t messageCopy[messageLength];
    int i,j;
    uint64_t nonce;
    uint64_t key[2];
    
    MakeKey((uint16_t *) key);
    for(i=0; i<testPrecision; i++)
    {
        for(j=0; j<messageLength; j++)
            message[j]= messageCopy[j] = rand()*rand();
        nonce = rand();
        IdeaCBCEncrypt(message, key, nonce, messageLength);
        IdeaCBCDecrypt(message, key, nonce, messageLength);
        for(j=0; j<messageLength; j++)
            if(message[j] != messageCopy[j])
            {
                printf(RED "CBC ERROR\n" COLOR_RESET);
                return 1;
            }
    }
    printf(GREEN "CBC Encryption OK\n" COLOR_RESET);
    
    MakeKey((uint16_t *) key);
    
    for(i=0; i<testPrecision; i++)
    {
        for(j=0; j<messageLength; j++)
            message[j]= messageCopy[j] = rand()*rand();
        nonce = rand();
        IdeaPCBCEncrypt(message, key, nonce, messageLength);
        IdeaPCBCDecrypt(message, key, nonce, messageLength);
        for(j=0; j<messageLength; j++)
            if(message[j] != messageCopy[j])
            {
                printf(RED "PCBC ERROR\n" COLOR_RESET);
                return 1;
            }
    }
    printf(GREEN "PCBC Encryption OK\n" COLOR_RESET);
    
    MakeKey((uint16_t *) key);
    
    for(i=0; i<testPrecision; i++)
    {
        for(j=0; j<messageLength; j++)
            message[j]= messageCopy[j] = rand()*rand();
        nonce = rand()*rand();
        uint64_t nonceb = nonce;
        IdeaCFBEncrypt(message, key, nonce, messageLength);
        IdeaCFBDecrypt(message, key, nonceb, messageLength);
        for(j=0; j<messageLength; j++)
            if(message[j] != messageCopy[j])
            {
                printf(RED "CFB ERROR\n" COLOR_RESET);
                return 1;
            }
    }
    printf(GREEN "CFB Encryption OK\n" COLOR_RESET);
    
    MakeKey((uint16_t *) key);
    
    for(i=0; i<testPrecision; i++)
    {
        for(j=0; j<messageLength; j++)
            message[j]= messageCopy[j] = rand()*rand();
        nonce = rand()*rand();
        IdeaOFB(message, key, nonce, messageLength);
        IdeaOFB(message, key, nonce, messageLength);
        for(j=0; j<messageLength; j++)
            if(message[j] != messageCopy[j])
            {
                printf(RED  "OFB ERROR\n" COLOR_RESET);
                return 1;
            }
    }
    printf(GREEN "OFB Encryption OK\n" COLOR_RESET);
    
    MakeKey((uint16_t *) key);
    
    for(i=0; i<testPrecision; i++)
    {
        for(j=0; j<messageLength; j++)
            message[j]= messageCopy[j] = rand()*rand();
        nonce =rand();
        IdeaCTR(message, key, nonce, messageLength);
        IdeaCTR(message, key, nonce, messageLength);
        for(j=0; j<messageLength; j++)
            if(message[j] != messageCopy[j])
            {
                printf(RED "CTR ERROR\n" COLOR_RESET);
                return 1;
            }
    }
    printf(GREEN "CTR Encryption OK\n" COLOR_RESET);
    
    return 0;
}

static int CoreTest()
{
    srand((unsigned int)time(NULL));
    uint64_t message[messageLength];
    uint64_t messageCopy[messageLength];
    int i;
    uint64_t key[2];
    
    MakeKey((uint16_t *) key);
    
    
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
    printf(GREEN "Single Encryption OK\n" COLOR_RESET);
    
    return 0;
}

static int StreamTest()
{
    srand((unsigned int)time(NULL));
    uint64_t message[messageLength];
    uint64_t messageCopy[messageLength];
    int i,j;
    uint64_t nonce;
    uint64_t key[2];
    IdeaEncryptStreamStatus eStatus;
    IdeaEncryptStreamStatus e2Status;
    IdeaDecryptStreamStatus dStatus;
    
    MakeKey((uint16_t *) key);
    
    nonce = rand();
    eStatus = IdeaStreamEncryptInit(key, nonce);
    dStatus = IdeaStreamDecryptInit(key, nonce);
    
    for(i=0; i<testPrecision; i++)
    {
        for(j=0; j<messageLength; j++)
            message[j]= messageCopy[j] = rand()*rand();
        
        for(j=0; j<messageLength; j++)
            IdeaStreamCBCEncrypt(message+j, eStatus);
        
        for(j=0; j<messageLength; j++)
            IdeaStreamCBCDecrypt(message+j, dStatus);
        
        for(j=0; j<messageLength; j++)
            if(message[j] != messageCopy[j])
            {
                printf(RED "StreamCBC ERROR\n" COLOR_RESET);
                return 1;
            }
    }
    printf(GREEN "StreamCBC Encryption OK\n" COLOR_RESET);
    
    IdeaStreamEncryptDelete(eStatus);
    IdeaStreamDecryptDelete(dStatus);
    
    MakeKey((uint16_t *) key);
    
    nonce = rand();
    eStatus = IdeaStreamEncryptInit(key, nonce);
    dStatus = IdeaStreamDecryptInit(key, nonce);
    
    for(i=0; i<testPrecision; i++)
    {
        for(j=0; j<messageLength; j++)
            message[j] = messageCopy[j] = rand()*rand();
        
        for(j=0; j<messageLength; j++)
            IdeaStreamPCBCEncrypt(message+j, eStatus);
        
        for(j=0; j<messageLength; j++)
            IdeaStreamPCBCDecrypt(message+j, dStatus);
        
        for(j=0; j<messageLength; j++)
            if(message[j] != messageCopy[j])
            {
                printf(RED "PCBC ERROR\n" COLOR_RESET);
                return 1;
            }
    }
    printf(GREEN "StreamPCBC Encryption OK\n" COLOR_RESET);
    
    IdeaStreamEncryptDelete(eStatus);
    IdeaStreamDecryptDelete(dStatus);
    
    MakeKey((uint16_t *) key);
    
    nonce = rand();
    eStatus = IdeaStreamEncryptInit(key, nonce);
    e2Status = IdeaStreamEncryptInit(key, nonce);
    
    for(i=0; i<testPrecision; i++)
    {
        for(j=0; j<messageLength; j++)
            message[j]= messageCopy[j] = rand()*rand();
        
        for(j=0; j<messageLength; j++)
            IdeaStreamCFBEncrypt(message+j, eStatus);
        
        for(j=0; j<messageLength; j++)
            IdeaStreamCFBDecrypt(message+j, e2Status);
        
        for(j=0; j<messageLength; j++)
            if(message[j] != messageCopy[j])
            {
                printf(RED "CFB ERROR\n" COLOR_RESET);
                return 1;
            }
    }
    printf(GREEN "StreamCFB Encryption OK\n" COLOR_RESET);
    
    IdeaStreamEncryptDelete(eStatus);
    IdeaStreamEncryptDelete(e2Status);
    
    MakeKey((uint16_t *) key);
    
    nonce = rand();
    eStatus = IdeaStreamEncryptInit(key, nonce);
    e2Status = IdeaStreamEncryptInit(key, nonce);

    
    for(i=0; i<testPrecision; i++)
    {
        for(j=0; j<messageLength; j++)
            message[j]= messageCopy[j] = rand()*rand();
        
        for(j=0; j<messageLength; j++)
            IdeaStreamOFB(message+j, eStatus);
        
        for(j=0; j<messageLength; j++)
            IdeaStreamOFB(message+j, e2Status);
        
        for(j=0; j<messageLength; j++)
            if(message[j] != messageCopy[j])
            {
                printf(RED  "OFB ERROR\n" COLOR_RESET);
                return 1;
            }
    }
    printf(GREEN "StreamOFB Encryption OK\n" COLOR_RESET);
    
    IdeaStreamEncryptDelete(eStatus);
    IdeaStreamEncryptDelete(e2Status);
    
    MakeKey((uint16_t *) key);
    
    nonce = rand();
    eStatus = IdeaStreamEncryptInit(key, nonce);
    e2Status = IdeaStreamEncryptInit(key, nonce);

    
    for(i=0; i<testPrecision; i++)
    {
        for(j=0; j<messageLength; j++)
            message[j]= messageCopy[j] = rand()*rand();
        
        for(j=0; j<messageLength; j++)
            IdeaStreamCFBEncrypt(message+j, eStatus);
        
        for(j=0; j<messageLength; j++)
            IdeaStreamCFBDecrypt(message+j, e2Status);
        
        for(j=0; j<messageLength; j++)
            if(message[j] != messageCopy[j])
            {
                printf(RED "CTR ERROR\n" COLOR_RESET);
                return 1;
            }
    }
    printf(GREEN "StreamCTR Encryption OK\n" COLOR_RESET);
    
    IdeaStreamEncryptDelete(eStatus);
    IdeaStreamEncryptDelete(e2Status);
    return 0;
}



int main()
{
    if(CoreTest())
        return 1;
    if(ModeTest())
        return 1;
    if(StreamTest())
        return 1;
    
    return 0;
}








