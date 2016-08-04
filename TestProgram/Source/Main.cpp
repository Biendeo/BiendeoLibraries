#include <iostream>
#include <string>

#include "Math/BigInteger.h"

int main(int argc, char* argv[]) {
	using namespace Biendeo;

	BigInteger a(1231241);

	BigInteger b(-98712512);

	BigInteger c = a * b;

	std::cout << a.ToString() + " * " + b.ToString() + " = " + c.ToString() + "\n";

	std::cout << sizeof(b);

	return 0;
}