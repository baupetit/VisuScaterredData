/** 
 * File : data.h
 * Authors : Benjamin Aupetit
 *           Nicolas  Cousin
 */

#ifndef DATA_H
#define DATA_H

#include "type.h"

/**
 * Allocate the data structure for a defined set of sample
 */
scaterred_data allocate_scaterred_data( int number_of_sample );

/**
 * Allocate the data structure for sampled data
 */
sampled_data   allocate_sampled_data_3D( boundingbox obb
					 real        spacing_X,
					 real        spacing_Y,
					 real        spacing_Z );


#endif
