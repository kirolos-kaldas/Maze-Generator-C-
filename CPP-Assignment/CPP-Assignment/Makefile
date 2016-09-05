FLAGS = -Wall -pedantic -std=c++14
DEBUG = -g -ggdb
PROG = mazer
OBJ = Main.o Maze.o Generator.o Cell.o Edge.o ArgsParser.o

%.o: %.cpp
	g++ $(FLAGS) $(DEBUG) -c $< -o $@

all: $(OBJ)
	g++ -o $(PROG) $(OBJ)

clean:
	rm -f $(OBJ) $(PROG)