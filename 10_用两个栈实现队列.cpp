#include <iostream>
#include <stack>
using namespace std;


/*
	题目描述
	用两个栈来实现一个队列，完成队列的Push和Pop操作。 队列中的元素为int类型。
*/

class Solution
{
public:
	void push(int node) 
	{
		stack1.push(node);
	}

	int pop() 
	{
		if (stack2.empty())
		{
			converse();
		}
		int ret = stack2.top();
		stack2.pop();
		return ret;
	}

protected:
	void converse()
	{
		while (!stack1.empty())
		{
			stack2.push(stack1.top() );
			stack1.pop();
		}
	}

private:
	stack<int> stack1;
	stack<int> stack2;
};





int main()
{
	Solution s1;
	s1.push(1);
	s1.push(2);
	s1.push(3);
	cout << s1.pop() << endl;
	cout << s1.pop() << endl;

	cout << s1.pop() << endl;
	s1.push(4);
	cout << s1.pop() << endl;


	return 0;
}
