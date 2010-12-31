/** 
 * File : data.h
 * Authors : Benjamin Aupetit
 *           Nicolas  Cousin
 */

#ifndef DATA_H
#define DATA_H

#include "type.h"

void computeBoundingBox2D(GridType type, BoundingBox2D *box, int nbSamples, Data2D *data);

void computeBoundingBox3D(GridType type, BoundingBox3D *box, int nbSamples, Data3D *data);


#endif //DATA_H
