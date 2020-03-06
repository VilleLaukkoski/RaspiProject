CXX		  := /mnt/e/linuxShit/compiler/cross-pi-gcc-9.2.0-2/bin/arm-linux-gnueabihf-gcc
CXX_FLAGS := -Wall -Wextra -std=c11 -ggdb

BIN		:= bin
SRC		:= src
INCLUDE	:= include
LIB		:= lib

LIBRARIES	:= -lwiringPi -lm -lpthread -lrt -lcrypt
EXECUTABLE	:= app


all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.c
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)

clean:
	-rm $(BIN)/*
