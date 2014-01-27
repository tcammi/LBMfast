/*
 * init.cpp
 *
 *  Created on: Jan 24, 2014
 *      Author: tc
 */

#include "init.h"
#include <stack>
#include <iostream>
#include <fstream>
#include <vector>
#include "helper.h"
using namespace std;

void initF(double*** &f, double*** &fEQ, double*** &fDummy, int Ny, int Nx) {

	f = new double**[9];
	fEQ = new double**[9];
	fDummy = new double**[9];

	for (int k = 0; k < 9; k++) {
		f[k] = new double*[Ny + 1];
		fEQ[k] = new double*[Ny + 1];
		fDummy[k] = new double*[Ny + 1];

		for (int i = 0; i < Ny + 1; i++) {
			f[k][i] = new double[Nx + 1];
			fEQ[k][i] = new double[Nx + 1];
			fDummy[k][i] = new double[Nx + 1];

			for (int j = 0; j < Nx + 1; j++) {
				f[k][i][j] = 0.;
				fEQ[k][i][j] = 0.;
				fDummy[k][i][j] = 0.;
			}
		}
	}

}

void initFlow(double** &v, double** &u, double ** &rho, int Ny, int Nx) {

	v = new double*[Ny + 1];
	u = new double*[Ny + 1];
	rho = new double*[Ny + 1];

	for (int i = 0; i < Ny + 1; i++) {
		v[i] = new double[Nx + 1];
		u[i] = new double[Nx + 1];
		rho[i] = new double[Nx + 1];

		for (int j = 0; j < Nx + 1; j++) {
			v[i][j] = 0.;
			u[i][j] = 0.;
			rho[i][j] = 1.;
		}
	}

}
