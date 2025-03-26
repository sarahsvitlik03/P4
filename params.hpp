//
//  params.hpp
//  p2
//
//  Created by Sarah Svitlik & Nicholas Larkin on 2/7/25.
//
#pragma once

#include <iostream>
#include <fstream>

using namespace std;

class Params {
public:
    Params(int argc, char* argv[]);
    const char* dir = ".";
    bool verbose = false;
    bool ignore_case = false;
    string search_words;
    const char* output_file = nullptr;
    ofstream output;
    void print();
    void usage();
    ~Params();
};
