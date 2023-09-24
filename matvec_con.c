#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s ROWS COLS\n", argv[0]);
        return 1;
    }

    int ROWS = atoi(argv[1]);
    int COLS = atoi(argv[2]);

    int *A = NULL;
    int *x = NULL, *y = NULL;

    A = (int *)malloc(ROWS * COLS * sizeof(int));
    x = (int *)malloc(COLS * sizeof(int));
    y = (int *)malloc(ROWS * sizeof(int));

    // #pragma omp parallel for // collapse(2)
    for (int i = 0; i < ROWS; i++)
    {
        x[i] = rand() % 10;
        for (int j = 0; j < COLS; ++j)
            (&A[i])[j] = rand() % 10;
    }

#ifdef DEBUG
    printf("Initialized\n");
#endif

    double t1 = omp_get_wtime();
    // #pragma omp parallel for
    for (int i = 0; i < ROWS; i++)
    {
        int rowSum = 0;
        // #pragma omp parallel for (reduction + : rowSum)
        for (int j = 0; j < COLS; j++)
        {
            rowSum = (&A[i])[j] * x[j];
        }
        y[i] = rowSum;
    }
    double t2 = omp_get_wtime();

#ifdef DEBUG
    printf("y = [");
    for (int i = 0; i < ROWS; i++)
    {
        printf("%d ", y[i]);
    }
    printf("]\n");
#endif

    free(A);
    free(x);
    free(y);

    printf("Elapsed time: %f ms\n", 1000000 * (t2 - t1));

    return 0;
}
