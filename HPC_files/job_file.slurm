#!/bin/bash
#SBATCH --job-name=42_tRat_Uval_Npart_sweepNum
#SBATCH --account=commons
#SBATCH --partition=himem
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=6
##SBATCH --mem-per-cpu=4GB
##SBATCH --time=3000:00:00
#SBATCH --mail-user=brendan.stork@sjsu.edu
#SBATCH --mail-type=ALL

echo "My job ran on:"
echo $SLURM_NODELIST

module purge
module load gnu/9.3.0
module load mkl-intel

./hubbard2d_fdp > UUval_4x2_Npart_tRat_sweepNum.out

echo "Program finished running with exit code $? at: `date`"
