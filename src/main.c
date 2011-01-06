/** 
 * File : main.c
 * Authors : Benjamin Aupetit
 *           Nicolas  Cousin
 */

#include "data.h"
#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

void description(){
	printf("\n\n##### DESCRIPTION UTILISATION #####\n");
	printf("Lecture et interpolation de données lues dans un fichier\n");
	printf("\t./visu -source fichier_source -cible fichier_cible -type type_données -resolution X Y [Z]\n");
	printf("Interpolation de données générées de façon aléatoire\n");
	printf("\t./visu -cible fichier_cible -type type_données -bornes Xmin Xmax Ymin Ymax [Zmin Zmax] Smin Smax -resolution X Y [Z]\n\n");

	printf("##### DESCRIPTION DES OPTIONS #####\n");
	printf("\t-source : Chemin vers le fichier de données à lire\n");
	printf("\t-cible : Chemin vers lequel écrire les données interpolées, le fichier doit avoir l'extension '.vtk'\n");
	printf("\t-type : Type de données, chaine devant obligatoirement être égale à '2D' ou '3D'\n");
	printf("\t-resolution : Nombre de points de la grille à calculer dans chaque direction, Z ne doit être précisé que si type vaut 3D\n");
	printf("\t-bornes : Bornes à utiliser pour la génération de données aléatoires, Zmin et Zmax ne doivent être précisés que si type vaut 3D, Smin et Smax correspondent aux bornes sur la valeur des scalaires\n\n");

	printf("##### EXEMPLES D'UTILISATION #####\n");
	printf("./visu -source ../source.txt -cible cible.vtk -type 2D -resolution 15 25\n");
	printf("./visu -cible cible.vtk -type 3D -bornes 0.51 0.89 1.18 2.21 0.0 1.0 0.0 1.0 -resolution 5 21 12\n\n");
}

