#pragma once

#include <vector>

namespace Biendeo {
	class BigInteger {
		public:

		BigInteger();
		// TODO: All the constructors.
		BigInteger(int x);

		friend BigInteger operator+(const BigInteger& b1, const BigInteger& b2);
		friend BigInteger operator-(const BigInteger& b1, const BigInteger& b2);
		friend BigInteger operator*(const BigInteger& b1, const BigInteger& b2);
		friend BigInteger operator/(const BigInteger& b1, const BigInteger& b2);
		friend BigInteger operator%(const BigInteger& b1, const BigInteger& b2);
		friend BigInteger operator-(const BigInteger& b);

		BigInteger& operator+=(BigInteger& b2);
		BigInteger& operator-=(BigInteger& b2);
		BigInteger& operator*=(BigInteger& b2);
		BigInteger& operator/=(BigInteger& b2);
		BigInteger& operator%=(BigInteger& b2);

		BigInteger& operator++();
		BigInteger& operator--();
		BigInteger operator++(int dummy);
		BigInteger operator--(int dummy);

		friend bool operator>(const BigInteger& b1, const BigInteger& b2);
		friend bool operator>=(const BigInteger& b1, const BigInteger& b2);
		friend bool operator<(const BigInteger& b1, const BigInteger& b2);
		friend bool operator<=(const BigInteger& b1, const BigInteger& b2);
		friend bool operator==(const BigInteger& b1, const BigInteger& b2);
		friend bool operator!=(const BigInteger& b1, const BigInteger& b2);

		static BigInteger Add(const BigInteger& b1, const BigInteger& b2);
		static BigInteger Subtract(const BigInteger& b1, const BigInteger& b2);
		static BigInteger Multiply(const BigInteger& b1, const BigInteger& b2);
		static BigInteger Divide(const BigInteger& b1, const BigInteger& b2);
		static BigInteger Modulus(const BigInteger& b1, const BigInteger& b2);

		static bool Greater(const BigInteger& b1, const BigInteger& b2);
		static bool Less(const BigInteger& b1, const BigInteger& b2);
		static bool Equals(const BigInteger& b1, const BigInteger& b2);

		static BigInteger FlipSign(const BigInteger& b);

		std::string ToString() const;
		static std::string ToString(const BigInteger& b1);

		private:
		enum class Sign {
			Positive,
			Negative
		};

		std::vector<bool> bits;
		Sign sign;
	};
}