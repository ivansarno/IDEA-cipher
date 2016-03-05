IDEA-cipher
===========

IDEA cryptography algorithm implementation

**IdeaCipher**

IdeaCipher is a stand alone command-line program that provides encryption/decryption of a file and key creation.  
Run "IdeaCipher -h" for complete man.

**IdeaLib**

IdeaLib provides a implementation of IDEA algorithm for every need:

	-Key creation function
	-Encryption/Decryption functions
	-Cipher Block Modes: CBC, PCBC, CFB, OFB, CTR
	-Random Number Generator based on IDEA
  
  
**Other**

The library is accompanied by:

	-Test program: to verify the proper functioning of the library
	-Makefile, with target: IdeaCipher, IdeaLib, Test, DebugIdeaCipher, DebugIdeaLib, DebugTest
  
Compiler Warning

Recommended C dialect: C11  
If your compiler reports warning or error for deprecated I/O function, define SAFEIO macro to solve


