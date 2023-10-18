import java.util.*;
import java.io.*;



public class SimulatedAnealed{

    int NbVariable;
    int NbConstraints;
    int IndCandidat;
    double Temperature; 
    double LowTemperature; 
    double Alpha;
    double L;
    

    /* Price function */
    int[] Price;
    /* Utility function */

    /*Matrix of constraint*/
    float[][] CostMatrix;
    /*Vector of solution*/
    int[]  NeighbourSolution;
    int[] CurrentSolution;
    int[] OptSolution;




    Boolean[]  Candidate_choosen; 
    float[] constraint;
    float[] Sumconstraint;


 
    SimulatedAnealed(String name, double temperature, double lowTemperature, double alpha, double pallier){

  
        Temperature = temperature;
        LowTemperature = lowTemperature;
        Alpha = alpha;
        L = pallier;
        

        File input = new File(name);
        
        
        try{
            Scanner reader = new Scanner(input);
            String[] nums = reader.nextLine().split(",");
            this.NbVariable = Integer.parseInt(nums[0]);
            this.NbConstraints = Integer.parseInt(nums[1]);
            this.Price = new int[this.NbVariable];
            this.NeighbourSolution = new int[this.NbVariable];
            this.CurrentSolution = new int[this.NbVariable];
            this.OptSolution = new int[this.NbVariable];
            this.CostMatrix = new float[this.NbConstraints][this.NbVariable];
            this.Candidate_choosen = new Boolean[this.NbVariable];
            this.constraint = new float[this.NbConstraints];
            this.Sumconstraint = new float[this.NbConstraints];

            nums = reader.nextLine().split(",");



            for(int i = 0; i < this.NbVariable; i++){
                this.Price[i] = Integer.parseInt(nums[i]);
                this.NeighbourSolution[i] = 0;
                this.CurrentSolution[i] = 0;
                this.OptSolution[i] = 0;
            }

                for(int i = 0; i < this.NbConstraints; i++){
                    nums = reader.nextLine().split(",");
      
                    for(int j = 0; j < this.NbVariable; j++ ){
                    this.CostMatrix[i][j] = Float.parseFloat(nums[j]);
                  }
                }

            nums = reader.nextLine().split(",");
            
            for(int i = 0; i < NbConstraints; i++){
                this.constraint[i] = Float.parseFloat(nums[i]);
                this.Sumconstraint[i] = 0;
            }
            reader.close();

        
    }
    catch (IOException e){
      System.out.println("no file");
     }

  };
  
  
  public void displayCostMatrix(){
        for(int i = 0; i < NbConstraints; i++){
            for(int j = 0; j < NbVariable; j++)
            {
                System.out.println(this.CostMatrix[i][j] + "\t") ; 

        }

        System.out.println("\nd");
        }
    }


    void InitSolution(){
        Random random = new Random();
        int choix = random.nextInt(4 - 0) + 0; 
        CurrentSolution[choix] = 1;
        NeighbourSolution[choix] = 1;

    }

    void add(){
        int compteur = 0;
        int indice;
        int choix; 
        List<Integer> listChoix = new ArrayList<Integer>();

        Random random = new Random();
       


    
        for(int i = 0; i < NbVariable; i++){
            if(NeighbourSolution[i] < 1){
                listChoix.add(i);
                compteur++;
            }
        }

        indice = random.nextInt(compteur - 0) + 0;
        choix = listChoix.get(indice);
        NeighbourSolution[choix] = 1;



    }




    void drop(){
        int compteur = 0;
        int indice;
        int choix; 
        Random random = new Random();
        List<Integer> listChoix = new ArrayList<Integer>();


        

    
        for(int i = 0; i < NbVariable; i++){
            if(NeighbourSolution[i] > 0){
                listChoix.add(i);
                compteur++;
            }
        }

        indice = random.nextInt(compteur - 0) + 0;
        choix = listChoix.get(indice);
        NeighbourSolution[choix] = 0;

    }

