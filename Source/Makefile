CFLAG = -std=c11 -O3
DebugCFLAG = -std=c11 -g
IdeaLibObjects = IdeaGenerators.o IdeaStream.o IdeaMode.o IdeaCore.o
IdeaLibFiles = IdeaGenerators.c IdeaStream.c IdeaMode.c IdeaCore.c
IdeaLibHeaders = IdeaLib.h

IdeaCipher : IdeaCipher.o $(IdeaLibObjects)

IdeaLib :  $(IdeaLibObjects)
	ar rcs IdeaLib.a $^

Test : Test.o $(IdeaLibObjects)

DebugIdeaCipher : IdeaCipher.c $(IdeaLibFiles) $(IdeaLibHeaders)
	$(CC) $(DebugCFLAG) IdeaCipher.c $(IdeaLibFiles) -o DebugIdeaCipher

DebugTest : Test.c $(IdeaLibFiles) $(IdeaLibHeaders)
	$(CC) $(DebugCFLAG) Test.c $(IdeaLibFiles) -o DebugTest
