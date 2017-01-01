//  Created by ivan sarno on 02/12/14.
//  Copyright (c) 2014 ivan sarno.
/*
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.

 */
//Version V.2.4

#ifdef _WIN32
#define _CRT_RAND_S
#define SAFEIO

#else
#include <fcntl.h>
#include <unistd.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include "IdeaLib.h"
#include "KeyCreation.h"
#include <string.h>
#include <sys/stat.h>



const char *manString = " IdeaCipher -h: print this man.\n \
IdeaCipher --help: print this man.\n \
IdeaCipher -k: creates a 128 bits key and a 64 bit nonce ad stores these in a file called key in the current directory.\n \
IdeaCipher -e inputFile: encrypt inputFile and creates the ouptput file and key file in the current directory. key file contains 172 random bit for key and nonce.\n \
IdeaCipher -e inputFile keyFile: encrypt inputFile and creates the ouptput file in the current directory, keyFile must contains 172 random bit for key and nonce.\n \
IdeaCipher -d inputFile keyFile: decrypt inputFile and create the ouptput file in the current directory. keyFile must contains 172 random bit for key and nonce.\n \
IdeaCipher -r numberOfBytes: store numberOfBytes cryptography safe random bytes in the ouptput file in the current directory.\n";


const char *errorInputString = "Input Error. Run \"IdeaCipher -h\" for help.\n";

//must be multiple of 8
#define bufferLength  8000


int FileOpen(FILE **message, FILE **output, char *messageFileName);
int MessageRead(FILE *message, uint64_t *buffer);
int MessageWrite(FILE *output, uint64_t *buffer, int length);
int64_t LengthRead(char *messageFileName);
int LengthWrite(FILE *output, int64_t messageLength);
int64_t OriginalLengthRead(FILE *message);
int KeyRead(char *keyFileName, uint64_t *key);
int KeyWrite(uint64_t *key);
int KeyGen(uint64_t *key);
int SystemRandom(uint64_t *buffer);
int Encrypt(char *messageFileName, char *keyFileName);
int Decrypt(char *messageFileName, char *keyFileName);
int GenAndStore();
int GenAndEncrypt(char *messageFileName);
int RandomGeneration(int number);


