//Simon Tobon - 7269-4319

#include "tree.h"
#include "Lexical.h"
#include "Parser.h"

using namespace std;

int main(int argc, char** argv) {
 
    string file;
    stack<Node*> stack;
    //Ast flag
    if (argc <= 2)
    {
        file = string(argv[1]);
    }
    //No ast flag
    else
    {
        file = string(argv[2]);
    }
    //Lexical analysis
    vector<Token> lexicalVec = LexVec(file);
    

    //Parser
    Tiny(lexicalVec, stack);

    //subc (without switches) should produce no output whatsoever for a syntactically
    //correct program, and a suitable error message for an incorrect one.

        //Required switches : -ast. This switch prints the abstract syntax tree, and nothing else.

    if (argc > 2 && string(argv[1]) == "-ast") {
        Node* init = stack.top();
        preOrderTraversal(init, "");
    }

    return 0;
}
