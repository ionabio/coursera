#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Assignment of option A, A list to generate dynamic arrays of 100 random integers

typedef struct list
{
    int value;
    struct list* next;
} list;

list *addToFront(list *head, int value)
{
    list *newHead = malloc(sizeof(list));
    newHead->value = value;
    newHead->next = head;
    return newHead;
}

int getSize(list *l)
{
    int size = 0;
    while (l != NULL)
    {
        size++;
        l = l->next;
    }
    return size;
}

// swap two nodes and return the new head
list* swap(list *a, list *b)
{
    //a{value, next = b}, b{value, next = ?}

    list* temp = b->next;
    b->next = a;
    a->next = temp;
    return b;
}

// bubble sort and return the head of sorted list
list* bubbleSort(list * head)
{
    int size = getSize(head);
    for (int i = 0; i < size - 1; i++)
    {
        list *current = head;
        list *next = head->next;
        list *previous = NULL; //to keep track of previous element, to see if head is swapped
        // Note that we are always swapping current and next and end of every iteration we update previous, regardless of swap
        // if swap has occured we need to update current 
        // a double linked linear list would make this easier, because it'd be easy to walk back and find the head
        for (int j = 0; j < size - 1 - i; j++)
        {
            if (current->value > next->value)
            {
                // swap the nodes
                current = swap(current, next);
                if (previous == NULL) //ie. head is swapped, change it
                { 
                    head = current;
                }
                else
                {
                    previous->next = current;
                }
                previous = current;
                current = current->next;
            }
            else
            {
                previous = current;
                current = next;
            }
            next = current->next;
        }
    }
    return head;// return the updated (sorted) head;
}

// free the allocated memory
void freeList(list *l)
{
    while (l != NULL)
    {
        list *temp = l;
        l = l->next;
        free(temp);
    }
}

//output the list, 5 per line
void printList(list *l)
{
    int count = 0;
    while (l != NULL)
    {
        printf("%d \t", l->value);
        count++;
        if (count % 5 == 0)
        {
            printf("\n");
        }
        l = l->next;
    }
}

int main(void)
{
    srand(time(NULL));
    // generate the list
    list *head = NULL;
    for (int i = 0; i < 100; i++)
    {
        int value = rand() % 100;
        head = addToFront(head, value);
    }

    printf("Unsorted list:\n");
    printList(head);
    printf("\n");


    head = bubbleSort(head);

    printf("--------------------\n");
    printf("Sorted list:\n");
    printList(head);
    printf("\n");

    freeList(head);

    return 0;
}