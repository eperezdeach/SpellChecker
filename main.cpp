#include <iostream>
#include <math.h>
#include <string.h>
#include <vector>
#include <fstream>
#define MIN(x,y) ((x) < (y) ? (x) : (y)) //calculate minimum between two values

int Lev_dist(char *s1, char *s2);

int main(){

    //std::vector<char*> list = {"apple","visited", "tree"};
    int dist=-1;
    char tmp[50];
    char wrd;
    int d;
    char *rec_wrd;

    //OPEN DICTIONARY
    std::ifstream dict("words_alpha.txt");
    if(!dict){std::cerr << "ERROR"; return -1;}

    char w1[] = "father";
    //char w2[] = "tree";
    while (!dict.eof()){
        dict >> tmp;
        d = Lev_dist(w1,tmp);
        if(dist==-1 || dist > d){
            std::cout << tmp << "\n";
            dist = d;
            strcpy(rec_wrd,tmp);
        }

    }

    std::cout << "Levenstein Distance: " << dist << std::endl;
    std::cout << "Recommended word: " << rec_wrd << std::endl;

    return 0;
}

int Lev_dist(char *s1, char *s2) {

    int i,j,l1,l2,t,track;
    int dist[50][50];
    //take the strings as input

    //stores the lenght of strings s1 and s2
    l1 = strlen(s1);
    l2= strlen(s2);
    for(i=0;i<=l1;i++) {
        dist[0][i] = i;
    }
    for(j=0;j<=l2;j++) {
        dist[j][0] = j;
    }
    for (j=1;j<=l1;j++) {
        for(i=1;i<=l2;i++) {
            if(s1[i-1] == s2[j-1]) {
                track= 0;
            } else {
                track = 1;
            }
            t = MIN((dist[i-1][j]+1),(dist[i][j-1]+1));
            dist[i][j] = MIN(t,(dist[i-1][j-1]+track));
        }
    }
    //std::cout<<"The Levinstein distance is:"<<dist[l2][l1];
    return dist[l2][l1];
}