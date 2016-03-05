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
//Version V.2.1

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
IdeaCipher -d inputFile keyFile: decrypt inputFile and create the ouptput file in the current directory. keyFile must contains 172 random bit for key and nonce.\n";

const char *errorInputString = "Input Error. Run \"IdeaCipher -h\" for help.\n";

int SystemRandom(uint64_t *buffer)
{
#ifdef _WIN32
    uint32_t *buff32 = (uint32_t *) buffer;
    for(int i=0; i<6; i++)
        if(rand_s(buff32))
            buff32++;
        else return 1;
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
        return 2;
    }

    if(fwrite(key, sizeof(uint64_t), 3, keyFile) != 3)
    {
        printf("Error: key writing fail\n");

        fclose(keyFile);
        return 3;
    }

    fclose(keyFile);
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
        return 2;
    }

    fclose(keyFile);
    return 0;
}

static inline int KeyGen(uint64_t *key)
{
    do
    {
        if(SystemRandom(key) != 0)
        {
            printf("Error: key generation fail\n");
            return 2;
        }
    }while(!KeyCheck(key));

    return 0;
}

//return information on size in bytes and in uint64_t in the first values of the array
uint64_t *MessageRead(char *messageFileName)
{
    FILE *input = NULL;
#ifndef SAFEIO
    input = fopen(messageFileName, "rb");
#else
    fopen_s(&input,messageFileName, "rb");
#endif

    if(!input)
    {
        printf("Error: Can't open input.\n");
        return NULL;
    }

    struct stat st;
    stat(messageFileName, &st);
    uint64_t byteSize = (uint64_t) st.st_size; //size in bytes
    uint64_t intSize = (uint64_t)  (st.st_size) / 8 + 1; //size in 64 bit integers

    //first 2 values of message contain size in bytes and integer of the message
    uint64_t *message = (uint64_t *) malloc((intSize + 2) * sizeof(uint64_t));
    if(!message)
    {
        printf("Error: memory allocation.\n");
        fclose(input);
        return NULL;
    }
    //set padding to 0
    message[intSize] = message[intSize+1] = 0;

    if(fread(message+2, sizeof(uint8_t), byteSize, input) != byteSize)
    {
        printf("Error: Can't read input file.\n");
        free(message);
        fclose(input);
        return NULL;
    }

    message[0] = intSize;
    message[1] = byteSize;

    fclose(input);
    return message;
}

int MessageWrite(uint64_t *message, uint64_t byteSize)
{
    FILE *output = NULL;
#ifndef SAFEIO
    output = fopen("output", "wb");
#else
    fopen_s(&output,"output", "wb");
#endif

    if(!output)
    {
        printf("Error: Can't create output file.\n");
        return 2;
    }

    if(fwrite(message, sizeof(uint8_t), byteSize, output) != byteSize)
    {
        printf("error on output writing\n");
        fclose(output);
        return 3;
    }

    fclose(output);
    return 0;
}

static inline int GenAndStore()
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
    uint64_t *message=MessageRead(messageFileName);

    if(!message)
        return 1;

    uint64_t key[3];
    if(KeyGen(key))
    {
        free(message);
        return 1;
    }

    //first 2 values of message contain size in bytes and integer of the message
    if(IdeaCBCEncrypt(message+2, key, key[2], message[0]) != message[0])
    {
        SecureMemoryWipe(key, 24);
        printf(("Error: Encryption fail.\n"));
        free(message);
        return 2;
    }

    //write origial file size in bytes to remove padding in decryption
    if(MessageWrite(message+1, (message[0]+1)*8))
    {
        SecureMemoryWipe(key, 24);
        free(message);
        return 3;
    }

    free(message);
    if(KeyWrite(key))
    {
        SecureMemoryWipe(key, 3);
        return 3;
    }

    SecureMemoryWipe(key, 3);
    return 0;
}

int Encrypt(char *messageFileName, char *keyFileName)
{
    uint64_t *message=MessageRead(messageFileName);

    if(!message)
        return 1;

    uint64_t key[3];
    if(KeyRead(keyFileName, key))
    {
        free(message);
        return 1;
    }

    //first 2 values of message contain size in bytes and integer of the message
    if(IdeaCBCEncrypt(message+2, key, key[2], message[0]) != message[0])
    {
        SecureMemoryWipe(key, 24);
        printf(("Error: Encryption fail.\n"));
        free(message);
        return 2;
    }

    //write origial file size in bytes to remove padding in decryption
    if(MessageWrite(message+1, (message[0]+1)*8))
    {
        SecureMemoryWipe(key, 24);
        free(message);
        return 3;
    }

    free(message);
    SecureMemoryWipe(key, 3);
    return 0;
}

int Decrypt(char *messageFileName, char *keyFileName)
{
    uint64_t *message=MessageRead(messageFileName);

    if(!message)
        return 1;

    uint64_t key[3];
    if(KeyRead(keyFileName, key))
    {
        free(message);
        return 1;
    }

    //first 2 values of message contain size in bytes and integer of the message
    if(IdeaCBCDecrypt(message+3, key, key[2], message[0]-1) != message[0]-1)
    {
        SecureMemoryWipe(key, 24);
        printf(("Error: Encryption fail.\n"));
        free(message);
        return 2;
    }

    //uising information stored in encryption phase to remove de padding
    if(MessageWrite(message+3, message[2]))
    {
        SecureMemoryWipe(key, 24);
        free(message);
        return 3;
    }

    free(message);
    SecureMemoryWipe(key, 3);
    return 0;
}

////////////
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

    printf("%s", errorInputString);

    return 1;
}
