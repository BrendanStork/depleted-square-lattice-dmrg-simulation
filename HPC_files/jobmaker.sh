#! /bin/bash
 
function folder_maker(){

	tRatio_array=( 0.25 )
        for tRat in "${tRatio_array[@]}"
        	do
        	echo $tRat
        	mkdir tRatio$tRat
        	cd tRatio$tRat

		t_array=( 0.500 )
		for t_hop in "${t_array[@]}"
			do
        		echo $t_hop
			tprime_array=( 2.000 )
			for tprime in "${tprime_array[@]}"
        			do
                		echo $tprime
				U_array=( 12.000 )
        			for Uval in "${U_array[@]}"
					do 
					echo $Uval
        				mkdir U$Uval
        				cd U$Uval
					#Np_array=( 1 3 5 7 9 11 13 15 ) # ( 2 4 6 8 10 12 14 16 )
					#Np_array=( 15 18 21 24) # 3 6 9 12)# 15 18 21 24 )
					#Np_array=( 20 24 28 32 ) # 4 8 12 16)# 20 24 ) #28 32 )
					for Npart in {20..20}
					#for Npart in "${Np_array[@]}"
						do
                                		echo $Npart
                                		mkdir Np$Npart
                                		cd Np$Npart
						for sweepNum in {15..15}
							do
							echo $sweepNum
							mkdir Sweep$sweepNum
							cd Sweep$sweepNum
							cp /home/bstork/fifthdepl/* .
							sed -i -e 's/U = Uval/U = '$Uval'/g' hubbard2d_fdp.cc
							sed -i -e 's/UUval/U'$Uval'/g' hubbard2d_fdp.cc
							sed -i -e 's/Npart = 0/Npart = '$Npart'/g' hubbard2d_fdp.cc
							sed -i -e 's/_Npart/_Np'$Npart'/g' hubbard2d_fdp.cc

							sed -i -e 's/Nsweeps = sweepNum/Nsweeps = '$sweepNum'/g' hubbard2d_fdp.cc
                         	        		sed -i -e 's/_SweepsweepNum.txt/_Sweep'$sweepNum'.txt/g' hubbard2d_fdp.cc
							sed -i -e 's/t0 = t_hop/t0 = '$t_hop'/g' hubbard2d_fdp.cc
							sed -i -e 's/t1 = tprime/t1 = '$tprime'/g' hubbard2d_fdp.cc
                                        		sed -i -e 's/_tRatiotRat/_tRatio'$tRat'/g' hubbard2d_fdp.cc

							sed -i -e 's/Uval/'$Uval'/g' job_file.slurm
							sed -i -e 's/Npart/'$Npart'/g' job_file.slurm
							sed -i -e 's/tRat/'$tRat'/g' job_file.slurm
							sed -i -e 's/sweepNum/'$sweepNum'/g' job_file.slurm
							make
							sbatch job_file.slurm
						cd ..
						done
					cd ..
					done
				cd ..		
				done		
			done
		done
	cd ..
	done

}
folder_maker
