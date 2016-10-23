/*
@author: Sir0ga90
@version: 0.1

//======================================================================//
	Wall - this is a rectangular matrix of '0'->"HOLE" & '1' -> "BRICK", 
	for example, wall 9*3 (W*H):
					110010011
					111111111
					000010000

	Matrix is a vector of vectors.
*/

#pragma once

//======================================================================//
#include "Construction.h"
#include <vector>

using namespace std;
//======================================================================//Constants 
const int MAX_MATRIX = 100;	   //max size of hight & width parametrs of matrix

//======================================================================//Typedefine's
typedef enum{					   //enum for matrix cells
	HOLE,		//0
	BRICK		//1
} Cell;

typedef vector<Cell> Line;			//type for matrix lines
typedef vector<Line> Wall_form;		//type for matrix

//======================================================================//
struct Index{							   //struct for indexing of Wall
	int i = 0;
	int j = 0;

	Index(int raws, int lines);
	Index() :i{0}, j{0}{}
};

//======================================================================//
class Wall :public Construction{
public:
	Wall_form form;
	void set_size(p_size h, p_size w);
	Cell get_cell(Index);
	void zero_out_cell(Index);

	Wall();
	Wall(p_size, p_size);			   //constructor with sizes
	~Wall();
};
