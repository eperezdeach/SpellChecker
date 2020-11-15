#include <iostream>
#include <fstream>
#include <chrono>
#include <string.h>
#include"functions.h"
#include<vector>
#include <sstream>

//-------------------------------------------------------------------------------------------------------------------------//
bool DictOK(std::string word) //FUNCION 1
{
    bool found = 0;
    std::ifstream dict("words_alpha.txt");
    if (!dict)
    {
        std::cerr << "Error, input file not found." << std::endl;
        return 1;
    }
    std::string tmp; //tmp: lectura de las palabras del diccionario

    if (int(word[0]) >= 65 && int(word[0]) <= 90) { word[0] = ::tolower(word[0]); }
    found = 0;
    while (!dict.eof()) { //Mientras no acabe el dictionario
        dict >> tmp; //Leer palabra x palabra
        if (tmp.length() != word.length() || tmp[0] != word[0]) continue;

        if (tmp == word) { //Comparar palabra puesta (word) vs. Palababra dictionario (tmp)
            found = 1;
            break;
        }
    }
    switch (found)
    {
        case 0:
            std::cout << word << " is INCORRECT." << std::endl;
            break;
        case 1:
            std::cout << word << " is CORRECT." << std::endl;
            break;
        default:
            break;
    }
    dict.close();
    return found;
}
//-------------------------------------------------------------------------------------------------------------------------//
bool ContraccionOK(std::string word) //FUNCION 2
{
    bool contrOK = 0; //variable mia interna de control, 0 mal 1 bien

    //Separo pre y post apostrofe
    std::vector <std::string> token;
    std::stringstream check(word);
    std::string intermediate;
    while (getline(check, intermediate, '\'')) { token.push_back(intermediate); }
    //asigno palabra y contraccion
    std::string contr = token[1];
    std::string wrd = token[0];

    //Caso 1: apostrofe es la ultima palabra. En este caso ir directamente a buscar wrd.
    if (word[word.length() - 1] == '\'')
    {
        std::cout << "Correct contraction." << std::endl;
        contrOK=DictOK(wrd);
        return contrOK;
    }
    //Caso 2: apostrofe colocado en pos incorrecta --> PALABRA MAL
    if (contr.length() > 2)
    {
        std::cout << "Incorrect contraction. " << std::endl;
        contrOK = 0;
    }
    //Caso 3: apostrofe en antepenúltima posicion.
    else if (contr.length() == 2)
    {
        std::vector <std::string> lst_2 = { "re","ll","ve" };
        for (auto c : lst_2)
        {
            if (c == contr)
            {
                std::cout << "Correct contraction. " << std::endl;
                contrOK=DictOK(wrd);
                break;
            }
        }
    }
    //Caso 4: apostrofe en penúltima posicion.
    else if (contr.length() == 1)
    {
        std::vector <std::string> lst_1 = { "m","s","d","t" };
        for (auto c : lst_1)
        {
            if (c == contr)
            {
                std::cout << "Correct contraction. " << std::endl;
                contrOK=DictOK(wrd);
                break;
            }
        }
    }
    return contrOK;
}
//-------------------------------------------------------------------------------------------------------------------------//
bool IsContr(std::string word) //FUNCIÓN 3
{
    bool busc = 0; // 0 no hay cntr, 1 hay
    //int numEl = word.length();
    for (int i = 0; i < word.length(); i++)
    {
        if (word[i] == (char)'\'')
        {
            std::cout << "Contraction found. \n ";
            busc = ContraccionOK(word);
            break;
        }
    }
    return busc;
}
//-------------------------------------------------------------------------------------------------------------------------//
bool IsNum(std::string word)
{
    //0 no es num, 1 es num
    //Convertir string en char array
    int numElem = word.length();
    char* word_array = new char[numElem+1];
    //strcpy(word_array, word.c_str()); // ver nota
    std::copy(word.begin(), word.end(), word_array);
    word_array[numElem] = '\0';
    //Asumo que wrd es un numero.
    //Busco chars que no sean digitos
    for (int i = 0; i < numElem; i++)
    {
        //int(wrd_array[i]) --> obtener cod. ASCII del char.
        //digitos tienen código ASCII [48,57]
        if (int(word_array[i]) < 48 || int(word_array[i]) > 57)
        {
            return 0; //no es num
            break;
        }
    }
    return 1;
}
