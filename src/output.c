/** 
 * File : output.c
 * Authors : Benjamin Aupetit
 *           Nicolas  Cousin
 */

#include "output.h"
#include <stdio.h>

void ecrireFichierVTK(char *filePath, SampledData2D data)
{
	FILE* file;

	if ((file = fopen(filePath,"w")) != NULL){
		// HEADER
		fprintf(file,"# vtk DataFile Version 3.0\n");
		fprintf(file,"vtk output\n");
		fprintf(file,"ASCII\n");
		fprintf(file,"DATASET STRUCTURED_POINTS\n");

		// DIMENSIONS
		fprintf(file,"DIMENSIONS %i %i 1\n", data.width, data.height);

		// SPACING
		real spacingX = (data.obb.xmax - data.obb.xmin) / (data.width-1);
		real spacingY = (data.obb.ymax - data.obb.ymin) / (data.height-1);
		fprintf(file,"SPACING %f %f 0\n",spacingX,spacingY);

		// ORIGIN
		fprintf(file,"ORIGIN %f %f 0\n",data.obb.xmin,data.obb.ymin);

		// POINT_DATA
		fprintf(file,"POINT_DATA %i\n",data.width*data.height);

		// TYPE DES DONNES : float
		fprintf(file,"SCALARS RTData float\n");
		// LOOKUP TABLE
		fprintf(file,"LOOKUP_TABLE default\n");

		// DONNEES
		int i;
		for (i = 0; i < data.width*data.height; ++i){
			fprintf(file,"%f ", data.sampledValue[i]);
		}

		// FERMETURE FICHIER
		fclose(file);
	}else{
		printf("\nE R R E U R - Impossible d'ouvrir le fichier %s\n", filePath);
    		return;
	}
}


