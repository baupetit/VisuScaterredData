/** 
 * File : interpolate.c
 * Authors : Benjamin Aupetit
 *           Nicolas  Cousin
 */

#include "interpolate.h"
#include <math.h>
#include <stdlib.h>



void multiQuadricInterpolation2D(GridType type, ScaterredData2D data, SampledData2D *result)
{
	// On calcule la bounding box et on la recopie dans result
	computeBoundingBox2D(type, &(data.obb), data.nbSamples, data.scaterred);
	(*result).obb = data.obb;

	// DUMMY
	real R = (real)1;
	
	// Variables
	int line, column, indX, indY;
	Matrix *H, *invH, *coefficients, *gridPoints, *gridScalars, *scalars;

	// CALCUL DE LA MATRICE des hk
	H = allocateMatrix(data.nbSamples, data.nbSamples);
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
	// Calcul de la matrice inverse des hk
	invH = invert(*H);
	
	// On recopie les valeurs d'interpolation dans une matrice
	scalars = allocateMatrix(1, data.nbSamples);
	for (line = 0; line < data.nbSamples; ++line){
		(*scalars).values[line] = data.scaterred[line].z;
	}
	
	// On calcule les coefficient alphai
	coefficients = multiply(*invH,*scalars);



	// On calcule les valeurs sur la grille régulière
	gridPoints = allocateMatrix(data.nbSamples, (*result).width*(*result).height);
	for (indY = 0; indY < (*result).height; ++indY){
		real pointY = data.obb.ymin + 
				(data.obb.ymax-data.obb.ymin)*indY/((*result).height-1);
		for (indX = 0; indX < (*result).width; ++indX){
			real pointX = data.obb.xmin + 
				(data.obb.xmax-data.obb.xmin)*indX/((*result).width-1);
			for (column = 0; column < data.nbSamples; ++column){
				Data2D xj = data.scaterred[column];
				(*gridPoints).values[(indY*(*result).width+indX)*data.nbSamples+column] = 
					sqrt(R*R + (pointX - xj.x) * (pointX - xj.x) + 
					     (pointY - xj.y) * (pointY - xj.y));
			}
		}
	}
	gridScalars = multiply(*gridPoints,*coefficients);

	// On recopie les valeurs calculées dans result
	(*result).sampledValue = malloc((*result).width*(*result).height*sizeof(real));
	for (line = 0; line < (*result).height; ++line){
		for (column = 0; column < (*result).width; ++column){
			(*result).sampledValue[line*(*result).width+column] = (*gridScalars).values[line*(*result).width+column];
		}
	}
	
	// On free toutes les matrices allouées
	deallocateMatrix(H);
	deallocateMatrix(invH);
	deallocateMatrix(scalars);
	deallocateMatrix(coefficients);
	deallocateMatrix(gridPoints);
	deallocateMatrix(gridScalars);
}


void multiQuadricInterpolation3D(GridType type, ScaterredData3D data, SampledData3D *result)
{
	// On calcule la bounding box et on la recopie dans result
	computeBoundingBox3D(type, &(data.obb), data.nbSamples, data.scaterred);
	(*result).obb = data.obb;

	// DUMMY
	real R = (real)1;
	
	// Variables
	int depth, line, column, indX, indY, indZ;
	Matrix *H, *invH, *coefficients, *gridPoints, *gridScalars, *scalars;

	// CALCUL DE LA MATRICE des hk
	H = allocateMatrix(data.nbSamples, data.nbSamples);
	for (line = 0; line < data.nbSamples; ++line){
		Data3D xi = data.scaterred[line];
		for (column = 0; column < data.nbSamples; ++column){
			Data3D xj = data.scaterred[column];

			(*H).values[line*(*H).width+column] = 
				sqrt(R*R + 
				     (xi.x - xj.x) * (xi.x - xj.x) +
				     (xi.y - xj.y) * (xi.y - xj.y) +
				     (xi.z - xj.z) * (xi.z - xj.z));
		}
	}
	// Calcul de la matrice inverse des hk
	invH = invert(*H);
	
	// On recopie les valeurs d'interpolation dans une matrice
	scalars = allocateMatrix(1, data.nbSamples);
	for (line = 0; line < data.nbSamples; ++line){
		(*scalars).values[line] = data.scaterred[line].z;
	}
	
	// On calcule les coefficient alphai
	coefficients = multiply(*invH,*scalars);

	// On calcule les valeurs sur la grille régulière
	gridPoints = allocateMatrix(data.nbSamples, (result->depth)*(result->width)*(result->height));
	for (indZ = 0; indZ < result-> depth; ++indZ){
		real pointZ = data.obb.zmin + (data.obb.zmax-data.obb.zmin)*indZ/(result->depth-1);
		for (indY = 0; indY < result->height; ++indY){
			real pointY = data.obb.ymin + (data.obb.ymax-data.obb.ymin)*indY/((*result).height-1);
			for (indX = 0; indX < (*result).width; ++indX){
				real pointX = data.obb.xmin + (data.obb.xmax-data.obb.xmin)*indX/((*result).width-1);
				for (column = 0; column < data.nbSamples; ++column){
					Data3D xj = data.scaterred[column];
					gridPoints->values[(indZ*(result->width)*(result->height)+indY*(result->width)+indX)*data.nbSamples+column] = 
						sqrt(R*R + (pointX - xj.x) * (pointX - xj.x) + (pointY - xj.y) * (pointY - xj.y) + (pointZ - xj.z) * (pointZ - xj.z));
				}
			}
		}
	}
	gridScalars = multiply(*gridPoints,*coefficients);

	// On recopie les valeurs calculées dans result
	result->sampledValue = malloc((result->width)*(result->height)*(result->depth)*sizeof(real));
	for (depth = 0; depth < result->depth; ++depth){
		for (line = 0; line < result->height; ++line){
			for (column = 0; column < result->width; ++column){
				result->sampledValue[depth*(result->width)*(result->height)+line*(result->width)+column] = 
					gridScalars->values[depth*(result->width)*(result->height)+line*(result->width)+column];
			}
		}
	}

	// On free toutes les matrices allouées
	deallocateMatrix(H);
	deallocateMatrix(invH);
	deallocateMatrix(scalars);
	deallocateMatrix(coefficients);
	deallocateMatrix(gridPoints);
	deallocateMatrix(gridScalars);
}
