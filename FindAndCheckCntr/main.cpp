#include <iostream>
#include <string.h>
#include <chrono>
#include <vector>
#include <sstream>

bool BuscarContr (std::string word)
{
    // 0 no está, 1 esta
    for (int i = 0; i < word.length() - 1; i ++ )
    {
        if (word[i] == (char) '\'')
        {
            return 1;
            break;
        }
    }
    return 0;
}

bool ContraccionOK (std::string word)
{
    //Separo pre y post apostrofe
    std::vector <std::string> token;
    std::stringstream check(word);
    std::string intermediate;
    while (getline(check, intermediate,'\'')){token.push_back(intermediate);}
    //asigno palabra y contraccion
    std::string contr=token [1];
    std::string wrd=token[0];

    bool contrOK = 0;//variable mia interna de control, 0 mal 1 bien
    //Caso 1: apostrofe colocado en pos incorrecta --> PALABRA MAL
    if (contr.length() > 2) std::cout <<"Incorrect \n";
    //Caso 2: apostrofe en antepenúltima posicion.
    else if (contr.length() == 2)
    {
        std::vector <std::string> lst_2 = {"re","ll","ve"};
        for (auto c: lst_2)
        {
            if (c == contr) {std::cout <<"Its the contr --> " << c; contrOK=1;break;}
        }
        //si control OK es uno, habría que comprobar que la palabra wrd esta en dic
    }
    //Caso 3: apostrofe en penúltima posicion.
    else if (contr.length() == 1)
    {
        std::vector <std::string> lst_1 = {"m","s","d","t"};
        for (auto c: lst_1)
        {
            if (c == contr) {std::cout <<"Its the contr --> " << c; contrOK=1;break;}
        }
        //si control OK es uno, habría que comprobar que la palabra wrd esta en dic
    }
    //Caso 4: apostrofe es la ultima palabra. En este caso ir directamente a buscar wrd.
    return contrOK;
}


int main() {
    std::string plbra;
    std::cout << "Introduce a word: " << std::endl;
    std:: cin >> plbra;
    auto start = std::chrono::steady_clock::now();
    bool esta = BuscarContr(plbra);
    if (esta == 0) std:: cout << "No contraction \n";
    else {
        bool ctrB = ContraccionOK(plbra);
        if (ctrB==0) std::cout << "Contraction Incorrect \n";
        else std::cout << "Contraction Correct \n";
    }
    auto stop = std::chrono::steady_clock::now();
    auto diff = stop - start;
    std::cout << std::chrono::duration <double,std::milli>(diff).count() << " ms" << "\n";
    return 0;
}
