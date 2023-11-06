#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Sort.h" // Include relevant headers

#define Nentries 13
#define Pas 2000
#define N0 10000
#define nbr_size 13
#define n_methode 5 
#define nbr_DATA 6   


void plotData(double ** * table);

int main() {
  srand(time(NULL));
  int array_size[Nentries];
  array_size[0] = N0;

  for (int i = 1; i < Nentries; i++) {
    array_size[i] = array_size[i - 1] + Pas;
  }

  double ***table = (double ***) malloc(nbr_DATA * sizeof(double ** ));
  for (int i = 0; i < nbr_DATA; i++) {
    table[i] = (double ** ) malloc(n_methode * sizeof(double * ));
    for (int j = 0; j < n_methode; j++) {
      table[i][j] = (double * ) malloc(Nentries * sizeof(double));
    }
  }

  for (int k = 0; k < nbr_DATA; k++) {
    for (int i = 0; i < Nentries; i++) {
      int size = array_size[i];
      int * array_sort = (int * ) malloc(size * sizeof(int));
      printf("hani dkhlte\n");
      runSortingExperiment(array_sort, k, size, table, i);
      printf("hani khrejte\n");
      free(array_sort); // Free dynamically allocated array
    }
  }

  printf("hani dkhlte plot\n");
  plotData(table);
  printf("hani khrejte plot\n");
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < n_methode; j++) {
      free(table[i][j]);
    }
    free(table[i]);
  }
  free(table);
  return 0;
}


// Function for Gaussian interpolation


void plotData(double *** table) {

  printf("im inside plot\n");
  // Open a pipe to Gnuplot for plotting
  FILE * gnuplotPipe = popen("gnuplot -persist", "w");
  if (gnuplotPipe == NULL) {
    perror("Error opening pipe to Gnuplot");
    exit(1);
  }
  printf("ana hda data title\n");

  char * TYPE_DATA_TITLE[nbr_DATA] = {
    "Sorting Duplicate Data",
    "Sorting Inversed Data",
    "Sorting Already Sorted Data",
    "Sorting Nearly Sorted Array",
    "Sorting Sub Sorted Array",
    "Sorting Random Data",
  };

  printf("hani hda appro\n");
  // Plot data points
    approximation(table, nbr_DATA, n_methode, nbr_size);
    printf("hani mora appro\n");

  
 for (int k = 0; k < nbr_DATA; k++) {
        printf("%d\n", k);
        fprintf(gnuplotPipe, "set terminal windows %d\n", k + 1);
        fprintf(gnuplotPipe, "set xlabel 'Array Size'\n");
        fprintf(gnuplotPipe, "set ylabel 'Time (seconds)'\n");
        fprintf(gnuplotPipe, "set style line 1 lt 1 lc rgb 'red' lw 2\n");
        fprintf(gnuplotPipe, "set style line 2 lt 2 lc rgb 'blue' lw 2\n");
        fprintf(gnuplotPipe, "set style line 3 lt 3 lc rgb 'green' lw 2\n");
        fprintf(gnuplotPipe, "set style line 4 lt 4 lc rgb 'purple' lw 2\n");
        fprintf(gnuplotPipe, "set title '%s'\n", TYPE_DATA_TITLE[k]);
        fprintf(gnuplotPipe, "plot '-' with lines linestyle 1 title 'Insertion Sort','-' with lines linestyle 2 title 'Quick Sort','-' with lines linestyle 3 title 'Selection Sort','-' with lines linestyle 4 title 'Merge Sort'\n");

    for (int j = 1; j < n_methode; j++) {
      for (int i = 0; i < Nentries; i++) {
        fprintf(gnuplotPipe, "%d %lf \n", (int)table[k][0][i], table[k][j][i]);
        printf("%d %lf \n", (int) table[k][0][i], table[k][j][i]);
      }
      fflush(gnuplotPipe);
      fprintf(gnuplotPipe, "e\n");
    }
  }

  pclose(gnuplotPipe);
}