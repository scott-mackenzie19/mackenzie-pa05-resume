//
// Created by Scott Mackenzie on 11/14/2021.
//

#ifndef INC_21F_FINAL_PROJ_TEMPLATE_ARTICLE_H
#define INC_21F_FINAL_PROJ_TEMPLATE_ARTICLE_H
#include <string>
#include "DSHash.h"
#include <vector>
#include <unordered_map>
using namespace std;


class article {
private :
    string ID;
    string titleName;
    string body;
    string path;
    // should value be vector of articles? instead of just article?
    //DSHash<string, article> People;
    //DSHash<string, article> Organizations;
    int numOccurences;

public:
    void setID(string&);
    void setTitle(string&);
    void setBody(string&);
    void setPath(string & filepath);
    void setPeople(DSHash<string, article>& table);
    void setOrganizations(DSHash<string, article>& table);
    DSHash<string, article>& getPeopleHash();
    DSHash<string, article>& getOrganizationsHash();
    void increment();
    void addPeople(string&, article);
    void addOrg(string&, article);
    string& getID();
    string& getTitle();
    string& getBody();
    string& getPath();
    int& getNumOccurences();
    bool operator ==(const article&);
    void setNum(int& num);
};


#endif //INC_21F_FINAL_PROJ_TEMPLATE_ARTICLE_H
