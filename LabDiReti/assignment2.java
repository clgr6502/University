import java.util.*;
import java.lang.*;
import java.util.concurrent.*;

class Assignment2{
   public static void main(String args[]){
      int max = Integer.parseInt(args[0]);

      Ufficio ufficio = new Ufficio(max);
      ufficio.esegui();
   }
}

//Classe che rappresenta il ThreadPool
class Ufficio{
   private ExecutorService pool;

   private ArrayBlockingQueue<Task> sala;
   private int k = 5;

   public Ufficio(int max){
      pool = new ThreadPoolExecutor(4, 4, 0L, TimeUnit.SECONDS,
      new ArrayBlockingQueue<>(4));

      sala = new ArrayBlockingQueue(max);
      this.k = max;
   }

   public void esegui(){
      //Riempio la coda con i tasks
      for(int i = 0; i < k; i++){
         sala.add(new Task(i));
      }

      //Svuoto la coda
      while(!sala.isEmpty()){
         try{
            pool.execute(sala.peek());
            sala.remove();
         }catch(RejectedExecutionException e){}
      }

      pool.shutdown();
      //RICHIESTA OPZIONALE
      try{
         if(!pool.awaitTermination(60, TimeUnit.SECONDS)){
            System.out.println(Thread.currentThread().getName() + "e' stato inattivo per troppo tempo");
            pool.shutdownNow();
         }
      }catch(InterruptedException e){
         pool.shutdownNow();
      }
   }
}

class Task implements Runnable{
   private int id;

   public Task(int id){
      this.id = id;
   }

   public void run(){
      System.out.println("----------------");
      System.out.println("Entra il cliente " + id);

      try{
         Long duration = (long)(Math.random() * 1000);
         System.out.println("[" + Thread.currentThread().getName() + "]" + " completa " + id + " in " + duration + "ms");
         System.out.println("");
         Thread.sleep(duration);
      }catch(InterruptedException e){
         e.printStackTrace();
      }
   }
}
