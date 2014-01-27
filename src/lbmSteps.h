/*
 * lbmSteps.h
 *
 *  Created on: Jan 24, 2014
 *      Author: tc
 */

#ifndef LBMSTEPS_H_
#define LBMSTEPS_H_
#include "structs.h"

void computeEQ(double*** &, double**, double**, double**, int[9][2], double[9],
		double, int, int);
void computeMacro(double***, double** &, double** &, double** &, int**,
		int[9][2], int, int);
void collision(double*** &, double***, int**, double, int, int);
void source(double*** &, double, double, int, int);
void applyBC(double***&, double*** ,int** ,solid* ,int [9],int ,int ,int );
void streaming(double*** &,double***,solid* ,int ,int **,int[9][2],int ,int );
#endif /* LBMSTEPS_H_ */
