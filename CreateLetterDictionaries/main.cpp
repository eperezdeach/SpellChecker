#include <iostream>
#include <fstream>
#include <typeinfo>
//using namespace std;

int main() {
    auto start = std::chrono::steady_clock::now();
    char file[] = "words_alpha.txt";
    std::string createDict = "Dict_";
    std::string typeFile = ".txt";
    char tmp[120];
    std::ifstream myfile(file);
    if (!myfile) { std::cerr << "No se puede abrir " << file; return 1;}
    std::cout << "Vamos a leer de " << file << std::endl;
    while(!myfile.eof()){
        myfile >> tmp;
        std::string dictLetter = createDict + tmp[0] + typeFile;
        std::ofstream dL(dictLetter, std::ios::app);
        if(!dL) std::cerr << "No se puede abrir dictionario con letra " + tmp[0] << std::endl;
        dL << tmp << "\n";
        dL.close();
    }
    myfile.close();
    auto stop = std::chrono::steady_clock::now();
    auto diff = stop-start;
    std::cout << std::chrono::duration <double, std::milli> (diff).count() << " ms" << "\n";
    return 0;
}
