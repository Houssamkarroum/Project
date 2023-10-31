#include <stdio.h>
#include <stdlib.h>
#define N 5000000
void Swapp(int *a,int *b){
 int tmp ;
 tmp= *a;
 *a=*b;
 *b=tmp;
}
int partition(int* array, int low, int high) {
    int pivot = array[high]; // Choose the last element as the pivot
    int i = (low - 1);

    for (int j = low; j < high; j++) {
        if (array[j] < pivot) {
            i++;
            Swapp(&array[i], &array[j]);
        }
    }

    Swapp(&array[i + 1], &array[high]);
    return (i + 1);
}

// Function to perform Quick Sort on an array of a given size
void quickSort(int* array, int size) {
    int low = 0;
    int high = size - 1;

    if (low < high) {
        int pivotIndex = partition(array, low, high);

        // Recursively sort elements before and after the pivot
        quickSort(array, pivotIndex);
        quickSort(array + pivotIndex + 1, size - pivotIndex - 1);
    }
}
void initialize_Array(int array[], int size){

         for (int i = 0; i < size; i++) {
            array[i] = rand()% (450 + 430 + 1) -43;
        }
}
int main (){
    int* t=(int*)malloc(N*sizeof(int));
    initialize_Array(t,N);
//    for (int i = 0; i < N; i++) printf("[%d]",t[i]);
  
    quickSort(t,N);
  printf("done");
    //    for (int i = 0; i < N; i++) printf("[%d]",t[i]);
    return 0;
}