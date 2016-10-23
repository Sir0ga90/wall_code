/*
@author: Sir0ga90
@version: 0.1

//======================================================================//
	Construction - base class for main type of classes in this programm:
		- Wall;
		- Block;
*/
#pragma once
//======================================================================//Includes
#include <iostream>

//======================================================================//Typedefine's
typedef uint32_t p_size;  //part size

//======================================================================//Class definition

class Construction{
public:
	Construction();
	Construction(p_size, p_size);
	~Construction();

	p_size get_hig(){ return hig; }
	p_size get_wid(){ return wid; }
protected:
	p_size hig;	   // hight (number of lines)
	p_size wid;	   // width (number of raws)
};
