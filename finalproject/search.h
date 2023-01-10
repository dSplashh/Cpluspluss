#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <fstream>
#include <sstream>

class Search{
    public:
        std::string word;
        std::string filename;
        std::vector< char > vec;
        std::vector< char > copyvec;
        std::vector < int > holdPos;

        Search(std::string word, std::string filename);
        void getFileContent(std::string fileName, std::vector< char > & vec);
        void naiveSearch(std::string pat, std::vector< char > txt, std::vector < int > &holdPos);
        int findMax(int a, int b);
        void badCharHeuristic(std::string str, int size, int badchar[256]);
        void search(std::vector< char > txt, std::string pat, std::vector < int > &holdPos);
        void rabinKarp(std::string pattern, std::vector< char > text, int q, std::vector < int > &holdPos);
        void modify(std::vector< char > & vec, std::vector < int > holdPos, std::string word, std::vector< char > &copyvec);
        void writeFile(std::string filename);
        void setup();
};
