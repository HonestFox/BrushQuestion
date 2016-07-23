#include<iostream>
#include<vector>
#include <cassert>
using namespace std;

/*
滑动窗口的最大值
		给定一个数组和滑动窗口的大小，找出所有滑动窗口里数值的最大值。
		例如，如果输入数组{2,3,4,2,6,2,5,1}及滑动窗口的大小3，那么一共存在6个滑动窗口，他们的最大值分别为{4,4,6,6,6,5}； 
		针对数组{2,3,4,2,6,2,5,1}的滑动窗口有以下6个： {[2,3,4],2,6,2,5,1}， {2,[3,4,2],6,2,5,1}， 
		{2,3,[4,2,6],2,5,1}， {2,3,4,[2,6,2],5,1}， {2,3,4,2,[6,2,5],1}， {2,3,4,2,6,[2,5,1]}。
*/

// 用C语言的特性(数组、指针)实现
int* GetSlidingWindowMax(int *Arr, int WindowSize, int ArrSize)
{
	assert(Arr);
	if (NULL == ArrSize)
	{
		return NULL;
	}
	int SlidingWindowNum = ArrSize - WindowSize + 1;      //滑动窗口的数目
	int *RetArr = new int[SlidingWindowNum];
	int CurIndex = 0;
	for (int i = 0; i < SlidingWindowNum; ++i)
	{
		int MaxVal = *(Arr + i);
		for (int j = 1; j < WindowSize; ++j)
		{
			if (MaxVal < *(Arr + i + j))
			{
				MaxVal = *(Arr + i + j);
			}
		}
		*(RetArr + CurIndex++) = MaxVal;
	}
	return RetArr;
}
void Test1()
{
	int arr[] = { 2,3,4,2,6,2,5,1 };
	int sz = sizeof(arr) / sizeof(*arr);
	int SlidingWindowNum = 3;
	int *RetArr = GetSlidingWindowMax(arr, SlidingWindowNum, sz);
	for (int i = 0; i < sz - SlidingWindowNum + 1; ++i)
	{
		cout << *(RetArr + i) << " ";
	}
	cout << endl;
	delete[] RetArr;	//回收并置空
}

// 用C++的特性(容器、引用)实现
vector<int> GetSlidingWindowMaxCpp(const vector<int>& Arr, unsigned int WindowSize)
{
	vector<int> RetArr;
	if (WindowSize > 0)      //若size 小于等于0 则返回空顺序表
	{
		for (int i = 0; i < Arr.size() - WindowSize + 1; ++i)
		{
			int MaxVal = Arr[i];
			for (int j = 1; j < WindowSize; ++j)
			{
				if (MaxVal < Arr[i + j])
				{
					MaxVal = Arr[i + j];
				}
			}
			RetArr.push_back(MaxVal);
		}
	}
	return RetArr;
}

void Test2()
{
	vector<int> arr = { 2,3,4,2,6,2,5,1 };
	vector<int> ret = GetSlidingWindowMaxCpp(arr, 3);
	for (auto &i : ret)
	{
		cout << i << " ";
	}
	cout << endl;
}

int main()
{
	Test1();
	return 0;
}
