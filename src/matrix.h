#ifndef MATRIX_H
#define MATRIX_H

#include "type.h"

Matrix* multiply(Matrix matrixA, Matrix matrixB);
void deallocateMatrix(Matrix* matrix);
void allocateMatrix(Matrix* matrix, int width, int height);

#endif //MATRIX_H
