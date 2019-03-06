#include <stdio.h>
#include <stdlib.h>
//i to index w arr
//n size drzewa
void kopbin(int arr[], int n,int i)
{

int tmp;
int naj = i; // najwiekszy jako korzen
int l = 2*i +1; // lewy
int p = 2*i +2; // prawy

//jesli lewy wiekszy niz korzen
if (l < n && arr[l] > arr[naj])
naj = l;

//jesli prawy wiekszy niz najwiekszy ostatni
if (p < n && arr[p] > arr[naj])
naj = p;

//jesli korzen nie jest naiwkeszy
if (naj !=i)
{
tmp = arr[i];
arr[i] = arr[naj];
arr[naj]= tmp;

//rekursywanie kopcowanie drzewai
kopbin(arr, n, naj);
}
}


void kopiec(int arr[], int n)
{
int tmp;
// budowanie kopca binarnego
for (int i = n/2-1; i>=0; i--)
kopbin(arr,n,i);
//po kolei sciagac ze sterty
for (int i=n-1; i>=0; i--)
{
//korzen na koniec
tmp = arr[0];
arr[0] = arr[i];
arr[i]= tmp;
// ponowne tworzenie drzewa
kopbin(arr, i, 0);
}
}

void pokazciag(int arr[], int n)
{
FILE *f = fopen("wynik.txt","w");
for (int i=0; i<n; ++i)
{
fprintf(f, "%d\n", arr[i]);
}
fclose(f);
for (int i=0; i<n; ++i)
printf("%d ", arr[i]);
}

int main ()
{
FILE *file;
file = fopen("liczby.txt", "r");

int tempInt;
int *arr = NULL;
size_t n = 0;

//funkcja do relokowania odpowiedniej ilosci pamieci 
while (fscanf(file, "%d", &tempInt) == 1)
{
int *tempArray = realloc(arr, (n + 1) * sizeof(int));
if (tempArray != NULL)
{
arr = tempArray;
arr[n++] = tempInt;
}
}

fclose(file);

kopiec(arr,n);

printf("Posortowany ciag: ");
pokazciag(arr,n);
}

