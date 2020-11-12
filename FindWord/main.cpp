#include <iostream>
#include <fstream>

int main() {

    //INPUT DICTIONARY
    std::ifstream dict("words_alpha.txt");
    if(!dict){std::cerr << "ERROR INPUT NOT FOUND"; return 1;}
    std::cout << "Reading file: words_alpha.txt\n";


    char word[50]; //Palabra a buscar
    char tmp[50]; //tmp: lectura de las palabras del diccionario
    int found=0;

    //ENTER WORD TO BE FOUND
    std::cout << "Word:? "; std::cin >> word;

    while(!dict.eof()){ //Mientras no acabe el dictionario
        dict >> tmp; //Leer palabra x palabra
        if(strcmp(word,tmp)==0){ //Comparar palabra puesta (word) vs. Palababra dictionario (tmp)
            found = 1;
            break;
        }
    }

    switch (found) {
        case 0: std::cout << word << " is not in the dictionary"; break;
        case 1: std::cout << word << " is in the dictionary"; break;
    }


    return 0;
}
