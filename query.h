//
// Created by Kate Bouis on 12/1/21.
//

#ifndef INC_21F_FINAL_PROJ_TEMPLATE_QUERY_H
#define INC_21F_FINAL_PROJ_TEMPLATE_QUERY_H
#include "rwfile.h"
#include "include/rapidjson/document.h"
#include <sstream>
namespace fs = std::filesystem;
using namespace rapidjson;

class query {
private:
    string path1= "/mnt/c/temp/output3.txt";
    string path2 = "/mnt/c/temp/output2.txt";
    string path3 = "/mnt/c/temp/output.txt";
    rwfile data;
public:
    void load();
    void handleBool();
    void stats();
    void write();
    vector <article> findArticles (unordered_map<string, article>);
    void display(vector<article>);
    void menu();
};


#endif //INC_21F_FINAL_PROJ_TEMPLATE_QUERY_H
