#include "matrix_chain.h"
#include "matrix.h"

namespace JC
{
	MatrixChainSolver::MatrixChainSolver(vector<shared_ptr<Matrix>> ms)
	{
		matrices_.assign(ms.begin(), ms.end());
	}
}