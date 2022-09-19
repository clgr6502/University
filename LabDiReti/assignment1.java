import java.util.*;
import java.lang.*;

class Main{
   public static void main(String[] args){
      float accuracy;
      long time;

      Scanner in = new Scanner(System.in);
      
      //System.
      accuracy = in.nextFloat();
      time = in.nextInt();

      Calculator piCalc = new Calculator(accuracy);

      Thread thread = new Thread(piCalc);
      thread.start();

      //Condizioni per terminazione
      try{
         thread.join(time);
      }catch(InterruptedException e){
         e.printStackTrace();
      }

      if(thread.isAlive()){
         thread.interrupt();
      }
   }
}

class Calculator implements Runnable{
   //Valore costante
   private final float accuracy;

   public Calculator(float accuracy){
      this.accuracy = accuracy;
   }

   public void run(){
      //Calcolo del pi-greco
      double pi = 0;
      double denom = 1;
      int i = 0;

      while(!Thread.interrupted()){
         if((i % 2) == 0){
            pi += (1 / denom);
         }else{
            pi -= (1 / denom);
         }
         denom += 2;
         i++;
      }
      pi *= 4;
      

      if((Math.abs(pi - Math.PI)) <= this.accuracy){
         if(!Thread.interrupted()){
            System.out.println("Accuracy of pi = " + pi);
            Thread.currentThread().interrupt();
            return;
         }
      }
   }
}
