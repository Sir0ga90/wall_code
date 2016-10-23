/*
@author: Sir0ga90
@version: 0.1

//======================================================================//

Check format of input file according to this
EXAMPLE:
3 3		|_int_space_int
101		|_int_int_int
111		|_int_int_int
111		|_int_int_int
4		|_int
1 1 4	|_int_space_int_space_int
2 1 6	|_int_space_int_space_int
1 3 1	|_int_space_int_space_int
3 4 5	|_int_space_int_space_int_!!!!NO NEW LINE HERE!!!!!


*/
//======================================================================//
#pragma once

//======================================================================//Includes
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Construction.h"
#include "Block.h"
#include "Wall.h"

//======================================================================//
typedef vector<string> Vecf;				 //vector of strings from file

//======================================================================//Function prototypes
void read_str(ifstream& is);
string get_str(ifstream& ss);
void get_wall_size_str(string s, int& h, int& w);
int chk_w_sz_loop(string::iterator& it, const string& s);
bool check_file_frmt(ifstream& is, Vecf& w_vec);
void file_to_str_vec(ifstream & is, Vecf & vec);
void check_input_wall(Vecf& vec, Vecf& w_vec, int h, int w);
void check_w_line(string & s, int w);
int check_block_num_line(string & s);
int chk_blk_num_loop(string::iterator & it, const string & s);
void check_blk_typs(Vecf & vec, int begin, int block_num);
void check_blk_typ(string s);
int chk_blk_sz_n_loop(string::iterator & it, const string & s);