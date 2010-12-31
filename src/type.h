/** 
 * File : type.h
 * Authors : Benjamin Aupetit
 *           Nicolas  Cousin
 */

#ifndef TYPE_H
#define TYPE_H

/**
 * Grid Type
 * DEFAULT_GRID : Normal Bounding Box
 * EXTENDED_GRID : 3 times the size of the normal bounding box in each direction
 */
enum _GridType
{
	DEFAULT_GRID,
	EXTENDED_GRID
};

typedef enum _GridType GridType;

typedef double real;

/** data input type
 * 2D plan or 3D
 */
enum data_type
{
	DATA_TYPE_UNKNOW, /** data type not defined */
	DATA_TYPE_2DPLAN, /* 2D plan */
	DATA_TYPE_3D      /* 3D      */
};

/**
 * Matrix
 */

struct _Matrix
{
	int width;
	int height;
	real *values;
};

typedef struct _Matrix Matrix;

/**
 * BoundingBox
 */
struct _BoundingBox2D
{
	real xmin, xmax, ymin, ymax, zmin, zmax;
};

struct _BoundingBox3D
{
	real xmin, xmax, ymin, ymax, zmin, zmax;
};

typedef struct _BoundingBox2D BoundingBox2D;
typedef struct _BoundingBox3D BoundingBox3D;

/** Data :
    hold the coordinates of scaterred data
*/
struct _Data2D 
{
	real x;
	real y;
	real z;
};

struct _Data3D 
{
	real x;
	real y;
	real z;
	real w;
};

typedef struct _Data2D Data2D;
typedef struct _Data3D Data3D;

/** Scaterred data structure 
 * hold scaterred data info
 */
struct _ScaterredData2D
{
	int           nbSamples;
	Data2D        *scaterred;
	BoundingBox2D obb;
};

struct _ScaterredData3D
{
	int           nbSamples;
	Data3D        *scaterred;
	BoundingBox3D obb;
};

typedef struct _ScaterredData2D ScaterredData2D;
typedef struct _ScaterredData3D ScaterredData3D;

/** SampledData 
 * hold sampled data over the area of the bouding box
 */
struct _SampledData2D
{
	int           width;
	int           height;
	BoundingBox2D obb;
	real          *sampledValue;
};

struct _SampledData3D
{
	int           width;
	int           height;
	int           depth;
	BoundingBox3D obb;
	real          *sampledValue;
};

typedef struct _SampledData2D SampledData2D;
typedef struct _SampledData3D SampledData3D;

#endif //TYPE_H
