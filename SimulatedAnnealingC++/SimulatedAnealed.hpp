#include<vector> 
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <math.h>      



struct SimulatedAnealed{

    int NbVariable;
    int NbConstraints;
    int IndCandidat;
    float Temperature; 
    float LowTemperature; 
    float Alpha;
    float L;

    /* Price function */
    std::vector<int> * Price;
    /* Utility function */

    /*Matrix of constraint*/
    std::vector<float>*CostMatrix;
    /*Vector of solution*/
    std::vector<int> * NeighbourSolution;
    std::vector<int> * CurrentSolution;
    std::vector<int> * OptSolution;




    std::vector<bool> * Candidate_choosen; 
    std::vector<float> * constraint;
    std::vector<float> * Sumconstraint;


 
    SimulatedAnealed(std::string name, float temperature, float lowTemperature, float alpha, float pallier){

        int k = 0;
        int number;
        int candidat; 

            std::ifstream fichier(name);
                if(fichier){

                   

                     fichier >> NbVariable;
                     fichier >> NbConstraints; 

                     Temperature = temperature;
                     LowTemperature = lowTemperature;
                     Alpha = alpha;
                     L = pallier;


                     Price = new std::vector<int>; 
                     NeighbourSolution = new std::vector<int>;
                     CurrentSolution = new std::vector<int>;
                     OptSolution =  new std::vector<int>;

                     CostMatrix = new  std::vector<float>[NbConstraints];
                     Candidate_choosen = new std::vector<bool>;
                     constraint = new std::vector<float>; 
                     Sumconstraint = new std::vector<float>[NbConstraints]; 

                     



                     while(k < NbVariable){
                        fichier >> number; 
                        Candidate_choosen[0].push_back(0);
                        Price[0].push_back(number);
                        NeighbourSolution[0].push_back(0); 
                        CurrentSolution[0].push_back(0)
;
                        OptSolution[0].push_back(0);

                         


                        k++;



                     };



                     for(int i = 0; i < NbConstraints; i++){
                        k = 0;

                        while(k < NbVariable){
                            fichier >> number; 
                            CostMatrix[i].push_back(number);
                            k++;
                        }
                     }

                     for(int i = 0; i < NbConstraints; i++){
                        fichier >> number;
                        constraint[0].push_back(number);
                        Sumconstraint[0].push_back(0);

                     }
                }
    }
                
                



    

    void displayCostMatrix(){
        for(int i = 0; i < NbConstraints; i++){
            for(int j = 0; j < NbVariable; j++)
            {
                std::cout << CostMatrix[i][j] << " ";

        }

        std::cout << std::endl;
        }
    }


    void InitSolution(){
        int choix = rand() % NbVariable;
        CurrentSolution[0][choix] = 1;
        NeighbourSolution[0][choix] = 1;

    }

    void add(){
        int compteur = 0;
        int nb_one = 0;
        int indice;
        int choix; 
        

        for(int i = 0; i < NbVariable; i++){
            if(NeighbourSolution[0][i] < 1){
            nb_one++;  
            }
        }
        int listChoix[nb_one];
        for(int i = 0; i < NbVariable; i++){
            if(NeighbourSolution[0][i] < 1){
                listChoix[compteur] = i;
                compteur++;
            }
        }

        indice = rand() % compteur;
        choix = listChoix[indice];
        NeighbourSolution[0][choix] = 1;



    }




    void drop(){
        int compteur = 0;
        int nb_one = 0;
        int indice;
        int choix; 
        

        for(int i = 0; i < NbVariable; i++){
            if(NeighbourSolution[0][i] > 0){
            nb_one++;  
            }
        }
        int listChoix[nb_one];
        for(int i = 0; i < NbVariable; i++){
            if(NeighbourSolution[0][i] > 0){
                listChoix[compteur] = i;
                compteur++;
            }
        }

        indice = rand() % compteur;
        std::cout << "indice à supprimer: " << indice << std::endl;
        choix = listChoix[indice];
        NeighbourSolution[0][choix] = 0;

    }

    float Boltzman(float a, float t){
        return exp(-a/t);
    }

