#include<iostream> 
#include<vector> 
#include<fstream> 
#include "SimulatedAnealed.hpp"

int main(){
      /*La fonction checkup n'est pas bonne */
 
   std::string file = "Knapsack.txt";

   SimulatedAnealed Recuit = SimulatedAnealed(file,900,10,0.5,2);
  /* Recuit.InitSolution();
   std::cout << Recuit.Sumconstraint[0][0] << std::endl;

   Recuit.CheckUpdateCurrentSolution(); */

  

   Recuit.resolve();



}
  






