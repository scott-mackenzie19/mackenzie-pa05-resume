//
// Created by Scott Mackenzie on 11/14/2021.
//

#include "article.h"

void article::setID(string& ID1) {
    this->ID = ID1;

}

void article::setTitle(string& title) {
    this->titleName = title;

}

void article::setBody(string& body1) {
    this->body = body1;

}

void article::addPeople(string& Person, article Art) {
    People.put(Person, Art);
}

void article::addOrg(string& Organization, article Art) {
    People.put(Organization, Art);
}

string& article:: getID() {
    return this->ID;
}

string &article::getTitle() {
    return this->titleName;
}

string &article::getBody() {
    return this->body;
}

int &article::getNumOccurences() {
    return this->numOccurences;
}

bool article::operator==(const article &file) {
    return (this->ID == file.ID);
}