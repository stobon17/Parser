#pragma once
#include <string>
#include <stack>

using namespace std;

struct Node
{
    int num = 0;
    string token;
    Node* left = NULL;
    Node* right = NULL;
};

class Token {
public:
    string token;
    string type;
};

void Build_tree(string str, int number, stack<Node*>& stack);