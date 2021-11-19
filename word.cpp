//
// Created by Scott Mackenzie on 11/17/2021.
//

#include "word.h"

void word::push_back(article article1) {
    if (articles_contains(article1)) { //if articles vector contains article, file returns as it doesn't need to append
        return;
    }
    articles.emplace_back(article1); //otherwise pushes back
}

bool word::articles_contains(article& file) {
    vector<article> ::iterator ptr;
    for (ptr = articles.begin(); ptr < articles.end(); ptr++) {
        if (ptr->getID() == file.getID()) {
            return true;
        }

    }
    return false;
}
