#include "Matrix.h"

#include <exception>

namespace Biendeo {
	namespace Math {
		Matrix::Matrix(int rows, int columns) : Matrix(rows, columns, NULL) {}

		Matrix::Matrix(int rows, int columns, double* data) {
			this->rows = rows;
			this->columns = columns;
			this->data.resize(columns);
			for (std::vector<double>& v : this->data) {
				v.resize(rows);
			}

			if (data == NULL) {
				for (int x = 0; x < columns; ++x) {
					for (int y = 0; y < rows; ++y) {
						Set(x, y, 0.0);
					}
				}
			} else {

			}
		}

		Matrix::~Matrix() {

		}

		int Matrix::Rows() {
			return rows;
		}

		int Matrix::Columns() {
			return columns;
		}

		double Matrix::Get(int row, int column) {
			if (InRange(row, column)) {
				return data.at(row).at(column);
			} else {
				throw std::out_of_range("Matrix::Get had an invalid range.");
			}
		}

		void Matrix::Set(int row, int column, double value) {
			if (InRange(row, column)) {
				data.at(row).at(column) = value;
			} else {
				throw std::out_of_range("Matrix::Set had an invalid range.");
			}
		}

		Matrix Matrix::Add(Matrix& m) {
			if (rows == m.rows && columns == m.columns) {
				Matrix r = Matrix(rows, columns);
				for (int x = 0; x < columns; ++x) {
					for (int y = 0; y < rows; ++y) {
						r.Set(x, y, Get(x, y) + m.Get(x, y));
					}
				}
				
				return r;
			} else {
				throw std::exception("Matrix::Add tried to add differently sized matrices.");
			}
		}

		Matrix Matrix::Subtract(Matrix& m) {
			if (rows == m.rows && columns == m.columns) {
				Matrix r = Matrix(rows, columns);
				for (int x = 0; x < columns; ++x) {
					for (int y = 0; y < rows; ++y) {
						r.Set(x, y, Get(x, y) - m.Get(x, y));
					}
				}

				return r;
			} else {
				throw std::exception("Matrix::Subtract tried to subtract differently sized matrices.");
			}
		}

		Matrix Matrix::Multiply(Matrix& m) {
			if (columns == m.rows) {
				Matrix r = Matrix(rows, m.columns);
				for (int x = 0; x < m.columns; ++x) {
					for (int y = 0; y < rows; ++y) {
						r.Set(x, y, 0.0);
						for (int j = 0; j < columns; ++j) {
							r.Set(x, y, r.Get(x, y) + Get(x, j) * m.Get(j, y));
						}
					}
				}

				return r;
			} else {
				throw std::exception("Matrix::Multiply tried to multiply two matrices of incompatible sizes.");
			}
		}

		Matrix Matrix::Multiply(double d) {
			Matrix r = Matrix(rows, columns);
			for (int x = 0; x < columns; ++x) {
				for (int y = 0; y < rows; ++y) {
					r.Set(x, y, Get(x, y) * d);
				}
			}

			return r;
		}

		Matrix Matrix::operator+(Matrix& m) {
			return Add(m);
		}

		Matrix Matrix::operator-(Matrix& m) {
			return Subtract(m);
		}

		Matrix Matrix::operator*(Matrix& m) {
			return Multiply(m);
		}

		Matrix Matrix::operator*(double d) {
			return Multiply(d);
		}

		Matrix Matrix::operator+=(Matrix & m) {
			(*this) = (*this) + m;
			return (*this);
		}

		Matrix Matrix::operator-=(Matrix & m) {
			(*this) = (*this) * m;
			return (*this);
		}

		Matrix Matrix::operator*=(Matrix & m) {
			(*this) = (*this) * m;
			return (*this);
		}

		Matrix Matrix::operator*=(double d) {
			(*this) = (*this) * d;
			return (*this);
		}

		bool Matrix::InRange(int row, int column) {
			return (row >= 0 && row < rows && column >= 0 && column < columns);
		}

		static Matrix MatrixIdentity(int size) {
			if (size > 0) {
				Matrix m = Matrix(size, size);

				for (int i = 0; i < size; ++i) {
					m.Set(i, i, 1.0);
				}

				return m;
			} else {
				throw std::out_of_range("MatrixIdentity had a non-positive size.");
			}
		}
	}
}


