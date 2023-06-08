#include "test/test.h"

void run_all(){
	test_snake_movement();
	return;
}

void test_snake_movement(){
	test_snake_movement_case1();
	test_snake_movement_case2();
	test_snake_movement_case3();
	test_snake_movement_case4();
	test_snake_movement_case5();
	test_snake_movement_case6();
	return;
}

void test_snake_movement_case1(){
	Snake t1;
	t1.set_direction(kGpioRight);
	bool actual = t1.snake_movement();
	assert_equals<bool>(true, actual, "moving the snake in upper left to the right");
	return;
}

void test_snake_movement_case2(){
	Snake t2;
	bool actual = t2.snake_movement();
	assert_equals<bool>(false, actual, "game over from snake in upper left moving up");
	return;
}

void test_snake_movement_case3(){
	Snake t3;
	t3.set_direction(kGpioLeft);
	bool actual = t3.snake_movement();
	assert_equals<bool>(false, actual, "game over from snake in upper left moving left");
	return;
}

void test_snake_movement_case4(){
	Snake t4;
	t4.set_direction(kGpioRight);
	t4.snake_movement();
	t4.set_direction(kGpioDown);
	int movements = 0;
	while(t4.snake_movement()){
		movements++;
	}
	assert_equals<int>(255, movements, "game over from snake traversing the screen and hitting the bottom edge");
	return;
}

void test_snake_movement_case5(){
	Snake t5;
	t5.set_direction(kGpioRight);
	int movements = 0;
	while(t5.snake_movement()){
		movements++;
	}
	assert_equals<int>(255, movements, "game over from snake traversing the screen and hitting the right edge");
	return;
}

void test_snake_movement_case6(){
	Snake t6;
	t6.set_direction(kGpioRight);
	bool first = t6.snake_movement();
	t6.set_direction(kGpioDown);
	bool second = t6.snake_movement();
	t6.set_direction(kGpioLeft);
	bool third = t6.snake_movement();
	t6.set_direction(kGpioUp);
	bool fourth = t6.snake_movement(); //consumes pellet
	t6.set_direction(kGpioRight);
	bool fifth = t6.snake_movement();
	t6.set_direction(kGpioDown);
	bool sixth = t6.snake_movement();
	t6.set_direction(kGpioLeft);
	bool seventh = t6.snake_movement(); //game over
	//cout << first << second << third << fourth << fifth << sixth << seventh << endl;
	bool actual = first && second && third && fourth && fifth && sixth && !seventh;
	assert_equals<bool>(true, actual, "eating pellet and running into self");
	return;
}
