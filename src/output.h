/** 
 * File : output.h
 * Authors : Benjamin Aupetit
 *           Nicolas  Cousin
 */

#ifndef OUTPUT_H
#define OUTPUT_H

void ecrireFichierVTK(char *filePath, int resolution, float *boundMin, float* boundMax, float **data);

#endif //OUTPUT_H
