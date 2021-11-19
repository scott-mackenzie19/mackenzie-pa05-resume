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
#include "article.h"
#include "word.h"
#include "porter2_stemmer.h"

using namespace std;

class rwfile {
private:
    vector<article> articles;
    DSAvlTree<string, vector<article>> wordTree;

public:
    void populate_tree(const string& path);
    void parse(const string& filename);
    void tokenize_file(article file);
};


#endif //INC_21F_FINAL_PROJ_TEMPLATE_RWFILE_H
