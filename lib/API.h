#ifndef API_H
#define API_H

#include <stdlib.h>

enum gpio_t {
  kGpioUp = 0,
  kGpioDown = 1,
  kGpioLeft = 2,
  kGpioRight = 3
};

/**
This function will sample the current instantaneous state of the GPIO pin when called.  It will return true if the button is pressed, and false otherwise.  This function takes 10 microseconds to complete.  Note that this switch is implemented as a raw push-button with no hardware filtering.
*/
bool GetGpio(gpio_t direction);

/**
This function will take a pointer to a 65536 byte array which will update the state of the screen based on the values in the array.  Each pixel can take a grey-scale value of 0 (white) to 255 (black).  This function takes 10 milliseconds to complete.

EDIT: I am interpreting this function to read the screen_buffer from left to right, row by row. So, indices increment by 1 to go left to right and 256 to go top to bottom.
*/
void UpdateScreen(unsigned char *screen_buffer);

/**
This function will give you the current system time in 1 microsecond ticks.  Ints are 32-bits on this system.
*/
unsigned int GetTicks();


#endif
