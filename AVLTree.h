//
// Created by Amanda Yu on 10/10/22.
//

#ifndef AVL_AVLTREE_H
#define AVL_AVLTREE_H

#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// node struct to store data
struct Node
{
    string name;
    string ufid;
    Node* left = nullptr;
    Node* right = nullptr;
    int height = 0;

    // node default constructor
    Node() {}

    // node constructor initializing variables
    Node(string n, string id)
    {
        name = n;
        ufid = id;
    }
};

class AVLTree
{
private:
    Node* head = nullptr;
    int size = 0;

public:
    // AVLTree default constructor
    AVLTree() {}

    // node height: left subtree - right subtree
    int nodeHeight(Node* node)
    {
        if(node == NULL)
        {
            return 0;
        }
        else
        {
            return 1 + max(nodeHeight(node->left), nodeHeight(node->right));
        }
    }

    /*
    int nodeBalance(Node* node)
    {
        return (node->left->height - node->right->height);
    }
     */

    // rotate left: right right case
    Node* rotateLeft(Node* node)
    {
        Node* rightChild = node->right;
        node->right = rightChild->left;
        rightChild->left = node;

        rightChild->height = nodeHeight(rightChild);
        node->height = nodeHeight(node);

        return rightChild;
    }

    // rotate right: left left case
    Node* rotateRight(Node* node)
    {
        Node* leftChild = node->left;
        node->left = leftChild->right;
        leftChild->right = node;

        leftChild->height = nodeHeight(leftChild);
        node->height = nodeHeight(node);

        return leftChild;
    }

    /*
    Node* rotateLeftRight(Node* node)
    {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    Node* rotateRightLeft(Node* node)
    {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    */

    // helper to add a student object into the tree with a specified name and gatorID
    Node* insertHelper(Node* head, string name, string id)
    {
        // base case
        if(head == nullptr)
        {
            return new Node(name, id);
        }

        if(stoi(head->ufid) > stoi(id))
        {
            head->left = insertHelper(head->left, name, id);
        }
        else
        {
            head->right = insertHelper(head->right, name, id);
        }

        // update height
        head->height = nodeHeight(head);

        // find balance factor
        int balance = nodeHeight(head->left) - nodeHeight(head->right);

        // balancing trees
        if(balance > 1)
        {
            // left left
            if(stoi(id) < stoi(head->left->ufid))
            {
                return rotateRight(head);
            }
            // left right
            else if(stoi(id) > stoi(head->left->ufid))
            {
                head->left = rotateLeft(head->left);
                return rotateRight(head);
            }
        }

        // balancing trees
        if(balance < -1)
        {
            // right right
            if (stoi(id) > stoi(head->right->ufid))
            {
                return rotateLeft(head);
            }
            // right left
            else if (stoi(id) < stoi(head->right->ufid))
            {
                head->right = rotateRight(head->right);
                return rotateLeft(head);
            }
        }
        return head;
    }

    // adds a student object into the tree with a specified name and gatorID
    void insert(string name, string id)
    {
        bool valid = true;

        // check if name only includes alphabets from [a-z, A-Z, and spaces]
        string checkString = "abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        for(int i = 0; i < name.length(); i++)
        {
            if(!isalpha(name[i]) && name[i] != ' ')
            {
                valid = false;
            }
        }

        // check if id is strictly 8 digits long
        if(id.length() != 8)
        {
            valid = false;
        }

        // check if id is a number between 0 and 99999999
        int ufid = stoi(id);
        if(ufid > 99999999 || ufid < 0)
        {
            valid = false;
        }

        // check if id is unique
        if(valid)
        {
            if(searchID(id) != "unsuccessful")
            {
                valid = false;
            }
        }

        // determines success or not
        if(valid)
        {
            head = insertHelper(head, name, id);
            cout << "successful" << endl;
        }
        else
        {
            cout << "unsuccessful" << endl;
        }

    }

