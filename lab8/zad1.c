#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int c[1001][1001];
char b[1000][1000];
int flags[1000][1000];

int LCS_LEN(char* x, char* y, int m, int n)
{
    int i,j;
    for(i=0; i<m+1; i++)
        c[i][0] = 0;
    for(i=0; i<n+1; i++)
        c[0][i] = 0;
    for(i=1; i<m+1; i++)
    {
        for(j=1; j<n+1; j++)
        {
            if(x[i-1] == y[j-1])
            {
                c[i][j] = c[i-1][j-1] + 1;
                b[i-1][j-1] = '\\';
            }
            else if(c[i-1][j] == c[i][j-1])
            {
                c[i][j] = c[i][j-1];
                b[i-1][j-1] = '#'; // w gore i w dol
            }
            else if(c[i-1][j] > c[i][j-1]) // >=
            {
                c[i][j] = c[i-1][j];
                b[i-1][j-1] = '|';
            }
            else //if(c[i][j-1] >= c[i-1][j])
            {
                c[i][j] = c[i][j-1];
                b[i-1][j-1] = '-';
            }

        }
    }
    return c[m][n];
}

int exist_hash_left(int m, int n)
{
    int i=0;
    for(i=0; i<m; i++)
    {
        if(b[i][n] == '\\')
        {
            return 1;
        }
    }
    return 0;
}

int exist_hash_up(int m, int n)
{
    int i=0;
    for(i=0; i<n; i++)
    {
        if(b[m][i] == '\\')
        {
            return 1;
        }
    }
    return 0;
}

void LCS_PRINT_ALL(char* x, int i, int j)
{
    //worked for : aaabbbccc cccbbbaaa and abaaba bbabba
    if(i==-1 || j==-1)
        return;

    if(b[i][j] == '#' && flags[i][j] == 0)
    {
        flags[i][j] = 4;
        if(exist_hash_left(i, j) == 1)
        {
            LCS_PRINT_ALL(x,i,j-1);
        }
        if(exist_hash_up(i, j) == 1)
        {
            LCS_PRINT_ALL(x, i-1, j);
        }
    }

    if (b[i][j] == '\\' && flags[i][j] == 0)
    {
        flags[i][j] = 1;
        LCS_PRINT_ALL(x,i-1, j-1);
        printf("%c", x[i]);
    }
    else if (b[i][j] == '|' && flags[i][j] == 0)
    {
        flags[i][j] = 2;
        LCS_PRINT_ALL(x,i-1, j);
    }
    else if (b[i][j] == '-' && flags[i][j] == 0)
    {
        flags[i][j] = 3;
        LCS_PRINT_ALL(x,i, j-1);
    }
}

void LCS_PRINT(char* x, int i, int j)
{
    if(i==-1 || j==-1) //b size = m, c size = m+1
        return;
    if (b[i][j] == '\\')
    {
        LCS_PRINT(x,i-1, j-1);
        printf("%c", x[i]);
    }
    else if (b[i][j] == '|')
    {
        LCS_PRINT(x,i-1, j);
    }
    else
        LCS_PRINT(x,i, j-1);

}


int main(int argc, char *argv[])
{
    if(argc == 3)
    {
        int m = strlen(argv[1]);
        int n = strlen(argv[2]);
        if(m > 1000 || n > 1000)
        {
            printf("Za dlugie slowo (>1000)!\n");
            return -1;
        }
        int i, j;
        for(i=0;i<m;i++)
            for(j=0;j<n;j++)
                flags[i][j] = 0;
        int len = LCS_LEN(argv[1], argv[2], m, n);
        printf("LCS_LEN:\t%d\n", len);
        printf("LCS_PRINT:\t"); LCS_PRINT(argv[1], m-1, n-1); printf("\n");
        printf("LCS_PRINT_ALL:\t"); LCS_PRINT_ALL(argv[1], m-1, n-1); printf("\n");
        printf("\nSCIEZKA:\n");
        for(i=0; i<m; i++)
        {
            for(j=0;j<n;j++)
                printf("%c ", b[i][j]);
            printf("\n");
        }
        printf("\nFLAGS:\n");
        for(i=0; i<m; i++)
        {
            for(j=0;j<n;j++)
                printf("%d ", flags[i][j]);
            printf("\n");
        }
    }
    else
    {
		printf("Niepoprawne wywolanie programu!\n");
		printf("Wywolanie program wymaga dwoch argumentow!\n");
		printf("./a.out slowo1 slowo2!\n");
		return -1;
    }
    return 0;
}
