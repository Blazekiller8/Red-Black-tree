#include <cstddef>
#include <iostream>

enum Color { RED, BLACK };

struct Node {
  int key;
  int value;
  Color color;
  Node *left, *right, *parent;

  Node(int key, int value)
      : key(key), value(value), color(RED), left(nullptr), right(nullptr),
        parent(nullptr) {}
};

class RedBlackTree {
private:
  Node *root;

  // Helper functions
  void rotateLeft(Node *&, Node *&);
  void rotateRight(Node *&, Node *&);
  void fixInsertion(Node *&, Node *&);
  void transplant(Node *, Node *);
  void fixDeletion(Node *);

  void inOrderPrint(Node *node) {
    if (node == nullptr)
      return;
    inOrderPrint(node->left);
    std::cout << "(" << node->key << " , " << node->value << ") -> ";
    inOrderPrint(node->right);
  }

  void preOrderPrint(Node *node) {
    if (node == nullptr)
      return;
    std::cout << "(" << node->key << " , " << node->value << ") -> ";
    preOrderPrint(node->left);
    preOrderPrint(node->right);
  }

  void postOrderPrint(Node *node) {
    if (node == nullptr)
      return;
    postOrderPrint(node->left);
    postOrderPrint(node->right);
    std::cout << "(" << node->key << " , " << node->value << ") -> ";
  }

public:
  // Creation
  RedBlackTree() : root(nullptr) {}

  Node *getRoot() { return root; }

  // Freeing
  void clear(Node *node) {
    if (node == nullptr)
      return;
    clear(node->left);
    clear(node->right);
    delete node;
    node = nullptr;
  }

  void destroy() {
    clear(root);
    root = nullptr;
  }

  // Operations
  void insert(int key, int value);
  void deleteNode(int key);
  Node *search(int key);
  Node *minimum(Node *root);
  Node *maximum(Node *root);
  Node *successor(Node *root);
  Node *predecessor(Node *root);

  // Print functions
  void inOrderPrint() { inOrderPrint(root); }
  void preOrderPrint() { preOrderPrint(root); }
  void postOrderPrint() { postOrderPrint(root); }

  // Dimensions
  int height(Node *node) {
    if (node == nullptr) {
      return 0;
    }
    return std::max(height(node->left), height(node->right)) + 1;
  }

  int depth(Node *node) {
    int d = 0;
    while (node != root) {
      d++;
      node = node->parent;
    }
    return d;
  }
};

// Left rotation
void RedBlackTree::rotateLeft(Node *&root, Node *&pt) {
  Node *pt_right = pt->right;

  pt->right = pt_right->left;
  if (pt->right != nullptr)
    pt->right->parent = pt;

  pt_right->parent = pt->parent;
  if (pt->parent == nullptr)
    root = pt_right;
  else if (pt == pt->parent->left)
    pt->parent->left = pt_right;
  else
    pt->parent->right = pt_right;

  pt_right->left = pt;
  pt->parent = pt_right;
}

// Right rotation
void RedBlackTree::rotateRight(Node *&root, Node *&pt) {
  Node *pt_left = pt->left;

  pt->left = pt_left->right;
  if (pt->left != nullptr)
    pt->left->parent = pt;

  pt_left->parent = pt->parent;
  if (pt->parent == nullptr)
    root = pt_left;
  else if (pt == pt->parent->left)
    pt->parent->left = pt_left;
  else
    pt->parent->right = pt_left;

  pt_left->right = pt;
  pt->parent = pt_left;
}

// Insertion fixup
void RedBlackTree::fixInsertion(Node *&root, Node *&pt) {
  Node *parent_pt = nullptr;
  Node *grand_parent_pt = nullptr;

  while ((pt != root) && (pt->color != BLACK) && (pt->parent->color == RED)) {
    parent_pt = pt->parent;
    grand_parent_pt = pt->parent->parent;

    // Case : A
    if (parent_pt == grand_parent_pt->left) {
      Node *uncle_pt = grand_parent_pt->right;
      if (uncle_pt != nullptr && uncle_pt->color == RED) {
        grand_parent_pt->color = RED;
        parent_pt->color = BLACK;
        uncle_pt->color = BLACK;
        pt = grand_parent_pt;
      } else {
        if (pt == parent_pt->right) {
          rotateLeft(root, parent_pt);
          pt = parent_pt;
          parent_pt = pt->parent;
        }
        rotateRight(root, grand_parent_pt);
        std::swap(parent_pt->color, grand_parent_pt->color);
        pt = parent_pt;
      }
    } else {
      // Case : B
      Node *uncle_pt = grand_parent_pt->left;
      if ((uncle_pt != nullptr) && (uncle_pt->color == RED)) {
        grand_parent_pt->color = RED;
        parent_pt->color = BLACK;
        uncle_pt->color = BLACK;
        pt = grand_parent_pt;
      } else {
        if (pt == parent_pt->left) {
          rotateRight(root, parent_pt);
          pt = parent_pt;
          parent_pt = pt->parent;
        }
        rotateLeft(root, grand_parent_pt);
        std::swap(parent_pt->color, grand_parent_pt->color);
        pt = parent_pt;
      }
    }
  }
  root->color = BLACK;
}

