/** 
 * File : output.c
 * Authors : Benjamin Aupetit
 *           Nicolas  Cousin
 */

#include "output.h"
#include "stdio.h"

void ecrireFichierVTK(char *filePath, int resolution, float *boundMin, float* boundMax, float **data)
{
	FILE* file;

	if ((file = fopen(filePath,"w")) != NULL){
		// HEADER
		fprintf(file,"# vtk DataFile Version 3.0\n");
		fprintf(file,"vtk output\n");
		fprintf(file,"ASCII\n");
		fprintf(file,"DATASET STRUCTURED_POINTS\n");

		// DIMENSIONS
		fprintf(file,"DIMENSIONS %i %i %i\n", resolution, resolution, resolution);

		// SPACING
		float spacingX = (boundMax[0] - boundMin[0]) / ((float)(resolution-1));
		float spacingY = (boundMax[1] - boundMin[1]) / ((float)(resolution-1));
		float spacingZ = (boundMax[2] - boundMin[2]) / ((float)(resolution-1));
		fprintf(file,"SPACING %f %f %f\n",spacingX,spacingY,spacingZ);

		// ORIGIN
		fprintf(file,"ORIGIN %f %f %f\n",boundMin[0],boundMin[1],boundMin[2]);

		// POINT_DATA
		fprintf(file,"POINT_DATA %i\n",resolution*resolution*resolution);

		// TYPE DES DONNES : float
		fprintf(file,"SCALARS RTData float\n");
		// LOOKUP TABLE
		fprintf(file,"LOOKUP_TABLE default\n");

		// DONNEES
		int i;
		for (i = 0; i < resolution * resolution * resolution; ++i){
			fprintf(file,"%f ", data[i][3]);
		}

		// FERMETURE FICHIER
		fclose(file);
	}else{
		printf("\nE R R E U R - Impossible d'ouvrir le fichier %s\n", filePath);
    		return;
	}
}

