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
    int nFiles=argc-2;
    int ncfgs=0;
    general_data_base tmp_combined_data, idata, combined_data, tmp_iog_data;
    vector<general_data_base> iog_data(nFiles);
    sprintf(tmp_combined_data.name,"%s",argv[2]);
    tmp_combined_data.load();
    tmp_combined_data.copy(idata);
    tmp_combined_data.copy(combined_data);
    int size=0;
    int size_data=tmp_combined_data.size/tmp_combined_data.dim[0].n_indices;
    for(int i=0; i< nFiles; ++i){
            sprintf(iog_data[i].name,"%s",argv[i+2]);
            iog_data[i].load();
	    ncfgs+=iog_data[i].dim[0].n_indices;
    }
    combined_data.dim[0].n_indices=ncfgs;
    combined_data.initialize();
    printf("total cfgs:%d\n",combined_data.dim[0].n_indices);
    for(int i=0, j=0; i< nFiles; ++i){
	    int new_size_data=iog_data[i].size/iog_data[i].dim[0].n_indices;
	    if(new_size_data!=size_data) {printf("The data size does not match\n");return -1;}
	    for(int m=0; m<iog_data[i].dim[0].n_indices;m++){
		    combined_data.dim[0].indices[j]=iog_data[i].dim[0].indices[m];
		    j++;
	    }
	    memcpy(combined_data.data+size,iog_data[i].data,sizeof(double)*iog_data[i].size);
	    size+=iog_data[i].size;
    }




    sprintf(combined_data.name,"%s",argv[1]);
    combined_data.save();
//    combined_data.print_all();
    return 0;
}
