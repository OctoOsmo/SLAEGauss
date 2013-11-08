#include <stdio.h>
#include <stdlib.h>

double **matrix = NULL;
double *vec = NULL;
size_t N;

int LoadMatrix(const char *filename)
{
    FILE *f = fopen(filename, "r");
    size_t i ,j;
    if(!f)
    {
        printf("file open error");
        exit(1);
    }
    fscanf(f, "%d", &N);
    printf("Matrix size = %d\n", N);
    CreateMatrix();
    CreateVector();
    for(i = 0; i < N; ++i)
    {
        for(j = 0; j < N; ++j)
            fscanf(f, "%lf", &matrix[i][j]);
        fscanf(f, "%lf", &vec[i]);
    }
    PrinMatrix();
    fclose(f);
    return 0;
}


void CreateMatrix(void)
{
    size_t i, j;
    matrix = malloc(sizeof(double*)*N);
    for(i = 0; i < N; ++i)
    {
        matrix[i] = (double*)malloc(sizeof(double)*N);
    }
}

void CreateVector(void)
{
    size_t i;
    vec = malloc(sizeof(double)*N);
}

void PrinMatrix(void)
{
    size_t i, j;
    printf("\n");
    for(i = 0; i < N; ++i)
    {
        for(j = 0; j < N; ++j)
            printf("%lf ", matrix[i][j]);
        printf("\n");
    }
}

int main(void)
{
    LoadMatrix("matrix.txt");
    return 0;
}
