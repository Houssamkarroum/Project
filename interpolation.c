#include <stdio.h>
#include <math.h>
#include "sort.h"
int main() {
 int table[5][2];
 int a=1,b=10;

 for(int i=0 ; i<5;i++){

        table[i][0]=a*(i+1);
        table[i][1]=b*(i+1);
 }


 int num_interpolated_points=5 ;



 for(int i=0 ; i<5;i++){
        if (i < 4 ) {
            double x1 = table[i+1][0];
            double y1 = table[i+1][1];
            double x0 = table[i][0];
            double y0 = table[i][1];

            for (int j = 1; j <= num_interpolated_points; j++) {
                double x = x0 + (x1- x0) * j / num_interpolated_points;

                double mean = x0 + (x1 - x0) / 2.0;
                double variance = (x1 - x0) / 4.0;
                double y = y0 + (y1 - y0) * gaussian(x, mean, variance);

                printf("%lf %lf\n", x, y);
         }
         
        }
        printf(" autre intervale\n");
}
}
// Perform Gaussian interpolation between data 
        // 
        // }