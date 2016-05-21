#include <iostream>
using namespace std;

/*
	题目描述
	大家都知道斐波那契数列，现在要求输入一个整数n，请你输出斐波那契数列的第n项。
	0 1 1 2 3 5 8 ......
	补充
	分别用递归和非递归实现
*/

class Solution
{
public:
	int Fibonacci(int n)			//非递归方式
	{
		int cur = 0;
		int next = 1;
		if (n == 0)
		{
			return 0;
		}
		while (--n)     //1 1    
		{
			int tmp = cur;
			cur = next;
			next += tmp;
		}
		return next;
	}
	int Fibonacci_recurrence(int n)   //递归方式
	{
		if (n <= 1)
		{
			return n;
		}
		else
		{
			return Fibonacci_recurrence(n - 1) + Fibonacci_recurrence(n - 2);
		}
	}
};

int main()
{
	Solution s1;
	cout << s1.Fibonacci_recurrence(0) << endl;
	cout << s1.Fibonacci_recurrence(1) << endl;
	cout << s1.Fibonacci_recurrence(2) << endl;
	cout << s1.Fibonacci_recurrence(3) << endl;
	cout << s1.Fibonacci_recurrence(4) << endl;
	cout << s1.Fibonacci_recurrence(5) << endl;

	return 0;
}
