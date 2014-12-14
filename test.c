//
//  main.c
//  IDEA
//
//  Created by ivan sarno on 02/12/14.
//  Copyright (c) 2014 ivan sarno. All rights reserved.
//

//main for testing

/*#include <stdio.h>
#include "Round.h"
#include "IDEA.h"
#include "Keycreate.h"

int main(int argc, const char * argv[]) {
    typeint2 key[]={0x0118, 0x00d7, 0x012c, 0x0270, 0x01e4, 0x489, 0x0445, 0x0700};
	typeint2 key2[] ={ 0x0118, 0x00d7, 0x012c, 0x0270, 0x01e4, 0x489, 0x0445, 0x0700};
    typeint message[]= {8158, 0x776, 7645, 3333}; 
    printf("%x %x %x %x\n",message[0],message[1],message[2],message[3]);

	typeint2 subkey[56];
	typeint2 dec[56];
	deckey(key, dec);
	keycreate(key2, subkey);
    
    IDEA_crypt(message,subkey);
    printf("%x %x %x %x\n",message[0],message[1],message[2],message[3]);
    IDEA_crypt(message,dec);
    printf("%x %x %x %x\n",message[0],message[1],message[2],message[3]);
     
   
}
*/