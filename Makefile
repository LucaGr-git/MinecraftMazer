.default: all

all: mazeRunner

clean:
	rm -f mazeRunner *.o

mazeRunner: Maze.o Agent.o mazeRunner.o HeightArray2D.o BlockArray3D.o MazeCoordinate.o
	g++ -Wall -Werror -std=c++17 -g -O -o $@ $^ -lmcpp

%.o: %.cpp
	g++ -Wall -Werror -std=c++17 -g -O -c $^