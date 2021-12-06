//
// Created by Kate Bouis on 12/1/21.
//

#ifndef INC_21F_FINAL_PROJ_TEMPLATE_QUERY_H
#define INC_21F_FINAL_PROJ_TEMPLATE_QUERY_H
#include "rwfile.h"
#include "include/rapidjson/document.h"
namespace fs = std::filesystem;
using namespace rapidjson;

class query {
private:

public:
    void menu();
    void handleBool();
    void stats();
    void load();
    void write();
};


#endif //INC_21F_FINAL_PROJ_TEMPLATE_QUERY_H
