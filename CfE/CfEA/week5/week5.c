#include <stdio.h>
#define SIZE 1000

// this program reads 1000 values from the txt file in the same folder
// and prints the average of the values

int main(void){
    FILE *file;
    file = fopen("elephant_seal_data.txt", "r");

    int i = 0;
    int sum = 0;
    int average = 0;
    int values[SIZE];

    for(i = 0; i<SIZE; i++){
        fscanf(file, "%d",&values[i]);
        sum += values[i];
    }
    average = sum/SIZE;
    printf("The average of the values is: %d\n", average);
}