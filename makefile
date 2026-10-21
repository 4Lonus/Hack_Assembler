# mostly copied from my own personal makefile for c++ projects
OUT			:= assembler.exe
SCR			:= $(wildcard src/*cpp src/**/*.cpp)
CXXFLAGS	:= -std=c++23
BUILD_DIR	:= .build

# BC I'm on windows, for linux sh or whatever other command line i would have to change them mannually, OR make some really big if statement
# but i'm too lazy to copy it from my own makefile... so...
MKDIR		:= cmd /c if not exist $(BUILD_DIR) mkdir
CLR			:= cls
RM			:= cmd /c rmdir /s /q

EXE			:= $(BUILD_DIR)/$(OUT)

.PHONY: build run clean clear cls

all: build run clean

build:
	$(MKDIR) $(BUILD_DIR)
	g++ $(SCR) $(CXXFLAGS) -o $(EXE)

run:
	$(CLR)
	./$(EXE)

clean:
	-$(RM) $(BUILD_DIR)

clear: clean

cls: clean
	$(CLR)