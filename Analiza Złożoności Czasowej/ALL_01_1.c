// kompilowaæ z opcjami -lrt -lm, tj. np. gcc ALL_01.c -lrt -lm
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define MAX 60000l
#define MLD 1000000000.0
/////////////////////////////////////////////
//   PROCEDURA 1                           //
/////////////////////////////////////////////
double procedura1(long int n){
 float x=0;
 long int i,j,k;

 for(i=n-1;i>=1;i--){
  if((i % 2) == 1){;
   for(j=1;j<i+1;j++) ;
   for(k=i+1;k<n+1;k++) x=x+1;
  }
 }
 return x;
}
/////////////////////////////////////////////
//   PROCEDURA 2                           //
/////////////////////////////////////////////
int procedura2(long int n){
int *A;
long int d,g,i,x,suma; 

 A=(int *) malloc(n*sizeof(int)); 
 for(i=0;i<n;i++)
   A[i]=(rand()% 21)-10;
 
 x=0;
 for(d=1;d<n+1;d++)
 for(g=d;g<n+1;g++){
   suma=0;
   for(i=d;i<g+1;i++)
    suma=suma+A[i];
   if (suma>x) x=suma;
 }
 
free(A);
return x; 
}
/////////////////////////////////////////////
//   PROCEDURA 3                           //
/////////////////////////////////////////////
void procedura3(long int n){
 long int i,j,k;

 for(i=1;i<(int)sqrt(n)+1;i++){
  j=1;
  while (j<sqrt(n)) j+=j;
 }
}
/////////////////////////////////////////////
//   POMIAR CZASU DLA WIELU PRÓB           //
/////////////////////////////////////////////
int main(){
  struct timespec tp0, tp1;
  double Tn,Fn,x;
  long int n; // liczba testów
  
for(n=100000;n<300000;n=n+500000){

clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);

// przyk³adowe obliczenia
// x=procedura1(n);
// x=procedura2(n);
 procedura3(n);

clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);

// zgadywana funkcja czasu
     Fn=n;
//     Fn=20000*n;
  //   Fn=n*log(n);
//   Fn=n*n;
//    Fn=n*n/1000+100n;
//     Fn=n*n*n;
//     Fn=n*n*n*sqrt(n);

  Tn=(tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);
  printf("   n: %5ld    czas: %3.5lf    wspolczynnik: %3.3lf\n",n,Tn, Fn/Tn);
}
return 1;
