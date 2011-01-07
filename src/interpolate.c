/** 
 * File : interpolate.c
 * Authors : Benjamin Aupetit
 *           Nicolas  Cousin
 */

#include "interpolate.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

// shepard ui coefficient
#define SHEPARD_UI 4

// return the distance between two 2D sample
inline static real dist2sample(const Data2D a, const Data2D b)
{
	const real xd = a.x - b.x;
	const real yd = a.y - b.y;
	return sqrt((xd*xd) + (yd*yd));
}

// return the distance between two 3D sample
inline static real dist3sample(const Data3D a, const Data3D b)
{
	const real xd = a.x - b.x;
	const real yd = a.y - b.y;
	const real zd = a.z - b.z;
	return sqrt((xd*xd) + (yd*yd) +(zd*zd));
}

// compute wi(x)
inline static real computeWINom(ScaterredData2D data, Data2D X, int i)
{
	real nom = 1;
	// compute nom
	const int nbSample = data.nbSamples;
	int j;
	for (j=0;j<nbSample;++j)
	{
		// ignore case j==i
		if (j==i)
		{
			continue;
		}
		nom *= pow(dist2sample(X,data.scaterred[j]),SHEPARD_UI);
	}

	return nom;
}

// compute wi(x)
inline static real computeWINom3(ScaterredData3D data, Data3D X, int i)
{
	real nom = 1;
	// compute nom
	const int nbSample = data.nbSamples;
	int j;
	for (j=0;j<nbSample;++j)
	{
		// ignore case j==i
		if (j==i)
		{
			continue;
		}
		nom *= pow(dist3sample(X,data.scaterred[j]),SHEPARD_UI);
	}

	return nom;
}

// return the shepard interpolation for the point X
// => F(X)
inline static real sheparderp(ScaterredData2D data, Data2D X)
{
	real result = 0;
	const int nbSample = data.nbSamples;
	real denom = 0;
	// compute denom
	int k;
	for (k=0;k<nbSample;++k)
	{
		int j;
		real prod = 1;
		for (j=0;j<nbSample;++j)
		{
			// ignore case j==k
			if (j==k)
			{
				continue;
			}
			//printf("dist k X : %f \n",dist2sample(X,data.scaterred[k]));
			//printf("d %f %f x %f %f\n",data.scaterred[j].x,data.scaterred[j].y,X.x,X.y);
			prod *= pow(dist2sample(X,data.scaterred[j]),SHEPARD_UI);
		}
		denom += prod;
	}
	//printf("denom : %f\n",denom);
	// compute F(X)
	int i;
	for (i=0;i<nbSample;++i)
	{
		// compute wi
		real wiNom = computeWINom(data,X,i);
		//printf("Om NOm nom nom : %f\n",wiNom);
		// add to result
		result += data.scaterred[i].z * (wiNom/denom);
	}
	return result;
}

// return the shepard interpolation for the point X
// => F(X)
inline static real sheparderp3(ScaterredData3D data, Data3D X)
{
	real result = 0;
	const int nbSample = data.nbSamples;
	real denom = 0;
	// compute denom
	int k;
	for (k=0;k<nbSample;++k)
	{
		int j;
		real prod = 1;
		for (j=0;j<nbSample;++j)
		{
			// ignore case j==k
			if (j==k)
			{
				continue;
			}
			//printf("dist k X : %f \n",dist2sample(X,data.scaterred[k]));
			//printf("d %f %f x %f %f\n",data.scaterred[j].x,data.scaterred[j].y,X.x,X.y);
			prod *= pow(dist3sample(X,data.scaterred[j]),SHEPARD_UI);
		}
		denom += prod;
	}
	//printf("denom : %f\n",denom);
	// compute F(X)
	int i;
	for (i=0;i<nbSample;++i)
	{
		// compute wi
		real wiNom = computeWINom3(data,X,i);
		//printf("Om NOm nom nom : %f\n",wiNom);
		// add to result
		result += data.scaterred[i].w * (wiNom/denom);
	}
	return result;
}

void shepardInterpolation2D(GridType type, ScaterredData2D data, SampledData2D* result, 
			    real xmin, real xmax, real ymin, real ymax )
{
	// On calcule la bounding box et on la recopie dans result
	computeBoundingBox2D(type, &(data.obb), data.nbSamples, data.scaterred);
	(*result).obb = data.obb;
	
	// pour chaque point de la grille
	int line, column;
	const real spacingX = (xmax - xmin) / (real)(result->width-1);
	const real spacingY = (ymax - ymin) / (real)(result->height-1);
	//printf("spacingX : %f, spacingY : %f, xmin : %f, ymin : %f",spacingX,spacingY,xmin,ymin);
	for (line=0;line<result->height;++line)
	{
		for (column=0;column<result->width;++column)
		{
			Data2D x = { xmin + column*spacingX,
				     ymin + line*spacingY,
			             0 };
			real val = sheparderp(data,x);
			//printf("coordonées (%d,%d) = (%f,%f) = %f\n",i,j,x.x,x.y,val);
			result->sampledValue[line*(result->width)+column] = val;
		}
	}
}

void shepardInterpolation3D(GridType type, ScaterredData3D data, SampledData3D* result, 
			    real xmin, real xmax, real ymin, real ymax, real zmin, real zmax )
{
	// On calcule la bounding box et on la recopie dans result
	computeBoundingBox3D(type, &(data.obb), data.nbSamples, data.scaterred);
	(*result).obb = data.obb;
	
	// pour chaque point de la grille
	int column, line, slice;
	const real spacingX = (xmax - xmin) / (real)(result->width-1);
	const real spacingY = (ymax - ymin) / (real)(result->height-1);
	const real spacingZ = (zmax - zmin) / (real)(result->depth-1);
	for (slice=0;slice<result->depth;++slice)
	{
		for (line=0;line<result->height;++line)
		{
			for (column=0;column<result->width;++column)
			{
				Data3D x = { xmin + column*spacingX,
					     ymin + line*spacingY,
					     zmin + slice*spacingZ,
					     0 };
				real val = sheparderp3(data,x);
				result->sampledValue[slice*(result->width)*(result->height)+ line*(result->width)+column] = val;
			}
		}
	}
}

void multiQuadricInterpolation2D(GridType type, ScaterredData2D data, SampledData2D *result)
{
	// On calcule la bounding box et on la recopie dans result
	computeBoundingBox2D(type, &(data.obb), data.nbSamples, data.scaterred);
	(*result).obb = data.obb;
	
	/*
	// CALCUL DE R : CRITERE DE FRANKE
	real R = ;
	int i,j;
	for (i = 0; i<data.nbSamples-1; ++i){
		for (j = i+1; j<data.nbSamples; ++j){
			real D = sqrt(pow(data.scaterred[i].x-data.scaterred[j].x,2)+pow(data.scaterred[i].y-data.scaterred[j].y,2));
			
		}
	}
	*/

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

			(*H).values[line*(H->width)+column] = 
				sqrt(R + 
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
	//(*result).sampledValue = malloc((*result).width*(*result).height*sizeof(real));
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
	Matrix *H = NULL, *invH = NULL, *coefficients = NULL, *gridPoints = NULL, *gridScalars = NULL, *scalars = NULL;

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
	//result->sampledValue = malloc((result->width)*(result->height)*(result->depth)*sizeof(real));
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
