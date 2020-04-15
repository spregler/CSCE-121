// Seth Pregler
// 827008197
// 2.27.20
// Different Digits HW 2


#include <iostream>
#include "functions.h"
using namespace std; 


bool is_valid_range(int a, int b) {
	if ((a > 0 ) && (a <= b) && (b <= 10000)) {
		return true;
	}
	else {
		return false;
	}
}

int count_digit_occurrences(int number, int digit) {
	int count = 0;
	
	while (number > 0) {
		if (number % 10 == digit) {
			++count;
		}
		number /= 10;
	}
	return count;
}


bool has_repeated_digits(int number) {
	
	for (int i = 0; i < 10; i++) {
		if ((count_digit_occurrences(number, i)) > 1) {
			return true;
		} 	
	}
	return false;
}
	
int count_valid_numbers(int a, int b) {
	int valNums = 0;

	while(a <= b) {
		if (!has_repeated_digits(a)) {
			valNums++;
			a++;
		}
		else {
			a++;
		}
	}	
	return valNums;
}