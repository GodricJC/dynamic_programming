#ifndef BAR_CUTTING_H
#define BAR_CUTTING_H

#include <map>
#include <vector>
using std::map;
using std::vector;

namespace JC
{
	typedef map<int, double> ValueTable;
	class BarCuttingSolver
	{
	public:
		BarCuttingSolver();
		void setValueTable(const ValueTable& vt);
		void setValueTable(int* lens, double* values, int size);
		void maxValue(int totalLen, double& mv, vector<int>& parts) const;
	private:
		ValueTable vt_;
	};
}

#endif
