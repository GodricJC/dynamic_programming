#include "stdafx.h"

#include "BarCutting.h"
#include <iostream>

using namespace JC;
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	BarCuttingSolver bcs;
	int lens[] { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	double values[] { 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
	bcs.setValueTable(lens, values, 10);
	double mv;
	vector<int> parts;
	for (int i = 1; i < 100; ++i)
	{
		cout << "�ܳ���" << i << endl;
		bcs.maxValue(i, mv, parts);
		cout << "����ֵ��" << mv << endl;
		cout << "��ɣ�";
		for (auto j : parts)
			cout << j << " ";
		cout << endl << endl;
	}

	system("pause");
	return 0;
}

