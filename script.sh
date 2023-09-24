#!/bin/bash
echo "====================="
echo "Contiguous, no optimization"
echo
g++ -fopenmp matvec_con.c && ./sim.py
echo "====================="
echo "Separate, no optimization"
echo
g++ -fopenmp matvec_sep.c && ./sim.py
echo "====================="
echo "Contiguous, -O1"
echo
g++ -fopenmp -O1 matvec_con.c && ./sim.py
echo "====================="
echo "Contiguous, -O2"
echo
g++ -fopenmp -O2 matvec_con.c && ./sim.py
echo "====================="
echo "Contiguous, -O3"
echo
g++ -fopenmp -O3 matvec_con.c && ./sim.py

