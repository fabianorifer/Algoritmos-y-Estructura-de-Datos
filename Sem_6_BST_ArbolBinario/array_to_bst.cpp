//
// Created by luisr on 25/09/2024.
//
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
 /*
class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return convertToBST(nums, 0, nums.size() - 1);
    }

private:
    TreeNode* convertToBST(vector<int>& nums, int left, int right) {
        if (left > right) {
            return nullptr;
        }

        // Elige el elemento del medio como la raíz
        int mid = left + (right - left) / 2;
        TreeNode* node = new TreeNode(nums[mid]);

        // Construir el subárbol izquierdo y derecho recursivamente
        node->left = convertToBST(nums, left, mid - 1);
        node->right = convertToBST(nums, mid + 1, right);

        return node;
    }
};
*/