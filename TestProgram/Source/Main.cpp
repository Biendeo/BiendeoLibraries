#include <iostream>
#include <string>

#include "Math/BigInteger.h"

int main(int argc, char* argv[]) {
	using namespace Biendeo;

	BigInteger a(123);

	BigInteger b(-987);

	BigInteger c = a * b;

	std::cout << a.ToString() + " * " + b.ToString() + " = " + c.ToString() + "\n";

	std::cout << sizeof(b);

	return 0;
}