import java.util.*;
import java.util.concurrent.*;
import java.lang.*;

class Main4{
   public static void main(String args[]){
      int max = Integer.parseInt(args[0]);
      int nthread = Integer.parseInt(args[1]);

      Server server = new Server(max, nthread);
      server.esegui();
   }
}

class Server{
   private ExecutorService pool;

   private int k;
   private int max;

   public Server(int max, int nthread){
      this.max = max;
      this.k = nthread;

      pool = Executors.newFixedThreadPool(k);
   }

   public void esegui(){
      for(int i = 0; i < max; i++){
         Task task = new Task(i);
         pool.execute(task);
      }
      pool.shutdown();

      try{
         if(!pool.awaitTermination(60, TimeUnit.SECONDS)){
            System.out.println("Thread inattivo per troppo tempo");
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
      try{
         System.out.println("Task " + id + " in esecuzione");
         Thread.sleep(1000);
      }catch(InterruptedException e){
         e.printStackTrace();
      }
   }
}
