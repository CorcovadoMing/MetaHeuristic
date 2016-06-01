.PHONY: test clean

CPP=g++
CPPFLAGS=-O3 -std=c++11
SRC_FOLDER=src
TEST_FOLDER=test
MAIN_FILE=main.cpp
EXE=run

pso:
	@$(CPP) $(CPPFLAGS) $(SRC_FOLDER)/pso/*.cpp pso_$(MAIN_FILE) -o $(EXE)

ga:
	@$(CPP) $(CPPFLAGS) $(SRC_FOLDER)/ga/*.cpp ga_$(MAIN_FILE) -o $(EXE)

test:
	@$(CPP) $(CPPFLAGS) $(SRC_FOLDER)/ga/*.cpp $(TEST_FOLDER)/ga/*.cpp -o $(EXE) && ./$(EXE)

clean:
	@rm ./$(EXE)

