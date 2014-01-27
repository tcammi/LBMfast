/*
 * structs.h
 *
 *  Created on: Jan 24, 2014
 *      Author: tc
 */

#ifndef STRUCTS_H_
#define STRUCTS_H_

struct solid {

	int i, j;
	int Nl;
	int * link;
	int id;
	int ** nodes;
	bool surrounded;
};

#endif /* STRUCTS_H_ */
