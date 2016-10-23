/*
@author: Sir0ga90
@version: 0.1
*/

#include "Construction.h"

//======================================================================//Constructors
Construction::Construction() :wid{0}, hig{0}{}

//======================================================================//
Construction::Construction(p_size lines, p_size raws){
	hig = lines;
	wid = raws;
}

//======================================================================//
Construction::~Construction(){}					 //destructor
//======================================================================//Member func's
