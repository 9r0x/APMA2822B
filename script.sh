#!/bin/bash
echo "====================="
echo "Contiguous, no optimization"
echo
gcc -fopenmp matvec_con.c && ./sim.py
echo "====================="
echo "Separate, no optimization"
echo
gcc -fopenmp matvec_sep.c && ./sim.py
echo "====================="
echo "Contiguous, -O1"
echo
gcc -fopenmp -O1 matvec_con.c && ./sim.py
echo "====================="
echo "Contiguous, -O2"
echo
gcc -fopenmp -O2 matvec_con.c && ./sim.py
echo "====================="
echo "Contiguous, -O3"
echo
gcc -fopenmp -O3 matvec_con.c && ./sim.py

