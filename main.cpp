#include <iostream>
#include <memory>

template <typename T>
class TreeNode {
public:
    T data;
    std::unique_ptr<TreeNode<T>> left = nullptr;
    std::unique_ptr<TreeNode<T>> right = nullptr;
};

template <typename T>
class BinarySearchTree {
private:
    std::unique_ptr<TreeNode<T>> root = nullptr;

public:
    // Function to add a node to the BST
    void insert(const T& value) {
        root = insertNode(std::move(root), value);
    }

    // Function to search for a value in the BST
    bool search(const T& value) const {
        return searchNode(root.get(), value);
    }

    // Function to modify a node in the BST
    void modify(const T& oldValue, const T& newValue) {
        root = deleteNode(std::move(root), oldValue);
        root = insertNode(std::move(root), newValue);
    }

    // Function to delete a node from the BST
    void remove(const T& value) {
        root = deleteNode(std::move(root), value);
    }

private:
    // Recursive helper function to insert a node into the BST
    std::unique_ptr<TreeNode<T>> insertNode(std::unique_ptr<TreeNode<T>> node, const T& value) {
        if (!node) {
            return std::make_unique<TreeNode<T>>(value);
        }

        if (value < node->data) {
            node->left = insertNode(std::move(node->left), value);
        } else if (value > node->data) {
            node->right = insertNode(std::move(node->right), value);
        }

        return node;
    }

    // Recursive helper function to search for a value in the BST
    bool searchNode(const TreeNode<T>* node, const T& value) const {
        if (!node) {
            return false;
        }

        if (value == node->data) {
            return true;
        } else if (value < node->data) {
            return searchNode(node->left.get(), value);
        } else {
            return searchNode(node->right.get(), value);
        }
    }

    // Recursive helper function to delete a node from the BST
    std::unique_ptr<TreeNode<T>> deleteNode(std::unique_ptr<TreeNode<T>> node, const T& value) {
        if (!node) {
            return nullptr;
        }

        if (value == node->data) {
            if (!node->left) {
                return std::move(node->right);
            } else if (!node->right) {
                return std::move(node->left);
            } else {
                // Node with two children, replace with the in-order successor
                T successorValue = findMin(node->right.get());
                node->data = successorValue;
                node->right = deleteNode(std::move(node->right), successorValue);
            }
        } else if (value < node->data) {
            node->left = deleteNode(std::move(node->left), value);
        } else {
            node->right = deleteNode(std::move(node->right), value);
        }

        return node;
    }

    // Helper function to find the minimum value in a subtree
    T findMin(const TreeNode<T>* node) const {
        while (node->left) {
            node = node->left.get();
        }
        return node->data;
    }
};

int main() {
    BinarySearchTree<int> bst;

    // Insert nodes
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    bst.insert(60);
    bst.insert(80);

    // Search for a value
    std::cout << "Search 40: " << (bst.search(40) ? "Found" : "Not found") << std::endl;

    // Modify a node
    bst.modify(40, 45);

    // Search again after modification
    std::cout << "Search 40: " << (bst.search(40) ? "Found" : "Not found") << std::endl;
    std::cout << "Search 45: " << (bst.search(45) ? "Found" : "Not found") << std::endl;

    // Remove a node
    bst.remove(45);

    // Search after removal
    std::cout << "Search 45: " << (bst.search(45) ? "Found" : "Not found") << std::endl;

    return 0;
}
