/*
 * BinarySearchTree.cpp
 * COMP15
 * Spring 2020
 * Sam Lacet-Brown
 *
 * Implementation of the Binary Search Tree class.
 * Behaves like a standard BST except that it handles multiplicity
 * If you insert a number twice  and then remove it once, then it will
 * still be in the data structure
 */

#include <cstring>
#include <iostream>
#include <limits>

#include "BinarySearchTree.h"

using namespace std;

//constructor
BinarySearchTree::BinarySearchTree()
{
    root = nullptr;
}

//decontructor
BinarySearchTree::~BinarySearchTree()
{
    post_order_delete(root);
    root = nullptr;
}

/* post_order_delete
 *    Purpose: Find the smallest element of the tree
 *    Parameters: A node to check
 *    Returns: N/A
*/
void BinarySearchTree::post_order_delete(Node *node)
{
    if(node == nullptr) {
        return;
    }
    post_order_delete(node->left);
    post_order_delete(node->right);
    zeroLeft(node, find_parent(root, node));
    return;
}

// copy constructor
BinarySearchTree::BinarySearchTree(const BinarySearchTree &source)
{
    root = nullptr;
    if(source.root != nullptr) {
        root = pre_order_copy(source.root);
    }
}

// assignment overload
BinarySearchTree &BinarySearchTree::operator=(const BinarySearchTree &source)
{
    if(this == &source) {
        return *this;
    }
    if(root != nullptr) {
        post_order_delete(root);
        root = nullptr;
    }
    if(source.root != nullptr) {
        root = pre_order_copy(source.root);
    }
    return *this;
}

/* pre_order_copy
 *    Purpose: Copy everything below a node
 *    Parameters: A node to copy
 *    Returns: A node that contains the full tree below it
 */
BinarySearchTree::Node *BinarySearchTree::pre_order_copy(Node *node) const {
    if(node == nullptr) {
        return nullptr;
    }
    Node *newNode = new Node;
    newNode->data = node->data;
    newNode->count = node->count;
    newNode->left = pre_order_copy(node->left);
    newNode->right = pre_order_copy(node->right);
    return newNode;
}

/* find_min
 * Return the minimum element of the tree
 *
 * Implementation note:  A wrapper.  All the work is done in private version.
 *                       See private version for details.
 */
int BinarySearchTree::find_min() const
{
    if (root == nullptr)
                return numeric_limits<int>::max(); // INT_MAX
            return find_min(root)->data;
        }

/* find_min
 *    Purpose: Find the smllest element of the tree
 *    Parameters: A node to check
 *    Returns: The smallest element of the tree
 */
        BinarySearchTree::Node *BinarySearchTree::find_min(Node *node) const
        {
            Node *minNode = node;
            while(minNode->left != nullptr) {
                minNode = minNode->left;
            }
            return minNode;
        }

/* find_max
 * Return the maximum element of the tree
 *
 * Implementation note:  A wrapper.  All the work is done in private version.
 *                       See private version for details.
 */
        int BinarySearchTree::find_max() const
        {
            if (root == NULL) {
        return numeric_limits<int>::min(); // INT_MIN
    }
    return find_max(root)->data;
}

/* find_max
 *    Purpose: Find the largest element of the tree
 *    Parameters: A node to check
 *    Returns: The largest element of the tree
 */
BinarySearchTree::Node *BinarySearchTree::find_max(Node *node) const
{
    Node *maxNode = node;
    while(maxNode->right != nullptr) {
        maxNode = maxNode->right;
    }
    return maxNode;
}

/* contains
 * Return true if element is contained, false otherwise
 *
 * Implementation note:  A wrapper.  All the work is done in private version.
 *                       See private version for details.
 */
bool BinarySearchTree::contains(int value) const
{
    return contains(root, value);
}

/* contains
 *    Purpose: Checks if the tree contains the given value
 *    Parameters: A node to count
 *    Returns: True if the valie is within the tree, false otherwise
 */
