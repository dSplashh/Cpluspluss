#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

void readFile(std::vector< std::vector < double > > &cellsgrid, std::string filename){

    std::ifstream inFile(filename);
    std::string line;

    while (std::getline(inFile, line)) {
        std::vector < double > temp;
        std::istringstream stream(line);
        double val;
        while(stream >> val) {
            temp.push_back(val);
        }
        cellsgrid.push_back(temp);
    }
}

int conn4count(std::vector< std::vector < double > > &cellsgrid, int rows, int cols, int r, int c){
    if (r < 0 || r > rows || c < 0 || c > cols || cellsgrid[r][c] == 0){
        return 0;
    }
    else{
        cellsgrid[r][c] = 0;
        return 1 + conn4count(cellsgrid, rows, cols, r + 1, c) +
                   conn4count(cellsgrid, rows, cols, r - 1, c) +
                   conn4count(cellsgrid, rows, cols, r, c + 1) +
                   conn4count(cellsgrid, rows, cols, r, c - 1);
    }
}

int conn8count(std::vector< std::vector < double > > &cellsgrid, int rows, int cols, int r, int c){
    if (r < 0 || r > rows || c < 0 || c > cols || cellsgrid[r][c] == 0){
        return 0;
    }
    else{
        cellsgrid[r][c] = 0;
        return 1 + conn8count(cellsgrid, rows, cols, r + 1, c) +
                   conn8count(cellsgrid, rows, cols, r - 1, c) +
                   conn8count(cellsgrid, rows, cols, r, c + 1) +
                   conn8count(cellsgrid, rows, cols, r, c - 1) +
                   conn8count(cellsgrid, rows, cols, r - 1, c - 1) +
                   conn8count(cellsgrid, rows, cols, r - 1, c + 1) +
                   conn8count(cellsgrid, rows, cols, r + 1, c + 1) +
                   conn8count(cellsgrid, rows, cols, r + 1, c - 1);
    }
}

int find1(std::vector< std::vector < double > > &cellsgrid, int rows, int cols, int r, int c, int &blobcount, int connection){
    if (r > rows){
        return 0;
    }
    if (c > cols){
        return find1(cellsgrid, rows, cols, r + 1, 0, blobcount, connection);
    }
    if (cellsgrid[r][c] == 1){
        int count;

        if (connection == 4) {
            count = conn4count(cellsgrid, rows, cols, r, c);
        }
        else{
            count = conn8count(cellsgrid, rows, cols, r, c);
        }
        if (count > 1){
            blobcount++;
        }
        return find1(cellsgrid, rows, cols, r, c + 1, blobcount, connection);
    }
    else{
        return find1(cellsgrid, rows, cols, r, c + 1, blobcount, connection);
    }
}

int main(int argc, char *argv[]) {

    std::string filename = argv[1];
    int rows = std::stoi(argv[2]);
    int cols = std::stoi(argv[3]);
    int connection = std::stoi(argv[4]);
    int count = 0;

    std::vector< std::vector < double > > cellsgrid;

    readFile(cellsgrid, filename);

    find1(cellsgrid, rows - 1, cols - 1, 0, 0, count, connection);

    std::cout << count << std::endl;

    return 0;
}
