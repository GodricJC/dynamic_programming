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
	 * 二叉树的最优问题
	 * 首先应该想到的是子树递归的方式
	 * 对于一棵最优二叉搜索树树，其左右子树也一定是分别最优的
	 * 故对于有n个结点的二叉树，其最优二叉树为：
		optimal(1, n) = Min( optimal(1, k-1) Nk optimal(k+1, n) ), k=1, 2, ..., n
		cost(1, n) = Min( cost(1, k-1) + cost(k+1, n) + 1 * p(1, n) + 1 * q(1, n+1) )
	 * 子问题规模数为O(n^2)
	 * 问题时间复杂度为O(n^3)
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

		// 部分和，[i, j]的部分和为sum[j+1]-sum[i]
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
			for (int j = i; j >= 0; --j) // 计算records(j, i)
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
				minCost += wordsPartSum[i + 1] - wordsPartSum[j] + extraPartSum[i + 2] - extraPartSum[j]; // 这一部分都是一样的
				records[j][i].cost = minCost;
				records[j][i].root = minRoot;
			}
		}
		// 以上所有的计算对于extra都少了一次
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