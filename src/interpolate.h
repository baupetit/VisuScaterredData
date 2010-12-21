/** 
 * File : interpolate.h
 * Authors : Benjamin Aupetit
 *           Nicolas  Cousin
 */

#ifndef INTERPOLATE_H
#define INTERPOLATE_H

#include "data.h"
#include "matrix.h"

void multiQuadricInterpolation(GridType type, ScaterredData2D data, SampledData2D *result);



#endif //INTERPOLATE_H