void RedBlackTree::transplant(Node *u, Node *v) {
  if (u->parent == nullptr)
    root = v;
  else if (u == u->parent->left)
    u->parent->left = v;
  else
    u->parent->right = v;
  if (v != nullptr)
    v->parent = u->parent;
}

void RedBlackTree::fixDeletion(Node *x) {
  while (x != root && x->color == BLACK) {
    if (x == x->parent->left) {
      Node *w = x->parent->right;
      if (w->color == RED) {
        w->color = BLACK;
        x->parent->color = RED;
        rotateLeft(root, x->parent);
        w = x->parent->right;
      }
      if (w->left->color == BLACK && w->right->color == BLACK) {
        w->color = RED;
        x = x->parent;
      } else {
        if (w->right->color == BLACK) {
          w->left->color = BLACK;
          w->color = RED;
          rotateRight(root, w);
          w = x->parent->right;
        }
        w->color = x->parent->color;
        x->parent->color = BLACK;
        w->right->color = BLACK;
        rotateLeft(root, x->parent);
        x = root;
      }
    } else {
      Node *w = x->parent->left;
      if (w->color == RED) {
        w->color = BLACK;
        x->parent->color = RED;
        rotateRight(root, x->parent);
        w = x->parent->left;
      }
      if (w->right->color == BLACK && w->left->color == BLACK) {
        w->color = RED;
        x = x->parent;
      } else {
        if (w->left->color == BLACK) {
          w->right->color = BLACK;
          w->color = RED;
          rotateLeft(root, w);
          w = x->parent->left;
        }
        w->color = x->parent->color;
        x->parent->color = BLACK;
        w->left->color = BLACK;
        rotateRight(root, x->parent);
        x = root;
      }
    }
  }
  x->color = BLACK;
}

// Insertion
void RedBlackTree::insert(int key, int value) {
  Node *pt = new Node(key, value);
  // Perform the normal BST insertion
  Node *y = nullptr;
  Node *x = root;
  while (x != nullptr) {
    y = x;
    if (pt->key < x->key)
      x = x->left;
    else
      x = x->right;
  }
  pt->parent = y;
  if (y == nullptr)
    root = pt;
  else if (pt->key < y->key)
    y->left = pt;
  else
    y->right = pt;

  // Fix the Red-Black tree violations
  fixInsertion(root, pt);
}

// Search
Node *RedBlackTree::search(int key) {
  Node *pt = root;
  while (pt != nullptr && pt->key != key) {
    if (key < pt->key)
      pt = pt->left;
    else
      pt = pt->right;
  }
  return pt;
}

// Minimum
Node *RedBlackTree::minimum(Node *root) {
  Node *pt = root;
  while (pt->left != nullptr)
    pt = pt->left;
  return pt;
}

// Maximum
Node *RedBlackTree::maximum(Node *root) {
  Node *pt = root;
  while (pt->right != nullptr)
    pt = pt->right;
  return pt;
}

// Successor
Node *RedBlackTree::successor(Node *root) {
  Node *pt = root;
  if (pt->right != nullptr)
    return minimum(pt->right);
  Node *parent_pt = pt->parent;
  while (parent_pt != nullptr && pt == parent_pt->right) {
    pt = parent_pt;
    parent_pt = pt->parent;
  }
  return parent_pt;
}

// Predecessor
Node *RedBlackTree::predecessor(Node *root) {
  Node *pt = root;
  if (pt->left != nullptr)
    return maximum(pt->left);
  Node *parent_pt = pt->parent;
  while (parent_pt != nullptr && pt == parent_pt->left) {
    pt = parent_pt;
    parent_pt = pt->parent;
  }
  return parent_pt;
}

void RedBlackTree::deleteNode(int key) {
  Node *z = search(key);
  if (z == nullptr)
    return;

  Node *x, *y = z;
  bool yOriginalColor = y->color;
  if (z->left == nullptr) {
    x = z->right;
    transplant(z, z->right);
  } else if (z->right == nullptr) {
    x = z->left;
    transplant(z, z->left);
  } else {
    y = minimum(z->right);
    yOriginalColor = y->color;
    x = y->right;
    if (y->parent == z)
      x->parent = y;
    else {
      transplant(y, y->right);
      y->right = z->right;
      y->right->parent = y;
    }
    transplant(z, y);
    y->left = z->left;
    y->left->parent = y;
    y->color = z->color;
  }
  if (yOriginalColor == BLACK)
    fixDeletion(x);
  delete z;
}
