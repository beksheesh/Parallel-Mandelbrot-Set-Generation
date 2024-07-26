#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define WIDTH 1920
#define HEIGHT 1080
#define MAX_ITER 1000

int mandelbrot(double real, double imag) {
    int iter = 0;
    double z_real = real, z_imag = imag;
    while (z_real * z_real + z_imag * z_imag <= 4.0 && iter < MAX_ITER) {
        double temp = z_real * z_real - z_imag * z_imag + real;
        z_imag = 2.0 * z_real * z_imag + imag;
        z_real = temp;
        iter++;
    }
    return iter;
}

int main() {
    int *image = (int *)malloc(WIDTH * HEIGHT * sizeof(int));
    
    double start_time = omp_get_wtime();
    
    omp_set_num_threads(4);
    
    #pragma omp parallel for schedule(dynamic)
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            double real = (x - WIDTH / 2.0) * 4.0 / WIDTH;
            double imag = (y - HEIGHT / 2.0) * 4.0 / HEIGHT;
            image[y * WIDTH + x] = mandelbrot(real, imag);
        }
    }
    
    double end_time = omp_get_wtime();
    printf("Time taken: %f seconds\n", end_time - start_time);
    
    free(image);
    return 0;
}
