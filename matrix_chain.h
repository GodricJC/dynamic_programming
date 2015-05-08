#ifndef MATRIX_CHAIN_H
#define MATRIX_CHAIN_H

#include <vector>
#include <memory>

using std::vector;
using std::shared_ptr;

namespace JC
{
	class Matrix;
	class MatrixChainSolver
	{
	public:
		MatrixChainSolver(vector<shared_ptr<Matrix>> ms);
		
	private:
		vector<shared_ptr<Matrix>> matrices_;
	};
}

#endif