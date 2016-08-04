#include <iostream>
#include <string>

#include "Math/BigInteger.h"

int main(int argc, char* argv[]) {
	using namespace Biendeo;

	BigInteger a(INT32_MAX);

	BigInteger b(INT32_MAX);

	BigInteger c = a * b * b * b * b;

	std::cout << a.ToString() + " * " + b.ToString() + "^4 = " + c.ToString() + "\n";

	return 0;
}