int main(int argc, char **argv)
{
    //command selection
    if(argc < 2)
    {
        printf("%s", errorInputString);
        return 1;
    }
    if(strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
    {
        printf("%s", manString);
        return 0;
    }
    
    if(strcmp(argv[1], "-k") == 0)
        return GenAndStore();
    
    if(strcmp(argv[1], "-e") == 0 && argc==3)
        return GenAndEncrypt(argv[2]);
    
    if(strcmp(argv[1], "-e") == 0 && argc==4)
        return Encrypt(argv[2], argv[3]);
    
    if(strcmp(argv[1], "-d") == 0 && argc==4)
        return Decrypt(argv[2], argv[3]);
    
    if(strcmp(argv[1], "-r") == 0 && argc==3)
        return RandomGeneration(atoi(argv[2]));
    
    printf("%s", errorInputString);
    
    return 1;
}


int Encrypt(char *messageFileName, char *keyFileName)
{
    
    FILE *message, *output;
    uint64_t key[3];
    uint64_t buffer[bufferLength / 8];
    
    if(KeyRead(keyFileName, key) < 0)
        return 1;
    
    if(FileOpen(&message, &output, messageFileName) < 0)
        return 1;
    
    int64_t messageLength = LengthRead(messageFileName);
    if(LengthWrite(output, messageLength) < 0)
    {
        fclose(message);
        fclose(output);
        return 1;
    }
    
    IdeaStreamStatus streamStatus = IdeaStreamEncryptionInit(key, key[2]);
    
    while (messageLength > 0)
    {
        if(MessageRead(message, buffer) <  0)//< 0 error, 0 = end of file
            break;
        int i;
        for(i=0; i<(bufferLength/8); i++)
            IdeaStreamCBCEncrypt(buffer+i, streamStatus);
        
        if(MessageWrite(output, buffer, bufferLength) <  0)
            break;
        
        messageLength -= bufferLength;
    }
    
    fclose(message);
    fclose(output);
    SecureMemoryWipe(key, 24);
    if(messageLength > 0)
    {
        printf("Error: encryption not completed\n");
        return 1;
    }
    return 0;
}

int Decrypt(char *messageFileName, char *keyFileName)
{
    
    FILE *message, *output;
    uint64_t key[3];
    uint64_t buffer[bufferLength/8];
    
    if(KeyRead(keyFileName, key) < 0)
        return 1;
    
    if(FileOpen(&message, &output, messageFileName) < 0)
        return 1;
    
    int64_t messageLength = OriginalLengthRead(message);
    if(messageLength == 0)
    {
        fclose(message);
        fclose(output);
        return 1;
    }
    
    IdeaStreamStatus streamStatus = IdeaStreamDecryptionInit(key, key[2]);
    
    while (messageLength > bufferLength)
    {
        if(MessageRead(message, buffer) <  0)//< 0 error, 0 = end of file
            break;

        int i;
        for(i=0; i<(bufferLength/8); i++)
            IdeaStreamCBCDecrypt(buffer+i, streamStatus);
        
        if(MessageWrite(output, buffer, bufferLength) <  0)
            break;
        
        messageLength -= bufferLength;
    }
    
    //Process last byte without padding
    if(messageLength > 0 && MessageRead(message, buffer) >= 0)
    {

        int i;
        for(i=0; i<bufferLength/8; i++)
            IdeaStreamCBCDecrypt(buffer+i, streamStatus);

        if(MessageWrite(output, buffer, (int) messageLength) >= 0)
            messageLength = 0;
    }
    
    fclose(message);
    fclose(output);
    SecureMemoryWipe(key, 24);
    if(messageLength != 0)
    {
        printf("Error: decryption not completed\n");
        return 1;
    }
    return 0;
}

int GenAndStore()
{
    uint64_t key[3];
    
    if(KeyGen(key))
        return 1;
    
    if(KeyWrite(key))
    {
        SecureMemoryWipe(key, 24);
        return 1;
    }
    return 0;
}

int GenAndEncrypt(char *messageFileName)
{
    FILE *message, *output;
    uint64_t key[3];
    uint64_t buffer[bufferLength / 8];
    
    if(KeyGen(key) != 0)
        return 1;
    
    if(KeyWrite(key) != 0)
        return 1;
    
    if(FileOpen(&message, &output, messageFileName) < 0)
        return 1;
    
    int64_t messageLength = LengthRead(messageFileName);
    if(LengthWrite(output, messageLength) < 0)
    {
        fclose(message);
        fclose(output);
        return 1;
    }
    
    IdeaStreamStatus streamStatus = IdeaStreamEncryptionInit(key, key[2]);
    
    
    while (messageLength > 0)
    {
        if(MessageRead(message, buffer) <  0)//< 0 error, 0 = end of file
            break;
        int i;
        for(i=0; i<(bufferLength/8); i++)
            IdeaStreamCBCEncrypt(buffer+i, streamStatus);
        
        if(MessageWrite(output, buffer, bufferLength) <  0)
            break;
        
        messageLength -= bufferLength;
    }
    
    fclose(message);
    fclose(output);
    SecureMemoryWipe(key, 24);
    if(messageLength > 0)
    {
        printf("Error: encryption not completed\n");
        return 1;
    }
    return 0;
}

int RandomGeneration(int number)
{
    if(number == 0)
        return 0;
    
    FILE *output = NULL;
    
#ifndef SAFEIO
    output = fopen("output", "wb");
    
#else
    fopen_s(&output,"output", "wb");
#endif
    
    if(output == NULL)
    {
        printf("Error: can't create output file\n");
        return 1;
    }
    uint64_t key[3];
    if(SystemRandom(key))
    {
        printf("Error: Random Number Generation Fail\n");
        return 1;
    }
    
    uint8_t *buffer = (uint8_t *) malloc(number * sizeof(uint8_t));
    
    if(!buffer)
        return 1;
    
    IdeaGeneratorStatus status = IdeaGeneratorInit(key, key[2], 500);
    
    IdeaIterativeGenFill(status, buffer, number);
    
    IdeaGeneratorDelete(status);
    
    if(MessageWrite(output, (uint64_t *)buffer, number))
        return 2;
    
    SecureMemoryWipe(key, 3);
    SecureMemoryWipe(buffer, number);
    
    free(buffer);
    return 0;
}



///////////////////////support functions

int64_t LengthRead(char *messageFileName)
{
    struct stat st;
    stat(messageFileName, &st);
    return st.st_size;
}

int LengthWrite(FILE *output, int64_t messageLength)
{
    if(fwrite(&messageLength, sizeof(int64_t), 1, output) != 1)
    {
        printf("error on output writing\n");
        return -1;
    }
    return 0;
    
}

int64_t OriginalLengthRead(FILE *message)
{
    int64_t length;
    if(fread(&length, sizeof(int64_t), 1, message) != 1)
    {
        printf("error on input reading\n");
        return 0;
    }
    return length;
}

int MessageRead(FILE *message, uint64_t *buffer)
{
    uint64_t byteReaded = fread(buffer, sizeof(uint8_t), bufferLength, message);
    if(byteReaded < 1)
    {
        printf("error on input reading\n");
        return -1;
    }
    else if(byteReaded == bufferLength)
        return 1;
    return 0;
}


int MessageWrite(FILE *output, uint64_t *buffer, int length)
{
    if(fwrite(buffer, sizeof(uint8_t), length, output) != length)
    {
        printf("error on output writing\n");
        return -1;
    }
    return 0;
}

int KeyRead(char *keyFileName, uint64_t *key)
{
    FILE *keyFile = NULL;
    
#ifndef SAFEIO
    keyFile = fopen(keyFileName, "rb");
#else
    fopen_s(&keyFile,keyFileName, "rb");
#endif
    
    if(!keyFile || (fread(key, sizeof(uint64_t), 3, keyFile) != 3))
    {
        printf("Error: Can't read key file.\n");
        SecureMemoryWipe((void *)key, 24);
        return -1;
    }
    
    if(!KeyCheck(key))
    {
        printf("Error:Key not pass security test\n");
        SecureMemoryWipe((void *)key, 24);
        return -1;
    }
    
    fclose(keyFile);
    return 0;
}


int FileOpen(FILE **message, FILE **output, char *messageFileName)
{
    *message = NULL;
    *output = NULL;
    
#ifndef SAFEIO
    *message = fopen(messageFileName, "rb");
    *output = fopen("output", "wb");
    
#else
    fopen_s(message,messageFileName, "rb");
    fopen_s(output,"output", "wb");
#endif
    
    if(*message == NULL || output == NULL)
    {
        printf("Error: Can't read input file or create optput file.\n");
        fclose((*message));
        fclose(*output);
        return  -1;
    }
    
    return 0;
}

int SystemRandom(uint64_t *buffer)
{
#ifdef _WIN32
    uint32_t *buff32 = (uint32_t *) buffer;
    for(int i=0; i<6; i++)
    {
        if (rand_s(buff32))
            return 1;
        buff32++;
    }
    return 0;
#else
    
    int randomSource = open("/dev/random", O_RDONLY);
    if(read(randomSource, buffer, 24) !=24)
        return 1;
    
    close(randomSource);
    
    return 0;
#endif
}

int KeyWrite(uint64_t *key)
{
    FILE *keyFile = NULL;
    
#ifndef SAFEIO
    keyFile = fopen("key", "wb");
    
#else
    fopen_s(&keyFile,"key", "wb");
#endif
    
    if(keyFile == NULL)
    {
        printf("Error: can't create key file\n");
        return -2;
    }
    
    if(fwrite(key, sizeof(uint64_t), 3, keyFile) != 3)
    {
        printf("Error: key writing fail\n");
        
        fclose(keyFile);
        return -3;
    }
    
    fclose(keyFile);
    return 0;
}


int KeyGen(uint64_t *key)
{
    do
    {
        if(SystemRandom(key) != 0)
        {
            printf("Error: key generation fail\n");
            return -1;
        }
    }while(!KeyCheck(key));
    
    return 0;
}
