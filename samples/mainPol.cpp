#include <iostream>
#include "Polinome.h"
int main() {
	std::string s;
	std::cin >> s;
	Polinome p(s);
	std::cin >> s;
	Polinome d(s);
	(d+p).print();
	
	return 0;
}