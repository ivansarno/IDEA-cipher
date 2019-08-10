IDEA-cipher
===========

IDEA cryptography algorithm implementation

**This project was designed for learning purposes, its use in real systems is not recommended. This project is not updated regularly.**

**IdeaCipher**

IdeaCipher is a stand alone command-line program that provides encryption/decryption of a file, key creation and random bytes generation.  
Run "IdeaCipher -h" for complete manual.

**IdeaLib**

IdeaLib provides a implementation of IDEA algorithm for every need:

	-Key creation function
	-Encryption/Decryption functions
	-Cipher Block Modes: CBC, PCBC, CFB, OFB, CTR
	-Stream Operation (processing of individual blocks from a steam)
	-Random Number Generators based on IDEA
	-Parallel CTR mode using openmp


**Other**

The library is accompanied by:

	-Test program: to verify the proper functioning of the library
	-Makefile, with target: IdeaCipher, IdeaLib, Test, DebugIdeaCipher, IdeaLibParallel, TestParallel

Compiler Warning

Recommended C dialect: C11  
If your compiler reports warning or error for deprecated I/O function, define SAFEIO macro to solve