bool BinarySearchTree::contains(Node *node, int value) const
{
    if(node == nullptr) {
        return false;
    }
    if(node->data == value) {
        return true;
    } else {
        return contains(node->left, value) or contains(node->right, value);
    }
}

/* insert
 * Adds node to the tree
 *
 * Implementation note:  A wrapper.  All the work is done in private version.
 *                       See private version for details.
 */
void BinarySearchTree::insert(int value)
{
    root = insert(root, nullptr, value);
}

/* insert
 *    Purpose: Insert a node into the tree
 *    Parameters: A node to insert, the parent of that node, and a value
 *    Returns: An int equal to the number of nodes below it in the tree
 */
BinarySearchTree::Node *BinarySearchTree::insert
(Node *node, Node *parent, int value)
{
    if(node) {
        if (value == node->data) {
            node->count = node->count + 1;
            return node;
        } else if (value < node->data) {
            node->left = insert(node->left, node, value);
            return node;
        } else if(value > node->data) {
            node->right = insert(node->right, node, value);
            return node;
        }
    }
    Node *newNode = new Node;
    newNode->data = value;
    newNode->count = 1;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

/* remove
 * Removes node from the tree
 *
 * Implementation note:  A wrapper.  All the work is done in private version.
 *                       See private version for details.
 */
bool BinarySearchTree::remove(int value)
{
    return remove(root, nullptr, value);
}

bool BinarySearchTree::remove(Node *node, Node *parent, int value)
{
    if(tree_height(node) == -1) {
        return false;
    }
    while(node != nullptr and node->data != value) {   
        parent = node;
        if(value < node->data) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    if(node->data == value) {
        node->count--;
        if(node->count == 0) {
            zeroLeft(node, parent);
            return true;
        }
    }
    return false;
}

/* zeroLeft
 *    Purpose: Removes a node from the tree
 *    Parameters: A node to remove, and the parent of that node
 *    Returns: N/A
 */
void BinarySearchTree::zeroLeft(Node *node, Node *parent) {
    if(node == nullptr) {
        return;
    }
    if(node->left == nullptr and node->right ==  nullptr) {
        noChild(node, parent);
    } else if (node->left == nullptr xor node->right == nullptr) {
       oneChild(node, parent);
    } else { //two children
        Node *min = find_min(node->right);
        int minVal = min->data;
        int minCount = min->count;
        zeroLeft(min, find_parent(root, min));
        node->data = minVal;
        node->count = minCount;
    }
}

/* noChild 
 *    Purpose: Removes a node with no children
 *    Parameters: A node with no children to remove, and it's parent
 *    Returns: N/A
 */
void BinarySearchTree::noChild(Node *node, Node *parent) {
    if(node != root) {
        if(parent->left == node) {
            parent->left = nullptr;
        } else {
            parent->right = nullptr;
        }
    } else {
        root = nullptr;
    }
    delete node;
}

/* oneChild 
 *    Purpose: Removes a node with one child
 *    Parameters: A node with a single child to remove, and it's parent
 *    Returns: N/A
 */
void BinarySearchTree::oneChild(Node *node, Node *parent) {
    if(parent->left == node) {
        if(node->left) {
            parent->left = node->left;
        } else if (node->right) {
            parent->left = node->right;
        }
    } else if (parent->right == node) {
        if(node->left) {
            parent->right = node->left;
        } else if (node->right) {
            parent->right = node->right;
        }
    }
    delete node;
}

/* tree_height
 * Return the height of the tree
 *
 * Implementation note:  A wrapper.  All the work is done in private version.
 *                       See private version for details.
 */
int BinarySearchTree::tree_height() const
{
    return tree_height(root);
}

/* tree_height
 *    Purpose: Count the number of nodes in the tree
 *    Parameters: A node to count
 *    Returns: An int equal to the number of nodes below it in the tree
 */
int BinarySearchTree::tree_height(Node *node) const
{
    if (node == nullptr) {
        return -1;
    }
    return 1 + max(tree_height(node->left), tree_height(node->right));
}

/* node_count
 * Return the total number of nodes in the tree
 *
 * Implementation note:  A wrapper.  All the work is done in private version.
 *                       See private version for details.
 */
int BinarySearchTree::node_count() const
{
    return node_count(root);
}

/* node_count
 *    Purpose: Count the number of nodes in the tree
 *    Parameters: A node to count
 *    Returns: An int equal to the number of nodes below it in the tree
 */
int BinarySearchTree::node_count(Node *node) const
{
    if(node == nullptr) {
        return 0;
    }
    return (1 + node_count(node->right) + node_count(node->left));
}

/* count_total
 * Return the sum of all the node values in the tree (including duplicates)
 *
 * Implementation note:  A wrapper.  All the work is done in private version.
 *                       See private version for details.
 */
int BinarySearchTree::count_total() const
{
    return count_total(root);
}

/* count_total
 *    Purpose: Get the sum of all node values in the tree
 *    Parameters: A node to count
 *    Returns: An int equal to the number of nodes below it in the tree
 *    multiplied by the number of times each of those are present
 */
int BinarySearchTree::count_total(Node *node) const
{
    if(node == nullptr) {
        return 0;
    }
    int thisCount = node->data * node->count;
    return (thisCount + count_total(node->right) + count_total(node->left));
}

//given function
BinarySearchTree::Node *BinarySearchTree::find_parent(Node *node,
  Node *child) const
{
    if (node == nullptr)
        return nullptr;

        // if either the left or right is equal to the child,
        // we have found the parent
    if (node->left == child or node->right == child) {
        return node;
    }

        // Use the binary search tree invariant to walk the tree
    if (child->data > node->data) {
        return find_parent(node->right, child);
    } else {
        return find_parent(node->left, child);
    }
    return node;
}

//given function
void BinarySearchTree::print_tree() const
{
    size_t      numLayers  = tree_height() + 1;
    size_t      levelWidth = 4;
    const char *rootPrefix = "-> ";

        // Need numLayers * levelWidth characters for each layer of tree.
        // Add an extra levelWidth characters at front to avoid if statement
        // 1 extra char for nul character at end
    char *start = new char[(numLayers + 1) * levelWidth + 1];

    print_tree(root, start + levelWidth, start + levelWidth, rootPrefix);
    delete[] start;
}

//given function
// Logic and Output Reference: 
// https://www.techiedelight.com/c-program-print-binary-tree/
void BinarySearchTree::print_tree(Node *node, char *const currPos,
  const char *const fullLine,
  const char *const branch) const
{
    if (node == nullptr)
        return;

        // 4 characters + 1 for nul terminator
    using TreeLevel                    = char[5];
    static const int       levelLength = sizeof(TreeLevel) - 1;
    static const TreeLevel UP = ".-- ", DOWN = "`-- ", EMPTY = "    ",
    CONNECT = "   |";
        // Copies prev into dest and advances dest by strlen(prev)
    auto set = [](char *dest, const char *prev) {
        size_t p = strlen(prev);
        return (char *)memcpy(dest, prev, p) + p;
    };

    print_tree(node->right, set(currPos, EMPTY), fullLine, UP);

        // Clear any characters that would immediate precede the "branch"
        // Don't need to check for root (i.e start of array),fullLine is padded
    set(currPos - levelLength, EMPTY);

        // Terminate fullLine at current level
    *currPos = '\0';

    std::cerr << fullLine << branch << node->data
    << (node->count > 1 ? "*" : "") << endl;

        // Connect upper branch to parent
    if (branch == UP)
        set(currPos - levelLength, CONNECT);

        // Connect lower branch to parent
    print_tree(node->left, set(currPos, CONNECT), fullLine, DOWN);
}
