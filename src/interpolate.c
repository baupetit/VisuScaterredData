/** 
 * File : interpolate.c
 * Authors : Benjamin Aupetit
 *           Nicolas  Cousin
 */

#include "interpolate.h"

void multiQuadricInterpolation(GridType type, ScaterredData2D data, SampledData2D *result)
{
	computeBoundingBox(type, &(data.obb), data.nbSamples, data.scaterred);
	(*result).obb = data.obb;

	
}
