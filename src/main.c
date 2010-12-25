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

	// resolution
	result.width = 5;
	result.height = 5;

	multiQuadricInterpolation(DEFAULT_GRID,data,&result);
	ecrireFichierVTK("lol.vtk", result);

	// ON FREE TOUT
	free(data.scaterred);
	free(result.sampledValue);

	return 0;
} 

