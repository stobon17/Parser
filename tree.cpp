//Simon Tobon - 7269-4319

#include "tree.h"

void Build_tree(string token, int number, stack<Node*>& stack) 
{

    Node* node1 = NULL;
    Node* current = new Node;
    Node* left = new Node;

    if (number > 0) 
    {
        for (int i = 0; i < number; ++i) 
        {
            current = stack.top();
            stack.pop();
            current->right = node1;
            node1 = current;
        }
    }
    left->left = node1;
    left->token = token;
    left->num = number;
    stack.push(left);
}

void preOrderTraversal(Node* node, string str) 
{
    if (node == nullptr) 
    {
        return;
    }
    cout << str << node->token << "(" << node->num << ")" << endl;
    preOrderTraversal(node->left, str + ". ");
    preOrderTraversal(node->right, str);
}