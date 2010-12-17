/** 
 * File : output.h
 * Authors : Benjamin Aupetit
 *           Nicolas  Cousin
 */

#ifndef FILE_H
#define FILE_H

void ecrireFichierVTK(char *filePath, int resolution, float *boundMin, float* boundMax, float **data);

#endif //FILE_H
