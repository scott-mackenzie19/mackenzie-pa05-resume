//
// Created by Scott Mackenzie on 11/14/2021.
//

#ifndef INC_21F_FINAL_PROJ_TEMPLATE_ARTICLE_H
#define INC_21F_FINAL_PROJ_TEMPLATE_ARTICLE_H
#include <string>
#include <vector>
using namespace std;


class article {
private :
    string ID;
    string titleName;
    string body;
    vector<string> People;
    vector<string> Organizations;

public:
    void setID(string& ID1);
    void setTitle(string& title);
    void setBody(string& body1);
    void addPeople(string Person);
    void addOrganizations(string&);
    string& getID();
    string& getTitle();
    string& getBody();
    bool operator ==(const article& file);

};


#endif //INC_21F_FINAL_PROJ_TEMPLATE_ARTICLE_H
