/** 
 * File : data.c
 * Authors : Benjamin Aupetit
 *           Nicolas  Cousin
 */

#include "data.h"
#include <stdio.h>

void computeBoundingBox(GridType type, BoundingBox2D *box, int nbSamples, Data2D *data)
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
