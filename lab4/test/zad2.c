#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h> 
#include<errno.h>
#include <math.h>
#include <time.h>

#define MLD 1000000000.0 
#define MDN 256000 // maks. dlugosc napisu
#define MN 200001 // maks il napisow
 
char **A;
char **B;
 
//WYDRUKUJ -> NIESTOSOWANE
void drukuj(char **A, int n) {
    int i;
    for (i = 0; i<n; i++) {
//        printf("%i. %s \n",i+1,A[i]);
        }
}

//WCZYTAJ A
void czytaj(char **A, int ilosc) {
    FILE *f = fopen("nazwiskaASCII2","r");
    int i;
    char slowo[MDN+1]; 
    //int i = 0;
    for (i = 0; i<ilosc; i++)  {    
        fscanf(f,"%s",slowo);
        A[i] = (char*)calloc(MDN+1,1);
        strncpy(A[i], slowo, MDN);
   }

}
//WCZYTAJ B
void czytajB(char **B, int ilosc) {
    FILE *f = fopen("nazwiskaASCII2", "r");
    char slowo[MDN+1];
    int i = 0;
    for (i = 0; i<ilosc; i++) {
        fscanf(f, "%s", slowo);
        B[i] = (char*)calloc(MDN+1,1);
        strncpy(B[i], slowo, MDN);
    }
}

//ZAPISZ A
void zapisz(int ilosc){
    FILE *f = fopen("output2", "w");
    int i = 0;
    for(i = 0; i <ilosc; i++){
        fprintf(f, "%s \n", A[i]);
    }

    fclose(f);
    printf("Zapisano wynik z algorytmu RadixSort do pliku output2!\n");
}

//ZAPISZ B
void zapiszB(int ilosc){
    FILE *f = fopen("output2B", "w");
    int i;
    for(i = 0; i < ilosc; i++){
        fprintf(f, "%s \n", B[i]);
    }
    fclose(f);
    printf("Zapisano wynik z algorytmu QuickSort do pliku output2B!\n");
}



//RADIX SORT + COUNTING SORT
typedef char*string;
void CSort(string *A, int dlugosc,int i) {
 
   
    // A - tablica do sortowania
    // B - wynik sortowania
    // k - zakres warości w tablicy A
    // C - pomocnicza tablica "liczników"
   // for (int i = MDN - 1; i >= 0; i--) {//kolumny gdzie i to nr kolumny
       
        int k=256;
        int C[k];
        string B[dlugosc];
 
        for (int j = 0; j < k; j++) {
            C[j] = 0;
        }
        for (int j = 0; j < dlugosc; j++) {
            C[A[j][i]] = C[A[j][i]] + 1;
        }
        // teraz C[i] == ilość wartości równych "i" w tablicy A
        for (int j = 1; j < k; j++) {
            C[j] = C[j] + C[j - 1];
        }
        // teraz C[i] == ilość wartości mniejszych lub równych "i" w A
        for (int j = dlugosc-1; j >= 0; j--) {
            B[C[A[j][i]]-1] = A[j];
            C[A[j][i]] = C[A[j][i]] - 1;
        }
        for (int j = 0; j < dlugosc; j++) {
            A[j] = B[j];
        }
    }

void RSort(string *A, int dlugosc){
    int i;
    for(i = dlugosc; i >= 0; i--){
        CSort(A,dlugosc,i);
    }
}

//QUICKSORT
int Partition(char** B, int p, int r){
    char *temp;
    char *x = B[r];
    int i = p - 1;
    int j = 0;
    for(j = p; j<=r; j++){
        if(strcmp(B[j],x) <=0){
            i=i+1;
            temp = B[i];
            B[i] = B[j];
            B[j] = temp;
            }
        }
    if(i<r){
         return i;
    }else{
        return i-1;
    }
}
void QuickSort(char** B, int p, int r){
    if(p<r){
        int q = Partition(B, p, r);
        QuickSort(B, p, q);
        QuickSort(B, q+1, r);
    }
}


int main() {
	
struct timespec tp0, tp1;
struct timespec tp2, tp3;
double czas1, czas2;



// Licz ile wyrazow
    int count = 0;
    char c;
    FILE *fp = fopen("nazwiskaASCII", "r");  
  	for (c = getc(fp); c != EOF; c = getc(fp)) 
        if (c == '\n') 
            count = count +1;
    fclose(fp);     

// Maale znaki + brak polskihc
    FILE *inputFile = fopen("nazwiskaASCII", "rt");
    FILE *outputFile = fopen("nazwiskaASCII2", "wt");
    int x;
    while (EOF != (x = fgetc(inputFile))) {
        if (isalpha(x) || x=='\n'){
        fputc(tolower(x), outputFile);
	}
    }

      	fclose(inputFile);
	fclose(outputFile);


	//tworzenie A i B
	A = (char**)calloc(count, sizeof(char*));
	B = (char**)calloc(count, sizeof(char*));

//Tworzenie A
	czytaj(A, count);
    
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp0);
	RSort(A,count);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp1);
	czas1 = (tp1.tv_sec + tp1.tv_nsec / MLD) - (tp0.tv_sec + tp0.tv_nsec / MLD);

   	zapisz(count);

//Tworzenie B
	czytaj(B,count);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp2);
	QuickSort(B,0,count-1);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp3);
	czas2 = (tp3.tv_sec + tp3.tv_nsec / MLD) - (tp2.tv_sec + tp2.tv_nsec / MLD);
	
	zapiszB(count);
       // drukuj(B,count);
	
	printf("POMIAR CZASU \n");
	printf(" Radix Sort       |  QuickSort \n");
	printf(" %lf       |     %lf			\n", czas1, czas2);
	//printf("%lf ", czas2);
}

