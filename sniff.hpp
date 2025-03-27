//
//  sniff.hpp
//  P3
//
//  Created by Sarah Svitlik on 3/8/25.
//

#pragma once

#include <iostream>
#include <fstream>
#include "fileID.hpp"
#include "params.hpp"

using namespace std;

class Sniff {
private:
    Params& params;
    string fileName;
    string currentDir;
    string pathName;
    string dir;
    vector <string> sniffWords;
    vector<FileID> suspiciousFiles;

public:
    bool verbatim;
    Sniff(Params& paramsObj);
    void unpack(const string& argString);
    void oneDir();
    void travel(const string& current, const string& dirName);
    void run (string dirName);
    FileID oneFile(const string& fileName);
    ~Sniff();
 };
