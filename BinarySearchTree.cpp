#include "BinarySearchTree.h"
#include <iostream>
#include<iomanip>
#include<windows.h>
using namespace std;

void BinarySearchTree::insert(int val)
{
    tree_node* newNode = new tree_node;
    newNode->data = val;
    newNode->left = nullptr;
    newNode->right = nullptr;

    if (isEmpty())
    {
        root = newNode;
    }
    else
    {
        tree_node* current = root;
        tree_node* parent = nullptr;

        while (current)
        {
            parent = current;
            if (val < current->data)
                current = current->left;
            else
                current = current->right;
        }

        if (parent != nullptr) // Check if parent is not null
        {
            if (val < parent->data)
            {
                parent->left = newNode;
            }
            else
            {
                parent->right = newNode;
            }
        }
        else
        {
            // If parent is null, newNode becomes the root
            root = newNode;
        }
    }

}



void BinarySearchTree::remove(int val)
{
    bool found = false;
    if (isEmpty())
    {
        cout << "This Tree is empty!" << endl;
        return;
    }

    tree_node* curr, * parent;
    curr = root;
    parent = nullptr;

    // Locate the node to be deleted and its parent
    while (curr != nullptr)
    {
        if (curr->data == val)
        {
            found = true;
            break;
        }
        else
        {
            parent = curr;
            if (val > curr->data)
                curr = curr->right;
            else
                curr = curr->left;
        }
    }

    if (!found)
    {
        cout << "Data not found!" << endl;
        return;
    }

    // Case 1: Node with only one child or no child
    if (curr->left == nullptr || curr->right == nullptr)
    {
        tree_node* temp = (curr->left != nullptr) ? curr->left : curr->right;

        // No child case
        if (temp == nullptr)
        {
            if (parent == nullptr)
                root = nullptr; 
            else if (curr == parent->left)
                parent->left = nullptr;
            else
                parent->right = nullptr;
            delete curr;
        }
        else // One child case
        {
            if (parent == nullptr)
                root = temp;
            else if (curr == parent->left)
                parent->left = temp;
            else
                parent->right = temp;
            delete curr;
        }
    }
    else // Case 2: Node with two children
    {
        tree_node* successor = curr->right;
        tree_node* successorParent = nullptr;

        while (successor->left != nullptr)
        {
            successorParent = successor;
            successor = successor->left;
        }

        // Copy the inorder successor's data to this node
        curr->data = successor->data;

        // Delete the inorder successor
        if (successorParent != nullptr)
            successorParent->left = nullptr;
        else
            curr->right = nullptr;

        delete successor;
    }
}

void BinarySearchTree::print_postorder()
{
    postorder(root, 0);
}

void BinarySearchTree::postorder(tree_node* p, int indent)
    {
        if (p != NULL) {
            if (p->right) {
                postorder(p->right, indent + 6);
            }
            if (indent) {
                std::cout << std::setw(indent) << ' ';
            }
            if (p->right) std::cout << "   /\n" << std::setw(indent) ;
            std::cout << p->data << "\n";
            if (p->left) {
                std::cout << setw(indent) << ' ' << "  \\\n";
                postorder(p->left, indent + 6);
            }
        }
    }
