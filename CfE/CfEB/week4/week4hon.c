#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct bintree{
    int data;
    struct bintree* left;
    struct bintree* right;
} bintree;

//this implementation of binary tree uses recursion

// three helper functions are used:
//1-  to create node(with left and right set to Null)
bintree* createNode(int data)
{
    bintree* node = malloc(sizeof(bintree));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

//2- add elements, uses recurtion to find the right place and when found (that means the left or right place of the parent node is null), it creates a node (see 1.)
// Note that a pointer to pointer is used to be able to modify the pointers on the function call
void add(bintree** root, int data)
{
    if(*root == NULL)
    {
        *root = createNode(data);
        return;
    }
    if(data < (*root)->data)
    {
        add(&(*root)->left, data);
    }
    else
    {
        add(&(*root)->right, data);
    }
}

// 3- just a helper to print, but "inorder" walk requirment is used here, which is also a simplel recursion
void print(bintree* root)
{
    if(root == NULL)
    {
        return;
    }
    print(root->left);
    printf("%d ,", root->data);
    print(root->right);
}

// Main has the steps clear, (read from file, create an array and use that array to create the binary tree and print it)
int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("Usage: ./%s <file-name>\n", argv[0]);
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    int size = 0;
    assert(fscanf(file, "%d", &size) == 1);
    int* arr = malloc(size * sizeof(int));
    for(int i = 0; i < size; i++)
    {
        assert(fscanf(file, "%d", &arr[i]) == 1);
    }

    bintree* root = createNode(arr[0]);

    for(int i=1; i<size; i++)
    {
        add(&root, arr[i]);
    }

   printf("bintree from left to right: \n");
   print(root);
   printf("\n");
}