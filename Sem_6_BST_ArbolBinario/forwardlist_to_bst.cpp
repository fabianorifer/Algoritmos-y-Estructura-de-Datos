//
// Created by luisr on 25/09/2024.
//
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

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
    TreeNode* sortedListToBST(ListNode* head) {
        // Caso base: si la lista está vacía, retorna nullptr.
        if (!head) return nullptr;

        // Caso base: si solo hay un nodo, ese nodo será la raíz.
        if (!head->next) return new TreeNode(head->val);

        // Encontrar el nodo medio y el nodo anterior al medio.
        ListNode *slow = head, *fast = head, *prev = nullptr;
        while (fast && fast->next) {
            prev = slow;
            slow = slow->next;
            fast = fast->next->next;
        }

        // Desconectar el subárbol izquierdo.
        if (prev) prev->next = nullptr;

        // El nodo medio será la raíz del BST.
        TreeNode* root = new TreeNode(slow->val);

        // Recursivamente construir el subárbol izquierdo y derecho.
        root->left = sortedListToBST(head);  // El subárbol izquierdo será de head a prev.
        root->right = sortedListToBST(slow->next);  // El subárbol derecho será de slow->next en adelante.

        return root;
    }
};
*/