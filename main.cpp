#include "RedBlackTree.hpp"
#include <iostream>

using namespace std;

void printMenu() {
  cout << "Red-Black Tree Operations:" << endl;
  cout << "1. Insert" << endl;
  cout << "2. Delete" << endl;
  cout << "3. Search" << endl;
  cout << "4. Print In-Order" << endl;
  cout << "5. Print Pre-Order" << endl;
  cout << "6. Print Post-Order" << endl;
  cout << "7. Get Height" << endl;
  cout << "8. Get Depth" << endl;
  cout << "9. Find Minimum" << endl;
  cout << "10. Find Maximum" << endl;
  cout << "11. Find Successor" << endl;
  cout << "12. Find Predecessor" << endl;
  cout << "13. Clear" << endl;
  cout << "14. Exit" << endl;
  cout << "Enter your choice: ";
}

int main() {
  RedBlackTree tree;
  int choice, data, key;

  while (true) {
    printMenu();
    cin >> choice;

    switch (choice) {
    case 1:
      cout << "\nEnter the key of the data: ";
      cin >> key;
      cout << "\nEnter the data to be inserted: ";
      cin >> data;
      tree.insert(key, data);
      break;
    case 2:
      cout << "Enter the key of the data to be deleted: ";
      cin >> key;
      tree.deleteNode(key);
      break;
    case 3:
      cout << "Enter the key of the data to be searched: ";
      cin >> key;
      if (tree.search(key) != nullptr) {
        cout << key << " found in the tree." << endl;
      } else {
        cout << key << " not found in the tree." << endl;
      }
      break;
    case 4:
      cout << "In-Order Traversal:" << endl;
      tree.inOrderPrint();
      break;
    case 5:
      cout << "Pre-Order Traversal:" << endl;
      tree.preOrderPrint();
      break;
    case 6:
      cout << "Post-Order Traversal:" << endl;
      tree.postOrderPrint();
      break;
    case 7:
      cout << "Height: " << tree.height(tree.getRoot()) << endl;
      break;
    case 8:
      cout << "Depth: " << tree.depth(tree.getRoot()) << endl;
      break;
    case 9:
      cout << "Minimum value in the tree: " << tree.minimum(tree.getRoot())
           << endl;
      break;
    case 10:
      cout << "Maximum value in the tree: " << tree.maximum(tree.getRoot())
           << endl;
      break;
    case 11:
      cout << "Enter the key for which successor is to be found: ";
      cin >> key;
      cout << "Successor of " << key << " is "
           << tree.successor(tree.search(key)) << endl;
      break;
    case 12:
      cout << "Enter the key for which predecessor is to be found: ";
      cin >> key;
      cout << "Predecessor of " << key << " is "
           << tree.predecessor(tree.search(key)) << endl;
      break;
    case 13:
      tree.clear(tree.getRoot());
      break;
    case 14:
      tree.destroy();
      exit(0);
    default:
      cout << "Invalid choice. Try again." << endl;
    }
    cout << endl;
  }
  return 0;
}