//
//  fileID.cpp
//  P3
//
//  Created by Sarah Svitlik on 3/8/25.
//

#include "fileID.hpp"
#include <cstring>
#include <vector>
#include <string>

using namespace std;

FileID::FileID(const string& name, int type, const string& path) : output(name), iNode(type), pathName(path) {}

FileID::~FileID() {
    cout << "FileID destructor called for file: " << output << endl;
}
