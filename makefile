# mostly copied from my own personal makefile for c++ projects
OUT_EN			:= ensamblador.exe
SCR_EN			:= $(wildcard ensamblador/*cpp ensamblador/**/*.cpp)
OUT_DE			:= desensamblador.exe
SCR_DE			:= $(wildcard desensamblador/*cpp desensamblador/**/*.cpp)


CXXFLAGS		:= -std=c++23
BUILD_DIR		:= .build

# BC I'm on windows, for linux sh or whatever other command line i would have to change them mannually, OR make some really big if statement
# but i'm too lazy to copy it from my own makefile... so...
MKDIR			:= cmd /c if not exist $(BUILD_DIR) mkdir
CLR				:= cls
RM				:= cmd /c rmdir /s /q

EXE_EN			:= $(BUILD_DIR)/$(OUT_EN)
EXE_DE			:= $(BUILD_DIR)/$(OUT_DE)

.PHONY: build en_build de_build run en_run de_run clean clear cls

all: build run clean

#	BUILD
build: en_build de_build

en_build:
	$(MKDIR) $(BUILD_DIR)
	g++ $(SCR_EN) $(CXXFLAGS) -o $(EXE_EN)

de_build:
	$(MKDIR) $(BUILD_DIR)
	g++ $(SCR_DE) $(CXXFLAGS) -o $(EXE_DE)

#	RUN
run: 
	$(CLR)
	./$(EXE_EN)
	./$(EXE_DE)

en_run:
	$(CLR)
	./$(EXE_EN)

de_run:
	$(CLR)
	./$(EXE_DE)

#	CLEAN
clean:
	-$(RM) $(BUILD_DIR)

clear: clean

cls: clean
	$(CLR)