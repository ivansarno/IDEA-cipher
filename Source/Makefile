CFLAG = -std=c11 -O3
DebugCFLAG = -std=c11 -g
IdeaLibObjects = IdeaGenerators.o IdeaStream.o IdeaMode.o IdeaCore.o

IdeaCipher : IdeaCipher.o $(IdeaLibObjects)

IdeaLib :  $(IdeaLibObjects)
	ar rcs IdeaLib.a $^

Test : Test.o $(IdeaLibObjects)

DebugIdeaCipher : CFLAG = $(DebugCFLAG)
DebugIdeaCipher : IdeaCipher.o $(IdeaLibObjects)
	
DebugTest : CFLAG = $(DebugCFLAG)
DebugTest : Test.o $(IdeaLibObjects)
	
IdeaLibParallel : CFLAG = $(CFLAG) -fopenmp
IdeaLibParallel :  $(IdeaLibObjects)
	ar rcs IdeaLib.a $^

TestParallel : CFLAG = $(CFLAG) -fopenmp
TestParallel : Test.o $(IdeaLibObjects)
