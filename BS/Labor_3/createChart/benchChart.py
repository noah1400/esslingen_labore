import subprocess
import re
import matplotlib.pyplot as plt

BENCH_DIR = "../out/"
BENCH_NAMES = ["mmap_out.txt","pipes_out.txt","readv_out.txt"]
SIZES = [64, 256, 1024, 4096, 16384, 65536, 262144, 1048576, 4194304, 16777216]
SIZES = [x * 0.001 for x in SIZES]

for name in BENCH_NAMES:
    print("executing ", name)

    s = ""
    with open(BENCH_DIR+name) as f:
        for line in f:
            s += line

    m = re.findall(r"\((\d.*)\)",s,re.MULTILINE)
    y = [float(x.split(' ')[0]) for x in m]
    plt.plot(SIZES,y, label=name)
    print("Bandwidths of ", name)
    for g in m:
        print(g)
plt.legend()
plt.show()


