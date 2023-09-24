#!/usr/bin/env python3
import subprocess, re

WARMUP = 3
REP = 5

def run(rows, cols):
    p = subprocess.Popen(["./a.out", str(rows), str(cols)],
                          stdout=subprocess.PIPE)
    out, _ = p.communicate()
    out = out.decode("utf-8")
    return re.findall(r"([.\d]+)", out)[-1]

def main():
    # exp = 5 takes too long
    exp = range(1, 5)
    for i in exp:
        rows = 10 ** i
        cols = 10 ** i

        results = []
        
        # Warm up
        for _ in range(WARMUP):
            run(rows, cols)
        
        # Repeat and take average
        for _ in range(REP):
            results.append(float(run(rows, cols)))
        print(f"rows: {rows:5d}, cols: {cols:5d}, time: {(sum(results) / len(results)):.2f}ms")

if __name__ == "__main__":
    main()