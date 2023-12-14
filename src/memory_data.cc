#include <string>
#include <cstring>
#include <iostream>

#include "ins.h"
#include "memory_data.h"

void MEMORY_DATA::set_init_fname(const std::string fname, bool is_compressed){
    init_fname = fname;
    compressed = is_compressed;
}

void MEMORY_DATA::init(){
    uint64_t begin_size[8] = {0};
    char page[1<<14];
    uint64_t icount = 0;
    FILE *f;

    if(compressed) {
        std::string xz_d_command = "xz -v -dc " + init_fname + ".xz";
        f = popen(xz_d_command.c_str(), "r");
    } else {
        f = fopen(init_fname.c_str(), "rb");
    }

    if(f == NULL){
        printf("Could not open %s\n", init_fname.c_str());
        exit(1);
    }

    while (fread(begin_size, sizeof(begin_size), 1, f) == 1)
    {
        icount++;
        uint64_t addr = begin_size[0];
        uint64_t page_size = begin_size[1];

        if(fread(page, sizeof(page), 1, f) != 1)
            printf("Data Error\n");

        if(page_size != 16384){
            printf("Page Size Error\n");
            if(compressed) {
                pclose(f);
            } else {
                fclose(f);
            }
            exit(1);
        }
        memcpy(ram+addr, page, page_size);
    }

    if(compressed) {
        pclose(f);
    } else {
        fclose(f);
    }

    printf("Memory Data Load %ld pages\n", icount);
}

int64_t MEMORY_DATA::read(uint64_t addr, uint8_t size, bool sign){
    int64_t ret_data = 0;
    uint8_t ram_data_b = 0;
    uint16_t ram_data_h = 0;
    uint32_t ram_data_w = 0;
    uint64_t ram_data_d = 0;

    switch (size) {
        case SIZE_BYTE:
            ram_data_b = *((uint8_t *)(ram + addr));
            ret_data = sign? ((int8_t) ram_data_b) : (((uint64_t) ram_data_b) & 0xff);
            break;
        case SIZE_HWORD:
            ram_data_h = *((uint16_t *)(ram + addr));
            ret_data = sign? ((int16_t) ram_data_h) : (((uint64_t) ram_data_h) & 0xffff);
            break;
        case SIZE_WORD:
            ram_data_w = *((uint32_t *)(ram + addr));
            ret_data = sign? ((int32_t) ram_data_w) : (((uint64_t) ram_data_w) & 0xffffffff);
            break;
        case SIZE_DWORD:
            ram_data_d = *((uint64_t *)(ram + addr));
            ret_data = ram_data_d;
            break;
        default:
            break;
    }
    return ret_data;
}

void MEMORY_DATA::write(uint64_t addr, uint64_t wdata, uint8_t size){
    uint8_t ram_wdata_b = 0;
    uint16_t ram_wdata_h = 0;
    uint32_t ram_wdata_w = 0;
    switch (size) {
        case SIZE_BYTE:
            ram_wdata_b = (uint8_t) (wdata & 0xff);
            *((uint8_t *) (ram + addr)) = ram_wdata_b;
            break;
        case SIZE_HWORD:
            ram_wdata_h = (uint16_t) (wdata & 0xffff);
            *((uint16_t *) (ram + addr)) = ram_wdata_h;
            break;
        case SIZE_WORD:
            ram_wdata_w = (uint32_t) (wdata & 0xffff);
            *((uint32_t *) (ram + addr)) = ram_wdata_w;
            break;
        case SIZE_DWORD:
            *((uint64_t *) (ram + addr)) = wdata;
            break;
        default:
            printf("Memory Write Error! Size = %d\n", size);
            exit(1);
    }
}