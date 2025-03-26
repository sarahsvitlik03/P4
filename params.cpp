//
//  params.cpp
//  p2
//
//  Created by Sarah Svitlik & Nicholas Larkin on 2/7/25.
//

#include "params.hpp"
#include <getopt.h>
#include <cstring>
#include <vector>
#include <string>


using namespace std;

Params::Params(int argc, char* argv[]) {
    struct option longOpts[] = {
        {"verbose", no_argument, NULL, 'v'},
        {"output", required_argument, NULL, 'o'},
        {"dir", required_argument, NULL, 'd'},
        {"help", no_argument, NULL, 0},
        {"ignore-case", no_argument, NULL, 'i'},
        {NULL, 0, NULL, 0}
    };
    
    int ch;
    for (;;) { //Processes each switch
        ch = getopt_long(argc, argv, "ivd:o:h", longOpts, nullptr);
        if (ch == -1) break;
        switch (ch) {
            case 'i': ignore_case = true; break;
            case 'v': verbose = true; break;
            case 'd': dir = optarg; break;
            case 'o': output_file = optarg;
                      output.open(output_file);
                    if (!output.is_open()) {
                    cerr << "Failed to open output file: " << output_file << endl;
                    exit(EXIT_FAILURE);
                    }  break;
            case 'h': usage(); exit(0);
            case '?': //Catch invalid switches
            default: usage(); exit(0);
                
        }
        
    }
    
    if (optind < argc) {
        search_words = argv[optind];
    }
}

void Params::usage() {
    cout << "\nUsage: sniff [options] \"search words\" \n";
    cout << "Options: \n";
    cout << "  -i,  --ignore-case                Case-insenstive search.\n";
    cout << "  -v,  --verbose                    Enables verbose output.\n";
    cout << "  -d,  --dir <pathname>             Specify starting directory.\n";
    cout << "  -o,  --output <filename>          Specify output file.\n";
    cout << "  -h,  --help                       Display this usage message.\n";
    
}

void Params::print() {
    ostream& out = output_file ? output : cout;
    out << "Command: sniff " << (verbose ? "--verbose " : "") << (output_file ? string("-o ") + output_file + " " : "")
        << "--dir " << dir << " \"" << search_words << "\"\n";
    out << "Start at: " << dir << "\n";
    out << "Output file name: " << (output_file ? output_file : "None") << "\n";
    out << "Verbose? " << (verbose ? "Yes" : "No") << "\n";
    out << "Ignore case? " << (ignore_case ? "Yes" : "No") << "\n";
}

Params::~Params() {
    if (output.is_open()) {
        output.close(); 
    }
}


