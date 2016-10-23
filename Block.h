/*
@author: Sir0ga90
@version: 0.1

//======================================================================//
	Block - is a virtual rectangular form and have only discrete height and width from 1 to 8,
	for example, block -> 3(hight) * 4(width):
							1111
							1111
							1111
	but in real it's just only hight & width
*/
#pragma once

//======================================================================//Includes
#include<algorithm>
#include <exception>

#include "Construction.h"

using namespace std;

//======================================================================//Constants 
const int MAX_BLOCK_SIZE = 8;		//max size of hight & width parametrs of block
const int MAX_BLOCK_NUM = 20;		//max number of types of blocks

//======================================================================//Class definition
class Block :public Construction{
public:
	Block();
	Block(uint32_t n, p_size h, p_size w);
	~Block();

	uint32_t get_num(){ return num; }
	p_size get_area(){ return area; }

	void rotate();				   
	void dec_num();				   //decrease number value of block-type

	friend istream &operator>>(istream& is, Block& b);
private:
	uint32_t num;		//number of one type block
	p_size area;		//area of block: needed for sorting
};

//======================================================================//Predicate
/*
Predicate for sort function
*/																		
struct Comp_a{
	bool operator()(Block a, Block b)
		const{ return a.get_area() > b.get_area(); }
};

//======================================================================//Helper functions
/*
Check correctness of input data
*/
void check_wid(p_size w);
void check_hig(p_size h);