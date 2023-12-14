#ifndef MEMORY_DATA_H
#define MEMORY_DATA_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/mman.h>

#define MEMORY_SIZE ((uint64_t)1 << 40)

class MEMORY_DATA {
protected:
    std::string init_fname;
    bool compressed = false;

public:
    uint8_t * ram = nullptr;

    void set_init_fname(const std::string fname, bool is_compressed);
    void init();

    int64_t read(uint64_t addr, uint8_t size, bool sign);
    void write(uint64_t addr, uint64_t wdata, uint8_t zize);
    // constructor
    MEMORY_DATA (){
        ram = (uint8_t *)mmap(nullptr, MEMORY_SIZE, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
        if(ram == MAP_FAILED){
            printf("mmap error!\n");
            exit(1);
        }
    }
};

#endif
