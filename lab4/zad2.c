#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 10
#define ILE 5


char **As = NULL;
char **Bs = NULL;
char **T = NULL;
int lengthA;        //= strlen(As[0]);

size_t lenA[ILE];

int place[ILE];


void CSort(int p){

    int k = 123;
    int C[k];
    int i;

    for(i = 0; i < k; i++){
        C[i] = 0;
    }

    for(i = 0; i < ILE; i++){
        C[(int)As[i][p]]++;
    }

    for(i = 1; i <   k; i++){
        C[i] = C[i] + C[i - 1];
    }

    for(i = ILE - 1; i >= 0; i--){
        Bs[C[(int)As[i][p]] - 1] = As[i];
    //    printf("As[%i][%i] == %c ", i, p, As[i][p]);
  //      printf("C[%i] == %i ", (int)As[i][p], C[(int)As[i][p]]-1);
//        printf("  Bs[%i]  == %s \n", C[(int)As[i][p]] - 1, Bs[C[(int)As[i][p]] - 1]);

        //(As[i], Bs[C[(int)As[i][p]]], sizeof(As[i]));
        C[(int)As[i][p]]--;
    }


}

void RSort(int d){
    int i;
    for(i = d; i >= 0; i--){
        CSort(i);
        memcpy(As, Bs, sizeof(*As) * ILE);
        //memset(Bs, 0, ILE*MAX);
        puts("wykonane!");
    }
}

void wczytaj(){
    //	FILE *f = fopen("nazwiskaASCII", "r");
    FILE *f = fopen("plik", "r");
    int i;
    char tmp[MAX];
    int len;
    for(i = 0; i < ILE; i++){
        //	 fscanf(f, "%i", &place[i]);
        fscanf(f, "%s", tmp);
        len = strlen(tmp);
        As[i] = (char*)malloc(sizeof(char)*len);
        Bs[i] = (char*)malloc(sizeof(char)*len);
        strcpy(As[i], tmp);
        strcpy(Bs[i], tmp);
        lenA[i] = len;

    }
    printf("Wczytano prawidlowo!\n");
    fclose(f);
}
void wyswietl(char **a){
    int i;
    for(i = 0; i < ILE; i++){
        //int k = getK(i);
        printf("%i. %s  \n",i,  a[i]); //, lenA[i], k);
    }
    printf("\n");

}
void zapisz(){
    FILE *f = fopen("output", "w");
    int i;
    for(i = 0; i < ILE; i++){
    //	fprintf(f, "%i\t%s\n",place[i], As[i]);
        fprintf(f, "%s \n", Bs[i]);
    }

    fclose(f);
    printf("Zapisano pomyslnie!\n");
}


int main(void){
    //system("./slowo");
    //int i;
    //As = (char**)malloc(ILE*sizeof(char*));
    As = malloc(sizeof(*As) * ILE);
    Bs = malloc(sizeof(*As) * ILE);
    //Bs = (char**)malloc(ILE*sizeof(char*));
    T  = malloc(sizeof(*As) * ILE);
    //memcpy(T, As, sizeof(*As) * ILE);
    wczytaj();
    memcpy(T, As, sizeof(*As) * ILE);
    //memset(Bs, 0, ILE*10);
    //int k = getK(0);
    lengthA = strlen(As[0]);

    printf("\n");

    printf("org\n");
    wyswietl(As); // shows table AS
    wyswietl(Bs);
    //RSort(0);
  //  CSort(1);

    memcpy(As, Bs, sizeof(*As) * ILE);
    //wyswietl(T); // shows table AS
    wyswietl(As);
    wyswietl(Bs);
    RSort(6);
    wyswietl(Bs);
    //wyswietl(T);
    //wyswietl(Bs);



    zapisz();
    //	free(As);
    //	free(Bs);

    return 0;
}
