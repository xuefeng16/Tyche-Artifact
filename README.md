<p align="center">
  <h1 align="center"> Tyche-Artifact </h1>
  <p>  <p>
</p>

# Compile

ChampSim takes a JSON configuration script. Examine `champsim_config.json` for a fully-specified example. All options described in this file are optional and will be replaced with defaults if not specified. The configuration scrip can also be run without input, in which case an empty file is assumed.
```
$ ./config.sh <configuration file>
$ make
```

# Run simulation

Execute the binary directly.
```
$ bin/champsim --warmup_instructions 20000000 --simulation_instructions 100000000 -loongarch trace_name.champsim.trace.xz
```

# Trace
Each slice includes a trace, memory.bin (the initial value of mrmory), and regfile.txt (the initial value of architectural register). The traces are available at https://drive.google.com/drive/folders/1EzXBul1yRNQJn7Lv7EjuR8dWctPlTlT1?usp=sharing.