//
//  main.cpp
//  print_by_cfg
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

void print_to_txt(general_data_base & res, const char * filename, int gamma, int qxyz){
    int fileN=1;
    int dimcount=0;
    int datacount=0;
    int dataposition=0;
    ofstream logfile("log");
    
        
        int link, mom;
        int dim_c=res.find_dim(dim_conf);
        int dim_d=res.find_dim(dim_displacement);
        int dim_o=res.find_dim(dim_operator);
        int dim_p=res.find_dim(dim_momentum);
        int dim_it=res.find_dim(dim_t);
        int datajump=res.dim[dim_o].n_indices*res.dim[dim_d].n_indices*res.dim[dim_p].n_indices*res.dim[dim_it].n_indices*2;
        
        fileN*=res.dim[dim_o].n_indices;
        fileN*=res.dim[dim_d].n_indices;
        fileN*=res.dim[dim_p].n_indices;
        
        logfile << "dim=" << res.dim[dim_o].n_indices << "*" << res.dim[dim_d].n_indices << "*" << res.dim[dim_it].n_indices << "*" << res.dim[dim_c].n_indices << "\n data_jump=" << datajump << "\n first data=" << res.data[0] << endl;
        
        vector<string> output_filename(fileN,filename);
        for(int k=0;k<res.dim[dim_d].n_indices;k++){
            for (int l=0; l<res.dim[dim_o].n_indices; l++) {
                for (int p=0; p<res.dim[dim_p].n_indices; p++) {
                    int print_flag=1;
                    if (qxyz!=-1) {
                        if(res.dim[dim_p].indices[p]!=qxyz){
                            print_flag*=0;
                        }
                    }
                    if(gamma!=-1){
                        if(l!=gamma){
                            print_flag*=0;
                        }
                    }
                    if(print_flag==0){dimcount++;continue;}
                    datacount=0;
                    output_filename[dimcount]+="_G";
                    output_filename[dimcount]+=std::to_string(l);
                
                    output_filename[dimcount]+="_z";
                    link=res.dim[dim_d].indices[k];
                    if (link > 400) {
                        output_filename[dimcount]+="-";
                    }
                
                    output_filename[dimcount]+=std::to_string(link % 100);
                    mom=res.dim[dim_p].indices[p];
                    output_filename[dimcount]+="_px";
                    output_filename[dimcount]+=std::to_string((mom/10000)%100-50);
                    output_filename[dimcount]+="_py";
                    output_filename[dimcount]+=std::to_string((mom/100)%100-50);
                    output_filename[dimcount]+="_pz";
                    output_filename[dimcount]+=std::to_string((mom)%100-50);
                    output_filename[dimcount]+=".dat";
                    logfile << output_filename[dimcount] << endl;
                    ofstream outfile(output_filename[dimcount]);
                    outfile << res.dim[dim_c].n_indices << " " << res.dim[dim_it].n_indices << endl;
                    dataposition=dimcount*res.dim[dim_it].n_indices*2;
                
                    for (int m=0; m<res.dim[dim_c].n_indices; m++) {
                        logfile << "dataposition=" << dataposition << endl;
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
    if((opt=getopt(argc, argvment, "g:"))==-1){
        gamma=-1;
    }else{
        gamma=atoi(optarg);
        flag++;
    }
    if((opt=getopt(argc, argvment, "q:"))==-1){
        qxyz=-1;
    }else{
        qxyz=atoi(optarg);
        flag++;
    }
    std::cout<< "gamma="<<gamma<< std::endl;
    std::cout<< "q="<<qxyz<< std::endl;
    general_data_base combined_data, tmp;
    sprintf(combined_data.name,"%s",argv[flag]);
    combined_data.load();
    std::string str=combined_data.name;
    std::string filestr=str.substr(str.rfind("/")+1);
    std::string prefix=filestr.substr(0,filestr.find("_")+1);
    filestr=str.substr(str.rfind("src"),str.rfind("MIXED")-str.rfind("src"));
    prefix+=filestr;
    prefix+=str.substr(str.rfind("t"),str.rfind(".")-str.rfind("t"));
    if(combined_data.dim[combined_data.find_dim(dim_displacement)].n_indices > 65){
	combined_data.exclude(tmp,dim_displacement,65);
    }else combined_data.copy(tmp);
    	
    std::cout<< prefix << endl;
    print_to_txt(tmp, prefix.c_str(), gamma, qxyz);
    auto end_time=std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;
    std::cout<< "total time is: "<<elapsed.count() << endl;
    return 0;
}

