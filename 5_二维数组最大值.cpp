//传到牛客上提示 “段错误:您的程序发生段错误，可能是数组越界，堆栈溢出（比如，递归调用层数太多）等情况引起”
//由于在VS下测试完全通过，所以代码应该是没有问题的




#include <iostream>
#include <vector>
using namespace std;
/*
题目描述

在一个二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。请完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。
输入描述:
array： 待查找的二维数组
target：查找的数字


输出描述:
查找到返回true，查找不到返回false
*/
bool Find(vector<vector<int> > array, int target)
{
	int col = array.size() - 1;
	int row = array[0].size() - 1;
	if (target > array[col][row] || target < array[0][0])
	{
		return false;
	}
	int i = 0;
	int j = row;
	while (i <= col && i >= 0 && j <= row && j >= 0)
	{
		if (array[i][j] == target)
		{
			return true;
		}
		if (array[i][j] < target)
		{
			i++;
		}
		if (array[i][j] > target)
		{
			j--;
		}
	}
	return false;
}
void Test()
{
	vector<vector<int>> vec1;
	vector<int> v1 = { 1, 2, 4 };
	vector<int> v2 = { 3, 4, 5 };
	vector<int> v3 = { 8, 9, 10 };
	vec1 = { v1, v2, v3 };
	if (Find(vec1, 6))
	{
		cout << "找到" << endl;
	}
	else
	{
		cout << "未找到" << endl;
	}
}
int main()
{
	Test();
	return 0;
}
