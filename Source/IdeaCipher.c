//  Created by ivan sarno on 02/12/14.
//  Copyright (c) 2014 ivan sarno.
/*
 This file is part of IDEA-cipher library
 IDEA-cipher  is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 IDEA-cipher  is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with IDEA-cipher ; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
 USA
 */
//Version V.2.0

#include <stdio.h>
#include <stdlib.h>
#include "IDEA.h"
#include "KeyCreation.h"
#include <string.h>
#include <sys/stat.h>


const char *manString = " IdeaCipher -h: print this man.\n \
IdeaCipher --help: print this man.\n \
IdeaCipher -k: creates a 128 bits key and a 64 bit nonce ad stores these in a file called output in the current directory.\n \
IdeaCipher -e inputFile: encrypt inputFile and creates the ouptput file and key file in the current directory. key file contains 172 random bit for key and nonce.\n \
IdeaCipher -e inputFile keyFile: encrypt inputFile and creates the ouptput file in the current directory, keyFile must contains 172 random bit for key and nonce.\n \
IdeaCipher -d inputFile keyFile: decrypt inputFile and create the ouptput file in the current directory. keyFile must contains 172 random bit for key and nonce.\n";

const char *errorInputString = "Input Error. Run \"IdeaCipher -h\" for help.\n";

int KeyStore(uint64_t *key)
{
    printf("KeyStore not avaiable");
    return 0;
}

int Encryption(uint64_t *message, uint64_t *key, uint64_t size)
{
    printf("Encryption not avaiable");
    return 0;
    /*
    if(IdeaCBCEncrypt(message, key, key[2], size) == size)
    {
        printf("Error: encyption fail\n");
        return 3;
    }
    return 0;*/
}

int Decription(uint64_t *message, uint64_t *key, uint64_t size)
{
    printf("Decryption not avaiable");
    return 0;
    /*
     if(IdeaCBCDecrypt(message, key, key[2], size) == size)
     {
     printf("Error: encyption fail\n");
     return 3;
     }
     return 0;*/
}

int GenAndEncrypt(uint64_t *message, uint64_t size, FILE *output)
{
    printf("GenAndEncrypt not avaiable");
    return 0;

    /*uint64_t key[3];
    if(KeyStore(key) != 0)
    {
        printf("Error: key generation fail\n");
        SecureMemoryWipe((void *)key, 24);
        return 3;
    }
    if(Encryption(message, key, size) != 0)
    {
        SecureMemoryWipe((void *)key, 24);
        return 3;
    }

    if(fwrite(message, sizeof(uint64_t), size, output) != size)
    {
        printf("error on output writing\n");
        SecureMemoryWipe((void *)key, 24);
        return 3;
    }

    SecureMemoryWipe((void *)key, 24);
    return 0;*/
}

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
    {
        uint64_t key[3];
        int result = KeyStore(key);
        SecureMemoryWipe((void *)key, 24);
        return result;
    }

    if(argc < 3)
    {
        printf("%s", errorInputString);
        return 1;
    }

    //file reading
    FILE *input = NULL;
    FILE *output = NULL;
#ifndef SAFEIO
    input = fopen(argv[2], "rb");
    output = fopen("output", "wb");
#endif

#ifdef SAFEIO
    fopen_s(&input,argv[2], "rb");
    fopen_s(&output,"output", "wb");
#endif

    if(!input || !output)
    {
        printf("Error: Can't open input or create output file.\n");
        return 2;
    }

    struct stat st;
    stat(argv[2], &st);
    uint64_t size = (st.st_size) / 8 + 1;

    uint64_t *message = (uint64_t *) malloc(size * sizeof(uint64_t));
    if(!message)
    {
        printf("Error: memory allocation.\n");
        return 2;
    }
    //set padding to 0
    message[size-2] = message[size-1] = 0;

    if(fread(message, sizeof(char), st.st_size, input) != st.st_size)
    {
        printf("Error: Can't read input file.\n");
        return 2;
    }

    if(strcmp(argv[1], "-e") == 0 && argc==3)
    {
        int result;
        result = GenAndEncrypt(message, size, output);

        fclose(input);
        fclose(output);
        free(message);
        return result;
    }

    if(argc < 4)
    {
        printf("%s", errorInputString);
        free(message);
        return 1;
    }


    //key reading
    FILE *keyFile = NULL;
    uint64_t key[3];
#ifndef SAFEIO
    keyFile = fopen(argv[3], "rb");
#endif

#ifdef SAFEIO
    fopen_s(&keyFile,argv[3], "rb");
#endif

    if(!keyFile || (fread(key, sizeof(uint64_t), 3, keyFile) != 3))
    {
        printf("Error: Can't read key file.\n");
        SecureMemoryWipe((void *)key, 24);
        free(message);
        return 2;
    }

    int result;
    if(strcmp(argv[1], "-e") == 0)
        result = Encryption(message, key, size);
    else if(strcmp(argv[1], "-d") == 0)
        result = Decription(message, key, size);
        else
        {
            printf("%s", errorInputString);
            free(message);
            SecureMemoryWipe((void *)key, 24);
            return 1;
        }

    if(result==0)
        //output writing
        if(fwrite(message, sizeof(uint64_t), size, output) != size)
        {
            result = 3;
            printf("error on output writing\n");
        }

    SecureMemoryWipe((void *)key, 24);
    fclose(keyFile);
    fclose(input);
    fclose(output);
    free(message);
    return result;


}
