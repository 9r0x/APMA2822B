#include <iostream>
#include <omp.h>
#include <cmath>
#include <cassert>
#include <sys/time.h>

class Matrix;
double** ndarray(int, int);
Matrix* matmul(const Matrix*, const Matrix*);

class Matrix {
	public:
		int num_rows;
		int num_cols;
		double** mat;
		Matrix(int rws, int cls): num_rows(rws), num_cols(cls) {
			mat = ndarray(this->num_rows, this->num_cols);
		}
		Matrix* operator*(const Matrix* MB){
			assert(this->num_cols == MB->num_rows);
			Matrix* result = matmul(this, MB);
			return result;
		}
		void arange(void) {
#pragma omp parallel for
			for (int i=0; i<num_rows*num_cols; ++i) this->mat[0][i] = i;
		}
		void identity(void) {
#pragma omp parallel for
			for (int i=0; i<num_rows; ++i) {
				for (int j=0; j<num_cols; ++j) {
					if (i == j) this->mat[i][j] = 1.0;
					else this->mat[i][j] = 0.0;
				}
			}
		}
		void eye(void){
#pragma omp parallel for
			for (int i=0; i<num_rows; ++i) {
				for (int j=0; j<num_cols; ++j) {
					if (i != j) this->mat[i][j] = 0.0;
				}
			}
		}
		void print(void) {
			std::cout << "This matrix looks like this:" << std::endl;
			for (int i=0; i<num_rows; ++i) {
				std::cout << "| ";
				for (int j=0; j<num_cols; ++j) {
					std::cout << this->mat[i][j] << " | ";
				}
				std::cout << std::endl;
			}
		}
		~Matrix() {delete [] mat; delete [] mat[0];}

};

double** ndarray(int num_rows, int num_cols) {
	double** mat = new double*[num_rows];
	mat[0] = new double[num_rows*num_cols];
	for (int i=0; i<num_rows; ++i) {
		mat[i] = mat[0] + i*num_cols;
	}
	for (int i=0; i<num_rows*num_cols; ++i) mat[0][i] = 0.00;
	return mat;
}

Matrix* matmul(const Matrix* MA, const Matrix* MB) {
	// int num_rows = sizeof(matrix) / sizeof(double*);
	// int num_rows = matrix->num_rows;
	// int num_cols = sizeof(matrix[0]) / sizeof(double);
	// int num_cols = matrix->num_cols; 
	assert(MA->num_cols == MB->num_rows);
	Matrix* result = new Matrix(MA->num_rows, MB->num_cols);
#pragma omp parallel
{
#pragma omp for
	for (int i=0; i < MA->num_rows; ++i) {
		for (int k=0; k < MB->num_cols; ++k) {
			for (int j=0; j < MA->num_cols; ++j) {
				result->mat[i][k] += MA->mat[i][j] * MB->mat[j][k];
			}
		}	
	}
}
	return result;
}

int main() {
	int dim1, dim2, dim3;
	std::cout << "The number of rows for the first matrix: " << std::endl;
	std::cin >> dim1;
	std::cout << "The number of cols for the first matrix: " << std::endl;
	std::cin >> dim2;
    std::cout << "The number of cols for the second matrix: " << std::endl;
	std::cin >> dim3;
	//std::cout << num_rows << " " << num_cols << std::endl;

	Matrix* matrix = new Matrix(dim1, dim2);
	matrix->arange();
	matrix->print();

	Matrix* x = new Matrix(dim3, dim3);
	x->arange();
	x->eye();
	x->print();
	
	struct timeval tv_1, tv_2;

	int retval = gettimeofday(&tv_1, 0);
	if (retval < 0) return -1;

	Matrix* result = matmul(matrix, x);
	
	retval = gettimeofday(&tv_2, 0);
	if (retval < 0) return -1;
	
	result->print();

	std::cout << "time elapsed: " << tv_2.tv_sec - tv_1.tv_sec << " seconds" << tv_2.tv_usec - tv_1.tv_usec << " microseconds" << std::endl;
	result = *matrix*x;
	result->print();
}
