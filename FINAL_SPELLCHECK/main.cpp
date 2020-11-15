#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "functions.cpp"

int main(int argc, char *argv[]) {
    if (argc < 3)std::cerr << "ERROR WITH MAIN";
    auto start = std::chrono::steady_clock::now();
    //OPEN INPUT TXT
    std::ifstream input(argv[1]);
    if(!input) { std::cerr << "ERROR WITH INPUT FILE: " << argv[1]; return -1; }
    std::cout << "Reading " << argv[1] << " file.\n";

    //CREATE OUTPUT HTML
    std::ofstream out_html(argv[3]);
    if(!out_html){std::cerr << "ERROR WITH OUTPUT FILE: " << argv[3]; return -3; }
    std::cout << "Creating " << argv[3] << " file.\n";

    std::string line;
    std::vector<std::string> vec;


    std::string word;

    out_html << "<html>\n";
    int k=1;
    while(getline(input, line)){
        std::cout << k << "-Line: " << line << "\n";
        ++k;
        std::stringstream check(line);
        while(getline(check,word,' ')){
            vec.push_back(word);
        }
        for(auto w:vec){

            bool write;
            write = FindWord(w);
            switch (write) {
                case true:{
                    //output << w << " ";
                    out_html << "\t" << w << " ";
                    break;
                }
                case false:{
                    //output << "<a>" << w << "</a> ";
                    out_html << "\t<a style=\"color:red\">" << w << "</a> ";
                    break;
                }
            }
        }
        //output << "\n";
        out_html << "<br>\n";
        vec.clear();
    }


    out_html << "</html>\n";
    input.close();
    //output.close();
    out_html.close();

    auto stop = std::chrono::steady_clock::now();
    auto diff = stop-start;
    std::cout << std::chrono::duration <double, std::milli> (diff).count() << " ms" << "\n";
    return 0;
}
