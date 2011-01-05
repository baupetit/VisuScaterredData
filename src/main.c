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
	const int width = 50;
	const int height = 50;
	int i;
	
	// INIT
	initRand();
	
	/*
	// allocation
	data = allocateData2D(4);
	data->scaterred[0].x = 0.0;
	data->scaterred[0].y = 0.0;
	data->scaterred[0].z = 0.0;

	data->scaterred[1].x = 1.0;
	data->scaterred[1].y = 0.0;
	data->scaterred[1].z = 0.5;

	data->scaterred[2].x = 0.0;
	data->scaterred[2].y = 1.0;
	data->scaterred[2].z = 0.5;
	
	data->scaterred[3].x = 1.0;
	data->scaterred[3].y = 1.0;
	data->scaterred[3].z = 1.0;
	*/

	/*
	// init 
	//generateRandomData2D(data, 0.0,1.0);
	generateSinCData2D(data, 4,-2.0,2.0);
	*/

	data = readData2D("../data/villes_TN_2D.txt");

	if (data != NULL){
		// resolution
		result.width = width;
		result.height = height;
	
		multiQuadricInterpolation2D(DEFAULT_GRID,*data,&result);
		//multiQuadricInterpolation2D(EXTENDED_GRID,data,&result);

		ecrireFichierVTK2D("lol.vtk", result);

		// ON FREE TOUT
		//free(data.scaterred);
		freeData2D(data);
		free(result.sampledValue);
	}

	return 0;
} 

