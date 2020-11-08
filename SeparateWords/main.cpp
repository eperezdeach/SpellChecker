#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <string.h>
#define MIN(x,y) ((x) < (y) ? (x) : (y)) //calculate minimum between two values

//FUNCTION DECLARATION
int checkSpell(std::string str);
int Lev_dist(char *dict_word, std::string word);

int main(int argc, char *argv[]) {
    if(argc < 4){std::cerr << "ERROR NOT ENOUGH ARGUMENTS"; return -1;}
    auto start = std::chrono::steady_clock::now();
    int state;
    std::vector<std::string> list;
    char tmp[120];

    //INPUT FILE OPEN
    //std:: string file = "pruebaDoc.txt";
    std::ifstream doc(argv[1]);
    if (!doc) {std::cerr << "ERROR, file not found.\n"; return 1;}
    std::cout << "Reading file: " << argv[1] << "\n";

    //CREATE FILE OUTPUT TXT
    std::ofstream out_txt(argv[2]);
    if(!out_txt){std::cerr << "Unable to create output " << argv[2] << " for output"; return 2;}

    //CREATE FILE OUTPUT HTML
    std::ofstream out_html(argv[3]);
    if(!out_html){std::cerr << "Unable to create output " << argv[3] << " for output"; return 3;}

    out_html << "<html>\n";

    while(!doc.eof()){
        doc >> tmp;
        std::cout << tmp << " ";
        list.push_back(tmp);
    }
    std::cout << "\nList of Words: [\n";
    for (std::string w :list){
        state = ::checkSpell(w);
        //std::cout <<"word:" << w << "\n";
        switch(state){
            case -1: {
                //std::cout << w << " is not in the dictionary.\n";
                out_html << "<a style=\"color:red\">";
                out_html << w << " ";
                out_html << "</a>";
                break;
            }
            case 1: {
                //std::cout << w << " is in the dictionary.\n";
                out_html << w << " ";
                break;
            }
            default: break;
        }

    }

    std::cout << "]\n";
    out_html << "<html>\n";
    doc.close();
    out_html.close();
    out_txt.close();
    auto stop = std::chrono::steady_clock::now();
    auto diff = stop-start;
    std::cout << std::chrono::duration <double, std::milli> (diff).count() << " ms" << "\n";
    return 0;
}

int checkSpell(std::string str){
    str[0] = ::tolower(str[0]);
    int l = str.length();
    char *char_array;
    char_array = &str[0];
    std::string dictLetter = "words_alpha.txt";

    //CHECK FOR COMAS, POINTS
    if (str[l-1] == *"." || str[l-1]==*","){
        //std::cout << str << " tiene un PUNTO -> ";
        str.erase(str.end()-1);
        //std::cout << str << "\n";
    }

    //std::cout << "\nDictionary with letter " << str[0] << "\n";
    //OPEN DICTIONARY FULL DICTIONARY
    std::ifstream myDict(dictLetter);
    if (!myDict){std::cerr << "ERROR, file not found\n"; return 2;}
    //std::cout << "\nOpening file: " << dictLetter << "\n";
    char tmp[120];
    while (true){
        myDict >> tmp;
        int dist = -1;
        char *rec_word;
        if(strlen(tmp)>1){continue;}
        if(*tmp!=str[0]){continue;}
        //std::cout << str << "-> empieza con la letra " << tmp << "\n";
        //std::cout << "TMP1: " << tmp << "\n";
        if(str.compare(tmp)==0){myDict.close();return 1;}
        while(!myDict.eof()){
            myDict >> tmp;
            //std::cout << "TMP2: " << tmp << "\n";
            if(strlen(tmp)<=1){continue;}
            if(str.compare(tmp)==0){myDict.close();return 1;}
        }
        if(myDict.eof()){break;}
        if(strlen(tmp)<=1){break;}

    }
    //std::cout << str << " is not in the dictionary.\n";
    myDict.close();
    //std::cout << "The word: " << str << " is not in the dictionary.\n";
    return -1;
}

int Lev_dist(char *dict_word, std::string word) {
    int i,j,l1,l2,t,track;
    int dist[50][50];
    char *check;

    check = &word[0];

    //take the strings as input
    //char s1[] = "bisited";
    //char s2[] = "visited";
    //stores the lenght of strings s1 and s2
    l1 = strlen(dict_word);
    l2= strlen(check);
    for(i=0;i<=l1;i++) {
        dist[0][i] = i;
    }
    for(j=0;j<=l2;j++) {
        dist[j][0] = j;
    }
    for (j=1;j<=l1;j++) {
        for(i=1;i<=l2;i++) {
            if(dict_word[i-1] == check[j-1]) {
                track= 0;
            } else {
                track = 1;
            }
            t = MIN((dist[i-1][j]+1),(dist[i][j-1]+1));
            dist[i][j] = MIN(t,(dist[i-1][j-1]+track));
        }
    }
    std::cout<<"The Levinstein distance is:"<<dist[l2][l1];
    return dist[l2][l1];
}