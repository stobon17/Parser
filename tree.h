#pragma once
#include <string>
#include <stack>

using namespace std;

struct Node
{
    int num = 0;
    std::string token;
    Node* left = NULL;
    Node* right = NULL;
};

class Token {
public:
    std::string token;
    std::string type;
};

void Build_tree(std::string x, int n, std::stack<Node*>& S);