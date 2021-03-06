#OBJS specifies which files to compile as part of the project
OBJS = ~/programs/gb_emu/src/main.cpp ~/programs/gb_emu/src/cpu.cpp 

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = gb_emu

#This is the target that compiles our executable
all : $(OBJS)
	g++ $(OBJS)  -O3 -lSDL2 -std=c++11 -lSDL_ttf -o $(OBJ_NAME)
#debug build
debug : $(OBJS)
	g++ $(OBJS) -g3 -lSDL2 -std=c++11 -lSDL_ttf -o $(OBJ_NAME)
