/** 
 * File : interpolate.h
 * Authors : Benjamin Aupetit
 *           Nicolas  Cousin
 */

#ifndef INTERPOLATE_H
#define INTERPOLATE_H

#include "data.h"
#include "matrix.h"

void multiQuadricInterpolation2D(GridType type, ScaterredData2D data, SampledData2D *result);

void multiQuadricInterpolation3D(GridType type, ScaterredData3D data, SampledData3D *result);



#endif //INTERPOLATE_H
