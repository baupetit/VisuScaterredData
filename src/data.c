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

#define MAX_REC_LEN 1024
#define TRUE 1
#define FALSE 0

#define LIGNE_DATA_DIMENSION 0
#define LIGNE_NUMBER_POINTS 1
#define LIGNE_COORDONNEE_X 2
#define LIGNE_COORDONNEE_Y 3
#define LIGNE_COORDONNEE_Z 4
#define LIGNE_COORDONNEE_W 5


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

/* allocate results */
SampledData2D* allocateResult2D( int width, int height )
{
	SampledData2D* data;
	data = (SampledData2D*) malloc ( sizeof(SampledData2D) );
	if (data == NULL)
		return NULL;
	data->width = width;
	data->height = height;
	data->sampledValue = (real*)malloc( height * width * sizeof(real) );
	if(data->sampledValue == NULL)
	{
		free(data);
		return NULL;
	}
	return data;
}

SampledData3D* allocateResult3D( int width, int height, int depth )
{
	SampledData3D* data;
	data = (SampledData3D*) malloc ( sizeof(SampledData3D) );
	if (data == NULL)
		return NULL;
	data->width = width;
	data->height = height;
	data->depth = depth;
	data->sampledValue = (real*)malloc( height * width * depth * sizeof(real) );
	if(data->sampledValue == NULL)
	{
		free(data);
		return NULL;
	}
	return data;
}

/* free results */
void freeResult2D(SampledData2D* data)
{
	if (data!=NULL)
	{
		if (data->sampledValue!=NULL)
		{
			free(data->sampledValue);
		}
		free(data);
	}
}

