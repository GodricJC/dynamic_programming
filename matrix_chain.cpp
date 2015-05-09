#include "stdafx.h"
#include "matrix_chain.h"
#include "matrix.h"
#include <boost/lexical_cast.hpp>

namespace JC
{
	MatrixChainSolver::Record::Record(int m)
		: middle(m)
	{

	}

	MatrixChainSolver::MatrixChainSolver(vector<shared_ptr<Matrix>> ms)
	{
		matrices_.assign(ms.begin(), ms.end());
	}

	long MatrixChainSolver::solve(string& format) const
	{
		auto size = matrices_.size();
		vector<vector<Record>> records;

		for (int i = 0; i < size; ++i)
		{
			vector<Record> temp;
			auto r = Record(i);
			for (int i = 0; i < size; ++i)
				temp.push_back(r);
			records.push_back(temp);
		}

		/*
		 * �����i������Ai����С��costΪ�������֮һ
			Min(A1A2...Ai-1) * Min(Ai)
			Min(A1A2...Ai-2) * Min(Ai-1Ai)
			...
			Min(A1A2) * Min(A3A4...Ai)
			Min(A1) * Min(A2A3...Ai)
		 * ��Min(AjAj+1...Ai)���ֿ�����Min(Aj...Ak) * Min(Ak...Ai)�õ�
		 */
		for (int i = 1; i < size; ++i) // ��ӵ�i������
		{
			for (int j = i - 1; j >= 0; --j) // ����records[j][i]����Сֵ
			{
				auto minCost = records[j][i - 1].cost + records[i][i].cost
					+ matrices_[j]->nRow_ * matrices_[i-1]->nColumn_ * matrices_[i]->nColumn_;
				auto minMiddle = i - 1;
				for (int k = i - 2; k >= j; --k)
				{
					auto temp = records[j][k].cost + records[k + 1][i].cost
						+ matrices_[j]->nRow_ * matrices_[k]->nColumn_ * matrices_[i]->nColumn_;
					if (minCost > temp)
					{
						minCost = temp;
						minMiddle = k;
					}
				}
				records[j][i].cost = minCost;
				records[j][i].middle = minMiddle;
			}
		}
		/*
		 * �༭����˳��
		 */
		editResult(records, 0, size - 1, format);
		return records[0][size - 1].cost;
	}

	void MatrixChainSolver::editResult(const vector<vector<Record>>& records, int b, int e, string& str) const
	{
		if (b == e)
			str += string("M") + boost::lexical_cast<string>(b);
		else
		{
			str += "(";
			editResult(records, b, records[b][e].middle, str);
			editResult(records, records[b][e].middle + 1, e, str);
			str += ")";
		}
	}
}