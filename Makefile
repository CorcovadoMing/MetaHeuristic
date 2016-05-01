.PHONY: test clean

CPP=g++
CPPFLAGS=-O3 -std=c++11
SRC_FOLDER=src
TEST_FILE=test/test.cpp
MAIN_FILE=main.cpp
EXE=mhpsga

all:
	@$(CPP) $(CPPFLAGS) $(SRC_FOLDER)/*.cpp $(MAIN_FILE) -o $(EXE)

test:
	@$(CPP) $(CPPFLAGS) $(SRC_FOLDER)/*.cpp $(TEST_FILE) -o $(EXE) && ./$(EXE)

clean:
	@rm ./$(EXE)

