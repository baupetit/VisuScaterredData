/** 
 * File : data.c
 * Authors : Benjamin Aupetit
 *           Nicolas  Cousin
 */

#include "data.h"
#include <stdio.h>

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
