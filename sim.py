import subprocess, re

WARMUP = 3
REP = 5

def run(rows, cols):
    p = subprocess.Popen(["./matmul.out", str(rows), str(cols)],
                          stdout=subprocess.PIPE)
    out, _ = p.communicate()
    out = out.decode("utf-8")
    pattern = r"time elpased: ([e+-.\d]+) microseconds" 
    match = re.search(pattern, out)
    total_time = float(match.group(1))
    return total_time
    # return re.findall(r"([.\d]+)", out)[-1]

def main():
    # exp = 5 takes too long
    exp = range(1, 6)
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
        time = sum(results) / len(results)
        num_flops = 2 * rows * cols
        num_bytes = (rows * cols + rows + cols) * 4
        byteps = num_bytes / (time+1e-6) / 1e6
        arithmetic_intensity = num_flops / num_bytes
        flops = num_flops / (time+1e-6) / 1e6
        print(f"rows: {rows:5d}, cols: {cols:5d}, time: {(sum(results) / len(results)):.2f}us")
        print(f"flops: {flops:2f} GigaFLOPS , bytes: {byteps:2f} GigaBytes/second, arithmetic intensity: {arithmetic_intensity:.2f}")

if __name__ == "__main__":
    main()
