#include <iostream>
#include <fstream>

//INPUT: std::string wrd -> STRING TO BE FOUND IN THE DICTIOANRY
//OUTPUT: bool found -> RETURNS IF THE WORD IS FOUND(true: word found/false: word not found)
bool FindWord(std::string wrd) {

    bool found = false;

    //INPUT DICTIONARY
    std::ifstream dict("words_alpha.txt");
    if(!dict){std::cerr << "ERROR INPUT NOT FOUND"; return (found);} //ERROR READING DICTIONARY
    std::cout << "Reading file: words_alpha.txt\n";

    std::string tmp; //tmp: reading the words of the dictionary

    //Find if the first letter is a capital letter using ASCII code (ASCII:'A' = 65/ ASCII:'Z' = 90)
    if(int (wrd[0])>=65 && int (wrd[0])<=90) {wrd[0]=::tolower( wrd[0]);}
    while (!dict.eof()) { //while there is text to be read
        dict >> tmp; //reading word by word
        if(tmp.length()!= wrd.length() || tmp[0]!=wrd[0]) continue;
        if (tmp == wrd) { //Compare input word (word) vs. Dictionary words (tmp)
            found = true; //word is in the dictionary
            break;
        }
    }

    dict.close(); //Close dictionary
    return found; //return bool value
}
