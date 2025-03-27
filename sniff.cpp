//
//  sniff.cpp
//  P3
//
//  Created by Sarah Svitlik on 3/8/25.
//

#include "sniff.hpp"
#include <cstring>
#include <vector>
#include <string>
#include <sstream>
#include <dirent.h>
#include <sys/stat.h>

using namespace std;

Sniff::Sniff(Params& paramsObj) : params(paramsObj) {
    pathName = params.dir;
    unpack(params.search_words);
}

void Sniff::unpack(const string& argString) {
    istringstream instr(argString);
    string word;
    
    while(instr >> word) {
        sniffWords.push_back(word);
    }
}

void Sniff::run(string dir){
    
    
    //Set the current and path to the starting directory name
     pathName = dir;
    // Change the working directory to current.
    // Call travel() function
    //Construct a vector containing all files with sniff-words
    //Loop through the vector and print.
}

//Recursively processes a directory entry to find sniff words
void Sniff::travel(const string& current, const string& dirName){
    
    //Open the current directory
    DIR* dir = opendir(".");
    if (!dir){
        cerr << "Failed to open the current directory." << endl;
        return;
    }
    
    struct dirent* entry;
    while((entry = readdir(dir)) != nullptr) {
        string entryName = entry->d_name;
        
        int count = 0;

        count++;
        if (count <= 2){
            //Skips the first two entries
        }
        
        //Path to the current entry
        string entryPath = current + "/" + entryName;
        
        struct stat entryStat;
        if (stat(entryPath.c_str(), &entryStat) == -1) {
            cerr << "Failed to stat entry: " << entryName << endl;
            continue;
        }

        if (S_ISDIR(entryStat.st_mode)) {
            // Recursive call for subdirectories if it is a directory
            travel(entryPath, entryName);
        } else if (S_ISREG(entryStat.st_mode)) {
            // Process regular files using oneFile
            FileID fileID = oneFile(entryPath);

            // Check if sniff-words were found and store the file
            if (!fileID.sniffWords.empty()) {
                suspiciousFiles.push_back(fileID);
            }
        }
    }
    closedir(dir);
}
 

void Sniff::oneDir() {
    DIR* dir = opendir(".");
    if (!dir){
        cerr << "Failed to open the current directory." << endl;
        return;
    }
    
    cout << "Current Directory: ." << endl;
    
    //Skip the first two entries in the directory ( "." and "..."
    struct dirent* entry = nullptr;
    int count = 0;
    
    while ((entry = readdir(dir)) != nullptr) {
        count++;
        if (count <= 2){
            //Skips the first two entries
        }
        
        struct stat entryInfo;
        if (stat(entry->d_name, &entryInfo) == -1) {
            cerr << "Failed to stat entry: " << entry->d_name << endl;
        }
        
        if (params.verbose == true) {
            cout << "Entry: " << entry->d_name << endl;
        }
        
        if (S_ISDIR(entryInfo.st_mode) == true) {
                  // The entry is a directory
        }
              
        if (S_ISREG(entryInfo.st_mode)) {
                    FileID fileID = oneFile(entry->d_name);

                    // Check if sniff-words were found and store the file
                    if (!fileID.sniffWords.empty()) {
                        suspiciousFiles.push_back(fileID);
                    }
                }
            }

          closedir(dir);
          cout << "Done processing the directory." << endl;
      }

FileID Sniff::oneFile(const string& fileName) {
    FileID fileID(fileName, 0, pathName);

    ifstream fileStream(fileName);
    if (!fileStream.is_open()) {
        cerr << "Failed to open file: " << fileName << endl;
        return fileID;
    }

    string word;
    while (fileStream >> word) {
         word.erase(std::remove_if(word.end() - 1, word.end(), [](char c) { return !isalpha(c); }), word.end());

        for (const string& sniffWord : sniffWords) {
            if (word == sniffWord) {
                if (std::find(fileID.sniffWords.begin(), fileID.sniffWords.end(), word) == fileID.sniffWords.end()) {
                    fileID.sniffWords.push_back(word);
                }
            }
        }
    }

    fileStream.close();
    return fileID;
}

Sniff::~Sniff() {
    cout << "Sniff destructor called, cleaning up." << endl;
}
