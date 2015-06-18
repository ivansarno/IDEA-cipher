//Version V.1.2

#include <stdio.h>
#include <stdlib.h>
#include "IDEA.h"
#include "define.h"
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
		printf("error input\n");
		return -1;
	}

	int num = atoi(argv[1]); //number of char to process
	if (num % 8 || num < 0)
	{
		printf("error: number of character must be multiple of 8\ncomplete message and with random char\n");
		return -1;
	}

	num /= 2; //1 block of 16 bit represents 2 char

    FILE *textfile = NULL;
    FILE *keyfile = NULL;

#ifdef Unix
	textfile = fopen(argv[3], "rb");
	keyfile = fopen(argv[4], "rb");
#endif

#ifdef Windows
	fopen_s(&textfile,argv[3], "rb");
	fopen_s(&keyfile,argv[4], "rb");
#endif

	if (!(textfile && keyfile))
	{
		printf("error: can't open files\n");
		return -1;
	}

	uint16_t *text = (uint16_t *) malloc(num * sizeof(uint16_t));
    if(!text)
    {
        fclose(textfile);
        fclose(keyfile);
        printf("error: malloc fail\n");
        return -1;
    }
	uint16_t key[8];
    long check;

	check = fread(text, sizeof(uint16_t), num, textfile);
    if(check == num)
    {
        check = fread(key, sizeof(uint16_t), 8, keyfile);
        if(check == 8)
        {
            if (argv[2][0] == 'c' || argv[2][0] == 'e')
                check = IDEA_multi_encrypt(text, key,num);
            else if (argv[2][0] == 'd')
                check = IDEA_multi_decrypt(text, key,num);
                else
                    printf("invalid command\n");


            if(check == num)
            {
#ifdef Unix
                FILE *out = fopen("output", "wb");
#endif

#ifdef Windows
                FILE *out;
                fopen_s(&out,"output", "wb");
#endif

                if(out)
                {
                    if(fwrite(text, sizeof(uint16_t), num, out) !=num)
                        printf("error\n");
                    fclose(out);
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
