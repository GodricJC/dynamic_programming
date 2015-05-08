#include "stdafx.h"
#include "matrix.h"
#include <algorithm>
#include <cassert>
#include <numeric>

using namespace std;

namespace JC
{
	Matrix::Row::Row(int len)
		: len_(len)
		, value_(new double[len])
	{
		zero();
	}
	Matrix::Row::Row(const Row& other)
		: len_(other.len_)
		, value_(new double[len_])
	{
		for (int i = 0; i < len_; ++i)
			value_[i] = other.value_[i];
	}
	const double& Matrix::Row::operator[](int c) const
	{
		return value_[c];
	}
	double& Matrix::Row::operator[](int c)
	{
		return value_[c];
	}
	void Matrix::Row::zero()
	{
		for (int i = 0; i < len_; ++i)
			value_[i] = 0;
	}
	ostream& operator<<(ostream& out, const Matrix::Row& r)
	{
		for (int i = 0; i < r.len_; ++i)
			out << r.value_[i] << " ";
		return out;
	}



	Matrix::Matrix(int nr, int nc)
		: nRow_(nr)
		, nColumn_(nc)
		, rows_(static_cast<Row*>(operator new(sizeof(Row)*nr)))
	{
		for (int i = 0; i < nRow_; ++i)
			new(rows_ + i) Row(nc);
	}
	Matrix::~Matrix()
	{
		for (int i = 0; i < nRow_; ++i)
			(rows_ + i)->~Row();
		operator delete(rows_);
	}
	void Matrix::swap(Matrix& other)
	{
		std::swap(rows_, other.rows_);
		std::swap(nRow_, other.nRow_);
		std::swap(nColumn_, other.nColumn_);
	}
	Matrix::Matrix(const Matrix& other)
		: nRow_(other.nRow_)
		, nColumn_(other.nColumn_)
		, rows_(static_cast<Row*>(operator new(sizeof(Row)*nRow_)))
	{
		for (int i = 0; i < nRow_; ++i)
			new(rows_ + i) Row(other.rows_[i]);
	}
	Matrix& Matrix::operator=(const Matrix& other)
	{
		Matrix temp(other);
		this->swap(temp);
		return *this;
	}
	const Matrix::Row& Matrix::operator[](int r) const
	{
		return rows_[r];
	}
	Matrix::Row& Matrix::operator[](int r)
	{
		return rows_[r];
	}
	Matrix& Matrix::operator*=(const Matrix& rhs)
	{
		assert(this->nColumn_ == rhs.nRow_);
		Matrix result(nRow_, rhs.nColumn_);
		for (int i = 0; i < result.nRow_; ++i)
			for (int j = 0; j < result.nColumn_; ++j)
				for (int k = 0; k < nColumn_; ++k)
				{
					result[i][j] += rows_[i][k] * rhs.rows_[k][j];
				}
		swap(result);
		return *this;
	}
	Matrix operator*(const Matrix& lhs, const Matrix& rhs)
	{
		Matrix temp(lhs);
		temp *= rhs;
		return temp;
	}
	ostream& operator<<(ostream& out, const Matrix& m)
	{
		for (int i = 0; i < m.nRow_; ++i)
			out << m.rows_[i] << endl;
		return out;
	}
}