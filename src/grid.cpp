/*
 * grid.cpp
 *
 *  Created on: Jan 26, 2014
 *      Author: tc
 */

#include "grid.h"
#include <stack>
#include <iostream>
#include <fstream>
#include <vector>
#include "helper.h"
#include <string.h>
#include <stdio.h>

using namespace std;

void initGrid(int** &state, int Ny, int Nx) {




	state = new int*[Ny + 1];
	for (int i = 0; i < Ny + 1; i++)
		state[i] = new int[Nx + 1];

	for (int i = 0; i < Ny + 1; i++) {
		for (int j = 0; j < Nx + 1; j++) {
			state[i][j] = 1; // initialize everything as flow
		}
	}

	for (int j = 0; j < Nx + 1; j++) { // lower & uppwer wall
		state[0][j] = 0;
		state[Ny][j] = 0;
	}
 //CIRCLE
	int midx, midy;
	midx = Nx / 2;
	midy = Ny / 2;

	int R = 100;

	for (int i = 0; i < Ny + 1; i++) {
		for (int j = 0; j < Nx + 1; j++) {
			if (((i - midy) * (i - midy) + (j - midx) * (j - midx)) < R * R) {
				state[i][j] = 0;
			}
		}
	}

}

void readGridFromFile(int **& state, int &Ny, int &Nx, char folder[50],char id[50]) {

	char filename[100];
	strcpy(filename,folder);
	strcat(filename,id);
	fstream fp;
	vector<int> numbers;
	int number;

	fp.open(filename);

	if (fp.is_open()) {
		while (fp >> number) {
			numbers.push_back(number);
			fp.get();

		}
	} else {
		cout << "File was not opened!" << endl;
	}

	Ny = numbers[0];
	Nx = numbers[1];
	int counter = 2;

	state = new int*[Ny + 1];
	for (int i = 0; i < Ny + 1; i++)
		state[i] = new int[Nx + 1];

	for (int i = 0; i < Ny + 1; i++) {
		for (int j = 0; j < Nx + 1; j++) {
			state[i][j] = numbers[counter];
			counter++;
		}
	}

	fp.close();

}

void gridGeneration(solid* & boundary, int &Nb, int** &state, int Ny, int Nx,
		int c[9][2]) {
	//
	//
	// if cell == liquid : state = 1
	// if cell == solid  : state = 0
	// if cell == solid &  surrounded : state = -1
	//

	Nb = 0;
	for (int i = 0; i < Ny + 1; i++) {
		for (int j = 0; j < Nx + 1; j++) {
			if (state[i][j] == 0)
				Nb++;
		}
	}

	boundary = new solid[Nb];

	int counter = 0;
	for (int i = 0; i < Ny + 1; i++) {
		for (int j = 0; j < Nx + 1; j++) {
			if (state[i][j] == 0) {
				solid s;
				s.i = i;
				s.j = j;
				s.id = counter;
				int Nl = 0;
				stack<int> klink;
				stack<int> ilink;
				stack<int> jlink;
				// check neighbors
				for (int k = 1; k < 9; k++) { // detect solid neighbors
					int ii, jj;

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

					if (state[ii][jj] == 1) {
						Nl++; // liquid neighbor
						klink.push(k);
						ilink.push(ii);
						jlink.push(jj);

					}
				}

				s.Nl = Nl;
				s.link = new int[Nl];
				s.nodes = new int*[2];
				s.nodes[0] = new int[Nl];
				s.nodes[1] = new int[Nl];
				for (int c = 0; c < Nl; c++) {

					s.nodes[0][c] = ilink.top();
					s.nodes[1][c] = jlink.top();
					s.link[c] = klink.top();
					ilink.pop();
					jlink.pop();
					klink.pop();

				}

				// is the node surrounded by solid nodes?

				if (Nl == 0) {

					s.surrounded = true;
					state[s.i][s.j] = -1;// id for surrounded node

				} else
					s.surrounded = false;

				boundary[counter] = s;
				counter++;
			}
		}
	}
}

