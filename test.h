#include "main/snake.h"

#ifndef TEST_H
#define TEST_H

#include <string>
#include <iostream>
using namespace std;

void run_all();

void test_snake_movement();

void test_snake_movement_case1(); //single (valid) movement
void test_snake_movement_case2(); //hitting top edge
void test_snake_movement_case3(); //hitting left edge
void test_snake_movement_case4(); //hitting bottom edge
void test_snake_movement_case5(); //hitting right edge
void test_snake_movement_case6(); //eating pellet and hitting self

template <class T>
void assert_equals(T expected, T actual, string test_description){
	if(expected == actual){
		cout << "PASSED\n";
	}else{
		cout << "FAILED: " << test_description << endl << " Expected: " << expected << endl << " Acutal: " << actual << endl;
	}
}

#endif
