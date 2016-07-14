#pragma once

#include <vector>

namespace Biendeo {
	namespace Math {
		class Matrix {
			public:
			Matrix(int rows, int columns);
			Matrix(int rows, int columns, double* data);
			~Matrix();

			int Rows();
			int Columns();

			double Get(int row, int column);
			void Set(int row, int column, double value);

			Matrix Add(Matrix& m);
			Matrix Subtract(Matrix& m);
			Matrix Multiply(Matrix& m);
			Matrix Multiply(double d);

			Matrix operator+(Matrix& m);
			Matrix operator-(Matrix& m);
			Matrix operator*(Matrix& m);
			Matrix operator*(double d);

			Matrix operator+=(Matrix& m);
			Matrix operator-=(Matrix& m);
			Matrix operator*=(Matrix& m);
			Matrix operator*=(double d);

			protected:
			int rows;
			int columns;
			std::vector<std::vector<double>> data;

			bool InRange(int row, int column);

		};

		static Matrix MatrixIdentity(int size);
	}
}

