CFLAG = -std=c11 -O3
DebugCFLAG = -std=c11 -g
IdeaLibObjects = IdeaLib.o IdeaGenerators.o IdeaStream.o KeyCreation.o Round.o
IdeaLibFiles = IdeaLib.c IdeaGenerators.c IdeaStream.c KeyCreation.c Round.c
IdeaLibHeaders = IdeaLib.h KeyCreation.h Round.h

IdeaCipher : IdeaCipher.o $(IdeaLibObjects)

IdeaLib :  $(IdeaLibObjects)
	ar rcs IdeaLib.a $^

Test : Test.o $(IdeaLibObjects)

DebugIdeaCipher : IdeaCipher.c $(IdeaLibFiles) $(IdeaLibHeaders)
	$(CC) $(DebugCFLAG) IdeaCipher.c $(IdeaLibFiles) -o DebugIdeaCipher

DebugTest : Test.c $(IdeaLibFiles) $(IdeaLibHeaders)
	$(CC) $(DebugCFLAG) Test.c $(IdeaLibFiles) -o DebugTest
