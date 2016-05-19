#include <iostream>
#include <vector>
using namespace std;

/*
	题目描述:
					   输入某二叉树的前序遍历和中序遍历的结果，请重建出该二叉树。假设输入的前序遍历和中序遍历的结果中都不含重复的数字。例如输入前序遍历序列{1,2,4,7,3,5,6,8}和中序遍历序列{4,7,2,1,5,3,8,6}，则重建二叉树并返回。
*/

 struct TreeNode 
 {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) 
		 : val(x)
		 , left(NULL)
		 , right(NULL)
	 {}
 };

 class Solution
 {
 public:
	 struct TreeNode* reConstructBinaryTree(vector<int> pre, vector<int> in)
	 {
		 int sz = pre.size();
		 int index = 0;
		 if (sz <= 0)
		 {
			 return NULL;
		 }
		 //根节点
		 int val = pre[index];
		 TreeNode *head = new TreeNode(val);
		 index++;

		 auto aim = find(in.begin(), in.end(), val);

		 
	 }
 };


 class Solution
 {
 public:
	 struct TreeNode* reConstructBinaryTree(vector<int> pre, vector<int> in) 
	 {
		 int inlen = in.size();
		 if (inlen == 0)
		 {
			 return NULL;
		 }
		 vector<int> left_pre, right_pre, left_in, right_in;
	
		 TreeNode* head = new TreeNode(pre[0]);
	
		 int gen = 0;
		 for (int i = 0; i<inlen; i++)
		 {
			 if (in[i] == pre[0])
			 {
				 gen = i;
				 break;
			 }
		 }
	
		 for (int i = 0; i<gen; i++)
		 {
			 left_in.push_back(in[i]);
			 left_pre.push_back(pre[i + 1]);
		 }
		 for (int i = gen + 1; i<inlen; i++)
		 {
			right_in.push_back(in[i]);
			 right_pre.push_back(pre[i]);
		 }

    //转化为子问题
		 head->left = reConstructBinaryTree(left_pre, left_in);
		 head->right = reConstructBinaryTree(right_pre, right_in);
		 return head;
	 }
 };
