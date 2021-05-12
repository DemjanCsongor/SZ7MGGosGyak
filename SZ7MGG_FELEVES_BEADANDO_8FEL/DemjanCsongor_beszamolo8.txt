#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>

#define NUM_THREADS 10 //Szálak számának deklarálása

#define N 1000 //Tömb méretének deklarálása

int counter=0; //A szálak számlálója
int MaxTomb[10]; //A 10 szál maximumainak eltárolására szolgáló tömb

int main(){

int tomb[N];
int szum=0;
int i;
	//1000 random szám generáló ciklus
	srand(time(NULL));
	for (i=0; i<N; i++)
		tomb[i]=rand()%1000+1;
        szum+=i;
        printf("Legeneralt szamok:%d db\n\n", szum);

//Szálak létrehozása
  pthread_t threads[NUM_THREADS]; //Szálak deklarálása
  int thread_args[NUM_THREADS]; //Szálak argumentumainak megadása
  int result_code;
  unsigned index;
  int FI=0, SI=99; //Felosztást segítõ indexek, melyekkel egyesével létrehozza a szálakat

  for(index=0; index<NUM_THREADS; ++index){ //Ez a ciklus rendezi 10 tömbbe az 1000 számot
    thread_args[index]=index;
    printf("In main: created thread %d\n", index+1); //A main függvényben létrehozott szál számának kiírása
    result_code = pthread_create(&threads[index], NULL, maxSearch(FI,SI,tomb), &thread_args[index]); //A szál létrehozása, és a amximumkeresõ függvény hívása
    assert(!result_code); //Hibakód írása stderr
    FI+=100;
    SI+=100;
    // FirstIndex és SecondIndex növelése 100-zal a folytonosságot biztosítja
    counter++;
  }

    int u=0;
    for(;u<10;u++){ //A 10 szál maximumait eltároló tömb kiírása
        printf("%d. max:%d\n",u+1,MaxTomb[u]);
    }

    printf("\n");
    printf("A legnagyobb elem a generalt tombben:\n");
    maxSearch(0,10,MaxTomb); //Maximumokat eltároló tömb maximumának vizsgálata
}

void maxSearch(int FirstIndex, int SecondIndex, int array[]){ //Maximumkiválasztó eljárás

int maximum=0, c;
    printf("First index:%d\nSecond index:%d\n",FirstIndex, SecondIndex);

  for (c = FirstIndex; c < SecondIndex; c++){ //Maximum kiválasztására szolgáló ciklus
    if (array[c] > maximum){
       maximum  = array[c];
    }
  }
  MaxTomb[counter]=maximum;
  printf("MAX MAXSEARCH:%d\n\n", maximum);
}
