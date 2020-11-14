#include <iostream>
#include <string>
#include <chrono>

bool IsNum (std::string wrd)
{
    //Convertir string en char array
    int n=wrd.length();
    char wrd_array[n];
    strcpy(wrd_array, wrd.c_str()); // ver nota

    //Asumo que wrd es un numero.
    //Busco chars que no sean digitos
    for (int i =0; i < n; i++)
    {
        //int(wrd_array[i]) --> obtener cod. ASCII del char.
        //digitos tienen código ASCII [48,57]
        if (int(wrd_array[i])< 48 || int(wrd_array[i]) > 57 )
        {
            return 0; //no es num
            break;
        }
    }
    return 1; //si es un num
}

int main() {
    std::string plbra;
    std::cout << "Introduce a word: \n ";
    std:: cin >> plbra;

    auto start = std::chrono::steady_clock::now();
    bool esnum=IsNum(plbra);
    if (esnum==0) std::cout << "Not a number \n";
    else std::cout << "Its a number\n";

    auto stop = std::chrono::steady_clock::now();
    auto diff = stop - start;
    std::cout << std::chrono::duration <double,std::milli>(diff).count() << " ms" << "\n";

    return 0;
}


/*NOTA: esta función lo que hace es copiar lo que hay en el string en el array.
NO TIENE EN CUENTA ESPACIOS, es decir si el string es "Peter Smith",
 en el array solo se guardará "Peter". Para este caso particular que solo analizamos
 una palabra no importa, pero no sé como se haría lo mismo para frases.*/
