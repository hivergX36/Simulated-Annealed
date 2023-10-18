import random 
import math 

class SimulatedAnealed:
    
    def __init__(self, initemperature,stoppingCriteria,alpha, pallier):
        """Constructeur de notre classe"""
        
        self.NbVariable = 0
        self.Temperature = initemperature
        self.LowTEmperature = stoppingCriteria
        self.alpha = alpha
        self.pallier = pallier
        self.Nbconstraint = 0 
        self.PriceVariable = []
        self.ConstraintMatrix = []
        self.Constraint = []
        self.candidate_choosen = []
        self.current_solution = []
        self.CopySolution = []
        self.Optsolution = []
        self.IndCandidat = 0
        
    def parseKnapsack(self,text):
        with open(text, "r") as fichier:
           content = ''.join(fichier.readline().splitlines())
           content.split() 
           self.NbVariable = int(content[0])
           content = ''.join(fichier.readline().splitlines())
           content.split() 
           self.NbConstraint =  int(content[0])
           print(self.NbVariable)
           print(self.NbConstraint)
           k = self.NbVariable
           content = [line.strip() for line in fichier.readlines()]
           for i in range(self.NbVariable):
             self.PriceVariable.append(int(content[i]))
             
             
           for i in range(self.NbConstraint):
             l = [int(content[i]) for i in range(k, k + self.NbVariable) ]
             self.ConstraintMatrix.append(l)
             k += self.NbVariable
             
        self.Constraint = [int(content[i]) for i in range(k, k + self.NbConstraint)]
        self.Utility = [[0,i] for i in range(self.NbVariable)]
        self.CurrentSolution = [0 for i in range(self.NbVariable)]
        self.OptSolution = [0 for i in range(self.NbVariable)]
        self.CopySolution = [0 for i in range(self.NbVariable)]


    
    
    BoltzmanEquation = lambda a,b,t: math.exp(a/t)

        
    def initSolution(self):
      list_alea = [i for i in range(self.NbVariable)]
      indice = random.choice(list_alea)
      self.CurrentSolution[indice] = 1 
      self.Optsolution[indice] = 1
      
        
    def add(self):
      list_alea = [i for i in range(self.NbVariable) if self.CopySolution[i] == 0]
      indice = random.choice(list_alea)
      self.CopySolution[indice] = 1
      
    def drop(self):
      list_alea = [i for i in range(self.NbVariable) if self.CopySolution[i] == 1]
      indice = random.choice(list_alea)
      self.CopySolution[indice] = 0 
      
    def CheckUpdateCurrentSolution(self):
      BoltzmanEquation = lambda a,t: math.exp(a/t)

      admissible = True
      print("solution courrante: ")
      print(self.CurrentSolution)
      print("NbVariable: ")
      print(self.NbVariable)
      self.CopySolution = [self.CurrentSolution[i] for i in range(self.NbVariable)]
      self.add()
      delta = 0
      criteria = 0
      p = random.random()
      sum_constraint = [sum([self.CopySolution[i]  * self.ConstraintMatrix[j][i] for i in range(self.NbVariable)]) for j in range(self.NbConstraint)]
      print(sum_constraint)
      print(self.Constraint)
      for i in range(self.NbConstraint):
        if self.Constraint[i] < sum_constraint[i]:
          print("le voisin n'est pas admissible")
          self.drop()
          sum_constraint = [sum([self.CopySolution[i]  * self.ConstraintMatrix[j][i] for i in range(self.NbVariable)]) for j in range(self.NbConstraint)]
          if self.Constraint[i] < sum_constraint[i]:
            print("le voisin n'est finalement pas admissible")
            admissible = False
            break
          else:
            print("le voisin est finalement admissible")
            admissible = True
            break 
      delta = sum([self.CopySolution[i] * self.PriceVariable[i] for i in range(self.NbVariable)])   -  sum([self.CurrentSolution[i] * self.PriceVariable[i] for i in range(self.NbVariable)])
      criteria = BoltzmanEquation(-delta,self.Temperature)
      if (delta > 0 or criteria > p) and admissible:
        self.CurrentSolution = [self.CopySolution[i] for i in range(self.NbVariable)]
      else:
        self.CopySolution = [self.CurrentSolution[i] for i in range(self.NbVariable)]
          
        
        
    def UpdateBestSolution(self):
      Zneighbour = sum([self.CopySolution[i] * self.PriceVariable[i] for i in range(self.NbVariable)])
      Zbest = sum([self.OptSolution[i] * self.PriceVariable[i] for i in range(self.NbVariable)])
      if Zneighbour > Zbest:
        self.OptSolution = [self.CopySolution[i] for i in range(self.NbVariable)]
          
           
    def resolve(self):
      self.initSolution
      print(self.PriceVariable)
      print(self.CurrentSolution)
      while self.Temperature > self.LowTEmperature:
        self.CheckUpdateCurrentSolution()
        self.UpdateBestSolution()
        self.Temperature = self.alpha * self.Temperature 
        print(self.Temperature)

    

         
    def DisplaySolution(self):
      print(self.OptSolution)
    
        

      
             
        
             
             
            
             
            



             
            
            

            
             
          
            

        
        
        




     






    
      
        

