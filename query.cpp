//
// Created by Kate Bouis on 12/1/21.
//

#include "query.h"

void query::menu() {
    cout << "Welcome to our search engine! Please choose an option to get started: " << endl;
    cout << "1. Load Data" << endl;
    cout << "2. Execute Query" << endl;
    cout << "3. Show Stats" << endl;
    cout << "4. Write Persistence File" << endl;
    cout << "5. Exit" << endl;
    int choice;
    cin >> choice;
    if (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5) {
        cout << "Invalid Choice. Try Again.";
        menu();
    }
    else if (choice == 1) {
        load();
        menu();
    } else if (choice == 2) {
        handleBool();
        menu();
    } else if (choice == 3) {
        stats();
        menu();
    } else if (choice == 4) {
        write();
        menu();
    } else if (choice == 5) {
        cout << "Bye! Have a good day.";
    }
}

void query::handleBool() {
    cout << "Enter your search term.";
    rwfile data;
    string query;
    while (cin >> query) {
        Porter2Stemmer::trim(query);
        Porter2Stemmer::stem(query);
        if (query == "and") {

        }
    }
}
void query::stats() {
    rwfile stat1;
    cout << "We have " << stat1.getLines() << " files loaded into the engine." << endl;
    int numNodes = 0;
    ifstream input("output.txt");
    if (!input) exit(EXIT_FAILURE);
    string str;
    while (getline(input, str)) {
        numNodes++;
    }
    cout << "The Avl Tree is handling " << numNodes << " nodes." << endl;
    int numAuthors = 0;
    ifstream input2("outputPeople.txt");
    if (!input2) exit(EXIT_FAILURE);
    while (getline(input2, str)) {
        numAuthors++;
    }
    int numOrgs = 0;
    ifstream input3("outputOrgs.txt");
    if (!input3) exit (EXIT_FAILURE);
    while (getline(input3, str)) {
        numOrgs++;
    }
    cout << "We have files from "  << numAuthors << " authors and " << numOrgs << " organizations." << endl;
}
void query::load() {
cout << "Press 1 if you would like to load from persistence files and 2 if you would like to load from files on your computer." << endl;
int choice;
cin >> choice;
if (choice == 1) {
    rwfile data;
    data.readTree("output.txt");
    data.readPeople("outputPeople.txt");
    data.readOrgs("outputOrgs.txt");
} else if (choice == 2) {
    cout << "Enter path to your files." << endl;
    string path;
    cin >> path;
    rwfile data;
    data.loadStopWords();
    data.populate_tree(path);
    //populate people
    //populate orgs
} else {
    cout << "Bad answer. Back to menu." << endl;
}
}
void query::write() {
    cout << "Enter path to your files." << endl;
    string path;
    cin >> path;
    rwfile data;
    data.loadStopWords();
    data.populate_tree(path);
    //populate people
    //populate orgs
    data.printTree ("output.txt", data.getTree().populateVector());
    data.printPeople ("outputPeople.txt", data.getPeopleHash().populateVector());
    data.printOrgs ("outputOrgs.txt", data.getOrganizationsHash().populateVector());
}