/*
 * helper.cpp
 *
 *  Created on: Jan 24, 2014
 *      Author: tc
 */
#include "helper.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
using namespace std;

double negMod(int a, int b) {
	return (a % b + b) % b;
}

void copyToFrom(double***&A, double***B, int Ny, int Nx) {
	for (int k = 0; k < 9; k++) {
		for (int i = 0; i < Ny + 1; i++) {
			for (int j = 0; j < Nx + 1; j++) {
				A[k][i][j] = B[k][i][j];
			}
		}
	}

}

void printMatrix(double** A, int Ny, int Nx) {
	cout << endl;
	for (int i = 0; i < Ny + 1; i++) {
		for (int j = 0; j < Nx + 1; j++) {
			cout << A[i][j] << " ";
		}
		cout << endl;
	}
}
void printMatrix(double*** A, int k, int Ny, int Nx) {
	cout << endl;
	for (int i = 0; i < Ny + 1; i++) {
		for (int j = 0; j < Nx + 1; j++) {
			cout << A[k][i][j] << " ";
		}
		cout << endl;
	}
}
void printMatrix(int** A, int Ny, int Nx) {
	cout << endl;
	for (int i = 0; i < Ny + 1; i++) {
		for (int j = 0; j < Nx + 1; j++) {
			cout << A[i][j] << " ";
		}
		cout << endl;
	}
}

void printNl(solid* s, int N) {
	cout << N << endl;
	for (int i = 0; i < N; i++) {
		cout << s[i].Nl << " " << s[i].i << " " << s[i].j << endl;
	}

	cout << " neighbors " << endl;
	int id = 0;
	cout << "i=" << s[id].i << " " << "j=" << s[id].j << endl;
	for (int i = 0; i < s[id].Nl; i++) {
		cout << s[id].link[i] << " " << s[id].nodes[0][i] << " "
				<< s[id].nodes[1][i] << endl;

	}
}
void printSolid(solid* boundary, int Nb) {
	for (int i = 0; i < Nb; i++) {
		cout << endl;
		cout << "i=" << boundary[i].i << " j=" << boundary[i].j << " nl="
				<< boundary[i].Nl << endl;
		for (int k = 0; k < boundary[i].Nl; k++) {
			cout << boundary[i].link[k] << " " << boundary[i].nodes[0][k] << " "
					<< boundary[i].nodes[1][k] << endl;
		}
	}
}

void writeOutput(double** v, double**u, double**rho, int**state, int Ny, int Nx,
		char folder[50], char id[50]) {
	ofstream ofv, ofu, ofrho, ofgrid;
	char uc[100];
	char vc[100];
	char rhoc[100];
	char gridc[100];
	strcpy(vc, folder);
	strcpy(uc, folder);
	strcpy(rhoc, folder);
	strcpy(gridc, folder);

	strcat(vc, id);
	strcat(uc, id);
	strcat(rhoc, id);
	strcat(gridc, id);

	strcat(vc, "v.txt");
	strcat(uc, "u.txt");
	strcat(rhoc, "rho.txt");
	strcat(gridc, "grid.txt");



	ofv.open(vc);
	ofu.open(uc);
	ofrho.open(rhoc);
	ofgrid.open(gridc);

	for (int i = 0; i < Ny + 1; i++) {
		for (int j = 0; j < Nx + 1; j++) {
			ofv << v[i][j] << " ";
			ofu << u[i][j] << " ";
			ofrho << rho[i][j] << " ";
			ofgrid << state[i][j] << " ";
		}
		ofv << endl;
		ofu << endl;
		ofrho << endl;
		ofgrid << endl;
	}
	ofv.close();
	ofu.close();
	ofrho.close();
	ofgrid.close();

}

