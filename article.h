//
// Created by Scott Mackenzie on 11/14/2021.
//

#ifndef INC_21F_FINAL_PROJ_TEMPLATE_ARTICLE_H
#define INC_21F_FINAL_PROJ_TEMPLATE_ARTICLE_H
#include <string>
#include "DSHash.h"
#include <vector>
using namespace std;


class article {
private :
    string ID;
    string titleName;
    string body;
    //DSHash<string, article> People66;
    //DSHash<string, article> Organizations;
    int numOccurences;

public:
    void setID(string&);
    void setTitle(string&);
    void setBody(string&);
    void increment();
    void addPeople(string&, article);
    void addOrg(string&, article);
    string& getID();
    string& getTitle();
    string& getBody();
    int& getNumOccurences();
    bool operator ==(const article&);
    void setNum(int& num);
};


#endif //INC_21F_FINAL_PROJ_TEMPLATE_ARTICLE_H
