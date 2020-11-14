#include <iostream>
#include <fstream>

int main() {

    //INPUT DICTIONARY
    std::ifstream dict("words_alpha.txt");
    if(!dict){std::cerr << "ERROR INPUT NOT FOUND"; return 1;}
    std::cout << "Reading file: words_alpha.txt\n";


    std::string word; //Palabra a buscar
    std::string tmp; //tmp: lectura de las palabras del diccionario
    int found;

    //ENTER WORD TO BE FOUND
    //while(strcmp(word,"a")!=0) {
      //  memset(word, 0, 50);
        std::cout << "Word:? ";
        std::cin >> word;

        auto start = std::chrono::steady_clock::now();
        if(int(word[0])>=65 && int(word[0])<=90){word[0]=::tolower(word[0]);}
        std::cout << "word: " << word << "\n" ;
        found=0;
        while (!dict.eof()) { //Mientras no acabe el dictionario
            dict >> tmp; //Leer palabra x palabra
            if(tmp.length()!=word.length() || tmp[0]!=word[0]) continue;
            std::cout << "TMP: " << tmp << "\n";
            if (tmp == word) { //Comparar palabra puesta (word) vs. Palababra dictionario (tmp)
                found = 1;
                break;
            }
        }

        switch (found) {
            case 0:
                std::cout << word << " is not in the dictionary\n";
                break;
            case 1:
                std::cout << word << " is in the dictionary\n";
                break;
            default: break;
        }
   // }

    dict.close();
    auto stop = std::chrono::steady_clock::now();
    auto diff = stop-start;
    std::cout << std::chrono::duration <double, std::milli> (diff).count() << " ms" << "\n";
    return 0;
}
