#!/bin/bash

#SBATCH -n 1
#SBATCH -t 30:00
#SBATCH --mem=10G
#SBATCH -J run_different_alloc
#SBATCH -o run_different_alloc-%j.out
#SBATCH -e run_different_alloc-%j.err
#SBATCH --mail-type=FAIL
#SBATCH --mail-user=jiayu_zheng@brown.edu

python3 sim.py
