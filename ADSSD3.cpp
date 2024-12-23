#include<iostream>
#include<iomanip>
#include<fstream>
#include<vector>
#include<cmath>
#include<chrono>
using namespace std;
using namespace std::chrono;
vector<int> rngGenerator(vector<int>dataSet, int size)
{
	srand(time(0));
	for (int i = 0; i < size; i++)
	{
		dataSet.push_back(rand());
	}
	return dataSet;
}
vector<int>SedgewickGap(vector<int>sGap)
{
	sGap.push_back(1);
	for (int i = 1; i < 10; i++)
	{
		sGap.push_back(pow(4, i * 1) + 3 * pow(2, (i - 1)) + 1);
	}
	return sGap;
}
vector<int>HibbardGap(vector<int>hGap)
{
	for (int i = 1; i < 20; i++)
	{
		hGap.push_back(pow(2, i) - 1);
	}
	return hGap;
}
vector<int>GapResize(vector<int>gap, int length)
{
	for (int i = 0; i < gap.size(); i++)
	{
		if (gap[i] >= length / 4)
		{
			gap.resize(i);
			break;
		}
	}
	return gap;
}
vector<int>ShellSort(vector<int>dataSet, vector<int> gap)
{
	for (int g = gap.size() - 1; g >= 0; g--)
	{
		for (int i = gap[g]; i < dataSet.size(); i++)
		{
			int temp = dataSet[i];
			int j = 0;
			for (j = i; j >= gap[g] && dataSet[j - gap[g]] > temp; j -= gap[g])
			{
				dataSet[j] = dataSet[j - gap[g]];
			}
			dataSet[j] = temp;
		}
	}
	return dataSet;
}
int main()
{
	//datasets: 10000, 50000, 100000, 500000, 1000000
	int size[5] = { 10000, 50000, 100000, 500000, 1000000 };
	vector<int>dataSet;
	vector<int>resultSet;
	vector<int>sGap;
	vector<int>hGap;
	for (int s = 0; s < 5; s++)
	{
		dataSet = rngGenerator(dataSet, size[s]);
		sGap = SedgewickGap(sGap);
		hGap = HibbardGap(hGap);
		sGap = GapResize(sGap, size[s]);
		hGap = GapResize(hGap, size[s]);
		cout << "Hibbard sort with dataset size: " << size[s] << " test results" << endl;
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				auto start = high_resolution_clock::now();
				resultSet = ShellSort(dataSet, hGap);
				auto stop = high_resolution_clock::now();
				auto duration = duration_cast<milliseconds>(stop - start);
				cout << duration.count() << " ms" << "        ";
				resultSet.clear();
			}
			cout << endl;
			dataSet.clear();
			dataSet = rngGenerator(dataSet, size[s]);
		}
		cout << "Sedgewick sort with dataset size: " << size[s] << " test results" << endl;
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				auto start = high_resolution_clock::now();
				resultSet = ShellSort(dataSet, sGap);
				auto stop = high_resolution_clock::now();
				auto duration = duration_cast<milliseconds>(stop - start);
				cout << duration.count() << " ms" << "        ";
				resultSet.clear();
			}
			cout << endl;
			dataSet.clear();
			dataSet = rngGenerator(dataSet, size[s]);
		}
		dataSet.clear();
		sGap.clear();
		hGap.clear();
	}
}
