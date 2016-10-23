/*
@author: Sir0ga90
@version: 0.1
*/

//======================================================================//Includes
#include "Fill.h"

using namespace std;

//======================================================================//
/*
find brick in the wall
scan each line from up to dowm, from left to the right
*/
Index find_brick(Wall& wall){
	Index brick_pos(0, 0);
	for (p_size i = 0; i < wall.get_hig(); i++){		 	//increment line number

		for (p_size j = 0; j < wall.get_wid(); j++){		//increment raw number
			if (wall.form.at(i).at(j) == BRICK){
				brick_pos.i = i;
				brick_pos.j = j;
				return brick_pos;
			}
		}

	}
	return brick_pos;
}

//======================================================================//
/*
fill wall with all types of blocks
	in: store - block store
	in: wall - main wall
*/
bool fill_wall(vector<Block>& store, Wall& wall){
	Block& biggest = store.at(MAX_AREA_BLK_ID);
	Index pos;

	for (; store.size() > 0; ){
		pos = find_brick(wall);

		fit_max_block(pos, biggest, wall);
		take_type_block(store);
	}

	if (check_wall(wall)) return true;
	else return false;
}

//======================================================================//
/*
fit max-area block to the wall,
by running over all positions of wall
	in: pos - position of first finding block
	in: biggest - biggest-area type of blocks
	in: wall - filled wall
*/
void fit_max_block(Index pos, Block& biggest, Wall& wall){
	Index local_pos = pos;
	bool not_wall_end = true;

	while (not_wall_end){
		if (try_to_fit_block(pos, biggest, wall)){			 //try to fit the block in init position
			if_block_fit(local_pos, biggest, wall);
			not_wall_end = increment_position(pos, wall);
			return;
		}
		else if (try_to_fit_rotate(pos, biggest, wall)){	 //try to fit in rotate position
			if_block_fit(local_pos, biggest, wall);
			not_wall_end = increment_position(pos, wall);
			return;
		}
		else {
			not_wall_end = increment_position(pos, wall);
			local_pos = pos;							//sync local pos to new val of start index
		}
	}//while (not_wall_end)

}

//======================================================================//
/* 
try to fit the biggest-area block from block storage to the wall
	in: pos - index of first block
	in: blk - biggest area block
	in: wall - main wall
*/
bool try_to_fit_block(Index pos, Block& blk, Wall& wall){
	int line_cnt = 1;				   //1 line was already found

	if (check_d_line_bound(pos, blk, wall) == false)
		return false;

	for (; check_fit_in_line(pos, blk, wall); line_cnt++){
		if (line_cnt == blk.get_hig())
			return true;
	}
	return false;
}
//======================================================================//
/*
check if block width could be fit in part of wall-line
	in: pos - index of first brick
	in: blk - biggest area block
	in: wall - main wall
*/
bool check_fit_in_line(Index pos, Block& blk, Wall& wall){
	int cell_cnt = 1;				  // for counting of sequens of bricks

	if (check_r_line_bound(pos, blk, wall) == false)
		return false;

	for (; (wall.get_cell(pos) == BRICK); pos.j++, cell_cnt++){
		if (cell_cnt == blk.get_wid())
			return true;
	}
	return false;
}

//======================================================================//
/*
increment start position for installin one type block
	in: pos - previous position
	in: wall - main wall
*/
bool increment_position(Index& pos, Wall& wall){
	if (pos.j < wall.get_wid() - 1){
		pos.j++;						  // if in line -> incremetn row index
		return true;
	}
	else 
		if (pos.i < wall.get_hig() - 1){   // if line is over -> incremetn line index
			pos.i++;						   
			pos.j = 0;					   // and zero out row index
			return true;
		}
		else{
			return false;					 //if end of wall
		}		
}

//======================================================================//
/*
delete fitted block from the wall
	in: pos - start pos of block in the wall
	in: wall - main wall
	in: h - hight of block
	in: w - width of block
*/
void delete_wall_brick(Index pos, Wall& wall, p_size h, p_size w){
	p_size start = pos.i;

	for (; pos.i < start + h; pos.i++){
		del_line(wall, pos, w);
	}
}
												//======================//
/*
delete one line of block from line in wall
	in: wall - main wall
	in: pos - start pos of line of block in the wall
	in: w - width of block
*/
void del_line(Wall& wall, Index pos, p_size w){
	p_size start = pos.j;

	for (; pos.j < start + w; pos.j++){
		wall.zero_out_cell(pos);
	}
}
//======================================================================//
/* 
check if block could be fit in wall width bounds from position pos
	in: pos - index from which begin checking
	in: blk - biggest area block
	in: wall - main wall
	r-> right side of wall
*/	
bool check_r_line_bound(Index pos, Block& blk, Wall& wall){
	if ( pos.j + blk.get_wid() > wall.get_wid() ){
		return false;
	}
	else
		return true;
}

//======================================================================//
/*
check if block could be fit in wall hight bounds from position pos
	in: pos - index from which begin checking
	in: blk - biggest area block
	in: wall - main wall
	d-> down side of wall
*/
bool check_d_line_bound(Index pos, Block& blk, Wall& wall){
	if (pos.i + blk.get_hig() > wall.get_hig()){
		return false;
	}
	else
		return true;
}

//======================================================================//
/*
take next block in sequence	of blocks
or take next-type block
	in: store - block storage
*/
void take_type_block(vector<Block>& store){
	store.at(MAX_AREA_BLK_ID).dec_num();
	if (store.at(MAX_AREA_BLK_ID).get_num() < 1)
		take_next_type_block(store);
}

//======================================================================//
/*
take next-type block in store of blocks
	in: store - block storage
*/
void take_next_type_block(vector<Block>& store){
	store.erase(store.begin());			 // delete unusable biggest-area block
}

//======================================================================//
/*
check if wall have bricks or only holes
	in: wall - main wall
*/
bool check_wall(Wall& wall){
	Index pos;
	for (; pos.i < wall.get_hig(); pos.i++){
		if (check_line(wall, pos) == false)
			return false;
	}
	return true;
}

												//======================//
/*
check if wall have bricks or only holes
	in: wall - main wall
	in: pos - used only 'j' - mean width of block type
*/
bool check_line(Wall& wall, Index& pos){
	for (; pos.j < wall.get_wid(); pos.j++){
		if (wall.get_cell(pos) == BRICK)
			return false;
	}
	pos.j = 0;
	return true;
}

//======================================================================//
/*
try to fit in wall but with exchanged W & H
	
*/
bool try_to_fit_rotate(Index pos, Block& blk, Wall& wall){
	blk.rotate();
	if(try_to_fit_block(pos, blk, wall))
		return true;
	else return false;
}

//======================================================================//
/*
delete brick from wall, it's known that it fit
	in: pos - start position of block
	in: biggest - biggext-area block type
*/
void if_block_fit(Index pos, Block& biggest, Wall& wall){
	delete_wall_brick(pos, wall,
					  biggest.get_hig(),
					  biggest.get_wid());
}