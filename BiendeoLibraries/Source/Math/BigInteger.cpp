#include "BigInteger.h"

#include <string>

namespace Biendeo {
	BigInteger::BigInteger() : BigInteger(0) {
	}

	BigInteger::BigInteger(int x) {
		if (x < 0) {
			sign = Sign::Negative;
			x *= -1;
		} else {
			sign = Sign::Positive;
		}

		while (x > 0) {
			bits.push_back(x % 2 ? true : false);
			x >>= 1;
		}
	}

	BigInteger BigInteger::Add(const BigInteger& b1, const BigInteger& b2) {
		if (b1.sign == Sign::Negative && b2.sign == Sign::Positive) {
			return Subtract(b2, FlipSign(b1));
		} else if (b1.sign == Sign::Positive && b2.sign == Sign::Negative) {
			return Subtract(b1, FlipSign(b2));
		} else if (b1.sign == Sign::Negative && b2.sign == Sign::Negative) {
			return Add(FlipSign(b1), FlipSign(b2));
		} else {
			if (b2.bits.size() > b1.bits.size()) {
				return Add(b2, b1);
			}

			BigInteger r = b1;

			bool carry = false;
			for (int i = 0; i < b1.bits.size(); ++i) {
				int value = 0;
				b1.bits.at(i) ? ++value : value;
				if (i < b2.bits.size()) {
					b2.bits.at(i) ? ++value : value;
				}
				carry ? ++value : value;
				
				carry = false;

				if (value >= 2) {
					value -= 2;
					carry = true;
				}

				value == 1 ? r.bits.at(i) = true : r.bits.at(i) = false;
			}

			if (carry) {
				r.bits.push_back(true);
			}

			return r;
		}
	}

	BigInteger BigInteger::Subtract(const BigInteger& b1, const BigInteger& b2) {
		if (b1.sign == Sign::Negative && b2.sign == Sign::Positive) {
			return FlipSign(Add(b2, FlipSign(b1)));
		} else if (b1.sign == Sign::Positive && b2.sign == Sign::Negative) {
			return Add(b1, FlipSign(b2));
		} else if (b1.sign == Sign::Negative && b2.sign == Sign::Negative) {
			return FlipSign(Subtract(FlipSign(b1), FlipSign(b2)));
		} else {
			if (Less(b1, b2)) {
				return FlipSign(Subtract(b2, b1));
			}

			BigInteger r = b1;

			bool carry = false;
			for (int i = 0; i < b1.bits.size(); ++i) {
				int value = 0;
				b1.bits.at(i) ? ++value : value;

				if (i < b2.bits.size()) {
					b2.bits.at(i) ? --value : value;
				}

				carry ? --value : value;

				carry = false;

				if (value < 0) {
					value += 2;
					carry = true;
				}

				value == 1 ? r.bits.at(i) = true : r.bits.at(i) = false;
			}

			while (!r.bits.back() && r.bits.size() > 1) {
				r.bits.pop_back();
			}

			return r;
		}
	}

	BigInteger BigInteger::Multiply(const BigInteger& b1, const BigInteger& b2) {
		BigInteger r = 0;

		for (int i = 0; i < b2.bits.size(); ++i) {
			if (b2.bits.at(i)) {
				BigInteger x = b1;
				if (x.sign == Sign::Negative) {
					x = FlipSign(x);
				}
				for (int j = 0; j < i; ++j) {
					x.bits.insert(x.bits.begin(), false);
				}
				r += x;
			}
		}

		if (b1.sign != b2.sign) {
			r.sign = Sign::Negative;
		}

		return r;
	}

	BigInteger BigInteger::Divide(const BigInteger& b1, const BigInteger& b2) {
		BigInteger r = 0;
		BigInteger s = b1;

		while (s >= b2) {
			BigInteger x = b2;
			BigInteger y = 1;
			while (x * 2 <= s) {
				x.bits.insert(x.bits.begin(), false);
				y.bits.insert(y.bits.begin(), false);
			}

			r += y;
			s -= x;
		}

		return r;
	}

	BigInteger BigInteger::Modulus(const BigInteger& b1, const BigInteger& b2) {
		return b1 - b2 * (b1 / b2);
	}

	bool BigInteger::Greater(const BigInteger& b1, const BigInteger& b2) {
		if (b1.sign == Sign::Positive && b2.sign == Sign::Negative) {
			return true;
		} else if (b1.sign == Sign::Negative && b2.sign == Sign::Positive) {
			return false;
		} else if (b1.sign == Sign::Negative && b2.sign == Sign::Negative) {
			return Greater(-b2, -b1);
		} else if (b1.bits.size() < b2.bits.size()) {
			return false;
		} else if (b1.bits.size() > b2.bits.size()) {
			return true;
		} else {
			for (int i = b1.bits.size() - 1; i >= 0; --i) {
				if (b1.bits.at(i) == true && b2.bits.at(i) == false) {
					return true;
				} else if (b1.bits.at(i) == false && b2.bits.at(i) == true) {
					return false;
				}
			}
			return false;
		}
	}

