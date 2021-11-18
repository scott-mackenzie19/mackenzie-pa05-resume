//
// Created by Kate Bouis on 11/15/21.
//

#include "catch.hpp"
#include "DSAvlTree.h"
#include "string"
using namespace std;

TEST_CASE ("DSAvlTree") {
    DSAvlTree<string, int> tree;
    // globally create tree
    string& var1 = tree.insert("yes", 5);
    string& var2 = tree.insert("no", 4);
    string& var3 = tree.insert("maybe", 3);
    // each section represents one function
    SECTION ("test contains") {
        REQUIRE (tree.contains(var1));
        REQUIRE (tree.contains("no"));
    }
}