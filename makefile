PATH_TO_MAIN ?= main.cpp
NAME ?= main
OUT_DIRECTORY ?= .
STEPS = compile link clean

all: $(STEPS)

compile: 
	@g++ -IInclude -c $(basename $(PATH_TO_MAIN)).cpp

link:
	@g++ $(notdir $(basename $(PATH_TO_MAIN)).o) -o $(OUT_DIRECTORY)/$(NAME) -LLibrary -lchargraph

clean: 
	@del *.o