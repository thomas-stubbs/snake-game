#include "main/snake.h"
#include <time.h>

int main(){
	//overhead tasks
	srand(time(NULL));
	Snake snake;
	snake.spawn_snake();
	snake.spawn_pellet();
	snake.update_screen();
	unsigned int clock = GetTicks()/500000;
	unsigned int ticks = GetTicks()%500000;

	//let's play

	while(true){
		while(snake.snake_movement()){

			//show movement on screen
			snake.update_screen();

			//ensure game loop takes 500ms (game clock) +- 40us for inner for loop. continually check GPIO to poll an instantaneous button press
			while(GetTicks()/500000 == clock || GetTicks()%500000 < ticks){
				for(int i=0; i<=3; i++){
					if(GetGpio(static_cast<gpio_t>(i))){
						snake.set_direction(static_cast<gpio_t>(i));
					}
				}
			}

			//increment clock and check for ineger overflow
			clock++;
			if(clock == 17179){
				clock = 0;
			}
		}
		while(true){ //if snake_movement results in game_over
			if(GetGpio(kGpioUp) || GetGpio(kGpioDown) || GetGpio(kGpioLeft) || GetGpio(kGpioRight)){
				break;
			}
		}
		snake.spawn_snake();
		snake.spawn_pellet();
		snake.update_screen();
		clock = GetTicks()/500000;
		ticks = GetTicks()%500000;
	}
	return 0;
}
