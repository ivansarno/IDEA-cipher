IDEA-cipher
===========

IDEA cryptography algorithm implementation

IDEA-cipher is a stand alone program with this command line syntax:

	IDEA cmd number_of_bytes input_file key_file
	
	when cmd is: -e to encrypt or -d to decrypt
	and key_file contains a random key of 128 bits

the program creates the output file in current directory.

IDEA.h contains a set of functions that implement IDEA algorithm for every need

**Compiler Warning**

If your compiler reports warning or error for deprecated I/O function, define SAFEIO macro to solve


