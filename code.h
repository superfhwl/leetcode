#ifndef __CODE_H__
#define __CODE_H__

#include <iostream>


// Definition for a binary tree node.
class TreeNode {
public:
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    void Print()
    {
        std::cout << "[";

        if (left != nullptr)
            std::cout << left->val << "<-";
        else
            std::cout << "null<-";
        
        std::cout << val;

        if (right != nullptr)
            std::cout << "->" << right->val;
        else
            std::cout << "->null";

        std::cout << "]";
    }
};



void call_code_94();
void call_code_123();
void call_code_4();
void call_code_296();
void call_code_98();
void call_code_17();

#endif // __CODE_H__
