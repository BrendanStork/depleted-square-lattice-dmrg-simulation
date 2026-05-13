#include "itensor/mps/lattice/latticebond.h"

namespace itensor {

LatticeGraph inline
squareDepl(int Nx,
                   int Ny,
                   Args const& args = Args::global())
    {
    //auto yperiodic = args.getBool("YPeriodic",false);
    // Periodicity on y is meaningless for one dimensional chain or a ladder
    //yperiodic = yperiodic && (Ny > 2);


    
    
        
    auto N = Nx*Ny*4;
    //int B = 3*N/2 - Nx;
    
    LatticeGraph latt;
    
    int siteNum[Nx][Ny][4];
    int sites[N][3];
    
    
    
    int bNum = 0;
    int C = 0;
    
    for (int i = 0; i < Nx; i++){
            for (int j = 0; j < Ny; j++){
                for (int k = 0; k < 4; k++){
                    
                    siteNum[i][j][k] = C;
                    sites[C][0] = i;
                    sites[C][1] = j;
                    sites[C][2] = k;
                    C++;
                    
                }
            }
        }
    
    
    
    
    
    for (int i = 0; i < N; i++){
            for (int j = 0; j < N; j++){
                
                if (sites[j][0]==sites[i][0]+1 && sites[i][2]==0 && sites[j][2]==2 && sites[i][1]==sites[j][1]){
                    
                    latt.emplace_back(i+1,j+1, "1");
                    bNum++;
                    
                }
                
                else if (sites[j][1]==sites[i][1]+1 && sites[i][2]==1 && sites[j][2]==3 && sites[i][0]==sites[j][0]){
                    
                    latt.emplace_back(i+1,j+1,"1");
                    bNum++;
                     
                }
                //sites[i, 1]==m-1 and sites[j, 1]==0 and sites[i, 2]==1 and sites[j, 2]==3 and sites[i, 0]==sites[j,0]:
                else if (sites[i][1]==Ny-1 && sites[j][1]==0 && sites[i][2]==1 && sites[j][2]==3 && sites[i][0]==sites[j][0]){
                    
                    latt.emplace_back(i+1,j+1,"1");
                    bNum++;
                    
                }
                
                else if (sites[i][0]==sites[j][0] && sites[i][1]==sites[j][1] && sites[j][2]==sites[i][2]+1){
                    
                    latt.emplace_back(i+1,j+1, "0");
                    bNum++;
                    
                }
                
                else if (sites[i][0]==sites[j][0] && sites[i][1]==sites[j][1] && sites[i][2]-sites[j][2]==3){
                 
                    latt.emplace_back(i+1,j+1, "0");
                    bNum++;
                    
                }
                
            }
        }
    
    return latt;
    }
}
    
    
    
    
    
    
    
    
    
    
   


