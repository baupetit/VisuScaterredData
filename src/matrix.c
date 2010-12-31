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
	Matrix *result = allocateMatrix(width,height);

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
	free(matrix);
}

Matrix* allocateMatrix(int width, int height)
{
	Matrix* matrix;
	matrix = malloc(sizeof(Matrix));
	(*matrix).width = width;
	(*matrix).height = height;
	(*matrix).values = malloc(height * width * sizeof(real));
	return matrix;
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


Matrix* copyMatrix(Matrix mat){
	Matrix *result = allocateMatrix(mat.width, mat.height);
	int line, column;
	for (line = 0; line < mat.height; ++line){
		for (column = 0; column < mat.width; ++column){
			(*result).values[line*mat.width+column] = mat.values[line*mat.width+column];
		}
	}
	return result;
}

Matrix* identity(int size){
	Matrix *result = allocateMatrix(size, size);
	int line, column;
	for (line = 0; line < size; ++line){
		for (column = 0; column < line; ++column){
			(*result).values[line*size+column] = ((real)0);
		}
		(*result).values[line*size+line] = ((real)1);
		for (column = line+1; column < size; ++column){
			(*result).values[line*size+column] = ((real)0);
		}
	}
	return result;
}

void LUfacto(Matrix mat, Matrix *L, Matrix *U)
{
	// L initialized to identity
	Matrix *tempL = identity(mat.width);
	// U initialized to mat
	Matrix *tempU = copyMatrix(mat);

	int width = mat.width;
	int height = mat.height;
	int pivotLine, currentLine, currentCol;

	for (pivotLine = 0; pivotLine < height-1; ++pivotLine){
		real pivot = (*tempU).values[pivotLine*width+pivotLine];
		for (currentLine = pivotLine+1; currentLine < height; ++currentLine){
			real value = (*tempU).values[currentLine*width+pivotLine];
			for (currentCol = pivotLine; currentCol < width; ++currentCol){
				(*tempU).values[currentLine*width+currentCol] = 
					(*tempU).values[currentLine*width+currentCol] -
					(*tempU).values[pivotLine*width+currentCol] * value / pivot;
				(*tempL).values[currentLine*width+currentCol] = 
					(*tempL).values[currentLine*width+currentCol] +
					(*tempL).values[pivotLine*width+currentCol] * value / pivot;
			}
		}
	}
	(*L).values = (*tempL).values;
	(*L).width = (*tempL).width;
	(*L).height = (*tempL).height;
	(*U).values = (*tempU).values;
	(*U).width = (*tempU).width;
	(*U).height = (*tempU).height;
	free(tempL);
	free(tempU);
}


Matrix* forwardLU(Matrix L, Matrix b)
{
	int line, column, k;
	Matrix *result = allocateMatrix(b.width, L.height);

	for (column = 0; column < b.width; ++column)
	{
		for (line = 0; line < L.height; ++line)
		{
			real temp = b.values[line*b.width+column];
			for (k = 0; k < line; ++k)
			{
				temp -= L.values[line*L.width+k] * (*result).values[k*b.width+column];
			}
			(*result).values[line*b.width+column] = temp / L.values[line*L.width+line];
		}
	}
	return result;
}


Matrix* backwardLU(Matrix U, Matrix Y)
{
	int line, column, k;
	Matrix *result = allocateMatrix(Y.width, U.height);

	// Solve for each column of matrix Y
	for (column = 0; column < Y.width; ++column)
	{
		for (line = U.height-1; line >= 0; --line)
		{
			real temp = Y.values[line*Y.width+column];
			for (k = U.width-1; k > line; --k){
				temp -= U.values[line*U.width+k] * (*result).values[k*Y.width+column];
			}
			(*result).values[line*Y.width+column] = temp / U.values[line*U.width+line];
		}
	}
	return result;
}

Matrix* invert(Matrix matrix)
{
	Matrix *id = identity(matrix.width);
	Matrix *L = malloc(sizeof(Matrix));
	Matrix *U = malloc(sizeof(Matrix));
	
	LUfacto(matrix,L,U);

	Matrix *Y = forwardLU(*L,*id);
	Matrix *X = backwardLU(*U,*Y);

	deallocateMatrix(L);
	deallocateMatrix(U);
	deallocateMatrix(Y);
	deallocateMatrix(id);

	return X;
}
