#include <iostream>
#include <vector>
#include <utility>
#include <vector>
#include <sstream>
#include <fstream>


class Maze{
    public:
        int seed;
        int rows;
        int columns;
        std::string filename;
        int *grid;
        int *visitors;

        Maze(int seed, int rows, int columns, std::string filename);
        void createGrid(int rows, int cols);
        void mazeCheck(std::pair < int, int > current, std::pair < int, int > neighbor, std::vector < std::pair < int, int > > &holdNeighbors, int rows, int cols, std::vector < char > &direction);
        void mazeChange(int seed, int rows, int cols);
        void writeFile(std::string filename, int rows, int cols);
        ~Maze();
};
