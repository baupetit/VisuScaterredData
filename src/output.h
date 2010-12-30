/** 
 * File : output.h
 * Authors : Benjamin Aupetit
 *           Nicolas  Cousin
 */

#ifndef OUTPUT_H
#define OUTPUT_H

#include "type.h"

void ecrireFichierVTK2D(char *filePath, SampledData2D data);
void ecrireFichierVTK3D(char *filePath, SampledData3D data);

#endif //OUTPUT_H
