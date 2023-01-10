#include "search.h"

int main(){

    std::string word;
    std::string filename;
    std::cout << "Word to search for:" << std::endl;
    std::cin >> word;
    std::cout << "Enter file name:" << std::endl;
    std::cin >> filename;

    Search search(word, filename);
    search.setup();
    search.writeFile(word);

    return 0;
  }
