/*
@author: Sir0ga90
@version: 0.1
*/
//======================================================================//Includes
#include "Check_format.h"

//======================================================================//Function definitions
/*
check if file formats fits needed format
	in: is - input streem
	in: w_fill_from - vector of string from which wall will be filled,
		contain only wall strings		
*/
bool check_file_frmt(ifstream& is, Vecf& w_fill_from)
try{
	const short wl_sz_line = 0;
	Vecf f_strings;
	int hig = 0;
	int wid = 0;
	int block_num_id = 0;		  // index of block number val
	int block_num = 0;			  // number of block types
	int blocks_id = 0;			  // index of first block

	file_to_str_vec(is, f_strings);
	get_wall_size_str(f_strings.at(wl_sz_line), hig, wid);
	check_input_wall(f_strings, w_fill_from, hig, wid);
	block_num_id = hig + 1;
	block_num = check_block_num_line(f_strings.at(block_num_id));
	blocks_id = block_num_id + 1;						
	check_blk_typs(f_strings, blocks_id, block_num);
	
	is.close();					  //before reopennig

	return true;
}
catch (exception& e){
	cerr << "CHECK ERROR: " << e.what() << endl;
	system("pause");
}
//======================================================================//
/*
read string from streem
	in: is - input streem
*/
void read_str(ifstream& is){
	string s;

	s = get_str(is);
}

										//==============================//
string get_str(ifstream& ist){
	string s;
	getline(ist, s);
	return s;
}

//======================================================================//
/*
read first line, with sizes of wall, and check it according to the format
	in: s - string for line
	in: h - hight of main wall
	in: w - width of main wall
*/
void get_wall_size_str(string s, int& h, int& w){
	string::iterator it = s.begin();

	if (isdigit(*it)){
		w = chk_w_sz_loop(it, s);
	}
	else
		throw exception("Unexpected wall-width value\n");

	if (it >= s.end())
		throw exception("Not good matrix size input, only one parametr\n");
	else if (*it != ' ')
		throw exception("Unexpected symbol after wall-width\n");

	it++;
	if (isdigit(*it)){
		h = chk_w_sz_loop(it, s);
	}
	else
		throw exception("Unexpected wall-hight value\n");

	if (!isdigit(*it) || it + 1 != s.end()){			// if last num not a number or next char not the end of string
		throw exception("Unexpected end of matrix-size line\n");
	}
}

//======================================================================//
/*
take all digits for values of hight & width of wall
	in: it - iterator for going through the string with values
	in: s - string with values
*/
int chk_w_sz_loop(string::iterator& it, const string& s){
	int i = 0;
	string num;
	static int pos = false;

	for (; isdigit(*it) && it + 1 < s.end(); it++){				//it+1 for not go out of scope
		num.push_back(*it);
	}

	if (pos)						// check it wid or hig
		num.push_back(*it);
	else
		pos = true;

	return stoi(num);
}

//======================================================================//
/*
take strings from file & push it in vector
& check if file have empty lines before end
	in: is - input streem
	in: vec - vector to fill
*/
void file_to_str_vec(ifstream& is, Vecf& vec){
	string s;

	while (!is.eof()){
		s = get_str(is);

		if (s == "")
			throw exception("Unexpected clear string in file\n");

		vec.push_back(s);
	}//while (!is.eof())
}

//======================================================================//
/*
check string for wall lines
	in: vec - full input vector
	in: w_vec - vector only for wall lines
	in: h - hight of main wall
	in: w - width of main wall 
*/
void check_input_wall(Vecf& vec, Vecf& w_vec, int h, int w){
	int start_index = 1;

	for (int i = start_index; i <start_index + h; i++){
		check_w_line(vec.at(i), w);
		w_vec.push_back( vec.at(i) );		 //fill vector of strings only for wall
	}
}

//======================================================================//
/*
check if width of line is according to wall width
	in: s - line
	in: w - width of main wall 
*/
void check_w_line(string& s, int w){
	if (s.size() < w || s.size() > w)
		throw exception("Wrong wall-line input\n");
	else
		return;
}

//======================================================================//
/*
check for correctnes of input number of block types
	in: s - string with ONE number
*/
int check_block_num_line(string& s){
	int block_type_num = 0;
	string::iterator it = s.begin();

	if (isdigit(*it)){
		block_type_num = chk_blk_num_loop(it, s);
	}
	else
		throw exception("Unexpected number of blocks\n");

	if (!isdigit(*it) || it + 1 != s.end()){			// if last num not a number or next char not the end of string
		throw exception("Unexpected number of block types value\n");
	}

	return block_type_num;
}

//======================================================================//
/*
take all digits for value of block types number
	in: it - iterator for going through the string with values
	out: number of block types
*/
int chk_blk_num_loop(string::iterator& it, const string& s){
	string num;
	static int pos = false;

	for (; isdigit(*it) && it + 1 < s.end(); it++){				//it+1 for not go out of scope
		num.push_back(*it);
	}
	num.push_back(*it);
	
	return stoi(num);
}

//======================================================================//
/*
check blocks for correctnes of input h & w & num of block types
	in: vec - input vector
	in: begin - index of first block
	in: block_num
*/
void check_blk_typs(Vecf& vec, int begin, int block_num){
	int i = begin;

	for (; i < vec.size(); i++){
		if (i >= begin + block_num)					   // greater number of block types
			throw exception("Unexpected end of file\n  \
	Check number of blocks");
		check_blk_typ(vec.at(i));
	}//for (; i < vec.size(); i++)

	if (i < begin + block_num)					   // check for less number of block types
		throw exception("Real number of block-types less then declared\n");
}

//======================================================================//
/*
check if all block parametrs is on their place
	in: s - string with block parameters
*/
void check_blk_typ(string s){
	int h = 0;
	int w = 0;
	int n = 0;
	string::iterator it = s.begin();

	if (isdigit(*it)){
		w = chk_blk_sz_n_loop(it, s);				//wid
	}
	else
		throw exception("Unexpected block-width value\n");

	if (it >= s.end())
		throw exception("Not good block size input, only one parametr\n");
	else if (*it != ' ')
		throw exception("Unexpected symbol after block-width\n");

	it++;
	if (isdigit(*it)){
		h = chk_blk_sz_n_loop(it, s);			  //hig
	}
	else
		throw exception("Unexpected block-hight value\n");

	if (it >= s.end())
		throw exception("Not good block size input, only two parametrs\n");
	else if (*it != ' ')
		throw exception("Unexpected symbol after block-hight\n");
	it++;
	if (isdigit(*it)){
		n = chk_blk_sz_n_loop(it, s);			  //num
	}
	else
		throw exception("Unexpected block number value\n");

	if (!isdigit(*it) || it + 1 != s.end()){			// if last num not a number or next char not the end of string
		throw exception("Unexpected end of block type line\n");
	}
}

//======================================================================//
/*
take all digits for value of block types number
	in: it - iterator for going through the string with values
	out:switch(pos)
			case 0 -> width of block
			case 1 -> hight of block
			case 2 -> number of this type blocks
*/
int chk_blk_sz_n_loop(string::iterator& it, const string& s){			//sz - size; n - number
	int i = 0;
	string num;
	static int pos = 0;

	for (; isdigit(*it) && it + 1 < s.end(); it++){				//it+1 for not go out of scope
		num.push_back(*it);
	}

	switch (pos){
	case 0:
		pos++;
		break;
	case 1:
		num.push_back(*it);
		pos++;
		break;
	case 2:
		num.push_back(*it);
		break;
	default:
		pos = 0;
		break;
	}

	return stoi(num);
}
