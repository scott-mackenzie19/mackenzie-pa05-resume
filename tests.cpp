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
    int& var1 = tree.insert("yes");
    int& var2 = tree.insert("no");
    int& var3 = tree.insert("maybe");
    // each section represents one function
    SECTION ("test contains") {
        REQUIRE (tree.contains("yes"));
        REQUIRE (tree.contains("no"));
    }
}