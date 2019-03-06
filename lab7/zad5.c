#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct Tree{
  char znak;
  int ilosc;
  struct Tree *right;
  struct Tree *left;
}TreeNode;

void DRUKUJ(TreeNode *n);
void WSTAW(TreeNode **n, char word);
TreeNode* SZUKAJ(TreeNode *n, char word);
TreeNode* MINIMUM(TreeNode *n);
TreeNode *USUN(TreeNode *n, char word);
TreeNode *USUNtotalnie(TreeNode *n, char word);

void DRUKUJ(TreeNode *n) //in-order - ciąg wartości niemalejących.
{
    if(n==NULL)
        return;
    DRUKUJ(n->left);
    printf("['%c' (%d)]\n", n->znak, n->ilosc);
    DRUKUJ(n->right);
}

void WSTAW(TreeNode **n, char word)
{
    if(word < 97 || word > 122)
    {
        printf("[ %c ] nie jest mala litera!\n", word);
        return;
    }
    TreeNode *tmp = NULL;
    if(*n == NULL)
    {
        tmp = (TreeNode *)malloc(sizeof(TreeNode));
        tmp->left = NULL;
        tmp->right = NULL;
        tmp->znak = word;
        tmp->ilosc = 1;
        *n = tmp;
        return;
    }

    if(word < (*n)->znak)
    {
        WSTAW(&(*n)->left, word);
    }
    else if(word > (*n)->znak)
    {
        WSTAW(&(*n)->right, word);
    }
    else
        (*n)->ilosc++;
}

TreeNode* SZUKAJ(TreeNode *n, char word)
{
    if(n!=NULL)
    {
        if(word == n->znak)
        {
            printf("Znalazlem [ %c ] w drzewie! Ilosc : (%d) \n", word, n->ilosc);
            return n;
        }
        else if(word > n->znak)
            SZUKAJ(n->right, word);
        else if(word < n->znak)
            SZUKAJ(n->left, word);
    }
    else
    {
        printf("Nie znalazlem [ %c ] w drzewie!\n", word);
        return NULL;
    }

}

TreeNode* MINIMUM(TreeNode *n)
{
	TreeNode* tmp = n;
	while (tmp->left != NULL)
		tmp = tmp->left;
	return tmp;
}


TreeNode *USUN(TreeNode *n, char word)
{
    if (n == NULL)
        return n;

	if (word < n->znak)
		n->left = USUN(n->left, word);
	else if (word > n->znak)
		n->right = USUN(n->right, word);
	else
    {
        if (n->ilosc > 1)
        {
            n->ilosc--;
            return n;
        }
        else if (n->ilosc == 1)
        {
            if (n->left == NULL)
            {
                TreeNode *tmp = n->right;
                free(n);
                return tmp;
            }
            else if (n->right == NULL)
            {
                TreeNode *tmp = n->left;
                free(n);
                return tmp;
            }
            TreeNode *tmp = MINIMUM(n->right);
            n->znak = tmp->znak;
            n->ilosc = tmp->ilosc;
            n->right = USUNtotalnie(n->right, tmp->znak);
        }
    }
	return n;
}

TreeNode *USUNtotalnie(TreeNode *n, char word) //usuwamy nie zwazajac na ilosc wystapien
{
    if (n == NULL)
    return n;

	if (word < n->znak)
		n->left = USUNtotalnie(n->left, word);
	else if (word > n->znak)
        n->right = USUNtotalnie(n->right, word);
    else
    {
        if (n->left == NULL)
        {
            TreeNode *tmp = n->right;
            free(n);
            return tmp;
        }
        else if (n->right == NULL)
        {
            TreeNode *tmp = n->left;
            free(n);
            return tmp;
        }
        TreeNode *tmp = MINIMUM(n->right);
        n->znak = tmp->znak;
        n->right = USUNtotalnie(n->right, tmp->znak);
    }
    return n;
}


int main()
{
    TreeNode *L = NULL;
    WSTAW(&L, '`');// -> nie dodamy tego, gdyz program obsluguje jedynie male litery (UTF-8)
    WSTAW(&L, 'g');
    WSTAW(&L, 'd');
    WSTAW(&L, 'j');
    WSTAW(&L, 'h');
    WSTAW(&L, 'k');
    WSTAW(&L, 'a');
    WSTAW(&L, 'e');
    WSTAW(&L, 'b');
    printf("\n===po wstawieniu (tylko jeden w ilosci)===\n");
    DRUKUJ(L);
    //zwiekszamy ilosc w lisciu jesli wstawiamy ten sam znak
    WSTAW(&L, 'j');
    WSTAW(&L, 'j');
    WSTAW(&L, 'h');
    WSTAW(&L, 'e');
    WSTAW(&L, 'e');
    WSTAW(&L, 'e');
    WSTAW(&L, 'b');
    WSTAW(&L, 'b');
    WSTAW(&L, 'b');
    printf("===po wstawieniu===\n");
    DRUKUJ(L);
    printf("\n====(usuwamy h)===\n");
    USUN(L, 'h'); // <- usuniecie liscia bez synow
    DRUKUJ(L);
    printf("\n===(usuwamy a)====\n");
    USUN(L, 'a'); // <-usuniecie liscia z jednym synem
    DRUKUJ(L);
    printf("\n===(usuwamy g)===\n");
    USUN(L, 'g'); // <- usuniecie czubka (zatem ma dwoch synow)
    DRUKUJ(L);

    
    printf("|====TEST SZUKANIA====|\n");
    TreeNode *T = NULL;
    T = SZUKAJ(L, 'b');
    
    DRUKUJ(T);
    printf("|=====================|\n");
    
}
