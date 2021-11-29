//
// Created Scott Mackenzie on 11/17/2021.
//

#ifndef INC_21F_FINAL_PROJ_TEMPLATE_WORD_H
#define INC_21F_FINAL_PROJ_TEMPLATE_WORD_H
#include <string>
#include "article.h"
#include <algorithm>
#include "word.h"
#include <iterator>
using namespace std;

class word {
public:
    vector<article> articles;
    string word;
    void push_back(article&);
    bool articles_contains(article& );
};


#endif //INC_21F_FINAL_PROJ_TEMPLATE_WORD_H
