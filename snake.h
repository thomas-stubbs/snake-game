#include "lib/API.h"

#ifndef SNAKE_H
#define SNAKE_H

class Snake{
	public:
		Snake();
		~Snake();
		void spawn_snake();
		void spawn_pellet();
		bool snake_movement(); //return false if game over
		void game_over();
		gpio_t get_direction();
		void set_direction(gpio_t dir);
		void update_screen();

	private:
		unsigned char screen_buffer [65536];
		gpio_t current_direction;
		const int increments[4] = {-256, 256, -1, 1};
		int direction_increment;
		unsigned int growing;
		size_t pellet_location;
		size_t head_index;
		size_t tail_index;
};

#endif
