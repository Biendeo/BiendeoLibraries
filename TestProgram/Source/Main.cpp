#include <iostream>
#include <string>

#include "Math/BigInteger.h"

int main(int argc, char* argv[]) {
	using namespace Biendeo;

	BigInteger a(5);

	BigInteger b(6);

	BigInteger c = a + b;

	std::cout << a.ToString() + " + " + b.ToString() + " = " + c.ToString();

	return 0;
}