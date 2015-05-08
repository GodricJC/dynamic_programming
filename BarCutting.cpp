#include "stdafx.h"
#include "BarCutting.h"

#include <memory>

using namespace std;

namespace JC
{
	BarCuttingSolver::BarCuttingSolver()
	{

	}

	void BarCuttingSolver::setValueTable(const ValueTable& vt)
	{
		vt_ = vt;
	}

	void BarCuttingSolver::setValueTable(int* lens, double* values, int size)
	{
		for (int i = 0; i < size; ++i)
			vt_.insert(make_pair(lens[i], values[i]));
	}
	void BarCuttingSolver::maxValue(int totalLen, double& mv, vector<int>& parts) const
	{
		unique_ptr<double[]> values(new double[totalLen + 1]);
		unique_ptr<int[]> addedWeight(new int[totalLen + 1]);
		values[0] = 0;
		addedWeight[0] = 0;
		for (int i = 1; i < totalLen + 1; ++i)
		{
			auto maxValue = values[i - 1];
			auto added = -1;
			for (auto& item : vt_)
			{
				if (item.first <= i)
				{
					auto temp = item.second + values[i - item.first];
					if (temp > maxValue)
					{
						maxValue = temp;
						added = item.first;
					}
				}
			}
			values[i] = maxValue;
			addedWeight[i] = added;
		}
		mv = values[totalLen];
		parts.clear();
		auto remaining = totalLen;
		while (remaining)
		{
			if (addedWeight[remaining] != -1)
			{
				parts.push_back(addedWeight[remaining]);
				remaining -= addedWeight[remaining];
			}
			else
				remaining -= 1;
		}
	}
}