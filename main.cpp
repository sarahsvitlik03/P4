//
//  main.cpp
//  Program 3
//
//  Created by Sarah Svitlik & Nicholas Larkin on 2/7/25.
//

#include <iostream>
#include "params.hpp"
#include "sniff.hpp"
#include "tools.hpp"

int main(int argc,  char * argv[]) {
    
    banner();
    cout << "Welcome to Program 3!";
    Params params(argc, argv);
    params.print();

    Sniff sniff(params);

    if (chdir(params.dir) != 0) {    
        perror("chdir failed");
        return 1;
    }

    sniff.oneDir();  
    bye();
    return 0;
}
