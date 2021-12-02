cmake_minimum_required(VERSION 3.17)
project(21f_final_proj_template)

set(CMAKE_CXX_STANDARD 17)

add_executable(21f_final_proj_template main.cpp catch_setup.cpp DSAvlTree.h DSHash.h rwfile.cpp rwfile.h article.h article.cpp tests.cpp DSLinkedList.h word.h word.cpp porter2_stemmer.h porter2_stemmer.cpp query.cpp query.h)
