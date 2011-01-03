/** 
 * File : main.c
 * Authors : Benjamin Aupetit
 *           Nicolas  Cousin
 */

#include "data.h"
#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

int main( int argc, char** argv )
{
	// DONNEES
	ScaterredData2D data;
	SampledData2D result;
	data.nbSamples = 4;
	data.scaterred = malloc(data.nbSamples*sizeof(Data2D));
	int i;
	data.scaterred[0].x = 0.0;
	data.scaterred[0].y = 0.0;
	data.scaterred[0].z = 0.0;

	data.scaterred[1].x = 1.0;
	data.scaterred[1].y = 0.0;
	data.scaterred[1].z = 0.5;

	data.scaterred[2].x = 0.0;
	data.scaterred[2].y = 1.0;
	data.scaterred[2].z = 0.5;
	
	data.scaterred[3].x = 1.0;
	data.scaterred[3].y = 1.0;
	data.scaterred[3].z = 1.0;



	for (i = 0; i < 4; ++i){
		printf("Point %i : %f %f %f\n",
		       i,
		       data.scaterred[i].x,
		       data.scaterred[i].y,
		       data.scaterred[i].z
		       );	
	}

	// resolution
	result.width = 100;
	result.height = 100;

	multiQuadricInterpolation2D(DEFAULT_GRID,data,&result);
	ecrireFichierVTK2D("lol.vtk", result);

	// ON FREE TOUT
	free(data.scaterred);
	free(result.sampledValue);

	return 0;
} 

