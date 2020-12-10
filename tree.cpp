#include "tree.h"

void Build_tree(std::string token, int number, std::stack<Node*>& stack) {

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