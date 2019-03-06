#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct List{
    char* WORD;
    struct List *next;
    struct List *prev;
}list;

list *L1 = NULL;
list *L2 = NULL;
list *L3 = NULL; //wynikowa scalania

void WSTAW(list **L, char* word)
{
    list *new_node=(list *)malloc(sizeof(list));
    new_node->WORD = word;
    new_node->next = *L;
    new_node->prev = NULL;
    *L = new_node;
}

void DRUKUJ(list *node)
{
    while(node!=NULL)
    {
        printf("%s \n", node->WORD) ;
        node=node->next;
    }
    printf("\n");
}

list* SZUKAJ(list* node, char* word)
{
    while(node!=NULL)
    {
        if(node->WORD == word)
        {
            return node;
        }
        node=node->next;
    }
    
    return NULL;
}

void USUN(list** L, char* word)
{
    
    list* previous;
    list* tmp = *L;

    while(tmp != NULL)
    {
        if(tmp->WORD == word)
        {
            if(tmp == *L)
            {
                *L = tmp->next;
                return;
            }

            else
            {
                previous->next = tmp->next;
                free(tmp);
                return;
            }
        }

        else
        {
            previous=tmp;
            tmp = tmp->next;
        }
  }

}

void BEZPOWTORZEN(list* L)
{
    list *node1, *node2, *tmp;
    node1 = L;
    while(node1 != NULL && node1->next != NULL)
    {
        node2 = node1;
        while(node2->next != NULL)
        {
            if(node1->WORD == node2->next->WORD)
            {
                tmp = node2->next;
                node2->next = node2->next->next;
                free(tmp);
            }
            else
            {
                node2 = node2->next;
            }
        }
        node1 = node1->next;
    }
}

void SCAL(list** lis1, list** lis2)
{
    list* tmp = (list*)malloc(sizeof(list));
    tmp = *lis1;
    while(tmp != NULL)
    {
        WSTAW(&L3, tmp->WORD);
        tmp = tmp->next;
    }
    tmp = *lis2;
    while(tmp != NULL)
    {
        WSTAW(&L3, tmp->WORD);
        tmp = tmp->next;
    }

    *lis1 = NULL;
    *lis2 = NULL;
}

void KASUJ(list** lis1){
    list* previous;
    list* tmp = *lis1;
    struct List *t;
    while(tmp != NULL){
        t = tmp->next;
        free(tmp);
        tmp = t;
    }
    *lis1 = NULL;
    printf("Lista zostala usunieta i pamiec zwolniona \n");
}

int main(void)
{	
    printf("pokazuje pusta liste first: \n");
    DRUKUJ(L1);

    printf("dodaje kot  i pies x2 i kanarek do first\n");
    WSTAW(&L1, "kot");
    WSTAW(&L1, "pies");
    WSTAW(&L1, "pies");
    WSTAW(&L1, "kanarek");

    printf("dodaje krowa i kurczak do second \n");
    WSTAW(&L2, "krowa");
    WSTAW(&L2, "kurczak");

    printf("pokazuje first\n");
    DRUKUJ(L1); 

    printf("pokazuje second\n");
    DRUKUJ(L2);

    printf("szukam slowa krowa \n");
    list* search;
    search=SZUKAJ(L2, "krowa");
    printf("Search [krowa]* : ");
    DRUKUJ(search);

    printf("usuwam slowo kot\n");
    USUN(&L1, "kot");

    printf("pokazuije first bez kota\n");
    DRUKUJ(L1); 

    printf("\nFirst bez powtrozen : \n");
    BEZPOWTORZEN(L1);
    DRUKUJ(L1);

    printf("\nL3 (scalenie L1 i L2) : ");
    SCAL(&L1, &L2);
    DRUKUJ(L3);
    DRUKUJ(L1); //puste po scaleniu!
    DRUKUJ(L2); //puste po scaleniu!
   
    printf("usuwam cala liste \n");
    KASUJ(&L3);

    printf("pokaz liste third\n");
    DRUKUJ(L3);

    return 0;
}
