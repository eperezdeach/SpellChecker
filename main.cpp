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
    bool is = DictOK(word); //�Est� en el diccionario?
    if (is == 1) //Si est�, terminamos.
    {
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "End of the program. " << std::endl;
    }
    else //No est� bien, comprobamos contracci�n.
    {
        IsNum(word);
        BuscarContr(word);
    }
    return 0; //Fin del main
}