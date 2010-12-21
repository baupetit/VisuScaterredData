/** 
 * File : matrix.c
 * Authors : Benjamin Aupetit
 *           Nicolas  Cousin
 */

#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>

Matrix* multiply(Matrix matrixA, Matrix matrixB)
{
	if (matrixA.width != matrixB.height){
		printf("ERREUR - Tried to multiply matrices with wrong dimensions\n");
		return NULL;
	}
	
	int line, column, k;
	int height = matrixA.height;
	int width = matrixB.width;
	Matrix *result = malloc(sizeof(Matrix));
	allocateMatrix(result,width,height);

	for (line = 0; line < height; ++line){
		for (column = 0; column < width; ++column){
			(*result).values[line*width+column] = 0;
			for (k = 0; k < matrixA.width; ++k){
				(*result).values[line*width+column] += matrixA.values[line*matrixA.width+k] * matrixB.values[k*width+column];
			}
		}
	}
	return result;
}

void deallocateMatrix(Matrix* matrix)
{
	free((*matrix).values);
}

void allocateMatrix(Matrix* matrix, int width, int height)
{
	(*matrix).width = width;
	(*matrix).height = height;
	(*matrix).values = malloc(height * width * sizeof(real));
}

void printMatrix(Matrix matrix)
{
	if (matrix.values){
		printf("\n");
		int line, column;
		for (line = 0; line < matrix.height; ++line){
			for (column = 0; column < matrix.width; ++column){
				printf("%f\t",matrix.values[line*matrix.width+column]);
			}
			printf("\n");
		}
		printf("\n");
	}
}
