#include <iostream>
#include <vector>
using namespace std;



/*
	题目描述
	把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。
	输入一个非递减序列的一个旋转，输出旋转数组的最小元素。例如数组{3,4,5,1,2}为{1,2,3,4,5}的一个旋转，该数组的最小值为1。
*/

class Solution
{
public:
	int minNumberInRotateArray(vector<int> rotateArray)
	{

		int ret = rotateArray[0];
		for (int i = 0; i < rotateArray.size() - 1; i++)
		{
			if (rotateArray[i] > rotateArray[i + 1])
			{
				ret = rotateArray[i + 1];
			}
		}
		return ret;
	}
};

void Test()
{
	vector<int> vi = { 3,4,5,1,2 };
	Solution s1;
	cout << s1.minNumberInRotateArray(vi) << endl;
}

int main()
{
	Test();
	return 0;
}






//改进方法，基于二分查找

class Solution_Better
{
public:
	int minNumberInRotateArray(vector<int> rotateArray)
	{
		if (rotateArray.size() == 0)
		{
			return 0;
		}
		int left = 0;
		int right = rotateArray.size() - 1;
		int mid = 0;
		while (left <= right)
		{
			mid = left + (right - left) / 2;                        //防止超出int的范围 所以不能写成 mid =(left + right) / 2  的形式
			if (rotateArray[mid] > rotateArray[right])
			{
				left = mid + 1;
			}
			else if (rotateArray[mid] < rotateArray[right])
			{
				right = mid;
			}
			else// if (rotateArray[mid] == rotateArray[right])
			{
				right = right - 1;
			}

			if (left >= right)
			{
				break;
			}
		}
		return rotateArray[left];
	}
};
