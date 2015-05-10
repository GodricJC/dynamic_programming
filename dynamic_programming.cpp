#include "stdafx.h"

#include "BarCutting.h"
#include "matrix.h"
#include "matrix_chain.h"
#include "optimal_search_tree.h"
#include <iostream>

using namespace JC;
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	// 钢条切割问题测试
	//BarCuttingSolver bcs;
	//int lens[] { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	//double values[] { 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
	//bcs.setValueTable(lens, values, 10);
	//double mv;
	//vector<int> parts;
	//for (int i = 1; i < 100; ++i)
	//{
	//	cout << "总长：" << i << endl;
	//	bcs.maxValue(i, mv, parts);
	//	cout << "最大价值：" << mv << endl;
	//	cout << "组成：";
	//	for (auto j : parts)
	//		cout << j << " ";
	//	cout << endl << endl;
	//}

	// 矩阵链乘法问题测试
	//Matrix ma(2, 2);
	//ma[0][0] = 1;
	//ma[0][1] = 2;
	//ma[1][0] = 3;
	//ma[1][1] = 4;
	//cout << ma << endl;
	//Matrix mb(2, 1);
	//mb[0][0] = 1;
	//mb[1][0] = 2;
	//cout << mb << endl;
	//Matrix mc = ma*mb;
	//cout << mc << endl;
	//system("pause");
	//vector<shared_ptr<Matrix>> ms;
	//ms.push_back(shared_ptr<Matrix>(new Matrix(30, 35)));
	//ms.push_back(shared_ptr<Matrix>(new Matrix(35, 15)));
	//ms.push_back(shared_ptr<Matrix>(new Matrix(15, 5)));
	//ms.push_back(shared_ptr<Matrix>(new Matrix(5, 10)));
	//ms.push_back(shared_ptr<Matrix>(new Matrix(10, 20)));
	//ms.push_back(shared_ptr<Matrix>(new Matrix(20, 25)));
	//MatrixChainSolver mcs(ms);
	//string format;
	//cout << mcs.solve(format) << endl;
	//cout << format << endl;

	// 最优二叉树问题测试
	vector<double> words{ .15, .1, .05, .1, .2 };
	vector<double> extra{ .05, .1, .05, .05, .05, .1 };
	OptimalSearchTreeSolver osts(words, extra);
	string str;
	cout << osts.solve(str) << endl;
	cout << str << endl;

	system("pause");
	return 0;
}

