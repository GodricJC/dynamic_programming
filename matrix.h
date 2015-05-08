#ifndef MATRIX_H
#define MATRIX_H

#include <memory>
#include <ostream>

using std::unique_ptr;
using std::ostream;

namespace JC
{
	class Matrix
	{
	public:
		class Row
		{
		public:
			Row(int len);
			Row(const Row& other);
			double& operator[](int c);
			const double& operator[](int c) const;
			void zero();
			friend ostream& operator<<(ostream& out, const Row& r);

		private:
			int len_;
			unique_ptr<double[]> value_{ nullptr };
		};

	public:
		Matrix(int nr, int nc);
		~Matrix();
		Matrix(const Matrix& other);
		Matrix& operator=(const Matrix& other);
		Row& operator[](int r);
		const Row& operator[](int r) const;
		Matrix& operator*=(const Matrix& rhs);
		friend Matrix operator*(const Matrix& lhs, const Matrix& rhs);
		friend ostream& operator<<(ostream& out, const Matrix& m);

	private:
		void swap(Matrix& other);
	private:
		int nRow_;
		int nColumn_;
		Row* rows_;
	};
}

#endif