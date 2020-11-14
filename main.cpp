#include <iostream>
#include <fstream>
#include<chrono>
#include<string.h>
#include"functions.h"
#include<vector>
#include <sstream>

int main() 
{
    std::string word; //Palabra a buscar
    std::cout << "Introduce text: ";
    std::cin >> word;
    bool is = DictOK(word); //¿Está en el diccionario?
    if (is == 1) //Si está, terminamos.
    {
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "End of the program. " << std::endl;
    }
    else //No está bien, comprobamos contracción.
    {
        IsNum(word);
        BuscarContr(word);
    }
    return 0; //Fin del main
}