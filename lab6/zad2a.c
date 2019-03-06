#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define WSIZE 30


typedef struct Dane{
    int liczba;
    char *nazwisko;
}dane;

int H(int k, int i, int size)
{
    int wynik;
    k = k%size;
    wynik = (k+i*i)%size;
    return wynik;
}

int string_to_int(char *slowo)
{
    int i;
    int wynik = 0;
    int x = 1;
    for(i=0; i<strlen(slowo); i++)
    {
        if((int)slowo[i] != 32)
            wynik = wynik * x + (int)slowo[i];
    }
    return wynik;
}

int HashInsert(dane T[], char* name, int size,int *error)
{
    int i, j;
    int x = 0;
    int count = 0;
    x = string_to_int(name);
    i = 0;
    do
    {
        j=H(x,i, size);
        if (T[j].liczba == 0 )
        {
            T[j].nazwisko = name;
            T[j].liczba = x;
            return j;
        }
	
	*error=*error+1;

	i=i+1;
     }
     while(i <size);
     return 0;
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

void stringarray_to_intarray(char **tab1, dane tab2[], int ilosc_linii, int max)
{
    int i, j;
    int wynik;
    int x = 1; //stala
    for (i=0; i<ilosc_linii; i++)
    {
        wynik = 0;
        for (j=0; j<max; j++)
        {
            if((int)tab1[i][j] != 32)
                wynik = wynik * x + (int)tab1[i][j];
        }
        tab2[i].liczba = wynik;
        tab2[i].nazwisko = tab1[i];
    }
}

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
        int tmp;
        char slowo[WSIZE];
        fscanf(file, "%d", &tmp);
        fscanf(file, "%s", slowo);
        tab[i] = (char*)malloc(WSIZE * sizeof(char));
        strcpy(tab[i],slowo);
    }
    fclose(file);
}

void array_reset(dane arr[], int size)
{
    int i;
    for(i = 0; i<size; i++)
    {
        arr[i].liczba = 0;
        arr[i].nazwisko = NULL;
    }
}

void array_print(dane T[], int size)
{
    int i;
    for(i=0; i<size; i++)
    {
        printf("%-4d. [%s](%d)\n",i, T[i].nazwisko, T[i].liczba);
    }
}

int wypelnienie(dane T[], int size)
{
    int i;
    int count = 0;
    for(i=0; i<size; i++)
    {
        if(T[i].liczba != 0)
        {
            count++;
        }
    }
    return count;
}

void array_print_S(char **t, int size)
{
    int i;
    for(i=0; i<size; i++)
    {
        printf("[%s]\n",t[i]);
    }
}

void array_reset_I(int t[], int size)
{
    int i;
    for(i=0; i<size; i++)
    {
        t[i] = 0;
    }
}

void array_avg(dane arr[], int size)
{
    int i;
    double avg;
    double ilosc=0, val=0;
    for(i = 0; i<size; i++)
    {
        if(arr[i].liczba != 0)
        {
            ilosc++;
            
        }
    }
    avg = ilosc/size;
    printf("SREDNIA WARTOSC : \t\t\t\t%.4f\n", avg);
}


int main()
{
    char *file_name = "nazwiskaASCII.txt";
    int n;
    n = lines_number(file_name);
    char **S;
    S = (char**) malloc(n * sizeof(char*));
    dane Sint[n]; //tablica z kodowaniem Stringow na liczby
    read_from_file(S,file_name, n);
    int max = max_len(S, n);
    same_len(S, n, max);
    stringarray_to_intarray(S, Sint, n, WSIZE);
    int error = 0;
/*
    array_print_S(S, 100);

    
    int size = 3;
    dane T[size];
    array_reset(T, size);
    HashInsert(T, "Dajnowicz", size);
    array_print(T,size);
    printf("\n");
      */  

    int m[] = {1000,1019,2000, 2003, 3000, 3023, 6000, 6007}; //4 pozytywne, 4 negatywne
    int i;
    printf("========================================================\n");
    for(i=0; i<8; i++)
    {
        printf("\nTABLICA O ROZMIARZE %d\n", m[i]);
        printf("DANE DLA 0.5 \n");
        dane T[m[i]];
        int *wsk = &error;
	float avgg;
        error=0;
        array_reset(T, m[i]);
        int kontrolka = 0.5 * m[i];
        int tmp[kontrolka]; //tablica indexow insertowanych danych do tab haszujacej
        array_reset_I(tmp, kontrolka);
        int j = 0;
        //Wypelnianie tablicy m[i] do 50%
        while(j < kontrolka)
        {
            tmp[j] = HashInsert(T, S[j], m[i],wsk);
            j++;
        }
        printf("Zajete miejsca (poczatek) : \t\t\t%d\n", wypelnienie(T, m[i]));

        //wypelnianie tablicy 5m/100
        for(j=0; j<(5*m[i]/100); j++)
        {
            HashInsert(T, S[j], m[i],wsk);
        }
        printf("Zajete miejsca (po 5m/100) : \t\t\t%d\n", wypelnienie(T, m[i]));

        array_avg(T, m[i]);
        printf("ile bylo kolizji : %d \n", error);
        avgg = error/(float)m[i];
        printf("sredni error w tej próbie: %f \n", avgg);
	error = 0;
      
        printf("DANE DLA 0.7 \n");
        array_reset(T, m[i]);
        kontrolka = 0.7 * m[i];
        tmp[kontrolka];
        array_reset_I(tmp, kontrolka);
        j = 0;
        //Wypelnianie tablicy m[i] do 70%
        while(j < kontrolka)
        {
            tmp[j] = HashInsert(T, S[j], m[i],wsk);
            j++;
        }
        printf("Zajete miejsca (poczatek) : \t\t\t%d\n", wypelnienie(T, m[i]));

        //wypelnianie tablicy 5m/100
        for(j=0; j<(5*m[i]/100); j++)
        {
            HashInsert(T, S[j], m[i],wsk);
        }
        printf("Zajete miejsca (po 5m/100) : \t\t\t%d\n", wypelnienie(T, m[i]));
	array_avg(T, m[i]);

        printf("ile bylo kolizji : %d \n", error);
        avgg = error/(float)m[i];
        printf("sredni error w tej próbie: %f \n", avgg);
        error= 0;

        printf("DANE DLA 0.9 \n");
        array_reset(T, m[i]);
        kontrolka = 0.9 * m[i];
        tmp[kontrolka];
        array_reset_I(tmp, kontrolka);
        j = 0;
        //Wypelnianie tablicy m[i] do 90%
        while(j < kontrolka)
        {
            tmp[j] = HashInsert(T, S[j], m[i],wsk);
            j++;
        }
        printf("Zajete miejsca (poczatek) : \t\t\t%d\n", wypelnienie(T, m[i]));

        //wypelnianie tablicy 5m/100
        for(j=0; j<(5*m[i]/100); j++)
        {
            HashInsert(T, S[j], m[i],wsk);
        }

        printf("Zajete miejsca (po 5m/100) : \t\t\t%d\n", wypelnienie(T, m[i]));


        array_avg(T, m[i]);
        printf("ile bylo kolizji : %d \n", error);
        avgg = error/(float)m[i];
        printf("sredni error w tej próbie: %f \n", avgg);
}
}
