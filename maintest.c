#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Sort.h"

#define Nentries 10
#define Pas 2000
#define N0 10000
#define n_methode 5
void runSortingExperiment(int *array, int k, int size,double ***table, int i);

// Function to create a plot using Gnuplot
void plotData(double ***table );

int main()
{
    srand(time(NULL));
   int array_size[Nentries];
    array_size[0] = N0;

    // Generate array sizes for testing
    for (int i = 1; i < Nentries; i++) {
        array_size[i] = array_size[i - 1] + Pas;
    }
    
    double ***table = (double ***)malloc(3 * sizeof(double **));
    for (int i = 0; i < 3; i++) {
        table[i] = (double **)malloc(n_methode * sizeof(double *));
        for (int j = 0; j < n_methode; j++) {
            table[i][j] = (double *)malloc(Nentries * sizeof(double));
        }
    }

    for (int k = 0; k < 3; k++)
    {
        // Measure and store sorting times for different algorithms
        for (int i = 0; i < Nentries; i++)
        {
            int size = array_size[i];
            int *array_sort = (int*) malloc(size * sizeof(int));

            runSortingExperiment(array_sort, k, size, table, i);
        }
    }

    plotData(table);
    // Free the dynamically allocated table
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < n_methode; j++) {
                free(table[i][j]);
            }
            free(table[i]);
        }
        free(table);
    return 0;
}

void runSortingExperiment(int *array, int k, int size, double ***table, int i)
{
    int *shell_array = (int*) malloc(size * sizeof(int));
    int *count_array = (int*) malloc(size * sizeof(int));
    int *quick_array = (int*) malloc(size * sizeof(int));
    int *merge_array = (int*) malloc(size * sizeof(int));

    switch (k)
    {
        case 0:
            duplicateData(array, size);
            break;
        case 1:
            inversedData(array, size);
            break;
        case 2:
            duplicateData(array, size);
            break;
        default:
            break;
    }

    // Copy the data to be sorted
    for (int j = 0; j < size; j++)
    {
        shell_array[j] = array[j];
        count_array[j] = array[j];
        quick_array[j] = array[j];
        merge_array[j] = array[j];
    }

    // Measure sorting times
    double shell_sorting_time = Messure_Sort_Time(shellSort, shell_array, size);
    double count_sorting_time = Messure_Sort_Time(countingSort, count_array, size);
    double quick_sorting_time = Messure_Sort_Time(Selection_Sort, quick_array, size);
    double merge_sorting_time = Messure_Sort_Time(merge_sort, merge_array, size);


    // Store the data for plotting
    table[k][0][i] = size;
    table[k][1][i] = shell_sorting_time;
    table[k][2][i] = count_sorting_time;
    table[k][3][i] = quick_sorting_time;
    table[k][4][i] = merge_sorting_time;

    // Free the dynamically allocated arrays
    free(array);
    free(shell_array);
    free(count_array);
    free(quick_array);
    free(merge_array);
}

// plot adta
void plotData(double ***table)
{
        // Open a pipe to Gnuplot for plotting
        FILE *gnuplotPipe = popen("gnuplot -persist", "w");
        if (gnuplotPipe == NULL)
        {
            perror("Error opening pipe to Gnuplot");
            exit(1);
        }

        char *TYPE_DATA_TITLE[3] = { "Sorted data", "Inversed sort", "Duplicate data" };

        // Configure Gnuplot settings for the plot
        int num_interpolated_points = 100;

        // Plot data points
        for (int k = 0; k < 3; k++)
        {
            fprintf(gnuplotPipe, "set terminal windows %d size 1500,800\n", k+1);
            fprintf(gnuplotPipe, "set xlabel 'Array Size'\n");
            fprintf(gnuplotPipe, "set ylabel 'Time (seconds)'\n");
            fprintf(gnuplotPipe, "set style line 1 lt 1 lc rgb 'red' lw 2\n");
            fprintf(gnuplotPipe, "set style line 2 lt 2 lc rgb 'blue' lw 2\n");
            fprintf(gnuplotPipe, "set style line 3 lt 3 lc rgb 'green' lw 2\n");
            fprintf(gnuplotPipe, "set style line 4 lt 4 lc rgb 'purple' lw 2\n");
            fprintf(gnuplotPipe, "set title '%s'\n", TYPE_DATA_TITLE[k]);
            fprintf(gnuplotPipe, "plot '-' with lines linestyle 1 title 'Shell Sort', \
                                    '-' with lines linestyle 2 title 'Count Sort', \
                                    '-' with lines linestyle 3 title 'Quick Sort', \
                                    '-' with lines linestyle 4 title 'Merge Sort'\n");

            for (int j = 1; j < n_methode; j++)
            {
                for (int i = 0; i < Nentries; i++)
                {
                    fprintf(gnuplotPipe, "%d %lf \n", (int)table[k][0][i], table[k][j][i]);
                   //here  
                    // if (i < Nentries-1)
                    // {
                    //     double x1 = table[k][0][i];
                    //     double y1 = table[k][j][i];
                    //     double x2 = table[k][0][i + 1];
                    //     double y2 = table[k][j][i + 1];

                    //     for (int l = 1; l <= num_interpolated_points; l++)
                    //     {
                    //         double x = x1 + (x2 - x1) * l / num_interpolated_points;
                    //         double mean = x1 + (x2 - x1) / 2.0;
                    //         double variance = (x2 - x1) / 4.0;
                    //         double y = y1 + (y2 - y1) * gaussian(x, mean, variance);

                    //         fprintf(gnuplotPipe, "%lf %lf\n", x, y);
                    //     }
                    // }  
                }

                fprintf(gnuplotPipe, "e\n");
                fflush(gnuplotPipe);
            }
            // fflush(gnuplotPipe);
        
             
        } 
        pclose(gnuplotPipe);
}