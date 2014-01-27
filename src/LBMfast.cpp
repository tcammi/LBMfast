//============================================================================
// Name        : LBMfast.cpp
// Author      : Thomas Camminady
// Version     :
// Copyright   : 
// Description : Main part of LBM solver in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cmath>
#include <ctime>
#include <unistd.h>
#include <sys/time.h>
#include "init.h"
#include "helper.h"
#include "structs.h"
#include "lbmSteps.h"
#include "grid.h"

using namespace std;

int main() {
	timeval a;
	gettimeofday(&a, 0);
	timeval b;
	int Nx = 50; // dim may be overwritten when reading from file
	int Ny = 50;
	int Niter = 0;
	double cs = 1. / sqrt(3.);
	double omega = 1.25;
	double w[9] = { 4. / 9., 1. / 9., 1. / 9., 1. / 9., 1. / 9., 1. / 36., 1.
			/ 36., 1. / 36., 1. / 36. };

	int c[9][2] = { { 0, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 }, { 1, 0 },
			{ -1, 1 }, { -1, -1 }, { 1, -1 }, { 1, 1 } };

	int mirror[9] = { 0, 3, 4, 1, 2, 7, 8, 5, 6 };
	int Nb;
	double *** f;
	double *** fEQ;
	double *** fDummy;
	double ** v, **u, **rho;
	int NiterMax = 1000;
	int** state;
	solid* boundary;

	bool fromFile = false;

	char infolder[] = "input/";
	char inid[] = "lambo2.txt";
	char outfolder[] = "output/";
	char outid[] = "circleNewVersion";

	if (fromFile) {
		readGridFromFile(state, Ny, Nx, infolder, inid);

	} else {
		initGrid(state, Ny, Nx);
	}
	initF(f, fEQ, fDummy, Ny, Nx);
	initFlow(v, u, rho, Ny, Nx);

	gridGeneration(boundary, Nb, state, Ny, Nx, c);
	computeEQ(fEQ, v, u, rho, c, w, cs, Ny, Nx);
	copyToFrom(f, fEQ, Ny, Nx);

	cout << "Ny = " << Ny << " Nx = " << Nx <<  endl;
	int Fluid = 0;
	int Wall = 0;
	int Surr = 0;
	for (int i=0;i<Ny+1;i++){
		for (int j=0;j<Nx+1;j++){
			if (state[i][j]==1) Fluid++;
			if (state[i][j]==0) Wall++;
			if (state[i][j]==-1) Surr++;


		}
	}
	cout << "N fluid =  " << Fluid << "\tN solid = " << Wall<< "\tN surrounded = "<< Surr << endl;
	cout << "(Nx+1)*(Ny+1) = " << (Nx+1)*(Ny+1) << " Sum of line above = " << Fluid+Wall+Surr << endl;
	cout << "NiterMax = " << NiterMax << endl;
	while (true && Niter <= NiterMax) {
		if (Niter % 50 == 0)
			cout << "Number of iterations = " << Niter << endl;
		computeMacro(f, v, u, rho, state, c, Ny, Nx);
		computeEQ(fEQ, v, u, rho, c, w, cs, Ny, Nx);
		collision(f, fEQ, state, omega, Ny, Nx);
		source(f,state, omega, cs, Ny, Nx);
		applyBC(f, fDummy, state, boundary, mirror, Nb, Ny, Nx);
		streaming(f, fDummy, boundary, Nb, state, c, Ny, Nx);
		Niter++;

	}
	gettimeofday(&b, 0);
	cout << "Elapsed time = " << (b.tv_sec - a.tv_sec) << " seconds." << endl;

	writeOutput(v, u, rho, state, Ny, Nx, outfolder, outid);
	cout << "Finished!" << endl;

	return 0;
}

