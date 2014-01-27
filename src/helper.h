/*
 * helper.h
 *
 *  Created on: Jan 24, 2014
 *      Author: tc
 */

#ifndef HELPER_H_
#define HELPER_H_
#include "structs.h"

double negMod(int , int );
void copyToFrom(double***&, double***, int , int );
void printMatrix(double**, int, int);
void printMatrix(int**, int, int);
void printNl(solid*, int);
void printMatrix(double*** , int ,int , int ) ;
void printSolid(solid* , int );
void writeOutput(double**,double**,double**,int**,int,int,char [50],char [50]);

#endif /* HELPER_H_ */
