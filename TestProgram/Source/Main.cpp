#include <iostream>
#include <string>

#include "Math/BigInteger.h"

int main(int argc, char* argv[]) {
	using namespace Biendeo;

	BigInteger a(9876);

	BigInteger b(1234);

	BigInteger c = a * b;

	std::cout << a.ToString() + " * " + b.ToString() + " = " + c.ToString() + "\n";

	return 0;
}