#ifndef MATRIX_H
#define MATRIX_H

#include "type.h"

void deallocateMatrix(Matrix* matrix);
Matrix* allocateMatrix(int width, int height);

Matrix* multiply(Matrix matrixA, Matrix matrixB);
Matrix* copyMatrix(Matrix mat);
Matrix* identity(int size);
void printMatrix(Matrix matrix);

void LUfacto(Matrix mat, Matrix *L, Matrix *U);
Matrix* forwardLU(Matrix L, Matrix b);
Matrix* backwardLU(Matrix U, Matrix Y);
Matrix* invert(Matrix matrix);

#endif //MATRIX_H
