#include <stdio.h>
#include <stdlib.h>
#include "IDEA.h"
#include "define.h"
/*
 IDEA-cipher is a stand alone program thet takes as input:
 
 number of char (multiple of 8);
 
 e to encrypt or d to decrypt
 
 text file
 
 key file (128 bit)
 
 and return output file in current directory
*/


int main(int argc, char **argv)
{
	if (argc <5)
	{
		printf("error input\n");
		return 0;
	}

	int num = atoi(argv[1]);
	if (num % 8)
	{
		printf("error: number of character must be multiple of 8\ncomplete message and key with random char\n");
		return 0;
	}

	num /= 2; //1 block of 16 bit represents 2 char

	FILE *textfile, *keyfile;

#ifdef unix
	textfile = fopen(argv[3], "rb");
	keyfile = fopen(argv[4], "rb");
#endif

#ifdef windows
	fopen_s(&textfile,argv[3], "rb");
	fopen_s(&keyfile,argv[4], "rb");
#endif

	if (!(textfile && keyfile))
	{
		printf("error input\n");
		return 0;
	}

	uint16_t *text = (uint16_t *) malloc(num * sizeof(uint16_t));
	uint16_t key[8];

	fread(text, sizeof(uint16_t), num, textfile);
	fread(key, sizeof(uint16_t), 8, keyfile);

	if (argv[2][0] == 'c' || argv[2][0] == 'e')
		IDEA_multi_encrypt(text, key,num);
	else if (argv[2][0] == 'd')
		IDEA_multi_decrypt(text, key,num);

#ifdef unix
	FILE *out = fopen("output", "wb");
#endif

#ifdef windows
	FILE *out; 
	fopen_s(&out,"output", "wb");
#endif

	fwrite(text, sizeof(uint16_t), num, out);

	fclose(textfile);
	fclose(keyfile);
	fclose(out);


	return 0;

}
