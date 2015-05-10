#ifndef OPTIAML_SEARCH_TREE_H
#define OPTIAML_SEARCH_TREE_H

#include <vector>
#include <string>

using std::vector;
using std::string;

namespace JC
{
	class OptimalSearchTreeSolver
	{
	private:
		struct Record
		{
			double cost{ 0 };
			int root{ 0 };
		};
	public:
		OptimalSearchTreeSolver(const vector<double>& ws, const vector<double>& es);
		double solve(string& str) const;
	private:
		void constructTree(const vector<vector<Record>>& records, int b, int e, string& str) const;
	private:
		vector<double> words_;
		vector<double> extra_;
	};
}
#endif