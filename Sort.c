#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
// for p two value  
void swapp(int *a,int *b){
 int tmp ;
 tmp= *a;
 *a=*b;
 *b=tmp;
}

// initializing definition
void initialize_Array(int array[], int size){

         for (int i = 0; i < size; i++) {
            array[i] = rand()% (450 + 430 + 1) -43;
        }
}
void shellSort(int arr[], int size) {
    for (int gap = size / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

// Selection Sort Definition
void Selection_Sort(int array[], int size){
  int i , j  , min_index = 0;

    for ( i = 0; i < size; i++) {
              min_index=i ;
                for (j = i+1 ; j < size; j++)
                {
                    if (array[j]<array[min_index])
                    {  
                       min_index=j;
                    }
                }   
               swapp(&array[i],&array[min_index]);
            }
    }

// Bubble Sort Methods 
void Bubble_Sort(int array[], int size ){
        int done =0;
        while (done==0)
            { 
               done =1;
               for (int j = 0; j < size-1 ; j++)
                  {
                     if (array[j+1] < array[j])
                     {
                     swapp(&array[j+1],&array[j]);
                     done=0;
                     }
                  }
        }       
}


// Insertion Sort Methods 

void Insertion_Sort(int array[], int size ){
   int Break, index , j;
        for (int i = 1; i < size; i++)
        {  
               j=i;
              
               while (j>0 && array[j]<array[j-1])
               {
                  swapp(&array[j],&array[j-1]);
                  j--;

               }
        }    
}

// Messure Sort Time

double Messure_Sort_Time(void (*Function_Sort)(int array[] , int size ), int array[], int size){
      double Time =0;
     clock_t Start = clock();
     Function_Sort(array, size);
     clock_t End = clock();
    Time = (double)(End - Start) / CLOCKS_PER_SEC;
    return Time ; 

}

// Function to sort an array using counting sort
void countingSort(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    int min = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }

    int range = max - min + 1;

    // Create a count array to store the count of each element
    int* count = (int*)malloc(range * sizeof(int));
    int* output = (int*)malloc(n * sizeof(int));

    // Initialize count array with zeros
    for (int i = 0; i < range; i++) {
        count[i] = 0;
    }

    // Store the count of each element
    for (int i = 0; i < n; i++) {
        count[arr[i] - min]++;
    }

    // Modify the count array to store the sum of counts
    for (int i = 1; i < range; i++) {
        count[i] += count[i - 1];
    }

    // Build the output array
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i] - min] - 1] = arr[i];
        count[arr[i] - min]--;
    }

    // Copy the sorted elements back into the original array
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    free(count);
    free(output);
}

void inversedData(int *t,int n){
   int i;
   for(i=0;i<n;i++){
    t[i]=n-i;
   }
 }

// alreadysorted
 void alreadySortedData(int *t,int n){
    int i;
   for(i=0;i<n;i++){
    t[i]=i;
   }
 }
 
 void duplicateData(int *t,int n){
      int i;
      srand(time(NULL));
      for(i=0;i<n;i++){
        t[i]=rand()%4;
      }
 }

void dataWithSortedSubarrays(int *t,int n){
    int i=n/4;
    inversedData(t,i);
    alreadySortedData(t+i,2*i);
    inversedData(t+2*i,3*i);
    alreadySortedData(t+3*i,n);
}

// Functionvoid 
void quickSort(int* t, int n) {
    int start = 0;
    int end = n - 1;

    int left = start - 1;
    int right = end + 1;
    const int pivot = t[start];

    if (start >= end)
        return;

    while (1) {
        do right--; while (t[right] > pivot);
        do left++; while (t[left] < pivot);

        if (left < right)
            swapp(&t[left], &t[right]);
        else
            break;
    }

    quickSort(t, right + 1);
    quickSort(t+right+1, n-right-1);
}



void merge(int* t,int* left,int* right,int n1,int n2){
    int i=0,j=0,k=0;
    while(i<n1 && j<n2){
        if(left[i]<right[j]){
            t[k] = left [i];
            i++;
        } else{
            t[k] = right[j];
            j++;
        }
        k++;
    }
    while(i<n1) {
        t[k] = left[i];
        i++;
        k++;
    }
    while(j<n2) {
        t[k] = right[j];
        j++;
        k++;
    }
}

void merge_sort(int * t,int n){
    if(n<2) return;
    int i,mid = n/2,*left,*right;
    left = (int*)malloc(mid*sizeof(int));
    right = (int*)malloc((n-mid)*sizeof(int));
    for(i=0;i<n;i++){
        if(i<mid) left[i] = t[i];
        else right[i-mid] = t[i];
    }
    merge_sort(left,mid);
    merge_sort(right,n-mid);
    merge(t,left,right,mid,n-mid);
    free(left);
    free(right);
}


double gaussian(double x, double mean, double variance) {
    return exp(-(x - mean) * (x - mean) / (2.0 * variance * variance));
}