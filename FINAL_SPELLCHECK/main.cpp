#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <thread>
#include <vector>
#include "functions.cpp"

std::string dict; //dict: Global variable that contains the dictionary in string format

class WriteHTML{
private:
    std::mutex write_mutex; //write_mutex: used to lock the writing of html
    std::once_flag _flag;
    std::ofstream f;//f: where it is going to be written
public:
    WriteHTML(){}
    ~WriteHTML(){}
    void beginHTML(){
        std::call_once(_flag, [&](){f.open("output.html");});
        f << "<html>\n";
        f << "\t<head>\n";
        f << "\t\t<title>CORRECTION TEXT</title>\n";
        f << "\t</head>\n";
        f << "\t<body>\n";

        f << "<h1>CORRECTED TEXT</h1>\n";
    } //Write the beginning of the HTML
    void endHTML(){
        f << "\t</body>\n";
        f << "</html>\n";
    } //Write the end of the HTML
    void rightWord(const std::string& s){
        std::call_once(_flag, [&](){f.open("output.html");});
        std::unique_lock<std::mutex> locker(write_mutex, std::defer_lock);
        f << s << " ";
    } //Write if the word is correct
    void wrongWord(const std::string& s){
        std::call_once(_flag, [&](){f.open("output.html");});
        std::unique_lock<std::mutex> locker(write_mutex, std::defer_lock);
        f <<"<a style=\"color:red\">" << s << "</a> ";
    } //Write if the word is incorrect
    void checkWord(bool b, const std::string& s){//Checks the option it is going to be used
        if(b){
            rightWord(s);
        }else{
            wrongWord(s);
        }
    }
};

void dict2str(std::string &d){
    std::string ln;

    std::ifstream in("words_alpha.txt");
    if(!in){std::cerr << "ERROR DICTIONARY" ; return;}
    while(!in.eof()){
        in >> ln;
        d += ln + " ";
    }
    in.close();
}//Convert the dictionary into string format

void wrds_line(const std::string ln, std::vector<std::string>& v){
    std::stringstream check(ln);
    std::string word;
    while(getline(check,word,' ')){
        v.push_back(word); //add word to vec
    }
    v.emplace_back("<br>\n");
}//Break the line into words

int main(int argc, char * argv[]) {

    if(argc < 3){std::cerr << "ERROR: NOT ENOUGH ARGUMENTS!\n";return -1;}
    auto start = std::chrono::steady_clock::now();
    dict2str(dict);


    std::string line; //line: line to be read of the input text
    std::vector<std::string> vec;//vec: vector that will contain the words of line
    std::size_t found;
    WriteHTML html; //html: Class that will be called to write the HTML
    html.beginHTML();// start html

    std::string in = "test_1.txt";//text to be read
    std::ifstream input(in);
    if(!input) { std::cerr << "ERROR WITH INPUT FILE: " << in; return -1; }

    while(getline(input, line)){//
        //thread t:
        std::thread t(wrds_line,std::ref(line),std::ref(vec));
        t.join();
    }

    bool f,c;//f: check is word is correct/ c: check if word has contraction
    for (auto w:vec){//loop vec
        found = dict.find(w);
        std::string tmp;//tmp: temporal string
        if(found!=std::string::npos){
            f=true; //found
        } else {
            f=false;
            tmp=w;//copy w in tmp
            tmp=DelSpecChar(tmp); //delete special characters
            if(tmp.length()==0){f=true;}
            tmp=Cap2Low(tmp);//convertto lower cases
            c=WordContr(tmp); //search for contraction
            if(c){
                tmp=ContraccionOK(tmp);//return tmp without contrac.
                found = dict.find(tmp);
                if (found != std::string::npos) {f = true;}
            }
        }
        //if not found, supose it is a number
        if(!f){
            found = dict.find(tmp);
            if (found != std::string::npos) {
                f = true;
            } else {
                f=IsNum(tmp);
            }
        }

        html.checkWord(f,w);//write html
    }

    html.endHTML();//end html
    auto stop = std::chrono::steady_clock::now();
    auto diff = stop-start;
    std::cout << std::chrono::duration <double, std::milli> (diff).count() << " ms" << "\n";

    return 0;
}
