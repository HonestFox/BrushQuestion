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
