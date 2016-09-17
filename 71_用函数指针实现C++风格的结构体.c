#include <stdio.h>
#include <stdlib.h>

struct LinkListNode;
typedef void(*pPushBack)(struct LinkListNode *This, int data);
struct LinkListNode* BuyNode(data);

typedef struct LinkListNode
{
	int _val;
	struct LinkListNode *_next;
	pPushBack _PushBack;
}LinkListNode;

void PushBack(LinkListNode *This, int data)
{
	if (This == NULL)
	{
		This = BuyNode(data);
	}
	LinkListNode *NewNode = BuyNode(data);
	LinkListNode *cur = This;
	while (cur && cur->_next != NULL)
	{
		cur = cur->_next;
	}
	cur->_next = NewNode;
}

LinkListNode* BuyNode(int data)
{
	LinkListNode *NewNode = (LinkListNode*)malloc(sizeof(LinkListNode));
	NewNode->_val = data;
	NewNode->_next = NULL;
	NewNode->_PushBack = &PushBack;
	return NewNode;
}

void Init(struct LinkListNode **This, int data)
{
	(*This) = BuyNode(data);
	(*This)->_val = data;
	(*This)->_next = NULL;
	(*This)->_PushBack = &PushBack;
}

int main()
{
	LinkListNode *Node1 = NULL;
	Init(&Node1, 1);
	Node1->_PushBack(Node1, 2);
	Node1->_PushBack(Node1, 3);
	Node1->_PushBack(Node1, 4);
	return 0;
}
