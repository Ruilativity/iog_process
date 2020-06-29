//
//  main.cpp
//  print_hadspec
//
//  Created by Rui Zhang on 9/26/18.
//  Copyright © 2018 Rui Zhang. All rights reserved.
//

#include <iostream>
#include "io_general_class.h"
#include <string>
#include <fstream>
#include <vector>
#include <unistd.h>
#include <chrono>
using std::string;
using std::endl;
using std::ofstream;
using std::vector;

void print_to_txt(general_data_base & res, const char * filename, int qxyz){
    int fileN=1;
    int dimcount=0;
    int datacount=0;
    int dataposition=0;
    ofstream logfile("log");
        
        int g1, mom;
	int dim_ch=res.find_dim(dim_channel);
        int dim_o=res.find_dim(dim_operator);
        int dim_p=res.find_dim(dim_momentum);
        int dim_it=res.find_dim(dim_t);
        int dim_c=res.find_dim(dim_conf);
        int datajump=res.dim[dim_o].n_indices*res.dim[dim_p].n_indices*res.dim[dim_it].n_indices*2;
        
        fileN*=res.dim[dim_o].n_indices;
        fileN*=res.dim[dim_ch].n_indices;
        fileN*=res.dim[dim_p].n_indices;
        
        logfile << "dim=" << res.dim[dim_ch].n_indices << "*" << res.dim[dim_o].n_indices << "*" << res.dim[dim_p].n_indices << "*" << res.dim[dim_it].n_indices << "*" << res.dim[dim_c].n_indices << "\n data_jump=" << datajump << "\n first data=" << res.data[0] << endl;
        
        vector<string> output_filename(fileN,filename);
	for(int i=0;i<res.dim[dim_ch].n_indices;i++){
        for(int k=0;k<res.dim[dim_o].n_indices;k++){
            for (int l=0; l<res.dim[dim_p].n_indices; l++) {
                datacount=0;
                if(res.dim[dim_p].indices[l]!=qxyz && qxyz!=-1){
			dimcount++;
			continue;
		}
		g1=(res.dim[dim_o].indices[k]);
                output_filename[dimcount]+="_proton";
                output_filename[dimcount]+=std::to_string(g1);
		output_filename[dimcount]+="_channel";
                output_filename[dimcount]+=std::to_string(i);
                output_filename[dimcount]+="_px";
                mom=(res.dim[dim_p].indices[l]/10000)%100-50;
                output_filename[dimcount]+=std::to_string(mom);
                output_filename[dimcount]+="_py";
                mom=(res.dim[dim_p].indices[l]/100)%100-50;
                output_filename[dimcount]+=std::to_string(mom);
                output_filename[dimcount]+="_pz";
                mom=(res.dim[dim_p].indices[l])%100-50;
                output_filename[dimcount]+=std::to_string(mom);
                output_filename[dimcount]+=".dat";
                logfile << output_filename[dimcount] << endl;
                ofstream outfile(output_filename[dimcount]);
                outfile << res.dim[dim_c].n_indices << " " << res.dim[dim_it].n_indices << endl;
                dataposition=dimcount*res.dim[dim_it].n_indices*2;
                
                for (int m=0; m<res.dim[dim_c].n_indices; m++) {
                    for (int n=0; n<res.dim[dim_it].n_indices; n++) {
                        outfile << n << " " << res.data[dataposition+2*n] << " " << res.data[dataposition+2*n+1] << endl;
                    }
                    dataposition+=datajump;
                }
                
                outfile.close();
                dimcount++;
            }
        }
	}
        logfile.close();
    
}

int main(int argc, const char * argv[]) {
    auto start_time=std::chrono::high_resolution_clock::now();
    char *const *argvment=(char *const *)argv;
    int gamma,qxyz;
    int opt = 0;
    int flag=1;
    if((opt=getopt(argc, argvment, "q:"))==-1){
        qxyz=-1;
    }else{
        qxyz=atoi(optarg);
        flag++;
    }
    std::cout<< "q="<<qxyz<< std::endl;
    general_data_base combined_data;
    sprintf(combined_data.name,"%s",argv[flag]);
    combined_data.load();
    print_to_txt(combined_data, "hadspec", qxyz);
    auto end_time=std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;
    std::cout<< "total time is: "<<elapsed.count() << endl;
    return 0;
}

