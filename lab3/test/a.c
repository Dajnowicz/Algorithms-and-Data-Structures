#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define MLD 1000000000.0

int C;
void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}
int partition(int arr[], int p, int r)
{
	int pivot = arr[r];    // pivot 
//	printf("pivot to %d \n", pivot);
	int i = (p - 1);  

	for (int j = p; j <= r - 1; j++)
	{ 
		if (arr[j] <= pivot)
		{
			i++;   
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[r]);
	if (i < r) {
		return i;
	}
	else {
		return (i + 1);
	}
}

void quickSort(int arr[], int p, int r)
{
	if (p < r)
	{
		int q = partition(arr, p, r);
		

		quickSort(arr, p, q); 
		quickSort(arr, q + 1, r);
	}
}
void Bubble(int *A, int p, int r);
void QuickSort_Bubble(int arr[], int p, int r) {
	if (p < r) {
		if (r - p + 1 < C) {
			Bubble(arr, p, r);
		}
		else {
			int q = partition(arr, p, r);
			QuickSort_Bubble(arr, p, q);
			QuickSort_Bubble(arr, q + 1, r);
		}
	}
}
void Bubble(int arr[], int p, int r) {
	int i, j;
	for (i = p; i <= r; i++) {
		for (j = p; j <= r; j++) {
			if (arr[j] > arr[j + 1]) {
				swap(&arr[j], &arr[j+1]);
			}
		}
	}

}

void printArray(int arr[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("%d ", arr[i]);
}



int main()
{
	struct timespec tp0, tp1;
	struct timespec tp2, tp3;
	struct timespec tp4, tp5;
	struct timespec tp6, tp7;

	struct timespec tp8, tp9;
	struct timespec tp10, tp11;
	struct timespec tp12, tp13;
	struct timespec tp14, tp15;

	struct timespec tp16, tp17;
	double czas1, czas2, czas3, czas4,czas5, czas6, czas7, czas8,czas9;
	double f_1, f_2;


	srand(time(NULL));
	int arr0[10];
	int arr01[10];	

	int arr[100];
	int arr2[500];
	int arr3[1000];
	int arr4[2500];

	int arr5[100];
	int arr6[500];
	int arr7[1000];
	int arr8[2500];



	int c = 0;
	for (int c = 0; c <= 99; c++) {
		arr[c] = (rand() % 99 + 1);
	}
	for (int c = 0; c <= 499; c++) {
		arr2[c] = (rand() % 499 + 1);
	}
	for (int c = 0; c <= 999; c++) {
		arr3[c] = (rand() % 999 + 1);
	}
	for (int c = 0; c <= 2499; c++) {
		arr4[c] = (rand() % 2499 + 1);
	}

	for (int c = 99; c >= 0; c--) {
		arr5[c] = c;
	}
	for (int c = 499; c>= 0; c--) {
		arr6[c] = c;
	}
	for (int c = 999; c >= 0; c--) {
		arr7[c] = c;
	}
	for (int c = 2499; c >= 0; c--) {
		arr8[c] = c;
	}

	for (c = 0; c <= 9; c++) {
		arr0[c] = (rand() % 52 + 1);
	}

	for (c = 0; c <= 9; c++) {
		arr01[c] = (rand() % 52 + 1);
	}
	
	int n01 = sizeof(arr01) / sizeof(arr01[0]);
	int n0 = sizeof(arr0) / sizeof(arr0[0]);
	int n = sizeof(arr) / sizeof(arr[0]);
	int n2 = sizeof(arr2) / sizeof(arr2[0]);
	int n3 = sizeof(arr3) / sizeof(arr3[0]);
	int n4 = sizeof(arr4) / sizeof(arr4[0]);
	int n5 = sizeof(arr5) / sizeof(arr5[0]);
	int n6 = sizeof(arr6) / sizeof(arr6[0]);
	int n7 = sizeof(arr7) / sizeof(arr7[0]);
	int n8 = sizeof(arr8) / sizeof(arr8[0]);

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp0);
	quickSort(arr, 0, n-1);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp1);
	czas1 = (tp1.tv_sec + tp1.tv_nsec / MLD) - (tp0.tv_sec + tp0.tv_nsec / MLD);
	
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp2);
	quickSort(arr2, 0, n2 - 1);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp3);
	czas2 = (tp3.tv_sec + tp3.tv_nsec / MLD) - (tp2.tv_sec + tp2.tv_nsec / MLD);
	
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp4);
	quickSort(arr3, 0, n3- 1);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp5);
	czas3 = (tp5.tv_sec + tp5.tv_nsec / MLD) - (tp4.tv_sec + tp4.tv_nsec / MLD);

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp6);
	quickSort(arr4, 0, n4 - 1);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp7);
	czas4 = (tp7.tv_sec + tp7.tv_nsec / MLD) - (tp6.tv_sec + tp6.tv_nsec / MLD);

	//BUBBLE NA RANDOM//

	C =log(n);

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp8);
	QuickSort_Bubble(arr, 0, n - 2);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp9);
	czas5 = (tp9.tv_sec + tp9.tv_nsec / MLD) - (tp8.tv_sec + tp8.tv_nsec / MLD);

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp10);
	QuickSort_Bubble(arr2, 0, n2 - 2);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp11);
	czas6 = (tp11.tv_sec + tp11.tv_nsec / MLD) - (tp10.tv_sec + tp10.tv_nsec / MLD);

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp12);
	QuickSort_Bubble(arr3, 0, n3 - 2);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp13);
	czas7 = (tp13.tv_sec + tp13.tv_nsec / MLD) - (tp12.tv_sec + tp12.tv_nsec / MLD);

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp14);
	QuickSort_Bubble(arr4, 0, n4 - 2);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp15);
	czas8 = (tp15.tv_sec + tp15.tv_nsec / MLD) - (tp14.tv_sec + tp14.tv_nsec / MLD);
	

	////////////////////////////////////////////////////////////
	//////////////////////TABELA//////////////////////////
	////////////////////////////////////////////////////////////



	

	printf("DANE LOSOWE \n");
	printf("Rozmiar tablicy N     |   QuickSort         |  QuickSort+Bubble \n");
	printf("    100               |       %lf      |		%lf			\n", czas1, czas5);
	printf("    500               |       %lf      |		%lf		    \n", czas2,czas6);
	printf("    1000              |       %lf      |		%lf		    \n", czas3,czas7);
	printf("    2500              |       %lf      |		%lf		    \n", czas4, czas8);

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp16);
	quickSort(arr5, 0, n5 - 1);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp17);
	czas9 = (tp17.tv_sec + tp17.tv_nsec / MLD) - (tp16.tv_sec + tp16.tv_nsec / MLD);

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp2);
	quickSort(arr6, 0, n6 - 1);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp3);
	czas2 = (tp3.tv_sec + tp3.tv_nsec / MLD) - (tp2.tv_sec + tp2.tv_nsec / MLD);

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp4);
	quickSort(arr7, 0, n7 - 1);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp5);
	czas3 = (tp5.tv_sec + tp5.tv_nsec / MLD) - (tp4.tv_sec + tp4.tv_nsec / MLD);

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp6);
	quickSort(arr8, 0, n8 - 1);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp7);
	czas4 = (tp7.tv_sec + tp7.tv_nsec / MLD) - (tp6.tv_sec + tp6.tv_nsec / MLD);

	//BUBBLE NA NIEKORZYSTNE//

