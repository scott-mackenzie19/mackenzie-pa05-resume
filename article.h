//
// Created by Scott Mackenzie on 11/14/2021.
//

#ifndef INC_21F_FINAL_PROJ_TEMPLATE_ARTICLE_H
#define INC_21F_FINAL_PROJ_TEMPLATE_ARTICLE_H
#include <string>
#include "DSHash.h"
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;


class article {
private :
    string ID;
    string titleName;
    string body;
    string path;
    int numOccurences;

public:
    void setID(string&);
    void setTitle(string&);
    void setBody(string&);
    void setPath(string & );
    bool operator < (article) const;
    void increment();
    string& getID();
    string& getTitle();
    string& getBody();
    string& getPath();
    int& getNumOccurences();
    bool operator ==(const article&);
    void setNum(int& num);
};


#endif //INC_21F_FINAL_PROJ_TEMPLATE_ARTICLE_H
