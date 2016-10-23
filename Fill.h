/*
@author: Sir0ga90
@version: 0.1

//======================================================================//
Functions that meeded for finding out if set of blocks can fill the wall, or not

*/

#pragma once

//======================================================================//Includes
#include <exception>
#include <fstream>

#include "Construction.h"
#include "Block.h"
#include "Wall.h"
#include "Input.h"

using namespace std;
//======================================================================//Constants
const int MAX_AREA_BLK_ID = 0;

//======================================================================//
Index find_brick(Wall& wall);
bool try_to_fit_block(Index , Block& blk, Wall&);
bool fill_wall(vector<Block>& store, Wall & wall);
void fit_max_block(Index pos, Block& store, Wall& wall);
bool increment_position(Index& pos, Wall& wall);
void delete_wall_brick(Index pos, Wall& wall, p_size h, p_size w);
bool check_d_line_bound(Index pos, Block& blk, Wall& wall);
bool check_r_line_bound(Index pos, Block& blk, Wall& wall);
bool check_fit_in_line(Index pos, Block& blk, Wall& wall);
void take_type_block(vector<Block>& store);
void take_next_type_block(vector<Block>& store);
bool check_wall(Wall& wall);
bool check_line(Wall& wall, Index& pos);
void del_line(Wall& wall, Index pos, p_size w);
void print_wall(Wall& wall);
bool try_to_fit_rotate(Index pos, Block & blk, Wall & wall);
void if_block_fit(Index pos, Block & biggest, Wall & wall);
bool cmp(int cell_cnt, Block& blk);