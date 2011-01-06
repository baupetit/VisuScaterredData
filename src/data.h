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

/* allocate results */
SampledData2D* allocateResult2D( int width, int height );
SampledData3D* allocateResult3D( int width, int height, int depth );

/* free results */
void freeResult2D(SampledData2D* data);
void freeResult3D(SampledData3D* data);

/* compute the bounding box associated with the 
   given set of data */
void computeBoundingBox2D(GridType type, BoundingBox2D *box, int nbSamples, Data2D *data);
void computeBoundingBox3D(GridType type, BoundingBox3D *box, int nbSamples, Data3D *data);

/* generate random scaterred data
   points coordinates are inside [rangeMin,rangeMax]
   value are inside [-1,1]
 */
void initRand();

ScaterredData2D* generateRandomData2D(int nbSamples, real minX, real maxX, 
				      real minY, real maxY, real minZ, real maxZ);
ScaterredData3D* generateRandomData3D(int nbSamples, real minX, real maxX, 
				      real minY, real maxY, real minZ, real maxZ, real minW, real maxW);


/* generate scaterred data based on the cardinal sinus function
   points coordinates are inside [rangeMin,rangeMax]
 */
ScaterredData2D* generateSinCData2D(int nbSamples, real factor, real minX, real maxX, 
				    real minY, real maxY);
ScaterredData3D* generateSinCData3D(int nbSamples, real factor, real minX, real maxX, 
				    real minY, real maxY, real minZ, real maxZ);

ScaterredData2D* readData2D(char* fileName);
ScaterredData3D* readData3D(char* fileName);

#endif //DATA_H
