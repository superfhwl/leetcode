
#include "code.h"
#include <vector>
#include "gtest/gtest.h"

#include <map>
#include <utility>
#include <limits.h>


using namespace std;

#define DEBUG
#ifdef DEBUG
    #define OJDBG std::cout
#else
    #define OJDBG  0 && std::cout
#endif

void call_code_98(){}

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

class Solution_98 {
private:

    TreeNode* getLeftLeaf()
    {
        TreeNode *node = m_root;
        while(node->left != nullptr)
        {
            node = node->left;
        }

        return node;
    }

    TreeNode* getRightLeaf()
    {
        TreeNode* node = m_root;
        while(node->right != nullptr)
        {
            node = node->right;
        }

        return node;
    }


    TreeNode* m_root;

public:
    bool isValidBST(TreeNode* root) {
        // 空为合法
        if (root == nullptr)
            return true;

        // 单独一个根节点合法
        if (root->left == nullptr && root->right == nullptr)
            return true;


        m_root = root;
        
        // 先求出最左叶子结点作为lower，以及最右叶子结点作为upper
        int lower = getLeftLeaf()->val;
        int upper = getRightLeaf()->val;

        return isValidBST(root, lower, upper);
    }

    bool isValidBST(TreeNode* root, int lower, int upper)
    {
        OJDBG << "lower=" << lower << " upper=" << upper << endl;
        if (root->val == lower)
        {
            // 等于下界时，只能是最左叶子，否则都是错误
            if (root == getLeftLeaf() && root != m_root)
                return true;
            else
                return false;
        }

        if (root->val == upper)
        {
            // 等于上界时，只能是最右叶子，否则都是错误
            if (root == getRightLeaf() && root != m_root)
                return true;
            else
                return false;
        }

        if (root->val < lower || root->val > upper)
        {
            // 超过上下界就是错误
            OJDBG << "Out of bound! val=" << root->val << endl;
            return false;
        }

        root->Print();

        // 1. 从根节点出发，有左子树就看左子树，递归进入
        // 2. 没有左子树就看右子树，递归进入
        // 3. 递归进入时，判断子树是否满足要求，若不满足直接返回失败
        // 4. 向左进入，则缩小upper，向右进入，则放大lower

        if (root->left != nullptr)
        {
            int newUpper = root->val;
            OJDBG << "newUpper=" << newUpper << endl;
            if(!isValidBST(root->left, lower, newUpper))
            {
                // 迭代退出，一路返回失败
                return false;
            }
        }

        if (root->right != nullptr)
        {
            int newLower = root->val;
            OJDBG << "newLower=" << newLower << endl;
            if(!isValidBST(root->right, newLower, upper))
            {
                return false;
            }
        }

        return true;
    }

}; 



TEST(Test_Code_98, test1)
{
    TreeNode root(2);
    TreeNode left(1);
    TreeNode right(3);
    root.left = &left;
    root.right = &right;

    Solution_98 sln;
    EXPECT_EQ(sln.isValidBST(&root), true);
}

TEST(Test_Code_98, test2)
{
    TreeNode root(5);
    TreeNode node_51(1);
    TreeNode node_54(4);
    TreeNode node_43(3);
    TreeNode node_46(6);
    root.left = &node_51;
    root.right = &node_54;
    node_54.left = &node_43;
    node_54.right = &node_46;

    Solution_98 sln;
    EXPECT_EQ(sln.isValidBST(&root), false);
}

TEST(Test_Code_98, test3)
{
    TreeNode root(10);
    TreeNode node_10_5(5);
    TreeNode node_10_15(15);
    TreeNode node_15_6(6);
    TreeNode node_15_20(20);
    root.left = &node_10_5;
    root.right = &node_10_15;
    node_10_15.left = &node_15_6;
    node_10_15.right = &node_15_20;

    Solution_98 sln;
    EXPECT_EQ(sln.isValidBST(&root), false);
}