	bool BigInteger::Less(const BigInteger& b1, const BigInteger& b2) {
		if (b1.sign == Sign::Negative && b2.sign == Sign::Positive) {
			return true;
		} else if (b1.sign == Sign::Positive && b2.sign == Sign::Negative) {
			return false;
		} else if (b1.sign == Sign::Negative && b2.sign == Sign::Negative) {
			return Less(-b2, -b1);
		} else if (b1.bits.size() > b2.bits.size()) {
			return false;
		} else if (b1.bits.size() < b2.bits.size()) {
			return true;
		} else {
			for (int i = b1.bits.size() - 1; i >= 0; --i) {
				if (b1.bits.at(i) == false && b2.bits.at(i) == true) {
					return true;
				} else if (b1.bits.at(i) == true && b2.bits.at(i) == false) {
					return false;
				}
			}
			return false;
		}
	}

	bool BigInteger::Equals(const BigInteger& b1, const BigInteger& b2) {
		if (b1.sign != b2.sign || b1.bits.size() != b2.bits.size()) {
			return false;
		} else {
			for (int i = 0; i < b1.bits.size(); ++i) {
				if (b1.bits.at(i) != b2.bits.at(i)) {
					return false;
				}
			}
			return true;
		}
	}

	BigInteger BigInteger::FlipSign(const BigInteger& b) {
		if (Equals(b, 0)) {
			return b;
		} else {
			BigInteger r = b;
			if (r.sign == Sign::Positive) {
				r.sign = Sign::Negative;
			} else {
				r.sign = Sign::Positive;
			}
			return r;
		}
	}

	std::string BigInteger::ToString() const {
		return ToString(*this);
	}

	std::string BigInteger::ToString(const BigInteger& b1) {
		std::string s;
		BigInteger r = b1;

		bool negative = r.sign == Sign::Negative;

		r.sign = Sign::Positive;

		if (r == 0) {
			return "0";
		}

		while (r > 0) {
			BigInteger m = r % 10;
			int value = 0;
			int exponent = 1;
			for (bool b : m.bits) {
				value += exponent * (b ? 1 : 0);
				exponent *= 2;
			}
			s = std::to_string(value) + s;
			r /= 10;
		}

		if (negative) {
			s = "-" + s;
		}

		return s;
	}

	BigInteger operator+(const BigInteger& b1, const BigInteger& b2) {
		return BigInteger::Add(b1, b2);
	}

	BigInteger operator-(const BigInteger& b1, const BigInteger& b2) {
		return BigInteger::Subtract(b1, b2);
	}

	BigInteger operator*(const BigInteger& b1, const BigInteger& b2) {
		return BigInteger::Multiply(b1, b2);
	}

	BigInteger operator/(const BigInteger& b1, const BigInteger& b2) {
		return BigInteger::Divide(b1, b2);
	}

	BigInteger operator%(const BigInteger& b1, const BigInteger& b2) {
		return BigInteger::Modulus(b1, b2);
	}

	BigInteger operator-(const BigInteger& b) {
		return BigInteger::FlipSign(b);
	}

	BigInteger& BigInteger::operator+=(const BigInteger& b2) {
		return (*this) = (*this) + b2;
	}

	BigInteger& BigInteger::operator-=(const BigInteger& b2) {
		return (*this) = (*this) - b2;
	}

	BigInteger& BigInteger::operator*=(const BigInteger& b2) {
		return (*this) = (*this) * b2;
	}

	BigInteger& BigInteger::operator/=(const BigInteger& b2) {
		return (*this) = (*this) / b2;
	}

	BigInteger& BigInteger::operator%=(const BigInteger& b2) {
		return (*this) = (*this) % b2;
	}

	BigInteger& BigInteger::operator++() {
		return (*this) += BigInteger(1);
	}

	BigInteger& BigInteger::operator--() {
		return (*this) -= BigInteger(1);
	}

	BigInteger BigInteger::operator++(int dummy) {
		BigInteger r = *this;
		++(*this);
		return r;
	}

	BigInteger BigInteger::operator--(int dummy) {
		BigInteger r = *this;
		--(*this);
		return r;
	}

	bool operator>(const BigInteger& b1, const BigInteger& b2) {
		return BigInteger::Greater(b1, b2);
	}

	bool operator>=(const BigInteger& b1, const BigInteger& b2) {
		return BigInteger::Greater(b1, b2) || BigInteger::Equals(b1, b2);
	}

	bool operator<(const BigInteger& b1, const BigInteger& b2) {
		return BigInteger::Less(b1, b2);
	}

	bool operator<=(const BigInteger& b1, const BigInteger& b2) {
		return BigInteger::Less(b1, b2) || BigInteger::Equals(b1, b2);
	}

	bool operator==(const BigInteger& b1, const BigInteger& b2) {
		return BigInteger::Equals(b1, b2);
	}

	bool operator!=(const BigInteger& b1, const BigInteger& b2) {
		return !BigInteger::Equals(b1, b2);
	}
}