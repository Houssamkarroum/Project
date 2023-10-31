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

void dataWithSortedSubarrays(int *t,int n);

void duplicateData(int *t,int n);

void inversedData(int *t,int n);

void quickSort(int* array,int size);


void merge_sort(int * t,int n);
double gaussian(double x, double mean, double variance);

#endif