//
//  main.cpp
//  combine_yibo
//
//  Created by Rui Zhang on 9/25/18.
//  Copyright © 2018 Rui Zhang. All rights reserved.
//

#include <iostream>
#include "io_general_class.h"
#include <string>
#include <vector>
using std::string;
using std::vector;


int main(int argc, const char * argv[]) {
    if(argc<4) return 1;
    general_data_base tmp_combined_data, idata, combined_data, tmp_iog_data;
    vector<general_data_base> iog_data(argc-2);
    sprintf(tmp_combined_data.name,"%s",argv[2]);
    tmp_combined_data.load();
    tmp_combined_data.copy(idata);
    tmp_combined_data.copy(combined_data);
    sprintf(combined_data.name,"%s",argv[1]);
    for (int i=3; i<argc; i++) {
        sprintf(tmp_iog_data.name,"%s",argv[i]);
        tmp_iog_data.load();
        combined_data.combine(idata,tmp_iog_data);
        combined_data.copy(idata);
    }
    combined_data.save();
//    combined_data.print_all();
    return 0;
}
