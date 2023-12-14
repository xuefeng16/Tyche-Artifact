#include <string>
#include <cstring>
#include <fstream>
#include <iostream>

#include "regfile.h"


void REGFILE::set_init_fname(const std::string fname){
    init_fname = fname;
}

void REGFILE::init(){
    uint64_t icount = 0;
    std::ifstream f(init_fname);
    if(f.fail()){
        printf("Could not open %s\n", init_fname.c_str());
        exit(1);
    }

    for (std::string line; std::getline(f, line);) {
        data[icount] = stoull(line.substr(line.length()-16, 16), NULL, 16);
        icount++;
    }
    f.close();

    if(data[0] != 0){
        printf("Register File Init Error!\n");
        exit(1);
    }
    printf("Register File Load %ld registers\n", icount);
}

uint64_t REGFILE::read(uint8_t addr){
    return data[addr];
}

void REGFILE::write(uint8_t addr, uint64_t wdata){
    data[addr] = wdata;
    return ;
}