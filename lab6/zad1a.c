#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define WSIZE 20

//funkcja haszujaca 
void Hash(int arr[], int k, int size){
    int h;
    h = k % size;
    arr[h] = arr[h]+1;
}

int max_len(char **tab, int ilosc_linii)
{
    int i, max=0;
    for(i=0;i<ilosc_linii;i++)
    {
        if(strlen(tab[i])>max)
        {
            max=strlen(tab[i]);
        }
    }
    return max;
}

void same_len(char **tab, int ilosc_linii, int max)
{
    int i, j;
    for (i=0; i<ilosc_linii; i++)
        for (j=strlen(tab[i]); j<max; j++)
            tab[i][j]=' ';
}

//ile linijek plik
int lines_number(char *name)
{
	FILE *file = fopen(name, "r");
	if (file == NULL)
	{
		printf("\nNie mozna otworzyc pliku %s!\n", name);
		exit(0);
	}
	int counter=0;
	int ch;

	do
	{
		ch = fgetc(file);
		if(ch == '\n')
			counter++;
	} while (ch != EOF);

	if(ch != '\n' && counter != 0)
		counter++;

	fclose(file);
	return counter;
}
//odczyt pliku
void read_from_file(char **tab, char *name, int ilosc_linii)
{
    FILE *file;
    file = fopen(name, "r");
	if (file == NULL)
	{
		printf("\nNie mozna otworzyc pliku %s!\n", name);
		exit(0);
	}
    int i;
    for(i=0; i<ilosc_linii; i++)
    {
        char slowo[WSIZE];
        fscanf(file, "%s", slowo);
        tab[i] = (char*)malloc(WSIZE * sizeof(char));
        strcpy(tab[i],slowo);
    }
    fclose(file);
}

//zerowanie T
void array_reset(int arr[], int size)
{
    int i;
    for(i = 0; i<size; i++)
    {
        arr[i] = 0;
    }
}

void array_print(int arr[], int size)
{
    int i;
	for(i = 0; i<size; i++)
	{
            printf("%-4d. [%4d]\n", i, arr[i]);
	}
	printf("\n");
}

// schemat konwersji stringu na liczbe 
//opcja B
void stringarray_to_intarray(char **tab1, int tab2[], int ilosc_linii, int max)
{
    int i, j;
    int wynik;
    int x = 2; //stala
    for (i=0; i<ilosc_linii; i++)
    {
        wynik = 0;
        for (j=0; j<max; j++)
        {
            if(tab1[i][j] != ' ')
                wynik = wynik * x + (int)tab1[i][j];
        }
        tab2[i] = wynik;
    }
}

//ile zer w T
void array_zero(int arr[], int size)
{
    int i;
    int sum=0;
    for(i = 0; i<size; i++)
    {
        if(arr[i] == 0)
            sum++;
    }
    printf("MIEJSCA ZEROWE : \t\t%d\n", sum);

}
//srednia wartosc pozycji nie zerowych
void array_avg(int arr[], int size)
{
    int i;
    double avg;
    double ilosc=0, val=0;
    for(i = 0; i<size; i++)
    {
        if(arr[i] != 0 && arr[i] != -1)
        {
            ilosc++;
            val += arr[i];
        }
    }
    avg = val/ilosc;
    printf("SREDNIA WARTOSC : \t\t%.4f\n", avg);
}
//max wartosc kolizji
void array_max(int arr[], int size)
{
    int i;
    int wynik = 0;
    for (i=0; i<size; i++)
    {
        if (arr[i] > wynik)
            wynik = arr[i];
    }
    printf("MAX WARTOSC :\t\t\t%d\n", wynik);
}


int main()
{
    char *file_name = "3700.txt";
    int n;
    n = lines_number(file_name);
    char **S;
    S = (char**) malloc(n * sizeof(char*));
    int Sint[n]; //tablica z kodowaniem Stringow na liczby
    read_from_file(S,file_name, n);
    int max = max_len(S, n);
    same_len(S, n, max);
    stringarray_to_intarray(S, Sint, n, max);

    //parzyste korzystne
    int m[] = {1000,1019, 1100, 1103, 1500, 1511}; //size tablicy "m"
    int i=0;
    printf("==========================================\n");
    for(i=0; i<6; i++)
    {
        int T[m[i]];
        array_reset(T, m[i]);
        int j;
        for(j=0; j<2*m[i]; j++)
        {
            Hash(T, Sint[j], m[i]);
        }
        printf("TABLICA[%d] (%d in.)\n", m[i], 2*m[i]);
    //    array_print(T, m[i]);

        //ilosc zerowych pozycji w T
        array_zero(T, m[i]);
        // srednia wartosc pozycji niezerowych
        array_avg(T, m[i]);
        //max wartosc kolizji
        array_max(T, m[i]);
        printf("==========================================\n");
    }
    return 0;
}
