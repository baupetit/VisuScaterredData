/** 
 * File : data.h
 * Authors : Benjamin Aupetit
 *           Nicolas  Cousin
 */

#ifndef DATA_H
#define DATA_H

#include "type.h"

/* allocate the given data */
ScaterredData2D* allocateData2D( int nbSamples );
ScaterredData3D* allocateData3D( int nbSamples );

/* free data */
void freeData2D(ScaterredData2D* data);
void freeData3D(ScaterredData3D* data);

/* compute the bounding box associated with the 
   given set of data */
void computeBoundingBox2D(GridType type, BoundingBox2D *box, int nbSamples, Data2D *data);
void computeBoundingBox3D(GridType type, BoundingBox3D *box, int nbSamples, Data3D *data);

/* generate random scaterred data
   points coordinates are inside [rangeMin,rangeMax]
   value are inside [-1,1]
 */
void initRand();

void generateRandomData2D(ScaterredData2D *data, 
			real rangeMin, real rangeMax);
void generateRandomData3D(ScaterredData3D *data, 
			real rangeMin, real rangeMax);


/* generate scaterred data based on the cardinal sinus function
   points coordinates are inside [rangeMin,rangeMax]
 */
void generateSinCData2D(ScaterredData2D *data,real factor,
		      real rangeMin, real rangeMax);
void generateSinCData3D(ScaterredData3D *data,real factor,
		      real rangeMin, real rangeMax);

ScaterredData2D* readData2D(char* fileName);
ScaterredData3D* readData3D(char* fileName);

#endif //DATA_H
