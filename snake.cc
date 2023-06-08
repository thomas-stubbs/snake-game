#include "snake.h"
#include <cstring> //memset

Snake::Snake(){
	memset(screen_buffer, 0, 65536); //clear the screen buffer array
	current_direction = kGpioUp;
	direction_increment = increments[current_direction];
	growing = 0;
	pellet_location = 0;
	head_index = 0;
	tail_index = 256;
	screen_buffer[256] = 255; //for testing purposes
}

Snake::~Snake(){}

void Snake::spawn_snake(){
	memset(screen_buffer, 0, 65536);
	uint8_t no_edges;
	do{
		head_index = rand()%64508 + 514; //random number between 514 & 65021 (excludes top and bottom rows)
		no_edges = head_index%256;
	}while(no_edges < 2 || no_edges > 253); //excludes first two and last two columns
	current_direction = static_cast<gpio_t>(rand()%4);
	direction_increment = increments[current_direction];
	tail_index = ((-1)*direction_increment)+head_index; //place tail adjacent to head, opposite to the direction of travel
	screen_buffer[head_index] = 255;
	screen_buffer[tail_index] = 255-current_direction; //encoding direction to next tail pixel in the color intensity
	return;
}

void Snake::spawn_pellet(){
	do{
		pellet_location = rand()%65536;
	}while(screen_buffer[pellet_location]);
	return;
}

bool Snake::snake_movement(){
	int next_head = head_index + direction_increment;
	if(next_head < 0 || next_head > 65535 || (current_direction == kGpioLeft && next_head%256 == 255) || (current_direction == kGpioRight && next_head%256 == 0) || screen_buffer[next_head]){ //all conditions for game over: hitting the top, bottom, left, or right edges, or hitting part of the existing snake body
		game_over();
		return false;
	}

	//move head
	screen_buffer[head_index] = 255-current_direction; // encode direction of next pixel in the color intensity
	head_index = next_head;
	screen_buffer[head_index] = 255;
	
	//move tail
	if(growing){ //do not move tail
		growing--;
	}else{
		uint8_t dir_to_next = 255 - screen_buffer[tail_index]; //retrieves direction to next snake pixel using color intensity encoding
		screen_buffer[tail_index] = 0; //whiten previous tail
		tail_index += increments[dir_to_next];
	}

	//check if head intersects a pellet
	if(next_head == pellet_location){ //this movement consumes a pellet
		growing += 3;
		do{
			spawn_pellet();
		}while(pellet_location == next_head); //in case spawn_pellet spawns a pellet to where the head is about to move to
	}

	return true;
}

void Snake::game_over(){
	memset(screen_buffer, 0, 65536);
	UpdateScreen(screen_buffer); //show a clear screen
	
	//verticals
	for(uint8_t row=10; row<=118; row++){
		screen_buffer[(256*row)+10] = 255; // first | of the G
		screen_buffer[(256*row)+74] = 255; // first | of the A
		screen_buffer[(256*row)+118] = 255; // second | of the A
		screen_buffer[(256*row)+133] = 255; // first | of the M
		screen_buffer[(256*row)+187] = 255; // second | of the M
		screen_buffer[(256*row)+202] = 255; // | of the E
		if(row>=64){
			screen_buffer[(256*row)+54] = 255; // second | of the G (half height)
		}
	}
	for(uint8_t row=138; row<=246; row++){
		screen_buffer[(256*row)+10] = 255; // first | of the O
		screen_buffer[(256*row)+54] = 255; // second | of the O
		screen_buffer[(256*row)+138] = 255; // | of the E
		screen_buffer[(256*row)+202] = 255; // first | of the R
		if(row<=192){
			screen_buffer[(256*row)+246] = 255; // second | of the R (half height)
		}
	}
	
	//horiontals
	for(uint8_t col=10; col<=54; col++){
		screen_buffer[(256*10)+col] = 255; // top - of the G
		screen_buffer[(256*118)+col] = 255; // bottom - of the G
		screen_buffer[(256*138)+col] = 255; // top - of the O
		screen_buffer[(256*246)+col] = 255; // bottom - of the O
		if(col>=32){
			screen_buffer[(256*64)+col] = 255; // middle - of the G (half length)
		}
	}
	for(uint8_t col=74; col<=118; col++){
		screen_buffer[(256*10)+col] = 255; //top - of the A
		screen_buffer[(256*64)+col] = 255; //middle - of the A
	}
	for(uint8_t col=138; col <=182; col++){
		screen_buffer[(256*138)+col] = 255; //top - of the E
		screen_buffer[(256*192)+col] = 255; //middle - of the E
		screen_buffer[(256*246)+col] = 255; //bottom - of the E
	}
	for(uint8_t col=202; col <=246; col++){
		screen_buffer[(256*10)+col] = 255; //top - of the E
		screen_buffer[(256*64)+col] = 255; //middle - of the E
		screen_buffer[(256*118)+col] = 255; //bottom - of the E
		screen_buffer[(256*138)+col] = 255; //top - of the R
		screen_buffer[(256*138)+col] = 255; //middle - of the R
	}

	//diagonals

	uint8_t col_offset = 1;
	uint8_t offset_counter = 0;
	for(uint8_t row=10; row<=118; row++){
		screen_buffer[(256*row)+133+col_offset] = 255; // \ of the M
		screen_buffer[(256*row)+187-col_offset] = 255; // / of the M
		offset_counter++;
		if(offset_counter == 4){
			col_offset++;
			offset_counter = 0;
		}
	}
	col_offset = 1;
	offset_counter = 0;
	for(uint8_t row=138; row<=246; row++){
		screen_buffer[(256*row)+69+col_offset] = 255; // \ of the V
		screen_buffer[(256*row)+123-col_offset] = 255; // / of the V
		offset_counter++;
		if(offset_counter == 4){
			col_offset++;
			offset_counter = 0;
		}
	}
	col_offset = 1;
	offset_counter = 0;
	for(uint8_t row = 192; row <=246; row++){
		screen_buffer[(256*row)+219+col_offset] = 255; // \ of the R (half height)
		offset_counter++;
		if(offset_counter == 2){
			col_offset++;
			offset_counter = 0;
		}
	}

	//display GAME OVER
	UpdateScreen(screen_buffer);
	return;
}
gpio_t Snake::get_direction(){
	return current_direction;
}

void Snake::set_direction(gpio_t dir){
	//check if selected direction is same (no action needed) or opposite (not supported) as current direction
	if(current_direction == dir || direction_increment == (-1)*increments[dir]){
		return;
	}

	//change direction
	current_direction = dir;
	direction_increment = increments[current_direction];
	return;
}

void Snake::update_screen(){
	screen_buffer[pellet_location] = 255;
	UpdateScreen(screen_buffer);
	screen_buffer[pellet_location] = 0; //remove pellet from screen buffer so snake_movement logic doesn't break
	return;
}
