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
	ScaterredData2D *data;
	SampledData2D result;
	const int nbSamples = 200;
	const int width = 100;
	const int height = 100;
	
	// INIT
	initRand();
	
	/* data.nbSamples = 4; */
	/* data.scaterred = malloc(data.nbSamples*sizeof(Data2D)); */
	/* int i; */
	/* data.scaterred[0].x = 0.0; */
	/* data.scaterred[0].y = 0.0; */
	/* data.scaterred[0].z = 0.0; */

	/* data.scaterred[1].x = 1.0; */
	/* data.scaterred[1].y = 0.0; */
	/* data.scaterred[1].z = 0.5; */

	/* data.scaterred[2].x = 0.0; */
	/* data.scaterred[2].y = 1.0; */
	/* data.scaterred[2].z = 0.5; */
	
	/* data.scaterred[3].x = 1.0; */
	/* data.scaterred[3].y = 1.0; */
	/* data.scaterred[3].z = 1.0; */

	// allocation
	data = allocateData2D(nbSamples);

	// init 
	//generateRandomData2D(data, 0.0,1.0);
	generateSinCData2D(data, 4,-2.0,2.0);

	int i;
	for (i = 0; i < nbSamples; ++i){
		printf("Point %i : %f %f %f\n",
		       i,
		       data->scaterred[i].x,
		       data->scaterred[i].y,
		       data->scaterred[i].z
		       );	
	}

	// resolution
	result.width = width;
	result.height = width;
	
	multiQuadricInterpolation2D(DEFAULT_GRID,*data,&result);
	//multiQuadricInterpolation2D(EXTENDED_GRID,data,&result);

	ecrireFichierVTK2D("lol.vtk", result);

	// ON FREE TOUT
	//free(data.scaterred);
	freeData2D(data);
	free(result.sampledValue);

	return 0;
} 

