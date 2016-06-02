.PHONY: pso ga test clean

CPP=g++
CPPFLAGS=-O3 -std=c++11
SRC_FOLDER=src
TEST_FOLDER=test
MAIN_FILE=main.cpp
EXE=run

all:
	@make pso
	@make ga

pso:
	@$(CPP) $(CPPFLAGS) $(SRC_FOLDER)/pso/*.cpp pso_$(MAIN_FILE) -o pso_$(EXE)

ga:
	@$(CPP) $(CPPFLAGS) $(SRC_FOLDER)/ga/*.cpp ga_$(MAIN_FILE) -o ga_$(EXE)

test:
	@$(CPP) $(CPPFLAGS) $(SRC_FOLDER)/ga/*.cpp $(TEST_FOLDER)/ga/*.cpp -o $(EXE) && ./$(EXE)

clean:
	@rm ./*_$(EXE)

