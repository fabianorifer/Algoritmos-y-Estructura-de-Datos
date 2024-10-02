//
// Created by luisr on 25/09/2024.
//
/*
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        return validate(root, nullptr, nullptr);
    }

private:
    // Función auxiliar recursiva que valida el árbol
    bool validate(TreeNode* node, TreeNode* minNode, TreeNode* maxNode) {
        // Si llegamos a un nodo nulo, es un BST válido
        if (!node) return true;

        // Si el valor del nodo viola las reglas de BST, retorna falso
        if (minNode && node->val <= minNode->val) return false;
        if (maxNode && node->val >= maxNode->val) return false;

        // Verificar el subárbol izquierdo (todos los nodos deben ser < node->val)
        // Verificar el subárbol derecho (todos los nodos deben ser > node->val)
        return validate(node->left, minNode, node) && validate(node->right, node, maxNode);
    }
};
*/