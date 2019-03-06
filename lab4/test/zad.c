#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h> 
#include<errno.h>
 
#define MDN 256 // maks. dlugosc napisu
#define MN 10 // maks il napisow
 
char **A;
 
void drukuj(char **A, int n) {
    // tablica napisów **A
    int i;

    for (i = 0; i<n; i++) {
//        A[i] = (int)tolower((int)A[i]);
        printf("%i. %s \n",i+1,A[i]);//kolejny znak
        //jeśli napiszesz A[i] to jest to samo co *(A+i)
        }
}

 
void czytaj(char **A, int ilosc) {
    FILE *f = fopen("plik2","r");
    int i;
    char slowo[MDN+1]; 
    //int i = 0;
    for (i = 0; i<ilosc; i++)  {    
        fscanf(f,"%s",slowo);
//        slowo[i] = tolower(slowo[i]);    
    //printf("%o", slowo[i]); 
        A[i] = (char*)calloc(MDN+1,1);
        strncpy(A[i], slowo, MDN);
   }

}

void zapisz(int ilosc){
    FILE *f = fopen("output", "w");
    int i = 0;
    for(i = 0; i <ilosc; i++){
        fprintf(f, "%s \n", A[i]);
    }

    fclose(f);
    printf("Zapisano pomyslnie!\n");
}

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
//}
void RSort(string *A, int dlugosc){
    int i;
    for(i = dlugosc; i >= 0; i--){
        CSort(A,dlugosc,i);
    }
}
 
int main() {
    
    int count = 0;
    char c;
   // A = (char**)calloc(n, sizeof(char*));
    FILE *fp = fopen("plik", "r");  
  
    // Extract characters from file and store in character c 
    for (c = getc(fp); c != EOF; c = getc(fp)) 
        if (c == '\n') // Increment count if this character is newline 
            count = count + 1; 
  
    // Close the file 
    fclose(fp);     
// 1. Open a file
    FILE *inputFile = fopen("plik", "rt");
    // 2. Open another file
    FILE *outputFile = fopen("plik2", "wt");

    // 3. Read the content of the input file
    int x;
    while (EOF != (x = fgetc(inputFile))) {
        // 4 & 5. Capitalize and write it to the output file
        fputc(tolower(x), outputFile);
    }

    // 6. Close all file handles
    fclose(inputFile);
    fclose(outputFile);

    A = (char**)calloc(count, sizeof(char*));
   
    czytaj(A, count);
    RSort(A,count);
    printf("tablica A: \n");
    drukuj(A, count);
    zapisz(count);
}
