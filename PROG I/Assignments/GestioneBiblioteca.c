#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define OPZ 5   /*N. opzioni menu*/
#define MAX 100 /*Lunghezza massima stringa*/

/*Struttura libri*/
struct nodo{
   int isbn;
   int inPrestito;
   int totali;
   char autore[MAX];
   char titolo[MAX];
   struct nodo *sx;
   struct nodo *dx;
};

void sMenu();
void inserisci(struct nodo **root, int isbn, char *tit, char *aut);
/*Funzioni per il menu*/
void stampa(struct nodo *root);
void cerca(struct nodo *root);
void cercalibro(struct nodo *root, char *titolo, char *autore);
void prestito(struct nodo *root);
void restituzione(struct nodo *root);
void esci(struct nodo *root);

int restituzioneLibro(struct nodo *root, int isbn);
int prestitoLibro(struct nodo *root, int isbn);

int main(){
   struct nodo *root = NULL;
   int cisbn, scelta;
   char tit[MAX], aut[MAX];
   /*Menu*/
   void(*menu[OPZ])(struct nodo*) = {
      stampa, cerca, prestito,
      restituzione, esci};
   /*lettura libro*/
   scanf("%d,%[^,],%[^\n]", &cisbn, tit, aut);

   while(cisbn != 0){
      /*All'inserimento dell'ISBN '0',
        ferma la lettura*/
      inserisci(&(root), cisbn, tit, aut);
      scanf("%d,%[^,],%[^\n]", &cisbn, tit, aut);
   }

   do{
      sMenu();
      while(scanf("%d", &scelta) != 1 || scelta < 1 || scelta > 5){
         printf("Errore. Scelta non valida.\n");
         scanf("%*[^\n]");
         scanf("%*c");
      }
      (*menu[scelta-1])(root);
   }while(scelta != 5);

   return 0;
}
/*Inserimento libri in un albero*/
void inserisci(struct nodo **root, int isbn, char *tit, char *aut){
   if(*root == NULL){
   *root = malloc(sizeof(struct nodo));
     if(*root != NULL){
         (*root)->isbn = isbn;
         strcpy((*root)->titolo, tit);
         strcpy((*root)->autore, aut);
         (*root)->totali = 1;
         (*root)->inPrestito = 0;
         (*root)->sx = NULL;
         (*root)->dx = NULL;
      }
   }
   else{
      /*Inserimento ordinato*/
      if((strcmp(aut, (*root)->autore)) < 0){
         inserisci(&((*root)->sx), isbn, tit, aut);
      }
      else if((strcmp(aut, (*root)->autore)) > 0){
         inserisci(&((*root)->dx), isbn, tit, aut);
      }
      else if((strcmp(aut, (*root)->autore)) == 0){
         /*In caso di duplicati*/
         if((strcmp(tit, (*root)->titolo)) < 0){
            inserisci(&((*root)->sx), isbn, tit, aut);
         }
         else if((strcmp(tit, (*root)->titolo)) > 0){
            inserisci(&((*root)->dx), isbn, tit, aut);
         }
         else if((strcmp(tit, (*root)->titolo)) == 0){
            (*root)->totali++;
         }
      }
   }
}

void sMenu(){
   printf("Scegli un opzione:\n1) Stampa catalogo.\n");
   printf("2) Cerca.\n3) Prestito.\n4) Restituzione.\n");
   printf("5) Esci.\nScelta:  ");
}

void stampa(struct nodo *root){
   if(root != NULL){
      stampa(root->sx);
      printf("%d - %s - %s (%d/%d)\n",
      root->isbn, root->autore, root->titolo,
      (root->totali - root->inPrestito),
      root->totali);
      stampa(root->dx);
   }
}

/*Funzioni per cercare un libro
  con confronto di autore e titolo*/
void cerca(struct nodo *root){
   char autore[MAX], titolo[MAX];

   printf("Inserire nome autore: ");
   fgets(autore, MAX, stdin);
   fgets(autore, MAX, stdin);
   autore[strlen(autore) - 1] = '\0';

   printf("Inserire titolo: ");
   fgets(titolo, MAX, stdin);
   titolo[strlen(titolo) - 1] = '\0';

   cercalibro(root, titolo, autore);
}

void cercalibro(struct nodo *root, char *titolo, char *autore){
   if(root == NULL){
      printf("Libro non trovato.\n");
   }
   else{
      int autCmp = strcmp(autore, root->autore);
      int titCmp = strcmp(titolo, root->titolo);

      if(autCmp == 0 && titCmp == 0){
         if(root->inPrestito < root->totali){
            printf("%d copie disponibili.\n",
            (root->totali - root->inPrestito));
         }
         else{
            printf("Non ci sono copie disponibili del libro richiesto.\n");
         }
      }
      else{
         /*Ricerca ricorsiva in albero*/
         if(autCmp < 0 || (autCmp == 0 && titCmp < 0)) {
            cercalibro(root->sx, titolo, autore);
         }
         else{
            cercalibro(root->dx, titolo, autore);
         }
      }
   }
}
/*Prestito libro tramite ISBN*/
void prestito(struct nodo *root){
   int isbn;

   printf("ISBN: ");
   scanf("%d", &isbn);	

   int ris = prestitoLibro(root, isbn);
   if(ris == -1){
      printf("Libro non trovato.\n");
   }
   else{
      if(ris == 0){
         printf("Non ci sono copie disponibili del libro richiesto.\n");
      }
      else{
         printf("Operazione completata.\n");
      }
   }
}

int prestitoLibro(struct nodo *root, int isbn){
   if(root != NULL){
      if(root->isbn == isbn){
         /*Non ci sono copie*/
         if((root->totali - root->inPrestito) == 0){
            return 0;
         }
         else{
            root->inPrestito++;
            return 1;
         }
      }
      else{
         int ris = prestitoLibro(root->sx, isbn);
         if(ris != -1){
            return ris;
         }
         else{
            return prestitoLibro(root->dx, isbn);
         }
      }
   }
   /*Non ci sono copie*/
   return -1;
}

/*Restituzione libro tramite ISBN*/
void restituzione(struct nodo *root){
   int isbn;

   printf("ISBN: ");
   scanf("%d", &isbn);

   int ris = restituzioneLibro(root, isbn);

   if(ris == -1){
      printf("Libro non trovato.\n");
   }
   else{
      if(ris == 0){
         printf("Non risultano copie in prestito.\n");
      }
      else{
         printf("Operazione completata.\n");
      }
   }
}

int restituzioneLibro(struct nodo *root, int isbn){
   int ris;
   if(root != NULL){
      if(root->isbn == isbn){
         if(root->inPrestito == 0){
            return 0;
         }
         else{
            root->inPrestito--;
            return 1;
         }
      }
      else{
         ris = restituzioneLibro(root->sx, isbn);
         if(ris != -1){
            return ris;
         }
         else{
            return restituzioneLibro(root->dx, isbn);
         }
      }
   }
   return -1;
}

void esci(struct nodo *root){
   printf("Bye\n");
}
