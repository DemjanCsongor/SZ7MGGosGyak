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

#define NUM_THREADS 10 //Sz�lak sz�m�nak deklar�l�sa

#define N 1000 //T�mb m�ret�nek deklar�l�sa

int counter=0; //A sz�lak sz�ml�l�ja
int MaxTomb[10]; //A 10 sz�l maximumainak elt�rol�s�ra szolg�l� t�mb

int main(){

int tomb[N];
int szum=0;
int i;
	//1000 random sz�m gener�l� ciklus
	srand(time(NULL));
	for (i=0; i<N; i++)
		tomb[i]=rand()%1000+1;
        szum+=i;
        printf("Legeneralt szamok:%d db\n\n", szum);

//Sz�lak l�trehoz�sa
  pthread_t threads[NUM_THREADS]; //Sz�lak deklar�l�sa
  int thread_args[NUM_THREADS]; //Sz�lak argumentumainak megad�sa
  int result_code;
  unsigned index;
  int FI=0, SI=99; //Feloszt�st seg�t� indexek, melyekkel egyes�vel l�trehozza a sz�lakat

  for(index=0; index<NUM_THREADS; ++index){ //Ez a ciklus rendezi 10 t�mbbe az 1000 sz�mot
    thread_args[index]=index;
    printf("In main: created thread %d\n", index+1); //A main f�ggv�nyben l�trehozott sz�l sz�m�nak ki�r�sa
    result_code = pthread_create(&threads[index], NULL, maxSearch(FI,SI,tomb), &thread_args[index]); //A sz�l l�trehoz�sa, �s a amximumkeres� f�ggv�ny h�v�sa
    assert(!result_code); //Hibak�d �r�sa stderr
    FI+=100;
    SI+=100;
    // FirstIndex �s SecondIndex n�vel�se 100-zal a folytonoss�got biztos�tja
    counter++;
  }

    int u=0;
    for(;u<10;u++){ //A 10 sz�l maximumait elt�rol� t�mb ki�r�sa
        printf("%d. max:%d\n",u+1,MaxTomb[u]);
    }

    printf("\n");
    printf("A legnagyobb elem a generalt tombben:\n");
    maxSearch(0,10,MaxTomb); //Maximumokat elt�rol� t�mb maximum�nak vizsg�lata
}

void maxSearch(int FirstIndex, int SecondIndex, int array[]){ //Maximumkiv�laszt� elj�r�s

int maximum=0, c;
    printf("First index:%d\nSecond index:%d\n",FirstIndex, SecondIndex);

  for (c = FirstIndex; c < SecondIndex; c++){ //Maximum kiv�laszt�s�ra szolg�l� ciklus
    if (array[c] > maximum){
       maximum  = array[c];
    }
  }
  MaxTomb[counter]=maximum;
  printf("MAX MAXSEARCH:%d\n\n", maximum);
}
