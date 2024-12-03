#include <iostream>
using namespace std;

template <typename T>
struct Node {
  T val;
  Node *left;
  Node *right;
  Node() : val(0), left(nullptr), right(nullptr) {}
  Node(T x) : val(x), left(nullptr), right(nullptr) {}
  Node(T x, Node *left, Node *right) : val(x), left(left), right(right) {}
};

template <typename T>
T max(T a, T b) {
  if (a < b) {
    return b;
  }else{
    return a;
  }
}

template <typename T>
class BinarySearchTree {
private:
  Node<T> *root;
  int size;

  Node<T> *insert(Node<T> *node, T val) {
    if (node == nullptr) {
      size++;
      return new Node<T>(val);
    }
    if (val < node->val) {
      node->left = insert(node->left, val);
    } else if (val > node->val) {
      node->right = insert(node->right, val);
    }
    return node;
  }

  bool find(Node<T> *node, T val){
    if (node == nullptr) return false;
    if (node->val == val) return true;
    if (val < node->val) return find(node->left, val);
    return find(node->right, val);
  }

  Node<T> *remove(Node<T> *node, T val) {
    if (node == nullptr) {
      return node;
    }
    if (val < node->val) {
      node->left = remove(node->left, val);
    } else if (val > node->val) {
      node->right = remove(node->right, val);
    } else {
      if (node->left == nullptr) {
        Node<T> *temp = node->right;
        delete node;
        size--;
        return temp;
      } else if (node->right == nullptr) {
        Node<T> *temp = node->left;
        delete node;
        size--;
        return temp;
      }
      Node<T> *temp = node->right;
      while (temp->left != nullptr) {
        temp = temp->left;
      }
      node->val = temp->val;
      node->right = remove(node->right, temp->val);
    }
    return node;
  }

  void inorder(Node<T> *node) {
    if (node == nullptr) {
      return;
    }
    inorder(node->left);
    std::cout << node->val << " ";
    inorder(node->right);
  }

  void preorder(Node<T> *node) {
    if (node == nullptr) {
      return;
    }
    std::cout << node->val << " ";
    preorder(node->left);
    preorder(node->right);
  }

  void postorder(Node<T> *node) {
    if (node == nullptr) {
      return;
    }
    postorder(node->left);
    postorder(node->right);
    std::cout << node->val << " ";
  }

  bool isBalanced(Node<T> *node) {
    if (node == nullptr) {
      return true;
    }
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);
    return abs(leftHeight - rightHeight) <= 1 && isBalanced(node->left) && isBalanced(node->right);
  }

  int height(Node<T> *node) {
    if (node == nullptr) {
      return 0;
    }
    return 1 + max(height(node->left), height(node->right));
  }

  bool isLeaf(Node<T> *node) {
    return node->left == nullptr && node->right == nullptr;
  }


public:

  BinarySearchTree() : root(nullptr), size(0) {}

  ~BinarySearchTree() {
    this->clear();
  }

  void insert(T val) {
    root = insert(root, val);
  }

  bool find(T val){
    return find(root, val);
  }

  void remove(T val) {
    root = remove(root, val);
  }

  void display(){
    int choice;
    std::cout << std::endl << "1. Inorder"<<std::endl<<"2. Preorder"<<std::endl<<"3. Postorder"<<std::endl<<std::endl;
    std::cin >> choice;
    switch (choice) {
      case 1:
        inorder(root);
        break;
      case 2:
        preorder(root);
        break;
      case 3:
        postorder(root);
        break;
      default:
        std::cout << "Invalid choice"<<std::endl;
    }
    std::cout << std::endl;
  }

  void clear() {
    while (root) {
      remove(root->val);
    }
  }

  int getSize() {
    return size;
  }

  bool isEmpty() {
    return size == 0;
  }

  Node<T> *getRoot() const {
    return root;
  }

  bool isBalanced() {
    return isBalanced(root);
  }

  int height() {
    return height(root);
  }

};

int main() {
    BinarySearchTree<int> bst;

    // Insertar elementos en el árbol
    bst.insert(10);
    bst.insert(5);
    bst.insert(20);
    bst.insert(3);
    bst.insert(7);
    bst.insert(15);
    bst.insert(25);

    // Mostrar el árbol en diferentes órdenes
    std::cout << "Mostrar arbol en diferentes ordenes:" << std::endl;
    bst.display();

    // Verificar si el árbol está balanceado
    if (bst.isBalanced()) {
        std::cout << "El arbol está balanceado." << std::endl;
    } else {
        std::cout << "El arbol no está balanceado." << std::endl;
    }

    // Verificar el tamaño del árbol
    std::cout << "El tamaño del arbol es: " << bst.getSize() << std::endl;

    // Buscar un valor
    int valueToFind = 15;
    if (bst.find(valueToFind)) {
        std::cout << "El valor " << valueToFind << " esta en el arbol." << std::endl;
    } else {
        std::cout << "El valor " << valueToFind << " no esta en el arbol." << std::endl;
    }

    // Eliminar un valor
    std::cout << "Eliminando el valor 10..." << std::endl;
    bst.remove(10);

    // Mostrar el árbol después de la eliminación
    std::cout << "Arbol despues de eliminar 10:" << std::endl;
    bst.display();

    // Verificar si el árbol está vacío
    if (bst.isEmpty()) {
        std::cout << "El arbol esta vacío." << std::endl;
    } else {
        std::cout << "El arbol no esta vacío." << std::endl;
    }

    return 0;
}
