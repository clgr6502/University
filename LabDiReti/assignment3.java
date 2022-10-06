import java.lang.*;
import java.util.*;
import java.util.concurrent.*;
import java.util.concurrent.locks.*;

class Assignment3{
   public static void main(String args[]){
      Scanner in = new Scanner(System.in);
      int prof, stud, tesisti;

      System.out.println("Inserire il numero dei prof, studenti e tesisti: ");
      prof = in.nextInt();
      stud = in.nextInt();
      tesisti = in.nextInt();

      Tutor tutor = new Tutor(prof, stud, tesisti);
      tutor.esegui();
   }
}

class Tutor{
   private int stud;
   private int prof;
   private int tesisti;

   public Tutor(int prof, int stud, int tesisti){
      this.stud = stud;
      this.prof = prof;
      this.tesisti = tesisti;
   }

   public void esegui(){
      ExecutorService pool = Executors.newCachedThreadPool();
      new Lab();

      while(prof != 0 || stud != 0 || tesisti != 0){
         if(prof != 0){
            pool.execute(new Prof());
            prof--;
         }else if(stud != 0){
            pool.execute(new Stud());
            stud--;
         }else if(tesisti != 0){
            pool.execute(new Tesista());
            tesisti--;
         }
      }
      pool.shutdown();
   }
}

class Lab{
   //Accesso alle risorse (pc) tramite WriteLock
   public static ReentrantReadWriteLock l = new ReentrantReadWriteLock();
   //Array che rappresenta i computer
   public static ArrayList<ReentrantReadWriteLock> pc = new ArrayList<>(20);

   public Lab(){
      for(int i = 0; i < 20; i++){
         pc.add(new ReentrantReadWriteLock());
      }
   }
}

class Prof implements Runnable{
   private ReentrantReadWriteLock.WriteLock lab = Lab.l.writeLock();

   public void run(){
      long durata = (long)(Math.random() * 1000);
      //k: numero di accessi
      int k = (int)(Math.random() * 5) + 1;

      //accedo al laboratorio k volte
      for(int i = 0; i < k; i++){
         try{
            lab.lock();
            System.out.println("Professore " + Thread.currentThread().getId() + " usa il laboratorio");
            Thread.sleep(durata);
         }catch(InterruptedException e){}
         finally{
            lab.unlock();
         }
      }
   }  
}

class Stud implements Runnable{
   //Read lock aula computer
   //per permettere agli altri studenti di utilizzare i pc
   private ReentrantReadWriteLock.ReadLock lab = Lab.l.readLock();
   //Read lock per i computer, minore priorità rispetto i tesisti
   private ArrayList<ReentrantReadWriteLock> pc = Lab.pc ;

   public void run(){
      long durata = (long) (Math.random() * 1000);
      ReentrantReadWriteLock.ReadLock pc_lock = new ReentrantReadWriteLock().readLock();

      int k = (int)(Math.random() * 5) + 1, i;

      boolean done;
      for(int j = 0; j < k; j++) {
         done = false;
         i = 0;
         try{
            lab.lock();
            while(!done){
               pc_lock = pc.get(i).readLock();
               //cerco un pc libero
               if(pc.get(i).getReadLockCount() == 0){
                  if(pc_lock.tryLock()){
                     System.out.println("Studente " + Thread.currentThread().getId() + " sta usando pc " + (i));
                     Thread.sleep(durata);
                     done = true;
                  }
               }
               i = (i + 1) % 20;
            }
         }catch(InterruptedException e){}
         finally{
            pc_lock.unlock();
            lab.unlock();
         }
      }
   }
}

class Tesista implements Runnable{
   private ReentrantReadWriteLock.ReadLock lab = Lab.l.readLock();
   //Write lock = maggiore priorità rispetto agli studenti
   private ReentrantReadWriteLock.WriteLock pc;
   //Il pc dedicato ai tesisti
   private int id = 5;


   public Tesista(){
      this.id = id;
      pc = Lab.pc.get(id).writeLock();
   }

   public void run(){
      long durata = (long)(Math.random() * 1000);
      int k = (int)(Math.random() * 5) + 1;

      //k utilizzi del laboratorio
      for(int i = 0; i < k; i++) {
         try{
            lab.lock();
            pc.lock();

            System.out.println("Tesista " + Thread.currentThread().getId() + " sta usando il pc");
            Thread.sleep(durata);
         }catch(InterruptedException e){}
         finally{
            pc.unlock();
            lab.unlock();
         }
      }
   }
}
