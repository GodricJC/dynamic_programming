#include "stdafx.h"

#include "BarCutting.h"
#include "matrix.h"
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
	Matrix ma(2, 2);
	ma[0][0] = 1;
	ma[0][1] = 2;
	ma[1][0] = 3;
	ma[1][1] = 4;
	cout << ma << endl;
	Matrix mb(2, 1);
	mb[0][0] = 1;
	mb[1][0] = 2;
	cout << mb << endl;
	Matrix mc = ma*mb;
	cout << mc << endl;
	system("pause");
	return 0;
}

