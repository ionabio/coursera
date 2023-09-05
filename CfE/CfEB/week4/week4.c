#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char * argv[])
{
    if(argc != 2){
        printf("Usage: %s <input file>\n", argv[0]);
        return 1;
    }
    FILE *ifp = fopen(argv[1], "r+");

    //Read number of elements

    int size;
    assert(fscanf(ifp, "%d", &size) == 1);
    // read into a dynamically allocated array

    int *data = calloc(size, sizeof(int)); //initialises to zero to avoid garbage values
    for(int i = 0; i< size; i++){
        assert(fscanf(ifp, "%d", &data[i]) == 1);
    }
    fclose(ifp);
    
    //output starting array
    printf("Size: %d\n", size);
    printf("Numbers: ");
    for(int i = 0; i< size; i++){
        printf("%d ", data[i]);
        if(i%10 == 9)
            printf("\n");
    }

    int max = data[0], sum = 0;
    for(int i = 0; i< size; i++){
        if(data[i] > max)
            max = data[i];
        sum += data[i];
    }
    double average = sum/(double)size;
    printf("\nMax: %d\nAverage: %lf \n", max, average);
    FILE* ofp = fopen("answer-hw3.txt", "w+");
    fprintf(ofp, "Max: %d\n", max);
    fprintf(ofp, "Average: %lf\n", average);
    fclose(ofp);
    printf("Max and Average are successfully written to answer-hw3.txt\n");
    printf("\n\n");
    free(data);
    return 0;
}