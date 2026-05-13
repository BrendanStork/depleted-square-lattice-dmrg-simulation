#include "itensor/all.h"
#include "kagome.h" //Custom kagome header file
#include <iomanip>

using namespace itensor;

int main(int argc, char *argv[])
  {
  int Nx = 7;
  int Ny = 2;
  double U = 0;
  int Npart = 1;
  int Nsweeps = 20;
	

	
  /* N = Nx * Ny * 6 when using kagome as Nx and Ny now represent the number of unit cells
  in the Nx and Ny direction, rather than the number of sites, with each cell consisting of six sites */
  auto N = Nx * Ny * 6;
  
	
  auto sites = Electron(N, {"ConserveSz", false,"ConserveNf", true});
  double t0 = 1.0;
  double t1 = 1.0;

 
  auto ampo = AutoMPO(sites);
	  
  //"squareDepl" is the 1/5th-depleted square lattice
  auto lattice = squareDepl(Nx, Ny, {"YPeriodic = ", false});
  for(auto j : lattice) //Modified the Itensor Hamiltonian algorithm to handle 2 bond types. This requires altering header file.
	  {
	  if (j.type == "0")
		  {
		  ampo += -t0, "Cdagup", j.s1, "Cup", j.s2;
		  ampo += -t0, "Cdagup", j.s2, "Cup", j.s1;
		  ampo += -t0, "Cdagdn", j.s1, "Cdn", j.s2;
		  ampo += -t0, "Cdagdn", j.s2, "Cdn", j.s1;
		  }
	  else if (j.type == "1")
		  {
		  ampo += -t1, "Cdagup", j.s1, "Cup", j.s2;
		  ampo += -t1, "Cdagup", j.s2, "Cup", j.s1;
		  ampo += -t1, "Cdagdn", j.s1, "Cdn", j.s2;
		  ampo += -t1, "Cdagdn", j.s2, "Cdn", j.s1;
		  }
	  }
  
  for(auto j : range1(N))
	  {
	  ampo += U, "Nupdn", j;
	  }
	
  auto H = toMPO(ampo); //Hamiltonian
  auto state = InitState(sites, "Emp"); //State initialized to empty
	
  


	//RANDOM INITIAL STATE
	//Creates random intial state in which Nup = Ndn for
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<int> distribution1(1, N);
	std::uniform_int_distribution<int> distribution2(1, 3);
	
	
	int Numpart = Npart;
	auto DnCnt = std::round((Npart/2.0));
	auto UpCnt = Npart-DnCnt;
	auto UpDnNpartCnt = Npart-N;
	
	auto DnCnt2 = DnCnt;
	auto UpCnt2 = UpCnt;
	
	int rand_num1;
	int rand_num2;
	std::vector<int> SiteList = {};
	auto InList = true;
	
	while(Numpart > 0){
		
		if(UpDnNpartCnt>0){
			
			InList = true;
			while(InList){
				
				rand_num1 = distribution1(generator);
				auto NotThere = std::find(SiteList.begin(), SiteList.end(), rand_num1);
				if (NotThere == SiteList.end()){
					InList = false;
					
				}
			}
			auto SiteNow = rand_num1;
			SiteList.push_back(SiteNow);
			state.set(SiteNow, "UpDn");
			UpCnt-=1;
			DnCnt-=1;
			UpDnNpartCnt-=1;
			Numpart-=2;
		}
		else{
			InList = true;
			while(InList){
				
				rand_num1 = distribution1(generator);
				auto NotThere = std::find(SiteList.begin(), SiteList.end(), rand_num1);
				if (NotThere == SiteList.end()){
					InList = false;
					print("Numpart<=N: ", rand_num1, "\n");
				}
			}
			auto SiteNow = rand_num1;
			SiteList.push_back(SiteNow);
			if(DnCnt == 0){
				state.set(SiteNow, "Up");
				UpCnt-=1;
				Numpart-=1;
			}
			else if(UpCnt == 0){
				state.set(SiteNow, "Dn");
				DnCnt-=1;
				Numpart-=1;
			}
			else if(Numpart >= 2){
				rand_num2 = distribution2(generator);
				//print(rand_num2, "\n");
				if(rand_num2 == 1){
					state.set(SiteNow, "Up");
					UpCnt-=1;
					Numpart-=1;
				}
				else if(rand_num2 == 2){
					state.set(SiteNow, "Dn");
					DnCnt-=1;
					Numpart-=1;
				}
				else{
					state.set(SiteNow, "UpDn");
					UpCnt-=1;
					DnCnt-=1;
					Numpart-=2;
				}
			}
		}
	}










/*
	
	// Alternate non-random state initialization
  for(auto j : range1(N))
	  {
	  state.set(j, (j == 1  ? "Dn" : "Emp"));
	  
	  }
*/
/* // Addtional alternate non-random state initialization
	for(auto idx : range1(Npart))
	   {
	   if(idx >1 and idx%2 == 0){
		   state.set(idx,"Up");
		}
	   else if(idx >1 and idx%2 != 0){
		   state.set(idx,"Dn");
	   }
	   }
*/

		   
  //ITensor sweep parameters
  auto sweeps = Sweeps(Nsweeps);
  sweeps.maxdim() = 20, 60, 100, 600, 5000, 10000, 12000;
  sweeps.noise() = 1E-3, 5E-3, 1E-4, 5E-4, 1E-5, 5E-6, 1E-6, 5E-7, 1E-7, 5E-8, 1E-8, 5E-9,  1E-9, 5E-10, 1E-10, 5E-11, 1E-11, 5E-12, 1E-12, 5E-13, 1E-13, 5E-14, 1E-14, 0;
  sweeps.cutoff() = 1E-2, 1E-4, 1E-8;
  sweeps.niter() = 16;

	
  
	
	auto psi0 = MPS(state);
	
	
	/* //ITensor Spin Expectation values algorithm
		for( auto j : range1(N) )
			{
			//re-gauge psi to get ready to measure at position j
			psi0.position(j);

			auto ket = psi0(j);
			auto bra = dag(prime(ket,"Site"));

			auto Szjop = op(sites,"Sz",j);

			//take an inner product
			auto szj = elt(bra*Szjop*ket);
		
			}
	 */
	
	
  auto [energy,psi] = dmrg(H,psi0,sweeps,{"Quiet=",true});
	
	
	
	
	
	
	
	
	
	
	
	
	/*
	//Density expectation values, based on ITensor operator framework
	
	println("\nj Nup = ");
		for( auto j : range1(N) )
			{
			
			psi.position(j);

			auto ket = psi(j);
			auto bra = dag(prime(ket,"Site"));

			auto Nupjop = op(sites,"Nup",j);

		
			auto Nuj = elt(bra*Nupjop*ket);
			printfln("%d %.12f",j,Nuj);
			}
	
	println("\nj Ndn = ");
		for( auto j : range1(N) )
			{
			psi.position(j);
			auto ket = psi(j);
			auto bra = dag(prime(ket,"Site"));
			auto Ndnjop = op(sites,"Ndn",j)
			auto Ndnj = elt(bra*Ndnjop*ket);
			printfln("%d %.12f",j,Ndnj);
			}
	
	
	*/
	
	
	//Spin Correlation, based on ITensor operator framework
	
	
	double SiSj[N][N]; //Spin correlation array
	
	
	for(int p = 1; p <= N ; p++){
		for (int i = 1; i <= N; i++){
			 
		
			auto psi1 = psi;
			auto psi2 = psi;
			auto Sziop = op(sites,"Sz",p);
			auto Szjop = op(sites,"Sz",i);
			
			
		  
			
			auto C = Sziop*psi1(p);
			psi1.set(p,C.noPrime());

			C = Szjop*psi2(i);
			psi2.set(i,C.noPrime());

			SiSj[p-1][i-1] = inner(psi1,psi2);
		}
	}
	

	/*
	//BOND CORRELATION AVERAGE
	
	double t0List[N]; // List of t0 correlations
	double t1List[B-N]; // List of t1 correlations
	double t0Sum = 0;
	double t1Sum = 0;
	int a = 0;
	int b = 0;
	for(int q = 0; q < N; q++){
		for(int n = 0; n < B; n++){
			if(lattice[n].s1 == q + 1 and lattice[n].type == "0"){
				int corrIndex = lattice[n].s2 -1;
				t0List[a] = SiSj[q][corrIndex];
				t0Sum += t0List[a];
				a++;
				
				}
			else if(lattice[n].s1 == q + 1 and lattice[n].type == "1"){
				int corrIndex = lattice[n].s2 -1;
				t1List[b] = SiSj[q][corrIndex];
				t1Sum += t1List[b];
				b++;
				
				}
		}
	}
	double Ave0 = t0Sum/N; //Averages
	double Ave1 = t1Sum/(B - N);
	
	
	//DENSITY CORRELATION
	
	double NtotCorr[N][N]; //Density correlation array
	

	
	for(int p = 1; p <= N ; p++){
		for (int i = 1; i <= N; i++){
			 
		
			auto psi1 = psi;
			auto psi2 = psi;
			auto Ntotiop = op(sites,"Ntot",p);
			auto Ntotjop = op(sites,"Ntot",i);
			
			
		  
			
			auto C = Ntotiop*psi1(p);
			psi1.set(p,C.noPrime());

			C = Ntotjop*psi2(i);
			psi2.set(i,C.noPrime());

			NtotCorr[p-1][i-1] = inner(psi1,psi2);
		}
	}
	*/
	
	
	
	
	
	
	
	
	
	
  //Value outputs
  PrintData(U);
  PrintData(lattice);
  PrintData(Nx);
  PrintData(Ny);
	
	std::cout << "\n" << "Energy = " << std::setprecision(13) << energy  << "\n";
	std::cout << "\n" << "SPIN CORRELATIONS" << "\n";
	for(int p = 0; p < N; p++){
		std::cout << "\n";
		for(int i = 0; i < N; i++){
			std::cout <<  std::setprecision(13) << SiSj[p][i]  << "  " << "\n";
			
		}
	}
	
	//std::cout << "\n" << "AVERAGES" << "\n";
	
	//std::cout << "Ave0 = " << Ave0 << "\n" << "Ave1 = " << Ave1 << "\n";
	/*
	std::cout << "\n" << "DENSITY CORRELATIONS" << "\n";
	
	for(int p = 0; p < N; p++){
		std::cout << "\n";
		for(int i = 0; i < N; i++){
			std::cout << NtotCorr[p][i] <<  std::setprecision(13) << "  " << "\n";
			
		}
	}
	std::cout << "\n";
	*/
	
	
	
	
	
	
	
	
	
	
	double siteSpin[N];
	
	println("\nj Sz = ");
		for( auto j : range1(N) )
			{
			//re-gauge psi to get ready to measure at position j
			psi.position(j);

			auto ket = psi(j);
			auto bra = dag(prime(ket,"Site"));

			auto Szjop = op(sites,"Sz",j);

			//take an inner product
			auto szj = elt(bra*Szjop*ket);
			printfln("%d %.12f",j,szj);
			siteSpin[j-1] = szj;
				
			}
	
 
//Superconducting phase characterization for s, s*, and d-wave
	/*
		print("Superconducting \n");
		
	int f_s[N][N];
		int f_es[N][N];
		int f_d[N][N];
		
		for(int i = 0; i < N; i++){
			for(int j = 0; j < N; j++){
				f_s[i][j] = 0;
				f_es[i][j] = 0;
				f_d[i][j] = 0;
			}
		}
		
		
	
		
		for (int i = 1; i<=N; i++){
			for (int k = 1; k<=N; k++){
				if (i == k){
					f_s[i-1][k-1] = 1;
					f_s[k-1][i-1] = 1;
				}
				
				for (int p = 0; p<B ; p++){
					if (lattice[p].s1 == i and lattice[p].s2 == k){
						f_es[i-1][k-1] = 1;
						f_es[k-1][i-1] = 1;
						//print(p, " ",i, " ", k, " ", f_ik[i-1][k-1], "\n");
						if ((i%2 == 0 and k%2 == 0)){
							f_d[i-1][k-1] = -1;
							f_d[k-1][i-1] = -1;
							//print(p, " ",i, " ", k, " ", f_ik[i-1][k-1], "\n");
							break;
						}
						else if(i%2 != 0 and k%2 != 0){
							f_d[i-1][k-1] = 1;
							f_d[k-1][i-1] = 1;
							//print(p, " ",i, " ", k, " ", f_ik[i-1][k-1], "\n");
							break;
						}
						else if(i%2 !=0 and k%2 == 0 and k== i+1){
							f_d[i-1][k-1] = 1;
							f_d[k-1][i-1] = 1;
							//print(p, " ",i, " ", k, " ", f_ik[i-1][k-1], "\n");
							break;
						}
						else if(abs(k-i) == 1 or abs(k-i) == 3){
							f_d[i-1][k-1] = -1;
							f_d[k-1][i-1] = -1;
							//print(p, " ",i, " ", k, " ", f_ik[i-1][k-1], "\n");
							break;
						}
						break;
					}
					
				}
			}
		}

	  int neighbors[N][3];
		for(int i = 0; i < N; i++){
			for(int j = 0; j < 3; j++){
				neighbors[i][j] = 0;
			}
		}
		
	for(auto j : lattice){
		for(int k=0 ; k<3; k++){
			if(neighbors[j.s1-1][k] == 0){
				neighbors[j.s1-1][k] = j.s2;
				break;
			}
		}
		for(int k=0 ; k<3; k++){
			if(neighbors[j.s2-1][k] == 0){
				neighbors[j.s2-1][k] = j.s1;
				break;
			}
		}
	}


 double gup[N][N]; //<cdag, c>
 double kup[N][N]; //<c, cdag>
	
	
	for(int m = 1; m <= N ; m++){
		for(int n = 1; n <= N; n++){
			
			auto Cupop_m = op(sites, "Cup", m);
			auto Cdagupop_m = op(sites, "Cdagup", m);
	
			auto Cupop_n = op(sites, "Cup", n);
			auto Cdagupop_n = op(sites, "Cdagup", n);
	
			auto psi_c_m = psi;
			auto psi_cdag_m = psi;
			auto psi_c_n = psi;
			auto psi_cdag_n = psi;
	
			auto C = Cupop_m*psi_c_m(m);
			psi_c_m.set(m,C.noPrime());
			
			C = Cdagupop_m*psi_cdag_m(m);
			psi_cdag_m.set(m,C.noPrime());
			
			C = Cupop_n*psi_c_n(n);
			psi_c_n.set(n,C.noPrime());
			
			C = Cdagupop_n*psi_cdag_n(n);
			psi_cdag_n.set(n,C.noPrime());
			
			gup[m-1][n-1] = inner(psi_c_m, psi_c_n);
			kup[m-1][n-1] = inner(psi_cdag_m, psi_cdag_n);
			
		}
	}


	//I needed four-operator expectation values for the superconducting analysis, which ITensor
	//didn't appear to easily support. I also needed them to operate accross four indices.
	//This gets around that by separating the bra and ket operators into chunks that are operated on
	//individually then combined, as well as separating the correlated and uncorrelated contributions.



	//double Pij_s[N][N];
	double Pij_es[N][N];
	double Pij_d[N][N];

	double PijTot_es[N][N];
	double PijTot_d[N][N];

	double PijUnCorr_es[N][N];
	double PijUnCorr_d[N][N];
	for(int i = 1; i <= N ; i++)
		{
			auto Cupop_i = op(sites, "Cup", i);
			auto Cdnop_i = op(sites, "Cdn", i);
			
			auto Cdagupop_i = op(sites, "Cdagup", i);
			auto Cdagdnop_i = op(sites, "Cdagdn", i);
			
			print("lattice = ", lattice[i-1].s1, " ", lattice[i-1].s2, "\n");
			
			
			
			for(int j = 1; j <= N ; j++)
			{
				
				auto Cupop_j = op(sites, "Cup", j);
				auto Cdnop_j = op(sites, "Cdn", j);
				
				auto Cdagupop_j = op(sites, "Cdagup", j);
				auto Cdagdnop_j = op(sites, "Cdagdn", j);
				
				//auto DelExp1_s = 0.0;
				//auto DelExp2_s = 0.0;
				
				auto DelExp1_es = 0.0;
				auto DelExp2_es = 0.0;
				
				auto DelExp1_d = 0.0;
				auto DelExp2_d = 0.0;
		
			//Initialize Uncorrelated Dels
				
		auto Uncorr_es = 0.0;
		auto Uncorr_d = 0.0;
				
		for(int kp = 0; kp < 3 ; kp++)
				{
					 
					int k = neighbors[i-1][kp];
			if(f_es[i-1][k-1] == 0){
						continue;
					}
					
					auto Cupop_k = op(sites, "Cup", k);
					auto Cdnop_k = op(sites, "Cdn", k);
					
					auto Cdagupop_k = op(sites, "Cdagup", k);
					auto Cdagdnop_k = op(sites, "Cdagdn", k);
					
			for(int lp = 0; lp < 3; lp++)
					{
						int l = neighbors[j-1][lp];
			if(f_es[j-1][l-1] == 0){
							continue;
						}

						
					
						auto psi_ik1 = psi;
						auto psi_ik2 = psi;
						auto psi_jl1 = psi;
						auto psi_jl2 = psi;
						
						auto psi_ik3 = psi;
						auto psi_ik4 = psi;
						auto psi_jl3 = psi;
						auto psi_jl4 = psi;
						
						
						auto Cupop_l = op(sites, "Cup", l);
						auto Cdnop_l = op(sites, "Cdn", l);
						
						auto Cdagupop_l = op(sites, "Cdagup", l);
						auto Cdagdnop_l = op(sites, "Cdagdn", l);
					  
						
						
						
						//First C operations
						
						auto C = Cdnop_k*psi_ik1(k);
						psi_ik1.set(k,C.noPrime());

						C = Cupop_k*psi_ik2(k);
						psi_ik2.set(k,C.noPrime());
						
						C = Cdnop_l*psi_jl1(l);
						psi_jl1.set(l,C.noPrime());

						C = Cupop_l*psi_jl2(l);
						psi_jl2.set(l,C.noPrime());
						
						//Second C operations
						
						auto D = Cdnop_i*psi_ik1(i);
						psi_ik1.set(i,D.noPrime());

						D = Cupop_i*psi_ik2(i);
						psi_ik2.set(i,D.noPrime());
						
						D = Cdnop_j*psi_jl1(j);
						psi_jl1.set(j,D.noPrime());

						D = Cupop_j*psi_jl2(j);
						psi_jl2.set(j,D.noPrime());
						
						
						
						//First Cdags
						auto Cdag = Cdagdnop_k*psi_ik3(k);
						psi_ik3.set(k,Cdag.noPrime());

						Cdag = Cdagupop_k*psi_ik4(k);
						psi_ik4.set(k,Cdag.noPrime());
						
						Cdag = Cdagdnop_l*psi_jl3(l);
						psi_jl3.set(l,Cdag.noPrime());

						Cdag = Cdagupop_l*psi_jl4(l);
						psi_jl4.set(l,Cdag.noPrime());
						
						//Second Cdags
						
						auto Ddag = Cdagdnop_i*psi_ik3(i);
						psi_ik3.set(i,Ddag.noPrime());

						Ddag = Cdagupop_i*psi_ik4(i);
						psi_ik4.set(i,Ddag.noPrime());
						
						Ddag = Cdagdnop_j*psi_jl3(j);
						psi_jl3.set(j,Ddag.noPrime());

						Ddag = Cdagupop_j*psi_jl4(j);
						psi_jl4.set(j,Ddag.noPrime());



			//Correlated
						auto Delcomp1 = ((inner(psi_ik1,psi_jl1) - inner(psi_ik1,psi_jl2) - inner(psi_ik2,psi_jl1) + inner(psi_ik2,psi_jl2)));
						auto Delcomp2 = ((inner(psi_ik3,psi_jl3) - inner(psi_ik3,psi_jl4) - inner(psi_ik4,psi_jl3) + inner(psi_ik4,psi_jl4)));
						
						//DelExp1_s += f_s[i-1][k-1]*f_s[j-1][l-1]*Delcomp1;
						//DelExp2_s += f_s[i-1][k-1]*f_s[j-1][l-1]*Delcomp2;
						
						
						DelExp1_es += f_es[i-1][k-1]*f_es[j-1][l-1]*Delcomp1;
						DelExp2_es += f_es[i-1][k-1]*f_es[j-1][l-1]*Delcomp2;
  
					  
						DelExp1_d += f_d[i-1][k-1]*f_d[j-1][l-1]*Delcomp1;
						DelExp2_d += f_d[i-1][k-1]*f_d[j-1][l-1]*Delcomp2;


			//Uncorrelated
						
			auto Uncorrcomp = gup[k-1][l-1]*gup[i-1][j-1] + gup[k-1][j-1]*gup[i-1][l-1] + kup[i-1][j-1]*kup[k-1][l-1] + kup[i-1][l-1]*kup[k-1][j-1];
			
						Uncorr_es += f_es[i-1][k-1]*f_es[j-1][l-1]*Uncorrcomp;
						Uncorr_d += f_d[i-1][k-1]*f_d[j-1][l-1]*Uncorrcomp;




					}
				}

		PijTot_es[i-1][j-1] = 0.25*(DelExp1_es + DelExp2_es);
				PijTot_d[i-1][j-1] = 0.25*(DelExp1_d + DelExp2_d);
											  
		PijUnCorr_es[i-1][j-1] = 0.5*(Uncorr_es);
				PijUnCorr_d[i-1][j-1] = 0.5*(Uncorr_d);

				Pij_es[i-1][j-1] = PijTot_es[i-1][j-1] - PijUnCorr_es[i-1][j-1];
				Pij_d[i-1][j-1] = PijTot_d[i-1][j-1] - PijUnCorr_d[i-1][j-1];


			}
		}

*/






   
	/*
	
	//CREATES FILES
	
   
	std::ofstream SpinFile("SpinFile_4x2_tRatiotRat_UUval_Npart_SweepsweepNum.txt");
	for(int i = 0; i < N; i++){
		
		SpinFile << std::setprecision(13) << siteSpin[i] << "\n";
		
	}
	SpinFile.close();
	
	
	std::ofstream SpinCorrFile("SpinCorrFile_4x2_tRatiotRat_UUval_Npart_SweepsweepNum.txt");
	for(int i = 0; i < N; i++){
		for(int j = 0; j< N; j++){
			SpinCorrFile <<  std::setprecision(13) << SiSj[i][j] << "\n";
		}
		SpinCorrFile << "\n";
	}
	SpinCorrFile.close();
   */
/*
	std::ofstream PFile("Pij_es_File_2x2_tRatiotRat_UUval_Npart_SweepsweepNum.txt");
		for(int i = 0; i < N; i++){
			for(int j = 0; j< N; j++){
				PFile <<  std::setprecision(13) << Pij_es[i][j] << "\n";
			}
			PFile << "\n";
		}
		PFile.close();

	std::ofstream PFile2("Pij_d_File_2x2_tRatiotRat_UUval_Npart_SweepsweepNum.txt");
		for(int i = 0; i < N; i++){
			for(int j = 0; j< N; j++){
				PFile2 <<  std::setprecision(13) << Pij_d[i][j] << "\n";
			}
			PFile2 << "\n";
		}
		PFile2.close();

	
	std::ofstream PCorrFile("PijCorr_es_File_2x2_tRatiotRat_UUval_Npart_SweepsweepNum.txt");
		for(int i = 0; i < N; i++){
			for(int j = 0; j< N; j++){
				PCorrFile <<  std::setprecision(13) << PijCorr_es[i][j] << "\n";
			}
			PCorrFile << "\n";
		}
		PCorrFile.close();

		std::ofstream PCorrFile2("PijCorr_d_File_2x2_tRatiotRat_UUval_Npart_SweepsweepNum.txt");
		for(int i = 0; i < N; i++){
			for(int j = 0; j< N; j++){
				PCorrFile2 <<  std::setprecision(13) << PijCorr_d[i][j] << "\n";
			}
			PCorrFile2 << "\n";
		}
		PCorrFile2.close();
	*/

/*
	std::ofstream N_File("N_File_4x2_tRatiotRat_SweepsweepNum.txt");
	N_File << Nx << "\n" << Ny << "\n" << N;
	N_File.close();


	std::ofstream C_File("ConvergeData_4x2_tRatiotRat_UUval_Npart_SweepsweepNum.txt");
C_File << Nsweeps << "\n" << std::setprecision(13) <<  energy << "\n" << std::setprecision(13) << SiSj[1][2] << "\n" << std::setprecision(13) << siteSpin[1] << "\n" <<std::setprecision(13) << siteSpin[2];
	C_File.close();
	  */
 /*
	std::ofstream PFile("PalphaFile_2x2_tRatiotRat_UUval_Npart_alpha1_SweepsweepNum.txt");
		for(int i = 0; i < N; i++){
			for(int j = 0; j< N; j++){
				PFile <<  std::setprecision(13) << P_ij[i][j] << "\n";
			}
			PFile << "\n";
		}
		PFile.close();
*/




   
   
	//Prints more values (ground state energy, U value spin expectation value, etc)
	PrintData(Nx);
	PrintData(Ny);
	PrintData(U);
	std::cout << "\n" << "Energy = " << std::setprecision(13) << energy  << "\n";
	for(int i = 1; i <= N; i++){
		std::cout <<  std::setprecision(13) << siteSpin[i]  << "  " << "\n";
		
	}*/
	
	
   
  return 0;
}
