/** 
 * File : interpolate.c
 * Authors : Benjamin Aupetit
 *           Nicolas  Cousin
 */

#include "interpolate.h"
#include <math.h>

void multiQuadricInterpolation(GridType type, ScaterredData2D data, SampledData2D *result)
{
	computeBoundingBox(type, &(data.obb), data.nbSamples, data.scaterred);
	(*result).obb = data.obb;

	// DUMMY
	real R = (real)1;
	int precision = 10;

	
	// CALCUL DE LA MATRICE des hk
	int line, column;
	Matrix *H = allocateMatrix(data.nbSamples, data.nbSamples);

	for (line = 0; line < data.nbSamples; ++line){
		Data2D xi = data.scaterred[line];
		for (column = 0; column < data.nbSamples; ++column){
			Data2D xj = data.scaterred[column];

			(*H).values[line*(*H).width+column] = 
				sqrt(R*R + 
				     (xi.x - xj.x) * (xi.x - xj.x) +
				     (xi.y - xj.y) * (xi.y - xj.y));
		}
	}

	Matrix *invH = invert(*H);
	
	Matrix *scalars = allocateMatrix(1, data.nbSamples);
	for (line = 0; line < data.nbSamples; ++line){
		(*scalars).values[line] = data.scaterred[line].z;
	}
	
	Matrix *coefficients = multiply(*invH,*scalars);

	printMatrix(*H);
	printMatrix(*coefficients);
	printMatrix(*multiply(*H,*coefficients));
	printMatrix(*scalars);

	// faire le calcul des points de la grille régulière à partir des coefficients
	// TODO
}
