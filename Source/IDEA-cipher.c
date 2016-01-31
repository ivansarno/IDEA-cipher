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
//Version V.1.4

#include <stdio.h>
#include <stdlib.h>
#include "IDEA.h"
#include <string.h>

/*
 IDEA-cipher is a stand alone program thet takes as input:

 number of char (multiple of 8);

 "e" to encrypt or "d" to decrypt

 text file

 key file (128 bit)

 and return output file in current directory
*/


int main(int argc, char **argv)
{
  //get input
	if (argc <5)
	{
		printf("error: incorrect arguments\n");
		return -1;
	}

	unsigned long original_number = atoi(argv[2]); //number of bytes to process
	unsigned long effective_number = original_number / 2; //size of IDEA block is 2 bytes
  while(effective_number % 4)
    effective_number++;

    FILE *textfile = NULL;
    FILE *keyfile = NULL;

#ifndef SAFEIO
	textfile = fopen(argv[3], "rb");
	keyfile = fopen(argv[4], "rb");
#endif

#ifdef SAFEIO
	fopen_s(&textfile,argv[3], "rb");
	fopen_s(&keyfile,argv[4], "rb");
#endif

	if (!(textfile && keyfile))
	{
		printf("error: can't open files\n");
		return -1;
	}

	uint16_t *text = (uint16_t *) malloc(effective_number * sizeof(uint16_t));
    if(!text)
    {
        fclose(textfile);
        fclose(keyfile);
        printf("error: malloc fail\n");
        return -1;
    }
	uint16_t key[8];
  unsigned long check;

	check = fread(text, sizeof(uint8_t), original_number, textfile);
    if(check == original_number)
    {
        check = fread(key, sizeof(uint16_t), 8, keyfile);
        if(check == 8)
        {
            //processing
            if (strcmp(argv[1], "-c")==0 || strcmp(argv[1], "-e")==0)
                check = IDEA_multi_encrypt(text, key, effective_number);
            else if (strcmp(argv[1], "-d")==0)
                check = IDEA_multi_decrypt(text, key, effective_number);
                else
                    printf("invalid command\n");

            if(check == effective_number)
            {
#ifndef SAFEIO
                FILE *out = fopen("output", "wb"); //open file
#endif

#ifdef SAFEIO
                FILE *out;
                fopen_s(&out,"output", "wb");
#endif

                if(out)
                {
                    if(fwrite(text, sizeof(uint16_t), effective_number, out) != effective_number) //writes output
                        printf("error on output writing\n");
                    fclose(out);
                    printf("output composed by %lu bytes\n", 2*effective_number);
                }
                else
                    printf("error: can't create out file\n");
            }
            else
                printf("error\n");


        }
        else
            printf("error: key size incorrect\n");

    }
    else
        printf("error: text size incorrect\n");


	fclose(textfile);
	fclose(keyfile);
  free(text);



	return 0;

}
