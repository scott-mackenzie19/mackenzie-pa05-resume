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
    vector<article> articles;
    DSAvlTree<string, unordered_map<string, article>> wordTree;

public:
    void populate_tree(const string&);
    void parse(const string&);
    void tokenize_file(article&);
    void printTree(string, vector<pair<string, unordered_map<string, article>>>);
    void printPeople(string, vector<pair<string, unordered_map<string, article>>>);
    void printOrgs(string, vector<pair<string, unordered_map<string, article>>>);
    DSAvlTree<string, unordered_map<string, article>>& getTree();
    // get people
    // get orgs
    DSAvlTree<string, unordered_map<string, article>> readTree(string);
    DSHash <string, vector<article>> readMap(string);
};


#endif //INC_21F_FINAL_PROJ_TEMPLATE_RWFILE_H
