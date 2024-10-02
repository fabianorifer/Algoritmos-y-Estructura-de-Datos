//
// Created by luisr on 25/09/2024.
//
/*
class BSTIterator {
public:
    // Pila para almacenar los nodos
    stack<TreeNode*> st;

    // Constructor
    BSTIterator(TreeNode* root) {
        // Inicializamos la pila con los nodos del lado izquierdo
        pushAllLeft(root);
    }

    // Devuelve el siguiente número en el recorrido in-order
    int next() {
        // Tomamos el nodo en la parte superior de la pila
        TreeNode* node = st.top();
        st.pop();
        // Después de visitar este nodo, movemos al subárbol derecho
        pushAllLeft(node->right);
        return node->val;
    }

    // Retorna si aún hay más nodos por recorrer
    bool hasNext() {
        return !st.empty();
    }

private:
    // Función auxiliar que empuja todos los nodos del lado izquierdo
    void pushAllLeft(TreeNode* node) {
        while (node) {
            st.push(node);
            node = node->left;
        }
    }
};
*/