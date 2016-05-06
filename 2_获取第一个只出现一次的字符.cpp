#include <iostream>
#include <cassert>
#include <queue>
using namespace std;

/*
题目描述

请实现一个函数用来找出字符流中第一个只出现一次的字符。例如，当从字符流中只读出前两个字符"go"时，第一个只出现一次的字符是"g"。当从该字符流中读出前六个字符“google"时，第一个只出现一次的字符是"l"。 
输出描述:
如果当前字符流没有存在出现一次的字符，返回#字符。
*/

//从一串字符串中读取
char FirstAppearOnce(const char *str)
{
	assert(str);
	if ('\0' == *str)
	{
		return '#';
	}

	const char *ptr = str;
	int arr[26] = { 0 };
	while (*ptr != '\0')
	{
		arr[*ptr - 'a']++;
		++ptr;
	}
	ptr = str;
	while (*ptr != '\0')
	{
		if (1 == arr[*ptr - 'a'])
		{
			return *ptr;  //找到
		}
		++ptr;
	}
	//没找到
	return '#';
}

void Test1()
{
	char *str = "aabbcdde";
	char ret = FirstAppearOnce(str);
	cout << ret << endl;

	char *str1 = "aabbcc";
	char ret1 = FirstAppearOnce(str1);
	cout << ret1 << endl;

	char *str2 = "";
	char ret2 = FirstAppearOnce(str2);
	cout << ret2 << endl;
}


//使用类，随时添加字符
	class Solution
	{
	public:
		//Insert one char from stringstream
		void Insert(char ch)
		{
			if (0 == _Arr[ch])  //第一次出现
			{
				_Arr[ch] = 1;
				_Que.push(ch);
			}
			else    //多次出现
			{
				_Arr[ch] = -1;
			}
		}
		//return the first appearence once char in current stringstream
		char FirstAppearingOnce()
		{
			char ret = '#';
			queue<int> tmp = _Que;
			if (!tmp.empty())
			{
				while (!tmp.empty())
				{
					ret = tmp.front();
					tmp.pop();
					if (1 == _Arr[ret])
					{
						return ret;
					}
				}
			}
			return '#';
		}
	private:
		int _Arr[256] = { 0 };
		queue<int> _Que;
	};

void Test3()
{
	//!@$%^&*()_
	Solution s1;
	s1.Insert('!');
	char ret = s1.FirstAppearingOnce();
	cout << ret << endl;
	s1.Insert('@');
	ret = s1.FirstAppearingOnce();
	cout << ret << endl;
	s1.Insert('$');
	ret = s1.FirstAppearingOnce();
	cout << ret << endl;
	s1.Insert('%');
	ret = s1.FirstAppearingOnce();
	cout << ret << endl;
	s1.Insert('^');
	ret = s1.FirstAppearingOnce();
	cout << ret << endl;
	s1.Insert('&');
	ret = s1.FirstAppearingOnce();
	cout << ret << endl;
	s1.Insert('*');
	ret = s1.FirstAppearingOnce();
	cout << ret << endl;
	s1.Insert('(');
	ret = s1.FirstAppearingOnce();
	cout << ret << endl;
	s1.Insert(')');
	ret = s1.FirstAppearingOnce();
	cout << ret << endl;

	//Solution s1;
	//s1.Insert('B');
	//char ret = s1.FirstAppearingOnce();
	//cout << ret << endl;
	//s1.Insert('a');
	//ret = s1.FirstAppearingOnce();
	//cout << ret << endl;
	//s1.Insert('b');
	//ret = s1.FirstAppearingOnce();
	//cout << ret << endl;
	//s1.Insert('y');
	//ret = s1.FirstAppearingOnce();
	//cout << ret << endl;
	//s1.Insert('B');
	//ret = s1.FirstAppearingOnce();
	//cout << ret << endl;
	//s1.Insert('a');
	//ret = s1.FirstAppearingOnce();
	//cout << ret << endl;
	//s1.Insert('b');
	//ret = s1.FirstAppearingOnce();
	//cout << ret << endl;
	//s1.Insert('y');
	//ret = s1.FirstAppearingOnce();
	//cout << ret << endl;

	//Solution s2;
	//s2.Insert('a');
	//s2.Insert('a');
	//s2.Insert('a');
	//char ret2 = s2.FirstAppearingOnce();
	//cout << ret2 << endl;

	//Solution s3;
	//char ret3 = s3.FirstAppearingOnce();
	//cout << ret3 << endl;
}
int main()
{
	Test3();
	return 0;
}
