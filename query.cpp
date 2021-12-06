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

}
void query::stats() {

}
void query::load() {

}
void query::write() {

}