#ifndef MATRIX_CHAIN_H
#define MATRIX_CHAIN_H

#include <vector>
#include <memory>
#include <string>

using std::vector;
using std::shared_ptr;
using std::string;

namespace JC
{
	class Matrix;
	class MatrixChainSolver
	{
	private:
		struct Record
		{
			int middle{ 0 };
			long cost{ 0 };
			Record(int m);
		};
	public:
		MatrixChainSolver(vector<shared_ptr<Matrix>> ms);
		long solve(string& format) const;
	private:
		void editResult(const vector<vector<Record>>& records, int b, int e, string& str) const;
	private:
		vector<shared_ptr<Matrix>> matrices_;
	};
}

#endif