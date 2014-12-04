//
//  main.c
//  IDEA
//
//  Created by ivan sarno on 02/12/14.
//  Copyright (c) 2014 ivan sarno. All rights reserved.
//

#include <stdio.h>
#include "Round.h"
#include "IDEA.h"
#include "Keycreate.h"

int main(int argc, const char * argv[]) {
    typeint2 key[]=/*{0x0960, 0x0af0, 0x0c80, 0x0190, 0x0320, 0x04b0};{0xb005, 0x7806, 0x4000, 0xc801, 0x0640, 0x07d0};*/{0x0064, 0x00c8, 0x012c, 0x0190, 0x01f4, 0x0258, 0x02bc, 0x0320};
    typeint message[]=/*{0xec90, 0xb610, 0xaa33, 0x22ec};{0xf1b7, 0x8e88, 0x78e2, 0x4170}; */{0x0532, 0x0a64, 0x14c8, 0x19fa};
    printf("%x %x %x %x\n",message[0],message[1],message[2],message[3]);
    //Round(message,key);
    
    /*IDEAencrypt(message,key);
    printf("%x %x %x %x\n",message[0],message[1],message[2],message[3]);
    IDEAdecrypt(message,key);
    printf("%x %x %x %x\n",message[0],message[1],message[2],message[3]);*/
     
    /*typeint subkey[56];
    printf("%x %x %x %x %x %x %x %x\n",key[0],key[1],key[2],key[3],key[4],key[5],key[6],key[7]);
    deckey(key,subkey);
    printf("%x %x %x %x %x %x %x %x\n",subkey[44],subkey[45],subkey[46],subkey[47],subkey[48],subkey[49],subkey[50],subkey[51]);
    return 0;*/
}