void checkArguments(int argc, char** argv, int *sourceIndex, int *cibleIndex, int *typeIndex,
		   int *resolutionX, int *resolutionY, int *resolutionZ,
		   real *minX, real *maxX, real *minY, real *maxY,
		   real *minZ, real *maxZ, real *minS, real *maxS){

	int i=1;
	int resolutionDejaDefinie=0;
	int bornesDejaDefinies=0;

	while (i<argc){
		if (stringCompare(argv[i],"-source")){
			if (*sourceIndex != -1){
				printf("ERREUR ARGUMENT - source est définie 2 fois ou +\n");
				exit(0);
			}	
			++i;
			*sourceIndex=i;
		}else if (stringCompare(argv[i],"-cible")){
			if (*cibleIndex != -1){
				printf("ERREUR ARGUMENT - cible est définie 2 fois ou +\n");
				exit(0);
			}
			++i;
			*cibleIndex=i;
		}else if (stringCompare(argv[i],"-type")){
			if (*typeIndex != -1){
				printf("ERREUR ARGUMENT - cible est définie 2 fois ou +\n");
				exit(0);
			}
			++i;
			*typeIndex=i;
			if ((!stringCompare(argv[i],"2D")) &&  (!stringCompare(argv[i],"3D"))){
				printf("ERREUR ARGUMENT - Le type de données doit être 2D ou 3D\n");
				exit(0);
			}
		}else if (stringCompare(argv[i],"-resolution")){
			if (*typeIndex == -1){
				// Type de données non encore connu
				printf("ERREUR ARGUMENT - Veuillez préciser le type de données avant la résolution ou les bornes\n");
				exit(0);
			}
			if (resolutionDejaDefinie){
				printf("ERREUR ARGUMENT - resolution est définie 2 fois ou +\n");
				exit(0);
			}
			// resolutionX
			++i;
			if (!convertToInt(argv[i], resolutionX)){
				printf("ERREUR ARGUMENT - Echec de la conversion de %s en INT\n",argv[i]);
				exit(0);
			}
			// resolutionY
			++i;
			if (!convertToInt(argv[i], resolutionY)){
				printf("ERREUR ARGUMENT - Echec de la conversion de %s en INT\n",argv[i]);
				exit(0);
			}
			//resolutionZ
			if (stringCompare(argv[*typeIndex],"3D")){
				++i;
				if (!convertToInt(argv[i], resolutionZ)){
					printf("ERREUR ARGUMENT - Echec de la conversion de %s en INT\n",argv[i]);
					exit(0);
				}
			}
			resolutionDejaDefinie=1;
		}else if (stringCompare(argv[i],"-bornes")){
			if (*typeIndex == -1){
				// Type de données non encore connu
				printf("ERREUR ARGUMENT - Veuillez préciser le type de données avant la résolution ou les bornes\n");
				exit(0);
			}
			if (bornesDejaDefinies){
				printf("ERREUR ARGUMENT - bornes sont définies 2 fois ou +\n");
				exit(0);
			}
			// minX
			++i;
			if (!convertToReal(argv[i], minX)){
				printf("ERREUR ARGUMENT - Echec de la conversion de %s en REAL\n",argv[i]);
				exit(0);
			}
			// maxX
			++i;
			if (!convertToReal(argv[i], maxX)){
				printf("ERREUR ARGUMENT - Echec de la conversion de %s en REAL\n",argv[i]);
				exit(0);
			}
			// minY
			++i;
			if (!convertToReal(argv[i], minY)){
				printf("ERREUR ARGUMENT - Echec de la conversion de %s en REAL\n",argv[i]);
				exit(0);
			}
			// maxY
			++i;
			if (!convertToReal(argv[i], maxY)){
				printf("ERREUR ARGUMENT - Echec de la conversion de %s en REAL\n",argv[i]);
				exit(0);
			}
			if (stringCompare(argv[*typeIndex],"3D")){
				// minZ
				++i;
				if (!convertToReal(argv[i], minZ)){
					printf("ERREUR ARGUMENT - Echec de la conversion de %s en REAL\n",argv[i]);
					exit(0);
				}
				// maxZ
				++i;
				if (!convertToReal(argv[i], maxZ)){
					printf("ERREUR ARGUMENT - Echec de la conversion de %s en REAL\n",argv[i]);
					exit(0);
				}
			}
			// minS
			++i;
			if (!convertToReal(argv[i], minS)){
				printf("ERREUR ARGUMENT - Echec de la conversion de %s en REAL\n",argv[i]);
				exit(0);
			}
			// maxS
			++i;
			if (!convertToReal(argv[i], maxS)){
				printf("ERREUR ARGUMENT - Echec de la conversion de %s en REAL\n",argv[i]);
				exit(0);
			}
			bornesDejaDefinies=1;
		}else{
			printf("ERREUR ARGUMENT - Argument non reconnu : %s\nVous avez peut être précisé trop ou pas assez de bornes ou de résolutions au vu du type\n",argv[i]);
			exit(0);
		}	
		++i;
	}

	if (*typeIndex==-1){
		printf("ERREUR ARGUMENT - Veuillez préciser le type de données\n");
		exit(0);
	}else if (*cibleIndex==-1){
		printf("ERREUR ARGUMENT - Veuillez préciser le fichier cible\n");
		exit(0);
	}else if (!resolutionDejaDefinie){
		printf("ERREUR ARGUMENT - Veuillez préciser la résolution\n");
		exit(0);
	}else if (!bornesDejaDefinies && (*sourceIndex==-1)){
		printf("ERREUR ARGUMENT - Veuillez préciser le fichier source ou les bornes pour une génération aléatoire\n");
		exit(0);
	}else if (bornesDejaDefinies && (*sourceIndex!=-1)){
		printf("ERREUR ARGUMENT - Veuillez préciser le fichier source ou les bornes pour une génération aléatoire, mais pas les 2 à la fois\n");
		exit(0);
	}
}


int stringCompare(char *s1, char *s2){
	if (s1 && s2){
		int i=0;
		while(1){
			if (s1[i]=='\0' && s2[i]=='\0')
				return 1;
			else if (s1[i]=='\0' || s2[i]=='\0')
				return 0;
			else if (s1[i]!=s2[i])
				return 0;
			i++;
		}
	}
}


int main( int argc, char** argv )
{
	// PARSING DES ARGUMENTS
	int sourceIndex=-1;
	int cibleIndex=-1;
	int typeIndex=-1;
	int resolutionX, resolutionY, resolutionZ;
	double minX, maxX, minY, maxY, minZ, maxZ, minS, maxS;

	checkArguments(argc, argv, &sourceIndex, &cibleIndex, &typeIndex, &resolutionX, &resolutionY, &resolutionZ,
		       &minX, &maxX, &minY, &maxY, &minZ, &maxZ, &minS, &maxS);

	// INIT
	initRand();
	
	if (stringCompare(argv[typeIndex],"2D")){
		ScaterredData2D *data=NULL;
		SampledData2D result;
		if (sourceIndex!=-1){
			data = readData2D(argv[sourceIndex]);
		}else{
			// RANDOM DATA
			
		}
		if (data != NULL){
			// RESOLUTION
			result.width = resolutionX;
			result.height = resolutionY;
	
			multiQuadricInterpolation2D(DEFAULT_GRID,*data,&result);
			//multiQuadricInterpolation2D(EXTENDED_GRID,*data,&result);
			
			ecrireFichierVTK2D(argv[cibleIndex], result);
			// ON FREE TOUT
			freeData2D(data);
			free(result.sampledValue);
		}
	}else{
		// 3D
		
	}


	
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
	return 0;
} 

