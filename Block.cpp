/*
@author: Sir0ga90
@version: 0.1
*/

#include "Block.h"

//======================================================================//Constructors
Block::Block() :num{0}, area{hig*wid}{}

//======================================================================//
Block::Block(uint32_t n, p_size h, p_size w){
	num = n;

	hig = h;
	check_hig(h);
	wid = w;
	check_wid(w);

	area = hig * wid;
}

//======================================================================//
Block::~Block(){}		 // destructor

//======================================================================//Member func's

/*	
rotate - change sizes of block from vertical to gorizontal
	orientation by interchanging it's width & hight
*/
void Block::rotate(){
	p_size temp = hig;
	hig = wid;
	wid = temp;
}

//======================================================================//
/*
decremet number of this type blocks
*/
void Block::dec_num(){
	num--;
}

//======================================================================//
istream &operator>>(istream  &is, Block &b){
	is >> b.wid >> b.hig >> b.num;

	check_wid(b.wid);
	check_hig(b.hig);

	b.area = b.hig*b.wid;
	return is;
}
//======================================================================//
void check_wid(p_size w){
	if (w < 1){
		throw exception("Hight of block less then 1\n");
	}
	else if (w > MAX_BLOCK_SIZE){
		throw exception("Hight of block not fit in block max sizes\n");		//wrong init prtection
	}
}

//======================================================================//
void check_hig(p_size h){
	if (h < 1){
		throw exception("Hight of block less then 1\n");
	}
	else if (h > MAX_BLOCK_SIZE){
		throw exception("Hight of block not fit in block max sizes\n");		//wrong init prtection
	}
};
