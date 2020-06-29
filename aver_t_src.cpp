//
//  
//  aver_t_src.cpp
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
    general_data_base tmp_combined_data, idata, combined_data, averaged_data, tmp_iog_data;
    vector<general_data_base> iog_data(argc-2);
    sprintf(tmp_combined_data.name,"%s",argv[2]);
    tmp_combined_data.load();
    string str(argv[2]);
    unsigned long first = str.find("t")+1;
    unsigned long last = str.find(".iog");
    std::cout<< str.substr(first,last-first) << std::endl;
    int t_src = std::stoi(str.substr(first,last-first));
    std::cout<< str<< std::endl;
    tmp_combined_data.insert_dimension(dim_t_source, t_src);
    std::cout<< t_src<< std::endl;
    tmp_combined_data.copy(idata);
    tmp_combined_data.copy(combined_data);
    sprintf(combined_data.name,"%s",argv[1]);
    for (int i=3; i<argc; i++) {
        sprintf(tmp_iog_data.name,"%s",argv[i]);
        tmp_iog_data.load();
        str=argv[i];
	std::cout<< str<< std::endl;
        first = str.find("t")+1;
        last = str.find(".iog");
        t_src = std::stoi(str.substr(first,last-first));
	std::cout<< t_src<< std::endl;
        tmp_iog_data.insert_dimension(dim_t_source, t_src);
        combined_data.combine(idata,tmp_iog_data);
        combined_data.copy(idata);
    }
    combined_data.aver(averaged_data, dim_t_source,0);
    sprintf(averaged_data.name,"%s",argv[1]);
    averaged_data.save();
    return 0;
}
