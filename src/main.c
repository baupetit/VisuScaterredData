/** 
 * File : main.c
 * Authors : Benjamin Aupetit
 *           Nicolas  Cousin
 */

#include "data.h"
#include <stdio.h>
#include <stdlib.h>

int main( int argc, char** argv )
{
	ScaterredData2D data;
	SampledData2D result;
	data.nbSamples = 10;
	data.scaterred = malloc(10*sizeof(Data2D));
	int i;
	for (i = 0; i < 10; ++i){
		data.scaterred[i].x = ((real)i) / ((real)10);
		data.scaterred[i].y = ((real)15) / ((real)i+1);
		data.scaterred[i].z = ((real)i*i) / ((real)10);
	}

	for (i = 0; i < 10; ++i){
		printf("Point %i : %f %f %f\n",
		       i,
		       data.scaterred[i].x,
		       data.scaterred[i].y,
		       data.scaterred[i].z
		       );	
	}

	multiQuadricInterpolation(DEFAULT_GRID,data,&result);
	//computeBoundingBox(DEFAULT_GRID, &(data.obb), data.nbSamples, data.scaterred);

	printf("Grid Min : %f %f\n",result.obb.xmin,result.obb.ymin);
	printf("Grid Max : %f %f\n",result.obb.xmax,result.obb.ymax);

	return 0;
} 

