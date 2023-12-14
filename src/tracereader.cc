/*
 *    Copyright 2023 The ChampSim Contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "tracereader.h"
#include "error.h"

#include <cassert>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

#include <memory_data.h>
#include <regfile.h>

extern MEMORY_DATA mem_data[NUM_CPUS];
extern REGFILE regfile[NUM_CPUS];

bool go_back_set;

#define WARMUP_INST 10000000

tracereader::tracereader(uint8_t cpu, std::string _ts) : cpu(cpu), trace_string(_ts)
{
  std::string last_dot = trace_string.substr(trace_string.find_last_of("."));

  if (trace_string.substr(0, 4) == "http") {
    // Check file exists
    char testfile_command[4096];
    sprintf(testfile_command, "wget -q --spider %s", trace_string.c_str());
    FILE* testfile = popen(testfile_command, "r");
    if (pclose(testfile)) {
      std::cerr << "TRACE FILE NOT FOUND" << std::endl;
      assert(0);
    }
    cmd_fmtstr = "wget -qO- -o /dev/null %2$s | %1$s -dc";
  } else {
    std::ifstream testfile(trace_string);
    if (!testfile.good()) {
      std::cerr << "TRACE FILE NOT FOUND" << std::endl;
      assert(0);
    }
    cmd_fmtstr = "%1$s -dc %2$s";
  }

  if (last_dot[1] == 'g') // gzip format
    decomp_program = "gzip";
  else if (last_dot[1] == 'x') // xz
    decomp_program = "xz";
  else {
    std::cout << "ChampSim does not support traces other than gz or xz compression!" << std::endl;
    assert(0);
  }

  open(trace_string);
}

tracereader::~tracereader() { close(); }

template <typename T>
ooo_model_instr tracereader::read_single_instr()
{
  T trace_read_instr;

#ifdef COLLECT_INSTR_NUM
  instr_num++;
#endif
  static uint64_t inst_cnt = 0;
  inst_cnt ++;

  bool go_back = (inst_cnt == WARMUP_INST);
  if(inst_cnt == WARMUP_INST)
    go_back_set = true;

  while (!fread(&trace_read_instr, sizeof(T), 1, trace_file) || go_back) {
    // reached end of file for this trace
    std::cout << "*** Reached end of trace: " << trace_string <<  std::endl;

    // Regfile & Memory initializaiton
    regfile[cpu].init();
    mem_data[cpu].init();

    // close the trace file and re-open it
    close();
    open(trace_string);
    #ifdef COLLECT_INSTR_NUM
        std::cout << "The Total Number of Instructions: " << instr_num << std::endl;
        exit(0);
    #endif
    go_back = false;
  }

  // copy the instruction into the performance model's instruction format
  ooo_model_instr retval(cpu, trace_read_instr);

  retval.wait_rob_empty = (inst_cnt == WARMUP_INST);
  return retval;
}

void tracereader::open(std::string trace_string)
{
  char gunzip_command[4096];
  sprintf(gunzip_command, cmd_fmtstr.c_str(), decomp_program.c_str(), trace_string.c_str());
  trace_file = popen(gunzip_command, "r");
  if (trace_file == NULL) {
    std::cerr << std::endl << "*** CANNOT OPEN TRACE FILE: " << trace_string << " ***" << std::endl;
    assert(0);
  }
}

void tracereader::close()
{
  if (trace_file != NULL) {
    pclose(trace_file);
  }
}

class cloudsuite_tracereader : public tracereader
{
  ooo_model_instr last_instr;
  bool initialized = false;

public:
  cloudsuite_tracereader(uint8_t cpu, std::string _tn) : tracereader(cpu, _tn) {}

  ooo_model_instr get()
  {
    ooo_model_instr trace_read_instr = read_single_instr<cloudsuite_instr>();

    if (!initialized) {
      last_instr = trace_read_instr;
      initialized = true;
    }

    last_instr.branch_target = trace_read_instr.ip;
    ooo_model_instr retval = last_instr;

    last_instr = trace_read_instr;
    return retval;
  }
};

class input_tracereader : public tracereader
{
  ooo_model_instr last_instr;
  bool initialized = false;

public:
  input_tracereader(uint8_t cpu, std::string _tn) : tracereader(cpu, _tn) {}

  ooo_model_instr get()
  {
    ooo_model_instr trace_read_instr = read_single_instr<input_instr>();

    if (!initialized) {
      last_instr = trace_read_instr;
      initialized = true;
    }

    last_instr.branch_target = trace_read_instr.ip;
    ooo_model_instr retval = last_instr;

    last_instr = trace_read_instr;
    return retval;
  }
};

class loongarch_tracereader : public tracereader
{
  ooo_model_instr last_instr;
  bool initialized = false;

public:
  loongarch_tracereader(uint8_t cpu, std::string _tn) : tracereader(cpu, _tn) {}

  ooo_model_instr get()
  {
    ooo_model_instr trace_read_instr = read_single_instr<loongarch_instr>();

    if (!initialized) {
      last_instr = trace_read_instr;
      initialized = true;
    }

    last_instr.branch_target = trace_read_instr.ip;
    ooo_model_instr retval = last_instr;

    last_instr = trace_read_instr;
    return retval;
  }
};


tracereader* get_tracereader(std::string fname, uint8_t cpu, uint8_t trace_type)
{
  if (trace_type == TRACE_TYPE_X86) {
    return new input_tracereader(cpu, fname);
  } else if (trace_type == TRACE_TYPE_LOONGARCH) {
    return new loongarch_tracereader(cpu, fname);
  } else if (trace_type == TRACE_TYPE_CLOUDSUITE) {
    return new cloudsuite_tracereader(cpu, fname);
  } else {
    lsassertm(0, "Invalid trace type");
    abort();
  }
}
