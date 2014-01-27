/*
 * lbmSteps.cpp
 *
 *  Created on: Jan 24, 2014
 *      Author: tc
 */

#include "lbmSteps.h"
#include "helper.h"
#include <iostream>
using namespace std;

void computeEQ(double*** &f, double** v, double** u, double** rho, int c[9][2],
		double w[9], double cs, int Ny, int Nx) {

	double csSq = cs * cs;
	double cDotu, uSq;

	for (int k = 0; k < 9; k++) {
		for (int i = 0; i < Ny + 1; i++) {
			for (int j = 0; j < Nx + 1; j++) {
				uSq = (v[i][j] * v[i][j] + u[i][j] * u[i][j]) / (2. * csSq);
				cDotu = (c[k][0] * v[i][j] + c[k][1] * u[i][j]) / csSq;

				f[k][i][j] = rho[i][j] * w[k]
						* (1 + cDotu - uSq + cDotu * cDotu / 2.);

			}
		}

	}

}

void computeMacro(double*** f, double** &v, double** &u, double** &rho,
		int** state, int c[9][2], int Ny, int Nx) {

	for (int i = 0; i < Ny + 1; i++) {
		for (int j = 0; j < Nx + 1; j++) {
			if (state[i][j] >= 1 && state[i][j] <= 4) {
				rho[i][j] = 0.0;
				v[i][j] = 0.0;
				u[i][j] = 0.0;
				for (int k = 0; k < 9; k++) {
					rho[i][j] += f[k][i][j];
					v[i][j] += f[k][i][j] * c[k][0];
					u[i][j] += f[k][i][j] * c[k][1];
				}
				v[i][j] /= rho[i][j];
				u[i][j] /= rho[i][j];
			}
		}
	}
}

void collision(double*** &f, double*** fEQ, int** state, double omega, int Ny,
		int Nx) {
	for (int k = 0; k < 9; k++) {
		for (int i = 0; i < Ny + 1; i++) {
			for (int j = 0; j < Nx + 1; j++) {
				if (state[i][j] >= 1 && state[i][j] <= 4) {
					f[k][i][j] += omega * (fEQ[k][i][j] - f[k][i][j]);
				}
			}
		}
	}
}

void source(double*** &f, int** state, double omega, double cs, int Ny,
		int Nx) {

	double rho0 = 1.;
	double nu = rho0 * (1. / omega - 0.5) * cs * cs;
	double um = 10;
	double H = Ny + 1.;

	double G = 8. * nu / H / H * um / 6.;

//	for (int i = 0; i < Ny + 1; i++) {
//		for (int j = 0; j < Nx + 1; j++) {
//			if (state[i][j] >= 1 && state[i][j] <= 4) {
//
//				f[1][i][j] += G;
//				f[5][i][j] += G;
//				f[8][i][j] += G;
//
//				f[3][i][j] -= G;
//				f[6][i][j] -= G;
//				f[7][i][j] -= G;
//			}
//		}
//	}

// let us only simulate constant inflow
	for (int i = 0; i < Ny + 1; i++) {
		for (int j = 0; j < Nx + 1; j++) {
			if (state[i][j] == 3) {
				f[1][i][j] = G;
				f[5][i][j] = G;
				f[8][i][j] = G;

			}
		}
	}

}

void applyBC(double*** &f, double*** fDummy, int** state, solid* boundary,
		int mirror[9], int Nb, int Ny, int Nx) {

	// TODO performance, avoid double copy
	int i, j, k, in, jn;
	for (int n = 0; n < Nb; n++) {
		if (boundary[n].surrounded) {
			// do nothing
		} else {
			i = boundary[n].i;
			j = boundary[n].j;
			for (int m = 0; m < boundary[n].Nl; m++) {
				k = boundary[n].link[m];
				in = boundary[n].nodes[0][m];
				jn = boundary[n].nodes[1][m];
				fDummy[k][i][j] = f[mirror[k]][in][jn];
			}
		}
	}

	// copy back but not all elements, this should be faster
	for (int n = 0; n < Nb; n++) {
		if (boundary[n].surrounded) {
			// do nothing
		} else {
			i = boundary[n].i;
			j = boundary[n].j;
			for (int m = 0; m < boundary[n].Nl; m++) {
				k = boundary[n].link[m];
				in = boundary[n].nodes[0][m];
				jn = boundary[n].nodes[1][m];
				f[mirror[k]][in][jn] = fDummy[k][i][j];

			}
		}
	}

}

void streaming(double*** &f, double*** fDummy, solid* boundary, int Nb,
		int **state, int c[9][2], int Ny, int Nx) {

	int ii, jj;
	for (int i = 0; i < Ny + 1; i++) {
		for (int j = 0; j < Nx + 1; j++) {
			if (state[i][j] == 1) { // liquid and inside
				// no need to take care of periodic wall
				for (int k = 0; k < 9; k++) {
					ii = i + c[k][0];
					jj = j + c[k][1];
					fDummy[k][ii][jj] = f[k][i][j];
				}

			} else if (state[i][j] == 2) { // liquid and periodic
				for (int k = 0; k < 9; k++) {

					ii = i + c[k][0];
					if (ii < 0)
						ii = Ny;
					if (ii > Ny)
						ii = 0;
					jj = j + c[k][1];
					if (jj < 0)
						jj = Nx;
					if (jj > Nx)
						jj = 0;

					fDummy[k][ii][jj] = f[k][i][j];
				}

			} else if (state[i][j] == 3) { // inflow
				// for inflow, stream inside
				// except: in source these elements are constant
				for (int k = 0; k < 9; k++) {
					if (k == 1 || k == 5 || k == 8) {
						// attention : inflow can still be periodic like left upper corner
						ii = i + c[k][0];
						if (ii < 0)
							ii = Ny;
						if (ii > Ny)
							ii = 0;
						jj = j + c[k][1];
						if (jj < 0)
							jj = Nx;
						if (jj > Nx)
							jj = 0;
						fDummy[k][ii][jj] = f[k][i][j];
					}
				}
			} else if (state[i][j] == 4) { // outflow

				// for outflow, just do nothing with these cells
			}
		}
	}

	for (int n = 0; n < Nb; n++) {
		if (boundary[n].surrounded) {
			// do nothing
		} else {
			int i = boundary[n].i;
			int j = boundary[n].j;

			for (int m = 0; m < boundary[n].Nl; m++) {

				int k = boundary[n].link[m];
				ii = boundary[n].nodes[0][m];
				jj = boundary[n].nodes[1][m];

				fDummy[k][ii][jj] = f[k][i][j];
			}
		}
	}

	copyToFrom(f, fDummy, Ny, Nx);
}
