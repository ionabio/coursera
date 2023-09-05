//Week 3 hon
//Submission by NN
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// the definition of doubly linked list
typedef struct dlist{
    int data;
    struct dlist *next;
    struct dlist *prev;
} dlist;

//Items are added to end of list. 
void addItemToTail(dlist *list, int data){
    //iterate to tail
    
    while(list != NULL && list->next != NULL){
        list = list->next;
    }
    //create new node
    list->next = malloc(sizeof(dlist));
    list->next->prev = list;
    list->next->next = NULL;
    list->next->data = data;    
}

//this is for IO, to be able to see before and after without code duplication
void printList(dlist *list){
    //print in 10 in a row
    int i = 0;
    while(list != NULL){
        printf("%d ", list->data);
        list = list->next;
        if(++i % 10 == 0)
            printf("\n");
    }
    printf("\n");
}

//the main algorithem, according to the second option (hence the list is not sorted)
void findAndRemoveDuplicateMethodB(dlist* list)
{
    //go to head
    while(list->prev != NULL)
        list = list->prev;
    
    //iterate through list
    while(list != NULL){
        //check if data is in list
        dlist *temp = list->next;
        while(temp != NULL){
            if(temp->data == list->data){
                dlist* oldtemp = temp; // to freeup afterward
                //remove temp
                temp->prev->next = temp->next;
                if(temp->next != NULL)
                   temp->next->prev = temp->prev;
                temp = temp->next;
                free(oldtemp);
            }
            else
            {
               temp = temp->next;
            }
            
        }
        list = list->next;
    }
}

//this is also for output the number of elements for testing
int count(dlist* list){
    if(list == NULL)
     return 0;

    while(list->prev != NULL)
        list = list->prev;

    int i = 1;
    while(list->next != NULL){
        list = list->next;
        ++i;
    }
    return i;
}

int main(void){
    srand(time(NULL));
    dlist *list = malloc(sizeof(dlist));
    list->data = rand()%50;
    list->prev = NULL;
    list->next = NULL;
    for(int i=0; i< 199; ++i)
       addItemToTail(list, rand()%50);

    printf("Before removing duplicates:\n");
    printf("Number of items: %d\n", count(list));
    printList(list);

    findAndRemoveDuplicateMethodB(list);

    printf("After removing duplicates:\n");
    printf("Number of items: %d\n", count(list));
    printList(list);
    return 0;
}