    // helper to print out a comma separated inorder traversal of the names in the tree
    void inOrderHelper(Node* head, vector<string>& inOrderVector)
    {
        // base case
        if(head == nullptr)
        {
            return;
        }

        // left, node, right
        inOrderHelper(head->left, inOrderVector);
        inOrderVector.push_back(head->name);
        inOrderHelper(head->right, inOrderVector);
    }

    // prints out a comma separated inorder traversal of the names in the tree
    void printInOrder()
    {
        vector<string> inOrderVector;

        inOrderHelper(this->head, inOrderVector);

        // loops through the vector and prints out the names
        for(int i = 0; i < inOrderVector.size()-1; i++)
        {
            cout << inOrderVector[i] << ", ";
        }

        cout << inOrderVector[inOrderVector.size()-1] << endl;
    }

    // helper to print out a comma separated preorder traversal of the names in the tree
    void preOrderHelper(Node* head, vector<string>& preOrderVector)
    {
        // base case
        if(head == nullptr)
        {
            return;
        }

        // node, left, right
        preOrderVector.push_back(head->name);
        preOrderHelper(head->left, preOrderVector);
        preOrderHelper(head->right, preOrderVector);
    }

    // prints out a comma separated preorder traversal of the names in the tree
    void printPreOrder()
    {

        vector<string> preOrderVector;

        preOrderHelper(this->head, preOrderVector);

        // loops through the vector and prints out the names
        for(int i = 0; i < preOrderVector.size()-1; i++)
        {
            cout << preOrderVector[i] << ", ";
        }

        cout << preOrderVector[preOrderVector.size()-1] << endl;
    }

    // helper to print out a comma separated postorder traversal of the names in the tree
    void postOrderHelper(Node* head, vector<string>& postOrderVector)
    {
        // base case
        if(head == nullptr)
        {
            return;
        }

        // left, right, node
        postOrderHelper(head->left, postOrderVector);
        postOrderHelper(head->right, postOrderVector);
        postOrderVector.push_back(head->name);
    }

    // prints out a comma separated postorder traversal of the names in the tree
    void printPostOrder()
    {
        vector<string> postOrderVector;

        postOrderHelper(this->head, postOrderVector);

        // loops through the vector and prints out the names
        for(int i = 0; i < postOrderVector.size()-1; i++)
        {
            cout << postOrderVector[i] << ", ";
        }

        cout << postOrderVector[postOrderVector.size()-1] << endl;
    }

    // helper to print the number of levels that exist in the tree
    void helperPrintLevelCount(Node* head)
    {
        // base case
        if(head == nullptr)
        {
            cout << "0";
        }
        else
        {
            cout << head->height << endl;
        }
    }

    // prints the number of levels that exist in the tree
    void printLevelCount()
    {
        helperPrintLevelCount(this->head);
    }

    // helper for searching for the student with the specified ID from the tree
    string searchIDHelper(Node* head, string id)
    {
        // base case
        if(head == NULL)
        {
            return "unsuccessful";
        }
        else
        {
            if(stoi(head->ufid) == stoi(id))
            {
                return head->name;
            }
            else if(stoi(head->ufid) > stoi(id))
            {
                return searchIDHelper(head->left, id);
            }
            else if(stoi(head->ufid) < stoi(id))
            {
                return searchIDHelper(head->right, id);
            }
        }
    }

    // search for the student with the specified ID from the tree
    string searchID(string id)
    {
        return searchIDHelper(this->head, id);
    }

    // helper to search for the student with the specified name, NAME in the tree
    string searchNameHelper(Node* head, string name)
    {
        // base case
        if(head == NULL)
        {
            return "";
        }
        else
        {
            // node, left, right
            if(head->name == name)
            {
                return head->ufid + "\n" + searchNameHelper(head->left, name) + searchNameHelper(head->right, name);
            }

            return searchNameHelper(head->left, name) + searchNameHelper(head->right, name);
        }
    }