    double Boltzman(double a, double t){
        return Math.exp(-a/t);
    }

    void displaycurrentsolution(){
        System.out.println("La solution courrante est: " + "\t") ;
        for(int i = 0; i < NbVariable ; i++){
          System.out.println(this.CurrentSolution[i]  + "\n");
            }
        }
    
    
    void displayNeighborSolution(){
       System.out.println( "La solution de voisinage est: ");
        for(int i = 0; i < NbVariable ; i++){
         System.out.println( NeighbourSolution[i] + "\n");
            }
        }

    void displayOptSolution(){

       System.out.println( "La solution optimale est: ");
        for(int i = 0; i < NbVariable ; i++){
         System.out.println(  OptSolution[i] + "\t");
            }
        }


    

    

    void CopyNeighborSolution(){
        for(int i = 0; i < NbVariable; i++){
                NeighbourSolution[i] = CurrentSolution[i];
            }
        }

        void CopyCurrentSolution(){
        for(int i = 0; i < NbVariable; i++){
               CurrentSolution[i] =  NeighbourSolution[i] ;
            
        }
        }
    
    void Sum_Constraint(){

          for(int i = 0; i < NbConstraints; i++){
                Sumconstraint[i] = 0;
            }

     
        for(int j = 0;j < NbConstraints; j++){
            for(int i = 0; i < NbVariable; i++){
                Sumconstraint[j] += CostMatrix[j][i] * NeighbourSolution[i];
            }
        }

     System.out.println( Sumconstraint[0] +  Sumconstraint[1] + "\t");


    }

    float Delta(){
        float Delta = 0;
        for(int i = 0; i < NbVariable; i++){
            Delta += NeighbourSolution[i] * Price[i] - CurrentSolution[i] * Price[i];
            }
            return Delta;
        }
        

       float DeltaZopt(){
        float delta = 0;
        for(int i = 0; i < NbVariable; i++){
            delta += NeighbourSolution[i] * Price[i] - OptSolution[i] * Price[i];
            }
            return delta;
        }

    
     void CheckUpdateCurrentSolution(){
        int compteur = 0;
        float DeltaNeighbour;  
        boolean admissible = true; 
        double criteria = 0;
        double p = Math.random() ;
        CopyNeighborSolution();
        displaycurrentsolution();
        add();
        displayNeighborSolution();

        Sum_Constraint();
 

/*Problème de boucle*/
/*Plutôt faire avec un compteur*/

        for(int i = 0; i < NbConstraints; i++){
            if(Sumconstraint[i] > constraint[i]){
                System.out.println("Le voisin n'est pas admissible!" + "\t");
                compteur += 1; 
            }
        }
                if(compteur > 0){
                    drop();
                    Sum_Constraint();
                     for(int i = 0; i < NbConstraints; i++){
                        if(Sumconstraint[i] > constraint[i]){
                            System.out.println( "Le voisin n'est finalement pas admissible!" + "\t");
                             admissible = false;
                             break;
                    }
                }
            }
        displaycurrentsolution();
        displayNeighborSolution();

        DeltaNeighbour = Delta();
        System.out.println("le delta est: " +  DeltaNeighbour + "\n");
        criteria = Boltzman(DeltaNeighbour,Temperature);
       System.out.println( "Le critère est: " +  criteria + "\t"); 
      System.out.println("La probabilité est: " +  p + "\t");
       System.out.println( "adimissible ? " + admissible + "\t");


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

                this.OptSolution[i]  = NeighbourSolution[i];


            }

            

        }


      }

      void resolve(){
        InitSolution();
        while(Temperature > LowTemperature){
            CheckUpdateCurrentSolution();
            UpdateBestSolution();
            Temperature = Alpha * Temperature;
            System.out.println("La température actuelle est: " + Temperature + "\t");
        }

        displayOptSolution();


      }


};


      
  

    

