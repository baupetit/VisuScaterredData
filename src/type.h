/** 
 * File : type.h
 * Authors : Benjamin Aupetit
 *           Nicolas  Cousin
 */

typedef double real;

/**
 * BoundingBox
 */
struct _BoundingBox
{
	real xmin, xmax, ymin, ymax;
};

/** Data :
    hold the coordinates of scaterred data
*/
struct _Data 
{
	real x;
	real y;
	real z;
};

typedef struct _Data Data;

/** Scaterred data structure 
 * hold scaterred data info
 */
struct _ScaterredData
{
	int         nbSamples;
	Data       *scaterred;
	BoundingBox obb;
};

typedef struct _ScaterredData ScaterredData;

/** SampledData 
 * hold sampled data over the area of the bouding box
 */
struct _SampledData
{
	real        width;
	real        height;
	BoundingBox obb;
	real       *sampledValue;
};

typedef struct _SampledData SampledData;
