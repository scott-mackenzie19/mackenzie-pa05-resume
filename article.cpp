//
// Created by Scott Mackenzie on 11/14/2021.
//

#include "article.h"

void article::setID(string ID1) {
    this->ID = ID1;

}

void article::setTitle(string title) {
    this->titleName = title;

}

void article::setBody(string body1) {
    this->body = body1;

}

void article::addPeople(string Person) {
    People.push_back(Person);

}

