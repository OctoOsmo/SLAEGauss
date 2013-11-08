#include <stdio.h>
#include <stdlib.h>

double **matrix = NULL;
double *vec = NULL;
size_t N;

void PrintMatrix(double **matrix, size_t N);
double *CreateVector(size_t N);
double **CreateMatrix(size_t N);


int LoadMatrix(const char *filename)
{
    FILE *f = fopen(filename, "r");
    size_t i ,j;
    if(!f)
    {
        printf("file open error\n");
        exit(1);
    }
    fscanf(f, "%d", &N);
    printf("Matrix size = %d\n", N);
    matrix = CreateMatrix(N);
    vec = CreateVector(N);
    for(i = 0; i < N; ++i)
    {
        for(j = 0; j < N; ++j)
            fscanf(f, "%lf", &matrix[i][j]);
        fscanf(f, "%lf", &vec[i]);
    }
    PrintMatrix(matrix, N);
    fclose(f);
    return 0;
}


double **CreateMatrix(size_t N)
{
    size_t i, j;
    matrix = (double **)malloc(sizeof(double*)*N);
    for(i = 0; i < N; ++i)
    {
        matrix[i] = (double*)malloc(sizeof(double)*N);
    }

	return matrix;
}

double *CreateVector(size_t N)
{
    double *vec = NULL;
    vec = malloc(sizeof(double)*N);
	return vec;
}

void PrintVector(double *v, size_t N)
{
    size_t i;
    printf("\n");
    for(i = 0; i < N; ++i)
    {
		printf("%lf ", v[i]);
    }
	printf("\n");
}

void PrintMatrix(double **matrix, size_t N)
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

size_t getMaxElementIndex(double *a, size_t N)
{
	size_t i, maxInd = 0;

	for(i = 1; i < N; ++i)
		if(abs(a[i]) > abs(a[maxInd]))
			maxInd = i;

	return maxInd;

}

void swapColumns(double **A, size_t k, size_t l, size_t N)
{
	size_t i;
	double t;

	for(i = 0; i < N; ++i)
	{
		t = A[i][k];
		A[i][k] = A[i][l];
		A[i][l] = t;
	}
}

int gaussSolver(double **A, double *b, double *x, size_t N)
{
	int i, j, k, maxInd;
	double s;
	double coef = 0.0;

	for(i = 0; i < N; ++i)
	{
		maxInd = getMaxElementIndex(A[i], N);
		
		if(maxInd != i)
			swapColumns(A, maxInd, i, N);

		//no solution
		if(A[i][i] == 0)
			return 1;

		for(j = i + 1; j < N; ++j)
		{
			coef = A[j][i]/A[i][i];
			for(k = i; k < N; ++k)
				A[j][k] -=  coef*A[i][k];

			b[j] -= coef*b[i];
		}
	}

	PrintMatrix(A, N);

	for(i = N - 1; i >= 0; --i)
	{
		s = b[i];
		for(j = i + 1; j < N; ++j)
			s -= A[i][j]*x[j]; 

		x[i] = s/A[i][i]; 
	}

	return 0;
}

int main(void)
{
    double *res = CreateVector(N);
	LoadMatrix("matrix.txt");

	gaussSolver(matrix, vec, res, N);
	PrintVector(res, N);

	//TODO: free mem
    return 0;
}