void freeResult3D(SampledData3D* data)
{
	if (data!=NULL)
	{
		if (data->sampledValue!=NULL)
		{
			free(data->sampledValue);
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

inline static real generateRandom(real min, real max)
{
	//return fmod(rand()+min,max);
	return ((rand()/(float)RAND_MAX) * (max - min)) + min;
}

ScaterredData2D* generateRandomData2D(int nbSamples, real minX, real maxX, real minY, real maxY, real minZ, real maxZ)
{
	if (nbSamples<2 || minX==maxX || minY==maxY || minZ==maxZ) return NULL;
	ScaterredData2D* data = allocateData2D(nbSamples);
	int ind = 0;
	for (;ind < nbSamples;++ind)
	{
		data->scaterred[ind].x = generateRandom(minX,maxX);
		data->scaterred[ind].y = generateRandom(minY,maxY);
		data->scaterred[ind].z = generateRandom(minZ,maxZ);
	}
	return data;
}

ScaterredData3D* generateRandomData3D(int nbSamples, real minX, real maxX, real minY, real maxY, real minZ, real maxZ, real minW, real maxW)
{
	if (nbSamples<2 || minX==maxX || minY==maxY || minZ==maxZ || minW==maxW) return NULL;
	ScaterredData3D* data = allocateData3D(nbSamples);
	int ind = 0;
	for (;ind < nbSamples;++ind)
	{
		data->scaterred[ind].x = generateRandom(minX,maxX);
		data->scaterred[ind].y = generateRandom(minY,maxY);
		data->scaterred[ind].z = generateRandom(minZ,maxZ);
		data->scaterred[ind].w = generateRandom(minW,maxW);
	}
	return data;
}

ScaterredData2D* generateSinCData2D(int nbSamples, real factor, real minX, real maxX, real minY, real maxY)
{
	if (nbSamples<2 || minX==maxX || minY==maxY) return NULL;
	ScaterredData2D* data = allocateData2D(nbSamples);
	int ind = 0;
	for (;ind < data->nbSamples;++ind)
	{
		data->scaterred[ind].x = generateRandom(minX,maxX);
		data->scaterred[ind].y = generateRandom(minY,maxY);
		real dist = sqrt(data->scaterred[ind].x*data->scaterred[ind].x + 
				 data->scaterred[ind].y*data->scaterred[ind].y);
		if (dist!=0){
			data->scaterred[ind].z = (sinf(factor*M_PI*dist) / (factor*M_PI*dist));
		}else{
			data->scaterred[ind].z = ((real)1.0);
		}
	}
	return data;
}

ScaterredData3D* generateSinCData3D(int nbSamples, real factor, real minX, real maxX, real minY, real maxY, real minZ, real maxZ)
{
	if (nbSamples<2 || minX==maxX || minY==maxY || minZ==maxZ) return NULL;
	ScaterredData3D* data = allocateData3D(nbSamples);
	int ind = 0;
	for (;ind < data->nbSamples;++ind)
	{
		data->scaterred[ind].x = generateRandom(minX,maxX);
		data->scaterred[ind].y = generateRandom(minY,maxY);
		data->scaterred[ind].z = generateRandom(minZ,maxZ);
		real dist = sqrt(data->scaterred[ind].x*data->scaterred[ind].x + 
				 data->scaterred[ind].y*data->scaterred[ind].y +
				 data->scaterred[ind].z*data->scaterred[ind].z);
		if (dist!=0){
			data->scaterred[ind].w = (sinf(factor*M_PI*dist) / (factor*M_PI*dist));
		}else{
			data->scaterred[ind].w = ((real)1.0);
		}
	}
	return data;
}


/*
 * LECTURE DE FICHIERS
 */

int convertToInt(char *mot, int *store){
	// VERIFICATION DE LA CONVERSION
	char *ptr;
	long int res = strtol(mot,&ptr,10);
	if (*ptr != '\0'){
		printf("\n-----   ERREUR DE CONVERSION : INT   -----\n");
		return FALSE;
	}
	*store = (int) res;
	return TRUE;
}

int convertToReal(char *mot, real *store){
	char *ptr;
	double res = strtod(mot,&ptr);
	if (*ptr != '\0'){
		printf("\n-----   ERREUR DE CONVERSION : REAL   -----\n");
		return FALSE;
	}
	*store = (real) res;
	return TRUE;
}

int isRelevantChar(char c){
	// ON NE LISTE QUE LES CARACTERES POUVANT ETRE PRESENTS DANS UN REAL OU UN INT 
	if ( c=='0' || c=='1' || c=='2' || c=='3' || c=='4' || c=='5' || c=='6' || c=='7' || c=='8' || c=='9' || c=='.' || c=='-' || c=='#' ){
		return TRUE;		
	}
	return FALSE;
}


char* lireMot(char line[MAX_REC_LEN], int *index){
	char *mot;
	int start = -1;
	int i;

	// LE DERNIER CARACTERE PERTINENT DANS LINE EST SUIVI DU CARACTERE NUL '\0'
	while (*index<MAX_REC_LEN && line[*index]!='\0'){
		if (start==-1 && isRelevantChar(line[*index])){
			start = *index;
		}else if (start!=-1 && (!isRelevantChar(line[*index]))){
			mot = malloc((*index-start+1)*sizeof(char));
			for (i=start; i<*index; ++i){
				mot[i-start] = line[i];
			}
			// ON N'OUBLIE PAS LE CARACTERE DE FIN DE CHAINE : '\0'
			mot[*index-start] = '\0';
			*index = *index +1;
			return mot;
		}
		*index = *index + 1;
	}
	return NULL;
}


ScaterredData2D* readData2D(char* fileName){
	FILE* f = NULL;
	f = fopen(fileName, "r");

	// DATA_DIMENSION
	int data_dim;
	// NUMBER_POINTS
	int numberPoints;
	// SCATERRED DATA
	ScaterredData2D* data;

	char line[MAX_REC_LEN]="";
	char *mot;
	int lineIndex = 0;
	int lineStatus = LIGNE_DATA_DIMENSION;
	// INDEX DE LA COORDONNEE DANS LE TABLEAU 
	int coordIndex = 0;
	// BOUCLE
	int i;

	if (f != NULL){
		while(fgets(line,MAX_REC_LEN,f)!=NULL){
			// LIRE LE PREMIER MOT DE LA LIGNE
			mot = lireMot(line, &lineIndex);
			// SI IL COMMENCE PAR UN # ON SKIP LA LIGNE
			if (mot!=NULL && mot[0]!='#'){
				while (mot!=NULL){
					// ANALYSE DU MOT SI IL EST PERTINENT
					if (lineStatus == LIGNE_DATA_DIMENSION){

						if (!convertToInt(mot,&data_dim)){
							free(mot);
							fclose(f);
							return NULL;
						}
						if (data_dim!=3){
							printf("ERREUR LECTURE - Fichier contient des données de mauvaise dimension : DATA_DIM = %i au lieu de 3\n",data_dim);
							free(mot);
							fclose(f);
							return NULL;
						}
						lineStatus = LIGNE_NUMBER_POINTS;

					}else if (lineStatus == LIGNE_NUMBER_POINTS){

						if (!convertToInt(mot,&numberPoints)){
							free(mot);
							fclose(f);
							return NULL;
						}
						lineStatus = LIGNE_COORDONNEE_X;
						
						// ON ALLOUE LE SCATERRED DATA
						data = allocateData2D(numberPoints);
	
					}else if (lineStatus == LIGNE_COORDONNEE_X){
	
						if (!convertToReal(mot,&(data->scaterred[coordIndex].x))){
							free(mot);
							fclose(f);
							// ON DESALLOUE CAR CA NE SERA PAS FAIT 
							// DANS LE MAIN SI UNE ERREUR SURVIENT
							freeData2D(data);
							return NULL;
						}
						lineStatus = LIGNE_COORDONNEE_Y;
	
					}else if (lineStatus == LIGNE_COORDONNEE_Y){
	
						if (!convertToReal(mot,&(data->scaterred[coordIndex].y))){
							free(mot);
							fclose(f);
							// ON DESALLOUE CAR CA NE SERA PAS FAIT 
							// DANS LE MAIN SI UNE ERREUR SURVIENT
							freeData2D(data);
							return NULL;
						}
						lineStatus = LIGNE_COORDONNEE_Z;
	
					}else if (lineStatus == LIGNE_COORDONNEE_Z){
	
						if (!convertToReal(mot,&(data->scaterred[coordIndex].z))){
							free(mot);
							fclose(f);
							// ON DESALLOUE CAR CA NE SERA PAS FAIT 
							// DANS LE MAIN SI UNE ERREUR SURVIENT
							freeData2D(data);
							return NULL;
						}
						lineStatus = LIGNE_COORDONNEE_X;
						++coordIndex;
						if (coordIndex>=(numberPoints)){
							// FIN
							free(mot);
							fclose(f);
							return data;
						}
	
					}
					free(mot);
					// LIRE MOT SUIVANT DANS LA LIGNE
					mot = lireMot(line, &lineIndex);
				}
			}else{
				// FREE SI C'ETAIT UNE LIGNE COMMENTAIRE
				if (mot!=NULL)
					free(mot);
			}
			// ON RECOMMENCERA L'ANALYSE A L'INDEX 0 DE LA LIGNE SUIVANTE
			lineIndex = 0;
		}
		fclose(f);
	}else{
		printf("\nE R R E U R - Impossible d'ouvrir le fichier %s\n",fileName);
	}

	return NULL;

}

ScaterredData3D* readData3D(char* fileName){
	FILE* f = NULL;
	f = fopen(fileName, "r");

	// DATA_DIMENSION
	int data_dim;
	// NUMBER_POINTS
	int numberPoints;
	// SCATERRED DATA
	ScaterredData3D* data;

	char line[MAX_REC_LEN]="";
	char *mot;
	int lineIndex = 0;
	int lineStatus = LIGNE_DATA_DIMENSION;
	// INDEX DE LA COORDONNEE DANS LE TABLEAU 
	int coordIndex = 0;
	// BOUCLE
	int i;

	if (f != NULL){
		while(fgets(line,MAX_REC_LEN,f)!=NULL){
			// LIRE LE PREMIER MOT DE LA LIGNE
			mot = lireMot(line, &lineIndex);
			// SI IL COMMENCE PAR UN # ON SKIP LA LIGNE
			if (mot!=NULL && mot[0]!='#'){
				while (mot!=NULL){
					// ANALYSE DU MOT SI IL EST PERTINENT
					if (lineStatus == LIGNE_DATA_DIMENSION){

						if (!convertToInt(mot,&data_dim)){
							free(mot);
							fclose(f);
							return NULL;
						}
						if (data_dim!=4){
							printf("ERREUR LECTURE - Fichier contient des données de mauvaise dimension : DATA_DIM = %i au lieu de 4\n",data_dim);
							free(mot);
							fclose(f);
							return NULL;
						}
						lineStatus = LIGNE_NUMBER_POINTS;

					}else if (lineStatus == LIGNE_NUMBER_POINTS){

						if (!convertToInt(mot,&numberPoints)){
							free(mot);
							fclose(f);
							return NULL;
						}
						lineStatus = LIGNE_COORDONNEE_X;
						
						// ON ALLOUE LE SCATERRED DATA
						data = allocateData3D(numberPoints);
	
					}else if (lineStatus == LIGNE_COORDONNEE_X){
	
						if (!convertToReal(mot,&(data->scaterred[coordIndex].x))){
							free(mot);
							fclose(f);
							// ON DESALLOUE CAR CA NE SERA PAS FAIT 
							// DANS LE MAIN SI UNE ERREUR SURVIENT
							freeData3D(data);
							return NULL;
						}
						lineStatus = LIGNE_COORDONNEE_Y;
	
					}else if (lineStatus == LIGNE_COORDONNEE_Y){
	
						if (!convertToReal(mot,&(data->scaterred[coordIndex].y))){
							free(mot);
							fclose(f);
							// ON DESALLOUE CAR CA NE SERA PAS FAIT 
							// DANS LE MAIN SI UNE ERREUR SURVIENT
							freeData3D(data);
							return NULL;
						}
						lineStatus = LIGNE_COORDONNEE_Z;

					}else if (lineStatus == LIGNE_COORDONNEE_Z){
	
						if (!convertToReal(mot,&(data->scaterred[coordIndex].z))){
							free(mot);
							fclose(f);
							// ON DESALLOUE CAR CA NE SERA PAS FAIT 
							// DANS LE MAIN SI UNE ERREUR SURVIENT
							freeData3D(data);
							return NULL;
						}
						lineStatus = LIGNE_COORDONNEE_W;	
	
					}else if (lineStatus == LIGNE_COORDONNEE_W){
	
						if (!convertToReal(mot,&(data->scaterred[coordIndex].w))){
							free(mot);
							fclose(f);
							// ON DESALLOUE CAR CA NE SERA PAS FAIT 
							// DANS LE MAIN SI UNE ERREUR SURVIENT
							freeData3D(data);
							return NULL;
						}
						lineStatus = LIGNE_COORDONNEE_X;
						++coordIndex;
						if (coordIndex>=(numberPoints)){
							// FIN
							free(mot);
							fclose(f);
							return data;
						}
	
					}
					free(mot);
					// LIRE MOT SUIVANT DANS LA LIGNE
					mot = lireMot(line, &lineIndex);
				}
			}else{
				// FREE SI C'ETAIT UNE LIGNE COMMENTAIRE
				if (mot!=NULL)
					free(mot);
			}
			// ON RECOMMENCERA L'ANALYSE A L'INDEX 0 DE LA LIGNE SUIVANTE
			lineIndex = 0;
		}
		fclose(f);
	}else{
		printf("\nE R R E U R - Impossible d'ouvrir le fichier %s\n",fileName);
	}
	return NULL;
}

