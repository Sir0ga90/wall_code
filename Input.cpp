/*
@author: Sir0ga90
@version: 0.2
	added: 
		-fill_wall_from_vec();
		-kill_input();
	excluded:
		-fill_wall();
*/
//======================================================================//
#include "Input.h"

//======================================================================//Function definitions
//promt to enter filename
string prompt(void){
	string filename;
	cout << "Enter file name with full path\n";
	cin >> filename;
	return filename;
}

//======================================================================//
/*
check that file is good
*/

inline void check_input_file(ifstream& ist){
	if (ist.good())	return;
	else 
		throw exception("Can't find or open the file\n");
}

//======================================================================//
/*
take W & H, & fill the wall
	in: is - input streem
	in: wall - which would be filled
	in: filename
*/
void wall_input(istream& is, Wall& wall, Vecf& wall_vec, string& filename){
	p_size h, w;		// h for hight, w for width
	is >> w >> h;
	wall.set_size(h, w);
	fill_wall_from_vec(wall, wall_vec);
}

//======================================================================//
/*
fill the wall from vector of strings
	in: wall - main wall
	in: wall_vec - vector of strings
*/
void fill_wall_from_vec(Wall& wall, Vecf& wall_vec){
	int cell;
	int ascii_zero = 48;

	for (uint32_t i = 0; i < wall.get_hig(); i++){
		wall.form.push_back(vector<Cell>());

		for (uint32_t j = 0; j < wall.get_wid(); j++){		//cycle for filling vector<Cell> in width
			cell = wall_vec.at(i).at(j) - ascii_zero;
			if (cell < HOLE || cell > BRICK)
				throw exception("Incorrect wall element. Please check & try again.\n");
			wall.form.at(i).push_back((Cell)cell);
		}

	}
}

//======================================================================//
/*
check & take number of block types & fill the block storage
	in: is - input streem
	in: store - block storage
*/
void block_input(istream& is, vector<Block> & store){
	uint16_t block_num = 0;
	is >> block_num;

	if (block_num > MAX_BLOCK_NUM)
		throw exception("Too mach block types. Please decrease it.\n");

	if (block_num < 1)
		throw exception("Number of block's must be a positive value. Please check it.\n");

	fill_block_storage(is, store, block_num);
}

//======================================================================//
/*
fill the block storage according to number of types of blocks
	in: is - input streem
	in: store - block storage
	in: type_num - number of types of blocks
*/
inline void fill_block_storage(istream& is, vector<Block>& store, uint16_t type_num){
	Block input_block;
	for (uint32_t i = 0; i < type_num; i++){		//cycle for filling vector<Block_storage> 
		is >> input_block;							//by types of blocks
		store.push_back(input_block);
	}
}

//======================================================================//
/*
union of inputs
	in: my_wall - which would be filled
	in: store - block storage
	in: openfile - name of file
*/
void common_input(Wall& my_wall, vector<Block>& blocks, string& openfile){
	ifstream is;
	is.open(openfile);
	check_input_file(is);
	Vecf wall_file;

	if (check_file_frmt(is, wall_file)){
		is.open(openfile);			// was closed after all checking funcs
		wall_input(is, my_wall, wall_file, openfile);
		
		kill_input(is, my_wall.form.size());

		block_input(is, blocks);
		sort_block_storage(blocks);
	}
	
	is.close();
}
//======================================================================//
/*
sort vector of blocks according to the biggest area:
biggest-area type will be on zero index
	in:	blocks - block storage
	Comp_a() - predicate for sortinting function
*/
void sort_block_storage(vector<Block>& blocks){
	sort(blocks.begin(), blocks.end(), Comp_a());
}

//======================================================================//
/*
pass wall-lines from input, because they are redundant
& wall filled from vector
	in: is - input stream from file
	in: h - hight of main wall
*/
void kill_input(istream& is, p_size h){
	int buf = 0;
	for (int i = 0; i < h; i++){
		is >> buf;
	}
}