    void displaycurrentsolution(){
        std::cout << "La solution courrante est: " << std::endl;
        for(int i = 0; i < NbVariable ; i++){
            std::cout <<   CurrentSolution[0][i]  << std::endl;
            }
        }
    
    
    void displayNeighborSolution(){
            std::cout << "La solution de voisinage est: " << std::endl;
        for(int i = 0; i < NbVariable ; i++){
            std::cout <<   NeighbourSolution[0][i]  << std::endl;
            }
        }

    void displayOptSolution(){

              std::cout << "La solution optimale est: " << std::endl;
        for(int i = 0; i < NbVariable ; i++){
            std::cout <<   OptSolution[0][i]  << std::endl;
            }
        }


    

    

    void CopyNeighborSolution(){
        for(int i = 0; i < NbVariable; i++){
                NeighbourSolution[0][i] = CurrentSolution[0][i];
            }
        }

        void CopyCurrentSolution(){
        for(int i = 0; i < NbVariable; i++){
               CurrentSolution[0][i] =  NeighbourSolution[0][i] ;
            
        }
        }
    
    void Sum_Constraint(){

          for(int i = 0; i < NbConstraints; i++){
                Sumconstraint[0][i] = 0;
            }

     
        for(int j = 0;j < NbConstraints; j++){
            for(int i = 0; i < NbVariable; i++){
                Sumconstraint[0][j] += CostMatrix[j][i] * NeighbourSolution[0][i];
            }
        }

        std::cout << Sumconstraint[0][0] << " " << Sumconstraint[0][1] << std::endl;


    }

    float Delta(){
        float Delta = 0;
        for(int i = 0; i < NbVariable; i++){
            Delta += NeighbourSolution[0][i] * Price[0][i] - CurrentSolution[0][i] * Price[0][i];
            }
            return Delta;
        }
        

       float DeltaZopt(){
        float delta = 0;
        for(int i = 0; i < NbVariable; i++){
            delta += NeighbourSolution[0][i] * Price[0][i] - OptSolution[0][i] * Price[0][i];
            }
            return delta;
        }

    
     void CheckUpdateCurrentSolution(){
        int compteur = 0;
        float DeltaNeighbour;  
        bool admissible = true; 
        float delta = 0;
        float criteria = 0;
        float p = (float)rand() / (float)RAND_MAX ;
        CopyNeighborSolution();
        displaycurrentsolution();
        add();
        displayNeighborSolution();

        Sum_Constraint();
 

/*Problème de boucle*/
/*Plutôt faire avec un compteur*/

        for(int i = 0; i < NbConstraints; i++){
            if(Sumconstraint[0][i] > constraint[0][i]){
                std::cout << "Le voisin n'est pas admissible!" << std::endl;
                compteur += 1; 
            }
        }
                if(compteur > 0){
                    drop();
                    Sum_Constraint();
                     for(int i = 0; i < NbConstraints; i++){
                        if(Sumconstraint[0][i] > constraint[0][i]){
                             std::cout << "Le voisin n'est finalement pas admissible!" << std::endl;
                             admissible = false;
                             break;
                    }
                }
            }
        displaycurrentsolution();
        displayNeighborSolution();

        DeltaNeighbour = Delta();
        std::cout << "le delta est: " << DeltaNeighbour << std::endl;
        criteria = Boltzman(DeltaNeighbour,Temperature);
        std::cout << "Le critère est: " << criteria << std::endl; 
        std::cout << "La probabilité est: " << p << std::endl;
        std::cout << "adimissible ? " << admissible << std::endl;


        if(admissible == true &&  (DeltaNeighbour > 0 || p < criteria)){

           

            CopyCurrentSolution();



        }else{
            CopyNeighborSolution();
        }


        displaycurrentsolution();
        displayNeighborSolution();

     }
   

      void UpdateBestSolution(){
       float deltaZopt =  DeltaZopt();
        if(deltaZopt > 0){

            for(int i = 0; i < NbVariable; i++){

                OptSolution[0][i]  = NeighbourSolution[0][i];


            }

            

        }


      }

      void resolve(){
        InitSolution();
        while(Temperature > LowTemperature){
            CheckUpdateCurrentSolution();
            UpdateBestSolution();
            Temperature = Alpha * Temperature;
            std::cout << "La température actuelle est: " << Temperature << std::endl;
        }

        displayOptSolution();


      }


};


      
  

    

