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
    std::cout << "Introduce text: \n";
    std::cin >> word;
    bool is = DictOK(word); //¿Está en el diccionario?
    if (is == 1) //Si está, terminamos.
    {
        std::cout << "\n \nEnd of the program. \n ";
    }
    else //No está bien, comprobamos cosas.
    {
        //Caso 1: Creo que es Num.
        bool esNum=IsNum(word);
        if (esNum==0) //no es num
        {
            bool hayContr=IsContr(word);
            if (hayContr==0) std::cout <<"Incorrect \n";
            else std::cout <<"Correct contraction \n";
        }
        else std::cout <<"Its a number \n" ;
    }
    return 0; //Fin del main
}
