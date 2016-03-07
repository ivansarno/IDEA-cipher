CFLAG = -std=c11 -O3
DebugCFLAG = -std=c11 -g

IdeaCipher : IdeaCipher.o IdeaLib.o IdeaGenerators.o KeyCreation.o Round.o

IdeaLib :  IdeaLib.o IdeaGenerators.o KeyCreation.o Round.o
	ar rcs IdeaLib.a $^

Test : Test.o IdeaLib.o KeyCreation.o Round.o

DebugIdeaCipher : IdeaCipher.c IdeaLib.c IdeaGenerators.c KeyCreation.c Round.c
	$(CC) $(DebugCFLAG) IdeaCipher.c IdeaLib.c IdeaGenerators.c KeyCreation.c Round.c -o DebugIdeaCipher

DebugTest : Test.c IdeaLib.c KeyCreation.c Round.c
	$(CC) $(DebugCFLAG) Test.c IdeaLib.c KeyCreation.c Round.c -o DebugTest