    // search for the student with the specified name, NAME in the tree
    void searchName(string name)
    {
        string id = searchNameHelper(this->head, name);

        // base case
        if(id == "")
        {
            cout << "unsuccessful" << endl;
        }
        else
        {
            cout << id;
        }
    }

    Node* maxNode(Node* node)
    {
        Node* temp = node;

        while(temp->right != NULL)
        {
            temp = temp->right;
        }

        return temp;
    }

    // helps remove the Nth gatorID from the inorder traversal of the tree (N = 0 for the first item, etc)
    void removeInOrderHelper(Node* head, int n, vector<string>& removeInOrderVector)
    {
        // base case
        if(head == nullptr)
        {
            return;
        }

        // left, node, right
        removeInOrderHelper(head->left, n, removeInOrderVector);
        removeInOrderVector.push_back(head->name);
        removeInOrderHelper(head->right, n, removeInOrderVector);
    }

    // remove the Nth gatorID from the inorder traversal of the tree (N = 0 for the first item, etc)
    void removeInOrder(int n)
    {
        vector<string> removeInOrderVector;

        removeInOrderHelper(this->head, n, removeInOrderVector);

        if(n > removeInOrderVector.size())
        {
            cout << "unsuccessful" << endl;
        }
        else
        {
            // loops through the vector
            for(int i = 0; i < removeInOrderVector.size(); i++)
            {
                if(n == i)
                {
                    // no children
                    if(head->left == NULL && head->right == NULL)
                    {
                        cout << "no children" << endl; // NEED TO DELETE
                        Node* temp = head;
                        head = nullptr;
                        delete temp;
                        cout << "successful" << endl;
                    }

                    // one child node
                    else if(head->left == NULL && head->right != NULL)
                    {
                        Node* temp = head->right;
                        *head = *head->right;
                        delete temp;
                        cout << "successful" << endl;
                    }

                    else if(head->left != NULL && head->right == NULL)
                    {
                        Node* temp = head->left;
                        *head = *head->left;
                        delete temp;
                        cout << "successful" << endl;
                    }

                    // two children
                    else
                    {
                        Node *temp = maxNode(head->left);

                        head->name = temp->name;
                        head->ufid = temp->ufid;

                        if (head == this->head)
                        {
                            this->head->left = NULL;
                            cout << "successful" << endl;
                        }
                        else
                        {
                            removeIDHelper(temp->ufid, head->right);
                        }
                    }
                }
            }
        }
    }

    // helper to find and remove the account with the specified ID from the tree
    void removeIDHelper(string id, Node* head)
    {
        // base case
        if(head == NULL)
        {
            cout << "unsuccessful" << endl;
        }

        if(stoi(head->ufid) > stoi(id))
        {
            removeIDHelper(id, head->left);
        }
        else if(stoi(head->ufid) < stoi(id))
        {
            removeIDHelper(id, head->right);
        }
        else
        {
            // no children
            if(head->left == NULL && head->right == NULL)
            {
                Node* temp = head;
                head = nullptr;
                delete temp;
                cout << "successful" << endl;
            }

            // one child node
            else if(head->left == NULL && head->right != NULL)
            {
                Node* temp = head->right;
                delete head;


                *head = *head->right;
                delete temp;
                cout << "successful" << endl;
            }
            else if(head->left != NULL && head->right == NULL)
            {
                Node* temp = head->left;
                *head = *head->left;
                delete temp;
                cout << "successful" << endl;
            }

            // two children
            else
            {
                Node *temp = maxNode(head->left);

                head->name = temp->name;
                head->ufid = temp->ufid;

                if (head == this->head)
                {
                    this->head->left = NULL;
                    cout << "successful" << endl;
                }
                else
                {
                    removeIDHelper(temp->ufid, head->right);
                }
            }
        }
    }

    // find and remove the account with the specified ID from the tree
    void removeID(string id)
    {
        if(searchID(id) != "unsuccessful")
        {
            removeIDHelper(id, this->head);
        }
        else
        {
            cout << "unsuccessful" << endl;
        }
    }
};

#endif //AVL_AVLTREE_H
