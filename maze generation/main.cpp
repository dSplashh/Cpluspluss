#include "maze.h"

int main(int argc, char *argv[]) {

    Maze maze((std::stoi(argv[1])),  (std::stoi(argv[2])),  (std::stoi(argv[3])), argv[4]);
    maze.mazeChange(maze.seed, maze.rows, maze.columns);
    maze.writeFile(maze.filename, maze.rows, maze.columns);

    return 0;
}
