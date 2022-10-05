#include "maze.h"

Maze::Maze(int seed, int rows, int columns, std::string filename) {
    this-> seed = seed;
    this-> rows = rows;
    this-> columns = columns;
    this-> filename = filename;
    grid = new int[rows * columns];
    visitors = new int[rows * columns];
}

void Maze::createGrid(int rows, int cols) {
    this-> rows = rows;
    this-> columns = cols;

    for (int r = 0; r < rows; r++){
        for (int c = 0; c < cols; c++){
            *(grid + (r * cols + c)) = 15;
            *(visitors + (r * cols + c)) = 0;
        }
    }
    *(grid + (0 * cols + 0)) -= 8;
    *(grid + ((rows - 1) * cols + (cols - 1))) -= 4;
    *(visitors + (0 * cols + 0)) = 1;
}

void Maze::mazeCheck(std::pair < int, int > current, std::pair < int, int > neighbor, std::vector < std::pair < int, int > > &holdNeighbors, int rows, int cols, std::vector < char > &direction) {

    this-> rows = rows;
    this-> columns = cols;

    if (current.first - 1 >= 0) {
        if (*(visitors + ((current.first - 1) * cols + current.second)) != 1) {
            neighbor.first = current.first - 1;
            neighbor.second = current.second;
            holdNeighbors.push_back(neighbor);
            direction.push_back('N');
        }
    }
    if (current.first + 1 <= rows - 1){
        if (*(visitors + ((current.first + 1) * cols + current.second)) != 1) {
            neighbor.first = current.first + 1;
            neighbor.second = current.second;
            holdNeighbors.push_back(neighbor);
            direction.push_back('S');
        }
    }
    if (current.second + 1 <= cols - 1) {
        if (*(visitors + (current.first * cols + current.second + 1)) != 1) {
            neighbor.first = current.first;
            neighbor.second = current.second + 1;
            holdNeighbors.push_back(neighbor);
            direction.push_back('E');
        }

    }
    if (current.second - 1 >= 0) {
        if (*(visitors + (current.first * cols + current.second - 1)) != 1) {
            neighbor.first = current.first;
            neighbor.second = current.second - 1;
            holdNeighbors.push_back(neighbor);
            direction.push_back('W');
        }

    }
}



void Maze::mazeChange(int seed, int rows, int cols) {
    this-> rows = rows;
    this-> columns = cols;
    std::srand(seed);

    createGrid(rows, cols);

    std::pair < int, int > current(0, 0);
    std::pair < int, int > neighbor;
    std::vector < std::pair < int, int > > holdNeighbors;
    std::vector< std::pair < int, int > > holdCurrent;
    std::vector < char > direction;

    holdCurrent.push_back(current);


    while (!holdCurrent.empty()) {
        current = holdCurrent.back();
        holdCurrent.pop_back();

        mazeCheck(current, neighbor, holdNeighbors, rows, cols, direction);

        if (!holdNeighbors.empty()) {
            
            holdCurrent.push_back(current);

            int idx = (std::rand() / ((RAND_MAX + 1u) / holdNeighbors.size()));

            if (direction[idx] == 'N') {
                *(grid + ((holdNeighbors[idx].first) * cols + (holdNeighbors[idx].second))) -= 4;
                *(grid + ((current.first) * cols + (current.second))) -= 8;
                *(visitors + ((holdNeighbors[idx].first) * cols + (holdNeighbors[idx].second))) = 1;
                holdCurrent.push_back(holdNeighbors[idx]);
            }
            else if (direction[idx] == 'S') {
                *(grid + ((holdNeighbors[idx].first) * cols + (holdNeighbors[idx].second))) -= 8;
                *(grid + ((current.first) * cols + (current.second))) -= 4;
                *(visitors + ((holdNeighbors[idx].first) * cols + (holdNeighbors[idx].second))) = 1;
                holdCurrent.push_back(holdNeighbors[idx]);
            }
            else if (direction[idx] == 'W') {
                *(grid + ((holdNeighbors[idx].first) * cols + (holdNeighbors[idx].second))) -= 2;
                *(grid + ((current.first) * cols + (current.second))) -= 1;
                *(visitors + ((holdNeighbors[idx].first) * cols + (holdNeighbors[idx].second))) = 1;
                holdCurrent.push_back(holdNeighbors[idx]);
            }
            else if (direction[idx] == 'E') {
                *(grid + ((holdNeighbors[idx].first) * cols + (holdNeighbors[idx].second))) -= 1;
                *(grid + ((current.first) * cols + (current.second))) -= 2;
                *(visitors + ((holdNeighbors[idx].first) * cols + (holdNeighbors[idx].second))) = 1;
                holdCurrent.push_back(holdNeighbors[idx]);
            }

            holdNeighbors.clear();
            direction.clear();
        }
    }
}

void Maze::writeFile(std::string filename, int rows, int cols){
    this-> rows = rows;
    this-> columns = cols;

    std::ofstream output_file(filename);

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            output_file << *(grid + (r * cols + c))  << " ";
        }
        output_file << "\n";
    }

    delete[] grid;
    delete[] visitors;
}

