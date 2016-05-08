//VS下用我想到的几个测试用例测了下都能通过，但传到牛客死活过不去，提示崩溃 也是醉了  有空再看看问题

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
	题目描述
	在一个排序的链表中，存在重复的结点，请删除该链表中重复的结点，重复的结点不保留，返回链表头指针。 例如，链表1->2->3->3->4->4->5 处理后为 1->2->5
*/
struct ListNode
{
	int val;
	struct ListNode *next;
	ListNode(int x) 
		:val(x)
		, next(NULL)
	{}
};

class Solution
{
public:
	Solution()
		:pHead(NULL)
	{}

	void PushBack(int data)
	{
		ListNode *NewNode = new ListNode(data);
		if (pHead == NULL)
		{
			pHead = NewNode;
			pTail = pHead;
		}
		else
		{
			pTail->next = NewNode;
			pTail = NewNode;
		}
	}

	void Print()
	{
		ListNode *cur = pHead;
		while (cur)
		{
			cout << cur->val << "->";
			cur = cur->next;
		}
		cout << "NULL" <<  endl;
	}


	void DeleteNode(ListNode *pNode, ListNode *pHead)		//删除某一结点
	{
		if (pNode == NULL)
		{
			return;
		}
		if (pNode->next == NULL)
		{
			//找到该结点的前一个节点
			ListNode *cur = pHead;
			while (cur->next  != pNode)
			{
				cur = cur->next;
			}
			//释放pNode 并将它的前一个节点cur的next指针指向NULL
			cur->next = NULL;
			delete pNode;
			pNode = NULL;
			return;
		}
		ListNode *del = pNode->next;
		pNode->val = del->val;
		pNode->next = del->next;
		delete del;
	}

	ListNode* deleteDuplication(ListNode* pHead)
	{
		if (pHead == NULL)
		{
			return pHead;
		}
		ListNode *prev = pHead;
		ListNode *cur = pHead->next;
		ListNode *DelLater = NULL;
		bool IsDel = false;
		while (cur)
		{
			if (cur->val == prev->val)    //遇到重复的元素 先保留第一个元素，删除后面与第一个元素相同的所有元素， 之后再删除掉第一个元素
			{
				IsDel = true;
				DelLater = prev;
				while (cur->val == DelLater->val)
				{
					DeleteNode(cur, pHead);
				}
			}
			//除首元素之外的相同元素均删掉后 删掉首元素
			if (IsDel == true)
			{
				if (DelLater->next == NULL && DelLater == pHead)   //若DelLater为唯一的元素
				{
					delete DelLater;
					pHead = NULL;
					return pHead;
				}
				DeleteNode(DelLater, pHead);
				cur = prev;
				if (DelLater == pHead)
				{
					pHead = cur;
				}
			}
			if (!IsDel)
			{
				prev = cur;
				cur = cur->next;
			}
			else
			{
				cur = prev->next;
				IsDel = false;
			}
			if (cur == NULL)
			{
				break;
			}
		}
		return pHead;
	}


//private:
	ListNode *pHead;
	ListNode *pTail;
};

void Test1()
{
	Solution s1;
	s1.PushBack(1);
	s1.PushBack(2);
	s1.PushBack(3);
	s1.PushBack(3);
	s1.PushBack(4);
	s1.PushBack(4);
	s1.PushBack(5);

	//s1.PushBack(1);
	//s1.PushBack(1);
	//s1.PushBack(1);
	//s1.PushBack(2);


	//s1.PushBack(1);
	//s1.PushBack(1);
	//s1.PushBack(1);

	s1.Print();
	ListNode * ret = s1.deleteDuplication(s1.pHead);

}
int main()
{
	Test1();
	return 0;
}
