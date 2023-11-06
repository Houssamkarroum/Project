#ifndef SORT_H
#define SORT_H
#include "Sort.c"



// for Swap two value
void Swapp(int * , int *);

// for the initialization of the 
void initialize_Array(int *, int );

void shellSort(int *, int );

// for the selection sort methods
void Selection_Sort(int *, int );

// for the selection sort methods
void Bubble_Sort(int *, int );

void Insertion_Sort(int *, int );

double Messure_Sort_Time(void (*Function_Sort)(int * , int ), int *, int );

void countingSort(int *, int );

void alreadySortedData(int *t,int n);

void createNearlySortedArray(int *t,int n);

void duplicateData(int *t,int n);

void inversedData(int *t,int n);

void quickSort(int* array,int size);
void dataWithV(int *t,int n);

void merge_sort(int * t,int n);

void runSortingExperiment(int *array, int k, int size, double ***table, int i);

void approximation(double ***table , int nbr_DATA , int nbr_methode , int nbr_size);

void dataWithSortedSubarrays(int *t, int n);


#endif