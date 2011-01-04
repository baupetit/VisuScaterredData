/** 
 * File : data.c
 * Authors : Benjamin Aupetit
 *           Nicolas  Cousin
 */

#include "data.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/* allocate the given data */
ScaterredData2D* allocateData2D( int nbSamples )
{
	ScaterredData2D* data;
	data = (ScaterredData2D*) malloc ( sizeof(ScaterredData2D) );
	if (data == NULL)
		return NULL;
	data->nbSamples = nbSamples;
	data->scaterred = (Data2D*)malloc( nbSamples * sizeof(Data2D) );
	if(data->scaterred == NULL)
	{
		free(data);
		return NULL;
	}
	return data;
}

ScaterredData3D* allocateData3D( int nbSamples )
{
	ScaterredData3D* data;
	data = (ScaterredData3D*) malloc ( sizeof(ScaterredData2D) );
	if (data == NULL)
		return NULL;
	data->nbSamples = nbSamples;
	data->scaterred = (Data3D*)malloc( nbSamples * sizeof(Data3D) );
	if(data->scaterred == NULL)
	{
		free(data);
		return NULL;
	}
	return data;
}

/* free data */
void freeData2D(ScaterredData2D* data)
{
	if (data != NULL)
	{
		if (data->scaterred != NULL)
		{
			free(data->scaterred);
		}
		free(data);
	}
}

void freeData3D(ScaterredData3D* data)
{
	if (data!=NULL)
	{
		if (data->scaterred!=NULL)
		{
			free(data->scaterred);
		}
		free(data);
	}
}

void computeBoundingBox2D(GridType type, BoundingBox2D *box, int nbSamples, Data2D *data)
{
	real minX, minY, maxX, maxY;
	
	if (nbSamples < 2) 
		printf("ERREUR - Tried to create a bounding box with less than 2 points\n");
	minX = data[0].x;
	minY = data[0].y;
	maxX = data[0].x;
	maxY = data[0].y;

	unsigned int i;
	for (i = 1; i < nbSamples; ++i){
		if (data[i].x < minX) minX = data[i].x;
		else if (data[i].x > maxX) maxX = data[i].x;

		if (data[i].y < minY) minY = data[i].y;
		else if (data[i].y > maxY) maxY = data[i].y;
	}

	if (type == DEFAULT_GRID){
		(*box).xmin = minX;
		(*box).ymin = minY;
		(*box).xmax = maxX;
		(*box).ymax = maxY;
	}else if (type == EXTENDED_GRID){
		(*box).xmin = 2*minX-maxX;
		(*box).ymin = 2*minY-maxY;
		(*box).xmax = 2*maxX-minX;
		(*box).ymax = 2*maxY-minY;
	}
}


void computeBoundingBox3D(GridType type, BoundingBox3D *box, int nbSamples, Data3D *data)
{
	real minX, minY, maxX, maxY, minZ, maxZ;
	
	if (nbSamples < 2) 
		printf("ERREUR - Tried to create a bounding box with less than 2 points\n");
	minX = data[0].x;
	minY = data[0].y;
	maxX = data[0].x;
	maxY = data[0].y;
	minZ = data[0].z;
	maxZ = data[0].z;

	unsigned int i;
	for (i = 1; i < nbSamples; ++i){
		if (data[i].x < minX) minX = data[i].x;
		else if (data[i].x > maxX) maxX = data[i].x;

		if (data[i].y < minY) minY = data[i].y;
		else if (data[i].y > maxY) maxY = data[i].y;

		if (data[i].z < minZ) minZ = data[i].z;
		else if (data[i].z > maxZ) maxZ = data[i].z;
	}

	if (type == DEFAULT_GRID){
		(*box).xmin = minX;
		(*box).ymin = minY;
		(*box).zmin = minZ;
		(*box).xmax = maxX;
		(*box).ymax = maxY;
		(*box).zmax = maxZ;
	}else if (type == EXTENDED_GRID){
		(*box).xmin = 2*minX-maxX;
		(*box).ymin = 2*minY-maxY;
		(*box).zmin = 2*minZ-maxZ;
		(*box).xmax = 2*maxX-minX;
		(*box).ymax = 2*maxY-minY;
		(*box).zmax = 2*maxZ-minZ;
	}
}

void initRand()
{
	/* init random generator with a seed based on the current time */
	srand(time(NULL));
}

inline static void generateRandom(real *r, real min, real max)
{
	//*r = fmod(rand()+min,max);
	*r = ((rand()/(float)RAND_MAX) * (max - min)) + min;
}

inline static void generate2DCoordinates(real *x, real *y, real min, real max)
{
	generateRandom(x,min,max);
	generateRandom(y,min,max);
}

inline static void generate3DCoordinates(real *x, real *y, real *z, real min, real max)
{
	generateRandom(x,min,max);
	generateRandom(y,min,max);
	generateRandom(z,min,max);
}

void generateRandomData2D(ScaterredData2D *data,
			real rangeMin, real rangeMax)
{
	int ind = 0;
	if (data==NULL)
		return;
	// init samples
	for (;ind < data->nbSamples;++ind)
	{
		generate2DCoordinates(&data->scaterred[ind].x,
				      &data->scaterred[ind].y,
				      rangeMin,rangeMax);
		generateRandom(&data->scaterred[ind].z,-1.0,1.0);
	}
}

void generateRandomData3D(ScaterredData3D *data, 
			real rangeMin, real rangeMax)
{
	int ind = 0;
	if (data==NULL)
		return;
	// init samples
	for (;ind < data->nbSamples;++ind)
	{
		generate3DCoordinates(&data->scaterred[ind].x,
				      &data->scaterred[ind].y,
				      &data->scaterred[ind].z,
				      rangeMin,rangeMax);
		generateRandom(&data->scaterred[ind].w,-1.0,1.0);
	}
}

void generateSinCData2D(ScaterredData2D *data, real factor,
		      real rangeMin, real rangeMax)
{
	int ind = 0;
	if (data==NULL)
		return;
	// init samples
	for (;ind < data->nbSamples;++ind)
	{
		generate2DCoordinates(&data->scaterred[ind].x,
				      &data->scaterred[ind].y,
				      rangeMin,rangeMax);
		real dist = sqrt(data->scaterred[ind].x*data->scaterred[ind].x + 
				 data->scaterred[ind].y*data->scaterred[ind].y);
		data->scaterred[ind].z = (sinf(factor*M_PI*dist) / (factor*M_PI*dist)) ;
	}
}

void generateSinCData3D(ScaterredData3D *data, real factor,
		      real rangeMin, real rangeMax)
{
	int ind = 0;
	if (data==NULL)
		return;
	// init samples
	for (;ind < data->nbSamples;++ind)
	{
		generate3DCoordinates(&data->scaterred[ind].x,
				      &data->scaterred[ind].y,
				      &data->scaterred[ind].z,
				      rangeMin,rangeMax);
		real dist = sqrt(data->scaterred[ind].x*data->scaterred[ind].x + 
				 data->scaterred[ind].y*data->scaterred[ind].y +
				 data->scaterred[ind].z*data->scaterred[ind].z);
		data->scaterred[ind].w = (sinf(factor*M_PI*dist) / (factor*M_PI*dist)) ;
	}
}
