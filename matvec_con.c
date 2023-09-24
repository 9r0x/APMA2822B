#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <ctime>

int main(int argc, char *argv[])
{

    srand(time(NULL));
    if (argc != 3)
    {
        printf("Usage: %s ROWS COLS\n", argv[0]);
        return 1;
    }

    int ROWS = atoi(argv[1]);
    int COLS = atoi(argv[2]);

    float *A = NULL;
    float *x = NULL, *y = NULL;

    A = (float *)malloc(ROWS * COLS * sizeof(float));
    x = (float *)malloc(COLS * sizeof(float));
    y = (float *)malloc(ROWS * sizeof(float));

    for (int i = 0; i < ROWS; i++)
    {
        x[i] = (float)rand() / RAND_MAX;
        for (int j = 0; j < COLS; ++j)
            (&A[i * ROWS])[j] = (float)rand() / RAND_MAX;
    }

#ifdef DEBUG
    printf("A = [");
    for (int i = 0; i < ROWS; i++)
    {
        printf("[");
        for (int j = 0; j < COLS; j++)
        {
            printf("%f ", (&A[i * ROWS])[j]);
        }
        printf("]\n");
    }
    printf("]\n");

    printf("x = [");
    for (int i = 0; i < ROWS; i++)
    {
        printf("%f ", x[i]);
    }
    printf("]\n");
#endif

    double t1 = omp_get_wtime();
    for (int i = 0; i < ROWS; i++)
    {
        float rowSum = 0;
        for (int j = 0; j < COLS; j++)
        {
            rowSum = (&A[i * ROWS])[j] * x[j];
        }
        y[i] = rowSum;
    }
    double t2 = omp_get_wtime();

#ifdef DEBUG
    printf("y = [");
    for (int i = 0; i < ROWS; i++)
    {
        printf("%f ", y[i]);
    }
    printf("]\n");
#endif

    free(A);
    free(x);
    free(y);

    printf("Elapsed time: %f ms\n", 1000000 * (t2 - t1));

    return 0;
}