//	C = log(n);

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp8);
	QuickSort_Bubble(arr5, 0, n5 - 2);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp9);
	czas5 = (tp9.tv_sec + tp9.tv_nsec / MLD) - (tp8.tv_sec + tp8.tv_nsec / MLD);

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp10);
	QuickSort_Bubble(arr6, 0, n6 - 2);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp11);
	czas6 = (tp11.tv_sec + tp11.tv_nsec / MLD) - (tp10.tv_sec + tp10.tv_nsec / MLD);

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp12);
	QuickSort_Bubble(arr7, 0, n7 - 2);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp13);
	czas7 = (tp13.tv_sec + tp13.tv_nsec / MLD) - (tp12.tv_sec + tp12.tv_nsec / MLD);

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp14);
	QuickSort_Bubble(arr8, 0, n8 - 2);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp15);
	czas8 = (tp15.tv_sec + tp15.tv_nsec / MLD) - (tp14.tv_sec + tp14.tv_nsec / MLD);



	printf("NIEKORZYSTNE \n");
	printf("Rozmiar tablicy N     |   QuickSort         |  QuickSort+Bubble \n");
	printf("    100               |       %lf      |		%lf			\n", czas9, czas5);
	printf("    500               |       %lf      |		%lf		    \n", czas2, czas6);
	printf("    1000              |       %lf      |		%lf		    \n", czas3, czas7);
	printf("    2500              |       %lf      |		%lf		    \n", czas4, czas8);

	printf("\n");
	printf("PRZYKALD Z QUICKSORTEM \n");
	printf("nie posortowany 1 array: ");
	for (c = 0; c <= 9; c++) {	
		printf("%d ", arr0[c]);
	}
	printf("\n");

	quickSort(arr0, 0, n0 - 1);
	printf("\n");
	printf("Posortowany array z pivotem na koncu: \n");
	printArray(arr0, n0);
	printf("\n");


	printf("\n");
	printf("PRZYKALD Z QS + BUB \n");
	printf("nie posortowany 1 array: ");
	for (c = 0; c <= 9; c++) {	
		printf("%d ", arr01[c]);
	}
	printf("\n");

	QuickSort_Bubble(arr01, 0, n01-2);
	printf("\n");
	printf("Posortowany array z pivotem na koncu: \n");
	printArray(arr01, n01);
	printf("\n");


	
}
