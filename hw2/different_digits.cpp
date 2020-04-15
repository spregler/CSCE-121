// Seth Pregler
// 827008197
// 2.27.20
// Different Digits HW 2


#include <iostream>
#include "functions.h"
using namespace std;


int main() {

	int a;
	int b; 
	int valNums;

	cout << "Enter numbers 0 < a <= b <= 10000: ";

	cin >> a;
	cin >> b;
	// call to is_valid_range() to validate range
	// if valid

	if (is_valid_range(a, b)) {
		//loop through a to b

		cout << "There are " << count_valid_numbers(a, b) << " valid numbers between " << a << " and " << b << endl;
	} 
	else {
		cout << "Invalid input" << endl;
	}
}