//
//  main.cpp
//  combine_data
//
//  Created by Rui Zhang on 8/26/18.
//  Copyright © 2018 Rui Zhang. All rights reserved.
//

#include <iostream>
#include "io_general_class.h"
#include <string>
#include <vector>
using std::string;
using std::vector;


int main(int argc, const char * argv[]) {
    if(argc>2) return 1;
    general_data_base combined_data;
    sprintf(combined_data.name,"%s",argv[1]);
    combined_data.load();
    combined_data.print_all();
    return 0;
}

