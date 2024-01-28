#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct ELEMENT {
  int x;
  struct ELEMENT *next;
};

struct ELEMENT *head = NULL;
struct ELEMENT *tab[10];
int genRandNum(int min, int max) {
  int num = (rand() % (max - min + 1)) + min;
  return (num);
}
void Insert(struct ELEMENT **L, int x) {
    struct ELEMENT *tmp = (struct ELEMENT*)malloc(sizeof(struct ELEMENT));
    tmp->x = x;
    tmp->next = NULL;
    if(!*L) *L = tmp;
    else {
        struct ELEMENT *robo = *L;
        while(robo->next != NULL) robo = (robo->next);
        robo->next = tmp;
    }
}
void genRandList(struct ELEMENT **L, int n) {
    for(int i=0; i<n; i++) {
        Insert(L, genRandNum(-500, 500));
    }
}

void Push(struct ELEMENT *(*arr)[], int x) {
    struct ELEMENT *tmp = (struct ELEMENT*)malloc(sizeof(struct ELEMENT));
    tmp->x = x;
    tmp->next = NULL;
    int h = abs(x%10);
    if((*arr)[h] == NULL) (*arr)[h] = tmp;
    else {
        struct ELEMENT *robo = (*arr)[h];
        struct ELEMENT *prev = NULL;

        while (robo != NULL && robo->x < x) {
            prev = robo;
            robo = robo->next;
        }

        if (prev == NULL) {
            tmp->next = (*arr)[h];
            (*arr)[h] = tmp;
        } else {
            tmp->next = robo;
            prev->next = tmp;
        }
    }
}
void Pop(struct ELEMENT *(*arr)[], int x) {
    int h = abs(x%10);
    struct ELEMENT *robo = (*arr)[h];
    struct ELEMENT *prev = (*arr)[h];
    if((*arr)[h] == NULL) return;
    else if((*arr)[h]->next == NULL && (*arr)[h]->x == x) {
        free((*arr)[h]);
        (*arr)[h]=NULL;
        return;
    }
    while(x == (*arr)[h]->x && robo->next != NULL) {
        robo = (*arr)[h]->next;
        (*arr)[h]->x = (*arr)[h]->next->x;
        (*arr)[h]->next = (*arr)[h]->next->next;
        free(robo);
    }
    robo = (*arr)[h];
    prev = (*arr)[h];
    while(robo != NULL) {
        if(robo->x == x) {
            prev->next = robo->next;
            free(robo);
            robo=prev;
        }
        prev = robo;
        robo = robo->next;
    }
}
void DelT(struct ELEMENT *(*arr)[]) {
    for(int i=0; i<10; i++) {
        struct ELEMENT *robo = (*arr)[i];
        struct ELEMENT *tmp = robo;
        while(robo != NULL) {
            tmp = robo;
            robo = robo->next;
            free(tmp);
        }
        (*arr)[i] = NULL;
    }
}
void PrintOne(struct ELEMENT *(*arr)[], int index) {
    struct ELEMENT *robo = (*arr)[index];
    printf("%d: ", index);
    if(robo != NULL) {
        while(robo->next != NULL) {
            printf("%d -> ", robo->x);
            robo = robo->next;
        }
        printf("%d", robo->x);
    } else printf("No items.");
    printf("\n");
}
void PrintAll(struct ELEMENT *(*arr)[]) {
    for(int i=0; i<10; i++) {
        struct ELEMENT *robo = (*arr)[i];
        printf("%d: ", i);
        if(robo != NULL) {
            while(robo->next != NULL) {
                printf("%d -> ", robo->x);
                robo = robo->next;
            }
            printf("%d", robo->x);
        } else printf("No items.");
        printf("\n");
    }
}

int main(void) {
    srand(time(NULL));
    genRandList(&head, 60);
    struct ELEMENT *robo = head;
    while(robo != NULL) {
        Push(&tab, robo->x);
        robo = robo->next;
    }
    int h=0;
    printf("Wygenerowana cala tablica dla 60 elementow (funkcja Push wstawia kazdy element, zas PrintAll jest przedstawione ponizej): \n");
    PrintAll(&tab);
    printf("\nPrzyklad uzycia PrintOne (dla indexu = 5): \n");
    PrintOne(&tab, 5);
    printf("\nProsze podac jeden element do usuniecia (funkcja Pop): \n");
    scanf("%d", &h);
    Pop(&tab, h);
    PrintAll(&tab);
    printf("\nProsze podac jeden element do dodania (funkcja Push): \n");
    scanf("%d", &h);
    Push(&tab, h);
    PrintAll(&tab);
    printf("\nPrzyklad uzycia DelT: \n");
    DelT(&tab);
    PrintAll(&tab);
    return 0;
}