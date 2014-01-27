/*
 * grid.h
 *
 *  Created on: Jan 26, 2014
 *      Author: tc
 */

#ifndef GRID_H_
#define GRID_H_
#include "structs.h"

void initGrid(int** &, int, int);
void gridGeneration(solid* &, int&, int**&, int, int, int[9][2]);
void readGridFromFile(int **&,int & ,int & ,char[50],char[50]);





#endif /* GRID_H_ */
