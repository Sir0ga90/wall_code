/*
@author: Sir0ga90
@version: 0.1

//======================================================================//

	Form of input is (ONLY FROM FILE):
		1: width and height of wall's shape matrix ­ two positive integers W and H separated by space
		   on their own line.
		2: wall's shape matrix ­ H strings each of length W, formed just of '1' - BRICK and '0' - HOLE
		   symbols with every string on its own line.
		3: the count of bricks' sorts ­ the positive integer C.
		4: list of bricks ­ C lines each containing three positive integers separated by space ­ width of
		   brick, height of brick and count of such bricks in the set.
	EXAMPLE:
						6 3
						101101
						111111
						111111
						4
						1 1 4
						2 1 6
						1 3 1
						3 4 5

*/
//======================================================================//
#pragma once

//======================================================================//Includes
#include <iostream>
#include <fstream>
#include <string>

#include "Construction.h"
#include "Block.h"
#include "Wall.h"
#include "Check_format.h"

using namespace std;
//======================================================================//Function prototypes
string prompt(void);
inline void check_input_file(ifstream&);
void wall_input(istream& is, Wall& wall, Vecf& wall_vec, string& filename);
void fill_wall_from_vec(Wall& wall, Vecf& wall_vec);
inline void fill_wall(istream& is, Wall& wall);

void block_input(istream& is, vector<Block> & store);
inline void fill_block_storage(istream& is, vector<Block>& store, uint16_t type_num);
void sort_block_storage(vector<Block>& blocks);

void kill_input(istream & is, p_size h);

void common_input(Wall& my_wall, vector<Block>& blocks, string &openfile);
