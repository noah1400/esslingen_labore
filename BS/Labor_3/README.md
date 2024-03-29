# Pipe Benchmark
This program is a benchmark that measures the performance of pipes in Linux. It performs a number of writes to a pipe and measures the number of ticks (clock cycles) taken to complete the operation. The size of the write and the number of measurements can be configured.
### Requirements
- Linux system with `getrdtsc` function available
- `gcc` compiler
### Building
To build the program, run:
```
make
```
This will compile the `bench_pipes` binary.
### Usage
To run the benchmark, execute the `bench_pipes` binary with no arguments:
```
./bench_pipes
```
The program will print the results of the benchmark to the console in the following format:
```
PID:<pid> time: min:<min_ticks> max:<max_ticks> Ticks Avg without min/max:<avg_ticks> Ticks (for <measurements> measurements) for <size> Bytes (MB/s)
```
### Configuration
The following constants can be modified in the `main` function to customize the benchmark:
- `MEASUREMENTS`: the number of times the write operation is performed
- `SLEEP_TIME`: the number of seconds to sleep before starting the benchmark
- `sizes`: an array of sizes for the write operation, in bytes
### Cleaning up
To remove the compiled binary and any other files generated by the build process, run:
```
make clean
```
**Please note that this code is intended to be used as a reference and not copied verbatim**