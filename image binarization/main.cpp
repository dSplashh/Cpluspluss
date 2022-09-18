#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cmath>

void readFile(std::vector<std::vector<double> > &image2DSpace, std::vector < double > &image1DSpace, std::string &fileName){

    std::ifstream inFile(fileName);
    std::string line;

    while (std::getline(inFile, line)) {
        std::vector <double> temp;
        std::istringstream stream(line);
        double val;
        while(stream >> val) {
            temp.push_back(val);
            image1DSpace.push_back(val);
        }
        image2DSpace.push_back(temp);
    }
}

void globalChange(std::vector<std::vector<double> > &image2DSpace, int threshold){
    int rows = image2DSpace.size();
    int cols = image2DSpace[0].size();

    for(int r = 0; r < rows; r++){
        for(int c = 0; c < cols; c++){
            if (image2DSpace[r][c] < threshold){
                image2DSpace[r][c] = 0;
            }
            else{
                image2DSpace[r][c] = 255;
            }
        }
    }
}

double localThreshold(std::vector < double > neyPixels, double minMax){
    double mean = 0;
    double add = 0;
    double stanDev = 0.0;

    for (int pix = 0; pix < neyPixels.size(); pix++){
        add += neyPixels[pix];
    }
    mean = add/neyPixels.size();

    double plus = 0;

    for(int pix = 0; pix < neyPixels.size(); pix++){
        plus += pow((neyPixels[pix] - mean), 2);
    }

    stanDev = sqrt(plus/neyPixels.size());

    double R = minMax * 0.5;

    double a = (stanDev/R) - 1;
    double b = a * 0.2;
    double c = b + 1.0;
    double d = c * mean;

    double localT = d;

    return localT;
}

double findLocals(std::vector<std::vector<double> > &image2DSpace, int size, int row, int col, double minMax){
    int rows = image2DSpace.size();
    int cols = image2DSpace[0].size();
    int buildSize = size/2;
    double localT;

    std::vector < double > neyPixels;

    for(int sRow = row - buildSize; sRow <= buildSize + row; sRow++){

        for(int sCol = col - buildSize; sCol <= buildSize + col; sCol++){

            if(sRow >= 0 && sRow < rows && sCol >= 0 && sCol < cols){
                neyPixels.push_back(image2DSpace[sRow][sCol]);
            }
        }
    }

    localT = localThreshold(neyPixels, minMax);

    return localT;
}

void writeFile(std::string outPutFile, std::vector<std::vector<double> > &processImage) {

    std::ofstream output_file(outPutFile);

    for (std::vector<std::vector<double> >::const_iterator i = (processImage).begin(); i != (processImage).end(); ++i) {
        for (std::vector<double>::const_iterator j = i->begin(); j != i->end(); ++j) {
            output_file << *j << " ";
        }
        output_file << "\n";
    }
}


void localChange(std::vector<std::vector<double> > &image2DSpace, int size, std::string write_file_name, double minMax){

    int rows = image2DSpace.size();
    int cols = image2DSpace[0].size();

    std::vector<std::vector<double> > image2DCopy = image2DSpace;

    for(int r = 0; r < rows; r++){
        for(int c = 0; c < cols; c++){
            double localT = findLocals(image2DSpace, size, r, c, minMax);
     
            if (image2DSpace[r][c] < localT){
                image2DCopy[r][c] = 0;
            }
            else{
                image2DCopy[r][c] = 255;
            }
        }
    }

    writeFile(write_file_name, image2DCopy);

}



int main(int argc, char *argv[]) {

    std::string type = argv[1];
    std::string name_of_infile = argv[2];
    std::string name_of_outfile = argv[3];
    double minMax;

    std::vector<std::vector<double > > pixels;

    std::vector<double> pixels1d;

    readFile(pixels, pixels1d, name_of_infile);

    std::sort(pixels1d.begin(), pixels1d.end());

    minMax = pixels1d[pixels1d.size() - 1] - pixels1d[0];

    if (type == "global") {
        int globalT;

        if (pixels1d.size() % 2 == 0) {
            int index = pixels1d.size() / 2;
            globalT = pixels1d[index];
        } else {
            int index = pixels1d.size() / 2;
            globalT = (pixels1d[index] + pixels1d[index + 1]) / 2;
        }

        globalChange(pixels, globalT);
        writeFile(name_of_outfile, pixels);

    }
    else if (type == "local"){
        int localSize = std::stoi(argv[4]);
        localChange(pixels, localSize, name_of_outfile, minMax);
    }

    return 0;
}
