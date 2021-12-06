//
// Created by Scott Mackenzie on 11/14/2021.
// Class loads each file into a separate file object

#ifndef INC_21F_FINAL_PROJ_TEMPLATE_RWFILE_H
#define INC_21F_FINAL_PROJ_TEMPLATE_RWFILE_H
#include <string>
#include <vector>
#include "string"
#include "include/rapidjson/document.h"
#include <filesystem>
#include <iostream>
#include <fstream>
#include "DSAvlTree.h"
#include "article.h"
#include "include/rapidjson/document.h"
#include "include/rapidjson/istreamwrapper.h"
#include "include/rapidjson/stringbuffer.h"
#include "include/rapidjson/filereadstream.h"
#include "article.h"
#include "word.h"
#include "porter2_stemmer.h"
#include <unordered_map>
#include "DSHash.h"

using namespace std;

class rwfile {
private:
    vector<string> stopWords;
    DSAvlTree<string, unordered_map<string, article>> wordTree;
    DSHash<string, vector <article>> People;
    DSHash<string, vector<article>> Organizations;
    int lines;

public:
    void setPeople(DSHash<string, vector<article>>&);
    void setOrganizations(DSHash<string, vector<article>>&);
    DSHash<string, vector<article>>& getPeopleHash();
    DSHash<string, vector<article>>& getOrganizationsHash();
    void addPeople(string&, article);
    void addOrg(string&, article);
    void populate_tree(const string& path);
    void parse(const string& file);
    void tokenize_file(article&);
    void printTree(string, vector<pair<string, unordered_map<string, article>>>);
    void printPeople(string, vector<pair<string, vector <article>>>);
    void printOrgs(string, vector<pair<string, vector <article>>>);
    DSAvlTree<string, unordered_map<string, article>>& getTree();
    void set_tree( DSAvlTree<string, unordered_map<string, article>>& tree);
    void readTree(const string&);
    void readPeople(string);
    void readOrgs(string);
    void loadStopWords();
    int getLines();
};


#endif //INC_21F_FINAL_PROJ_TEMPLATE_RWFILE_H
