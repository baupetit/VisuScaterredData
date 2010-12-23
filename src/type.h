/** 
 * File : type.h
 * Authors : Benjamin Aupetit
 *           Nicolas  Cousin
 */

#ifndef TYPE_H
#define TYPE_H

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
 * BoundingBox
 */
struct _boundingbox
{
	real xmin, xmax, ymin, ymax, zmin, zmax;
};

typedef struct _boundingbox boundingbox;

/** Data :
    hold the coordinates of scaterred data
*/
struct _data 
{
	real x;    /* coord x */
	real y;    /* coord y */
	real z;    /* coord z */
	real w;    /* value associted with the data */
};

typedef struct _data data;

/** Scaterred data structure 
 * hold scaterred data info
 */
struct _scaterred_data
{
	int         nbSamples;
	data       *scaterred;
	boundingbox obb;
};

typedef struct _scaterred_data scaterred_data;

/** SampledData 
 * hold sampled data over the area of the bouding box
 */
struct _sampled_data
{
	real        width;
	real        height;
	real        depth;
	real        spacing_X;
	real        spacing_Y;
	real        spacing_Z;
	boundingbox obb;
	real       *sampled_value;
};

typedef struct _sampled_data sampled_data;

#endif
