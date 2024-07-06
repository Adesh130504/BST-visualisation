
#include <iostream>
#include <cstdlib>
#include <iostream>
#include<iomanip>
#include<windows.h>
using namespace std;
class BinarySearchTree
{
public:
    struct tree_node
    {
        tree_node* left;
        tree_node* right;
        int data;
    };
    tree_node* root;


public:
    BinarySearchTree()
    {
        root = NULL;
    }

bool isEmpty() const
{ 
    return root == NULL; 
}
void insert(int val)
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



void remove(int val)
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

void print_postorder()
{
    postorder(root, 0);
}

void postorder(tree_node* p, int indent)
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
};
int main()
{
    BinarySearchTree b;
    int input;
    int insert;
    int del;
    while (1)
    {
        cout << endl << endl;
        cout << " Binary Search Tree Operations " << endl;
        cout << " ----------------------------- " << endl;
        cout << " 1. Insertion/Creation " << endl;
        cout << " 2. Printing " << endl;
        cout << " 3. Removal " << endl;
        cout << " 4. Exit " << endl;
        cout << " Enter your choice : ";
        cin >> input;
        system("cls");
        switch (input)
        {
        case 1: cout << " Enter Number to be inserted : ";
            cin >> insert;
            b.insert(insert);
            break;
        case 2: cout << endl;

            cout << " Printing " << endl;
            cout << " --------------------" << endl;
            b.print_postorder();

            break;
        case 3: cout << " Enter data to be deleted : ";
            cin >> del;
            b.remove(del);
            break;
        case 4:
            return 0;

        }
    }
}