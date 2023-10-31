#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Sort.h"

#define Nentries 60
#define Pas 2000
#define N0 1000000

void gettitre(int titleindex, char *title);
void lesfunction(int *array, int k, int size, double table[3][Nentries], int i);

// Function to create a plot using Gnuplot
void plotData(double table[3][Nentries], char *titre) {
    // Open a pipe to Gnuplot for plotting
    FILE *gnuplotPipe = popen("gnuplot -persist", "w");
    if (gnuplotPipe == NULL) {
        perror("Error opening pipe to Gnuplot");
        exit(1);
    }

    // Configure Gnuplot settings for the plot
    fprintf(gnuplotPipe, "set terminal wxt enhanced\n");
    fprintf(gnuplotPipe, "set title '%s'\n", titre); // Use '%s' to insert the title as a string
    fprintf(gnuplotPipe, "set xlabel 'Array Size'\n");
    fprintf(gnuplotPipe, "set ylabel 'Time (seconds)'\n");

    // Define line styles and colors for different sorting algorithms
    fprintf(gnuplotPipe, "set style line 1 lt 1 lc rgb 'red' lw 2\n");
    fprintf(gnuplotPipe, "set style line 2 lt 2 lc rgb 'blue' lw 2\n");
    fprintf(gnuplotPipe, "plot '-' with lines linestyle 1 title 'Shell Sort' smooth unique, \
                                 '-' with lines linestyle 2 title 'Count Sort' smooth unique\n");

    int num_interpolated_points=5000;  // number d point a creer entre deux point deja define
 
    // Plot the data for each sorting algorithm
    for (int i = 0; i < Nentries; i++) {
        fprintf(gnuplotPipe, "%d %lf \n", (int)table[0][i], table[1][i]);

          if (i<Nentries-1)
                                {
                                    double x1 = table[k][0][i];
                                    double y1 = table[k][j][i];
                                    double x2 = table[k][0][i+1];
                                    double y2 = table[k][j][i+1];

                                for (int j = 1; j <= num_interpolated_points; j++) {
                                    double x = x1 + (x2 - x1) * j / num_interpolated_points;
                                    double y = y1 + (y2 - y1) * exp(-(x - x1) * (x - x1) / (0.3 * (x2 - x1) * (x2 - x1)));
                                    fprintf(gnuplotPipe, "%lf %lf\n", x, y);
                                }
                                }
        

        // if (i < Nentries - 1) {
        //     double x1 = table[0][i];
        //     double y1 = table[1][i];
        //     double x2 = table[0][i + 1];
        //     double y2 = table[1][i + 1];

        //     for (int j = 1; j <= num_interpolated_points; j++) {
        //         double x = x1 + (x2 - x1) * j / num_interpolated_points;
        //         double y = y1 + (y2 - y1) * exp(-(x - x1) * (x - x1) / (2 * (x2 - x1) * (x2 - x1)));
        //         fprintf(gnuplotPipe, "%lf %lf\n", x, y);
        //     }
        // }

    }
    fprintf(gnuplotPipe, "e\n");
    fflush(gnuplotPipe);
    for (int i = 0; i < Nentries; i++) {
        fprintf(gnuplotPipe, "%d %lf \n", (int)table[0][i], table[2][i]);

        // Perform Gaussian interpolation between data points
        if (i < Nentries - 1) {
            double x1 = table[0][i];
            double y1 = table[2][i];
            double x2 = table[0][i + 1];
            double y2 = table[2][i + 1];

            for (int j = 1; j <= num_interpolated_points; j++) {
                double x = x1 + (x2 - x1) * j / num_interpolated_points;
                double y = y1 + (y2 - y1) * exp(-(x - x1) * (x - x1) / (2 * (x2 - x1) * (x2 - x1)));
                fprintf(gnuplotPipe, "%lf %lf\n", x, y);
            }
        }

    }
    fprintf(gnuplotPipe, "e\n");
    fflush(gnuplotPipe);

    // Close the Gnuplot pipe
    pclose(gnuplotPipe);
}

int main() {
    srand(time(NULL));
    double (*table)[Nentries] = (double(*)[Nentries])malloc(3 * Nentries * sizeof(double));
    char *TYPE_DATA_TITLE[2] = {
            "Sorted data", "Inversed sort" // Customize type data names here
        };
    int array_size[Nentries];
    array_size[0] = N0;

    // Generate array sizes for testing
    for (int i = 1; i < Nentries; i++) {
        array_size[i] = array_size[i - 1] + Pas;
    }

    int Type_data = 4;

    char *title = (char *)malloc(30 * sizeof(char));

    for (int k = 0; k < 2; k++) {
        // Measure and store sorting times for different algorithms
        for (int i = 0; i < Nentries; i++) {
            int size = array_size[i];
            int *array_sort = (int *)malloc(size * sizeof(int));

            lesfunction(array_sort, k, size, table, i);
        }
         // Pass Type_data to get the title
        plotData(table, TYPE_DATA_TITLE[k]);
    }

    // Free the dynamically allocated table
    free(table);

    return 0;
}


void lesfunction(int *array,int k,int size,double table[3][Nentries],int i){
int *shell_array = (int*)malloc(size * sizeof(int));
        int *count_array = (int*)malloc(size * sizeof(int));
            switch (k)
            {  
                case 0:
                    duplicateData(array,size);
                break;
                
                case 1:
                    inversedData(array,size);
                break;
            default:
                break;
            }

        // int *selected_array = (int*)malloc(size * sizeof(int));
        // int *inserted_array = (int*)malloc(size * sizeof(int));
        // int *bubble_array = (int*)malloc(size * sizeof(int));

        // Copy the data to be sorted
        for (int j = 0; j < size; j++) {
            // selected_array[j] = array[j];
            // bubble_array[j] = array[j];
            // inserted_array[j] = array[j];
            shell_array[j] = array[j];
            count_array[j] = array[j];
        }

        // Measure sorting times
        // double selected_sorting_time = Messure_Sort_Time(Selection_Sort, selected_array, size);
        // double inserted_sorting_time = Messure_Sort_Time(Insertion_Sort, inserted_array, size);
        // double bubble_sorting_time = Messure_Sort_Time(Bubble_Sort, bubble_array, size);
        double shell_sorting_time = Messure_Sort_Time(shellSort, shell_array, size);
        double count_sorting_time = Messure_Sort_Time(countingSort, count_array, size);

        // Store the data for plotting
        table[0][i] = size;
        // table[1][i] = selected_sorting_time;
        // table[2][i] = inserted_sorting_time;
        // table[3][i] = bubble_sorting_time;
        table[1][i] = shell_sorting_time;
        table[2][i] = count_sorting_time;

        // Free the dynamically allocated arrays
        free(array);
        // free(selected_array);
        // free(bubble_array);
        // free(inserted_array);
        free(shell_array);
        free(count_array);
          
}


// here 

 if (i < Nentries - 1)
                    {
                        double x1 = table[k][0][i];
                        double y1 = table[k][j][i];
                        double x2 = table[k][0][i + 1];
                        double y2 = table[k][j][i + 1];

                        for (int l = 1; l <= num_interpolated_points; l++)
                        {
                            double x = x1 + (x2 - x1) * l / num_interpolated_points;
                            double y = y1 + (y2 - y1) * exp(-(x - x1) * (x - x1) / (2.0 * (x2 - x1) * (x2 - x1)));
                            fprintf(gnuplotPipe, "%lf %lf\n", x, y);
                        }
                    }