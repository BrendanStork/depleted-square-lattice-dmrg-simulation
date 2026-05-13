#! /bin/bash

function submit_job(){
	for dir in $(
		ls -d */ $1
	); do
		cd $dir
		sbatch job_file.slurm
		cd ..
	done
}
submit_job $1

# example: sh jobsubmitter.sh /scratch/ei5/L24_444
