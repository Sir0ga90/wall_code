/*
@author: Sir0ga90
@version: 0.1
*/

#include "Wall.h"

//======================================================================//Constructors
Wall::Wall() : form{0}{}

Wall::Wall(p_size h, p_size w){
	hig = h;
	wid = w;
}

Wall::~Wall(){}

//======================================================================//
Index::Index(int raws, int lines){
	i = raws;
	j = lines;
}

//======================================================================//Member func's
void Wall::set_size(p_size h, p_size w){
	hig = h;
	wid = w;
}
//======================================================================//
/*
 return cell-value by index
	in: ind - index of needed cell
 */
Cell Wall::get_cell(Index ind){
	int first_ln = 0;				// line for taking wide	of wall

	if (ind.i > form.size() ||
		ind.j > form.at(first_ln).size())
		throw exception("get_cell(): cell not in bound of wall\n");

	return form.at(ind.i).at(ind.j);
}
//======================================================================//
void Wall::zero_out_cell(Index ind){
	int first_ln = 0;				// line for taking width of wall

	if (ind.i > form.size() ||
		ind.j > form.at(first_ln).size())
		throw exception("zero_out_cell(): not in bound of wall\n");

	form.at(ind.i).at(ind.j) = HOLE;
}
