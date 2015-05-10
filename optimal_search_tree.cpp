#include "stdafx.h"
#include "optimal_search_tree.h"
#include "boost/lexical_cast.hpp"

using namespace std;

namespace JC
{
	OptimalSearchTreeSolver::OptimalSearchTreeSolver(const vector<double>& ws, const vector<double>& es)
		: words_(ws)
		, extra_(es)
	{
	}

	/*
	 * ����������������
	 * ����Ӧ���뵽���������ݹ�ķ�ʽ
	 * ����һ�����Ŷ�����������������������Ҳһ���Ƿֱ����ŵ�
	 * �ʶ�����n�����Ķ������������Ŷ�����Ϊ��
		optimal(1, n) = Min( optimal(1, k-1) Nk optimal(k+1, n) ), k=1, 2, ..., n
		cost(1, n) = Min( cost(1, k-1) + cost(k+1, n) + 1 * p(1, n) + 1 * q(1, n+1) )
	 * �������ģ��ΪO(n^2)
	 * ����ʱ�临�Ӷ�ΪO(n^3)
	 */
	double OptimalSearchTreeSolver::solve(string& str) const
	{
		auto size = words_.size();
		vector<vector<Record>> records;
		{
			vector<Record> row;
			Record temp;
			for (int j = 0; j < size; ++j)
				row.push_back(temp);
			for (int j = 0; j < size; ++j)
				records.push_back(row);
		}

		// ���ֺͣ�[i, j]�Ĳ��ֺ�Ϊsum[j+1]-sum[i]
		vector<double> wordsPartSum;
		vector<double> extraPartSum;
		double temp1 = 0, temp2 = 0;
		wordsPartSum.push_back(temp1);
		extraPartSum.push_back(temp2);
		for (int i = 0; i < size; ++i)
		{
			temp1 += words_[i];
			wordsPartSum.push_back(temp1);
			temp2 += extra_[i];
			extraPartSum.push_back(temp2);
		}
		extraPartSum.push_back(temp2 + extra_[size]);

		for (int i = 0; i < size; ++i)
		{
			for (int j = i; j >= 0; --j) // ����records(j, i)
			{
				double left = (j - 1 < 0) ? 0 : records[j][j - 1].cost;
				double right = (j + 1 >= size) ? 0 : records[j + 1][i].cost;

				auto minCost = left + right;
				auto minRoot = j;
				for (int k = j + 1; k <= i; ++k)
				{
					left = records[j][k - 1].cost;
					right = (k + 1 >= size) ? 0 : records[k + 1][i].cost;
					auto tempCost = left + right;
					if (tempCost < minCost)
					{
						minCost = tempCost;
						minRoot = k;
					}
				}
				minCost += wordsPartSum[i + 1] - wordsPartSum[j] + extraPartSum[i + 2] - extraPartSum[j]; // ��һ���ֶ���һ����
				records[j][i].cost = minCost;
				records[j][i].root = minRoot;
			}
		}
		// �������еļ������extra������һ��
		for (int i = 0; i < size; ++i)
			for (int j = 0; j <= i; ++j)
				records[j][i].cost += extraPartSum[i + 2] - extraPartSum[j];

		str = "";
		constructTree(records, 0, size - 1, str);
		return records[0][size - 1].cost;
	}
	void OptimalSearchTreeSolver::constructTree(const vector<vector<Record>>& records, int b, int e, string& str) const
	{
		if (b > e)
			str += string("D") + boost::lexical_cast<string>(b)+string(" ");
		else
		{
			int root = records[b][e].root;
			str += string("K") + boost::lexical_cast<string>(root)+" ";
			str += "( ";
			constructTree(records, b, root - 1, str);
			constructTree(records, root + 1, e, str);
			str += ") ";
		}
	}
}