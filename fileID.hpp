//
//  fileID.hpp
//  P3
//
//  Created by Sarah Svitlik on 3/8/25.
//

#pragma once

#include <iostream>
#include <fstream>

using namespace std;

class FileID {
private:
    string output;
    int iNode;
    string pathName;
    
public:
    vector <string> sniffWords;
    FileID(const string& name, int type, const string& path);
    void print();
    void sniff();
    ~FileID();
};
