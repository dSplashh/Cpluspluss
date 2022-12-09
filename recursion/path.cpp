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

int findlowhigh(std::vector< std::vector < double > > &cellsgrid, int rows, int cols, int r, int c, int &Lr, int &Lc, int &Hr, int &Hc){
    if (r > rows){
        return 0;
    }
    if (c > cols){
        return findlowhigh(cellsgrid, rows, cols, r + 1, 0, Lr, Lc, Hr, Hc);
    }
    if (cellsgrid[r][c] < cellsgrid[Lr][Lc]){
        Lr = r;
        Lc = c;
        return findlowhigh(cellsgrid, rows, cols, r, c + 1, Lr, Lc, Hr, Hc);
    }
    if (cellsgrid[r][c] > cellsgrid[Hr][Hc]){
        Hr = r;
        Hc = c;
        return findlowhigh(cellsgrid, rows, cols, r, c + 1, Lr, Lc, Hr, Hc);
    }
    else{
        return findlowhigh(cellsgrid, rows, cols, r, c + 1, Lr, Lc, Hr, Hc);
    }
}

bool findPath(std::vector< std::vector < double > > cellsgrid, int rows, int cols, int Lr, int Lc, int Hr, int Hc, int save, std::vector< std::vector < double > > &copycellsgrid){
   if (Lr < 0 || Lr > rows || Lc < 0 || Lc > cols || copycellsgrid[Lr][Lc] == -1){
       return false;
   }
   if (Lr == Hr && Lc == Hc){
       return true;
   }
   if (cellsgrid[Lr][Lc] >= save){
       save = cellsgrid[Lr][Lc];
       copycellsgrid[Lr][Lc] = -1;
       return findPath(cellsgrid, rows, cols, Lr + 1, Lc, Hr, Hc, save, copycellsgrid) || findPath(cellsgrid, rows, cols, Lr - 1, Lc, Hr, Hc, save, copycellsgrid) || findPath(cellsgrid, rows, cols, Lr, Lc + 1, Hr, Hc, save, copycellsgrid) || findPath(cellsgrid, rows, cols, Lr, Lc - 1, Hr, Hc, save, copycellsgrid);
   }
   else {
       return false;
   }
}

int main(int argc, char *argv[]) {
    std::string filename = argv[1];
    int rows = std::stoi(argv[2]);
    int cols = std::stoi(argv[3]);
    int Lr = 0;
    int Lc = 0;
    int Hr = 0;
    int Hc = 0;
    std::string validpath = "no";

    std::vector< std::vector < double > > cellsgrid;
    std::vector< std::vector < double > > copycellsgrid;

    readFile(cellsgrid, filename);

    copycellsgrid = cellsgrid;

    findlowhigh(cellsgrid, rows - 1, cols - 1, 0, 0, Lr, Lc, Hr, Hc);

    if (!findPath(cellsgrid, rows - 1, cols - 1, Lr, Lc, Hr, Hc, cellsgrid[Lr][Lc], copycellsgrid)) {}
    else {
        validpath = "yes";
    }

    std::cout << Lr + 1 << " " << Lc + 1 << " " << Hr + 1 << " " << Hc + 1 << " " << validpath <<  std::endl;

    return 0;
}
