//Simon Tobon - 7269-4319

#include "Parser.h"

void Tiny(vector<Token>& tokenVector, stack<Node*>& stack) 
{
    Read(tokenVector, "program", stack);
    Name(tokenVector, stack);
    Read(tokenVector, ":", stack);
    Consts(tokenVector, stack);
    Types(tokenVector, stack);
    Dclns(tokenVector, stack);
    SubProgs(tokenVector, stack);
    Body(tokenVector, stack);
    Name(tokenVector, stack);
    Read(tokenVector, ".", stack);
    Build_tree("program", 7, stack);
}

void Consts(vector<Token>& tokenVector, stack<Node*>& stack) 
{
    //If token is const we must get the name of variables.
    if (tokenVector.begin()->token == "const") 
    {
        Read(tokenVector, "const", stack);
        Const(tokenVector, stack);
        int temp = 1;
        while (tokenVector.begin()->token == ",") 
        {
            Read(tokenVector, ",", stack);
            Const(tokenVector, stack);
            temp++;
        }
        Read(tokenVector, ";", stack);
        Build_tree("consts", temp, stack);
    }
    else 
    {
        Build_tree("consts", 0, stack);
    }
}

//Single variable case
void Const(vector<Token>& tokenVector, stack<Node*>& stack) 
{
    Name(tokenVector, stack);
    Read(tokenVector, "=", stack);
    ConstValue(tokenVector, stack);
    Build_tree("=", 2, stack);
}

void ConstValue(vector<Token>& tokenVector, stack<Node*>& stack) 
{
    if (tokenVector.begin()->type == "identifier")
    {
        Name(tokenVector, stack);
    }
    else if (tokenVector.begin()->type == "char")
    {
        Read(tokenVector, "<char>", stack);
    }
    else if (tokenVector.begin()->type == "integer")
    {
        Read(tokenVector, "<integer>", stack);
    }
    else 
    {
        cout << "Error!\n";
    }
}

void Types(vector<Token>& tokenVector, stack<Node*>& stack)
{
    int temp = 1;
    if (tokenVector.begin()->token == "type") 
    {
        Read(tokenVector, "type", stack);
        Type(tokenVector, stack);
        while (tokenVector.begin()->token == ";") 
        {
            Read(tokenVector, ";", stack);
            if (tokenVector.begin()->type == "identifier") 
            {
                Type(tokenVector, stack);
                temp++;
            }
        }
        Build_tree("types", temp, stack);
    }
    else 
    {
        Build_tree("types", 0, stack);
    }
}

void Type(vector<Token>& tokenVector, stack<Node*>& stack) 
{
    Name(tokenVector, stack);
    Read(tokenVector, "=", stack);
    LitList(tokenVector, stack);
    Build_tree("type", 2, stack);
}

void LitList(vector<Token>& tokenVector, stack<Node*>& stack) 
{
    int temp = 1;
    Read(tokenVector, "(", stack);
    Name(tokenVector, stack);
    while (tokenVector.begin()->token == ",") 
    {
        Read(tokenVector, ",", stack);
        Name(tokenVector, stack);
        temp++;
    }
    Read(tokenVector, ")", stack);
    Build_tree("lit", temp, stack);
}

void SubProgs(vector<Token>& tokenVector, stack<Node*>& stack) 
{
    int temp = 0;
    while (tokenVector.begin()->token == "function") 
    {
        temp++;
        Fcn(tokenVector, stack);
    }
    Build_tree("subprogs", temp, stack);
}

void Fcn(vector<Token>& tokenVector, stack<Node*>& stack) 
{
    Read(tokenVector, "function", stack);
    Name(tokenVector, stack);
    Read(tokenVector, "(", stack);
    Params(tokenVector, stack);
    Read(tokenVector, ")", stack);
    Read(tokenVector, ":", stack);
    Name(tokenVector, stack);
    Read(tokenVector, ";", stack);
    Consts(tokenVector, stack);
    Types(tokenVector, stack);
    Dclns(tokenVector, stack);
    Body(tokenVector, stack);
    Name(tokenVector, stack);
    Read(tokenVector, ";", stack);
    Build_tree("fcn", 8, stack);
}

void Params(vector<Token>& tokenVector, stack<Node*>& stack) 
{
    int temp = 1;
    Dcln(tokenVector, stack);
    while (tokenVector.begin()->token == ";") 
    {
        Read(tokenVector, ";", stack);
        Dcln(tokenVector, stack);
        temp++;
    }
    Build_tree("params", temp, stack);
}

void Dclns(vector<Token>& tokenVector, stack<Node*>& stack) 
{
    int temp = 0;
    if (tokenVector.begin()->token == "var") 
    {
        Read(tokenVector, "var", stack);
        temp = 1;
        Dcln(tokenVector, stack);
        while (tokenVector.begin()->token == ";") 
        {
            Read(tokenVector, ";", stack);
            if (tokenVector.begin()->type == "identifier") 
            {
                temp++;
                Dcln(tokenVector, stack);
            }
        }
    }
    Build_tree("dclns", temp, stack);

}

void Dcln(vector<Token>& tokenVector, stack<Node*>& stack) 
{
    int temp = 2;
    Name(tokenVector, stack);
    while (tokenVector.begin()->token == ",") 
    {
        temp++;
        Read(tokenVector, ",", stack);
        Name(tokenVector, stack);
    }
    Read(tokenVector, ":", stack);
    Name(tokenVector, stack);
    Build_tree("var", temp, stack);
}

void Body(vector<Token>& tokenVector, stack<Node*>& stack) 
{
    Read(tokenVector, "begin", stack);
    int temp = 1;
    Statement(tokenVector, stack);
    while (tokenVector.begin()->token == ";") 
    {
        Read(tokenVector, ";", stack);
        Statement(tokenVector, stack);
        temp++;
    }
    Read(tokenVector, "end", stack);
    Build_tree("block", temp, stack);
}

void Statement(vector<Token>& tokenVector, stack<Node*>& stack) 
{
    if (tokenVector.begin()->type == "identifier") 
    {
        Assignment(tokenVector, stack);
    }
    else
    {
        if (tokenVector.begin()->token == "begin")
        {
            Read(tokenVector, "begin", stack);
            int temp = 1;
            Statement(tokenVector, stack);
            while (tokenVector.begin()->token == ";")
            {
                Read(tokenVector, ";", stack);
                Statement(tokenVector, stack);
                temp++;
            }
            Read(tokenVector, "end", stack);
            Build_tree("block", temp, stack);
        }
        else
        {
            if (tokenVector.begin()->token == "output") 
            {
                Read(tokenVector, "output", stack);
                int temp = 1;
                Read(tokenVector, "(", stack);
                OutExp(tokenVector, stack);
                while (tokenVector.begin()->token == ",") 
                {
                    Read(tokenVector, ",", stack);
                    OutExp(tokenVector, stack);
                    temp++;
                }
                Read(tokenVector, ")", stack);
                Build_tree("output", temp, stack);
            }
            else
            {
                if (tokenVector.begin()->token == "if") 
                {
                    Read(tokenVector, "if", stack);
                    Expression(tokenVector, stack);
                    Read(tokenVector, "then", stack);
                    Statement(tokenVector, stack);
                    if (tokenVector.begin()->token == "else") 
                    {
                        Read(tokenVector, "else", stack);
                        Statement(tokenVector, stack);
                        Build_tree("if", 3, stack);
                    }
                    else 
                    {
                        Build_tree("if", 2, stack);
                    }
                }
                else
                {
                    if (tokenVector.begin()->token == "while")
                    {
                        Read(tokenVector, "while", stack);
                        Expression(tokenVector, stack);
                        Read(tokenVector, "do", stack);
                        Statement(tokenVector, stack);
                        Build_tree("while", 2, stack);
                    }
                    else
                    {
                        if (tokenVector.begin()->token == "repeat")
                        {
                            Read(tokenVector, "repeat", stack);
                            Statement(tokenVector, stack);
                            int x = 2;
                            while (tokenVector.begin()->token == ";")
                            {
                                ++x;
                                Read(tokenVector, ";", stack);
                                Statement(tokenVector, stack);
                            }
                            Read(tokenVector, "until", stack);
                            Expression(tokenVector, stack);
                            Build_tree("repeat", x, stack);
                        }
                        else
                        {
                            if (tokenVector.begin()->token == "for")
                            {
                                Read(tokenVector, "for", stack);
                                Read(tokenVector, "(", stack);
                                ForStat(tokenVector, stack);
                                Read(tokenVector, ";", stack);
                                ForExp(tokenVector, stack);
                                Read(tokenVector, ";", stack);
                                ForStat(tokenVector, stack);
                                Read(tokenVector, ")", stack);
                                Statement(tokenVector, stack);
                                Build_tree("for", 4, stack);
                            }
                            else
                            {
                                if (tokenVector.begin()->token == "loop")
                                {
                                    Read(tokenVector, "loop", stack);
                                    int temp = 1;
                                    Statement(tokenVector, stack);
                                    while (tokenVector.begin()->token == ";")
                                    {
                                        Read(tokenVector, ";", stack);
                                        Statement(tokenVector, stack);
                                        temp++;
                                    }
                                    Read(tokenVector, "pool", stack);
                                    Build_tree("loop", temp, stack);
                                }
                                else
                                {
                                    if (tokenVector.begin()->token == "case")
                                    {
                                        Read(tokenVector, "case", stack);
                                        int temp = 1;
                                        Expression(tokenVector, stack);
                                        Read(tokenVector, "of", stack);
                                        temp += Caseclauses(tokenVector, stack);
                                        if (tokenVector.begin()->token == "otherwise")
                                        {
                                            OtherwiseClause(tokenVector, stack);
                                            temp++;
                                        }
                                        Read(tokenVector, "end", stack);
                                        Build_tree("case", temp, stack);
                                    }
                                    else
                                    {
                                        if (tokenVector.begin()->token == "read")
                                        {
                                            Read(tokenVector, "read", stack);
                                            Read(tokenVector, "(", stack);
                                            int temp = 1;
                                            Name(tokenVector, stack);
                                            while (tokenVector.begin()->token == ",")
                                            {
                                                temp++;
                                                Read(tokenVector, ",", stack);
                                                Name(tokenVector, stack);
                                            }
                                            Read(tokenVector, ")", stack);
                                            Build_tree("read", temp, stack);
                                        }
                                        else
                                        {
                                            if (tokenVector.begin()->token == "exit")
                                            {
                                                Read(tokenVector, "exit", stack);
                                                Build_tree("exit", 0, stack);
                                            }
                                            else
                                            {
                                                if (tokenVector.begin()->token == "return")
                                                {
                                                    Read(tokenVector, "return", stack);
                                                    Expression(tokenVector, stack);
                                                    Build_tree("return", 1, stack);
                                                }
                                                else
                                                {
                                                    Build_tree("<null>", 0, stack);
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void OutExp(vector<Token>& tokenVector, stack<Node*>& stack) 
{
    if (tokenVector.begin()->type == "str") 
    {
        StringNode(tokenVector, stack);
        Build_tree("string", 1, stack);
    }
    else
    {
        Expression(tokenVector, stack);
        Build_tree("integer", 1, stack);
    }
}

void StringNode(vector<Token>& tokenVector, stack<Node*>& stack) 
{
    Read(tokenVector, "<string>", stack);
}

int Caseclauses(vector<Token>& tokenVector, stack<Node*>& stack) 
{
    int temp = 1;
    Caseclause(tokenVector, stack);
    while (tokenVector.begin()->token == ";") 
    {
        Read(tokenVector, ";", stack);
        if (tokenVector.begin()->type == "integer" || tokenVector.begin()->type == "char" || tokenVector.begin()->type == "identifier") 
        {
            temp++;
            Caseclause(tokenVector, stack);
        }
    }
    return temp;
}

void Caseclause(vector<Token>& tokenVector, stack<Node*>& stack) 
{
    CaseExpression(tokenVector, stack);
    int x = 2;
    while (tokenVector.begin()->token == ",") 
    {
        Read(tokenVector, ",", stack);
        CaseExpression(tokenVector, stack);
        ++x;
    }
    Read(tokenVector, ":", stack);
    Statement(tokenVector, stack);
    Build_tree("case_clause", x, stack);
}

void CaseExpression(vector<Token>& tokenVector, stack<Node*>& stack) 
{
    ConstValue(tokenVector, stack);
    if (tokenVector.begin()->token == "..") 
    {
        Read(tokenVector, "..", stack);
        ConstValue(tokenVector, stack);
        Build_tree("..", 2, stack);
    }
}

void OtherwiseClause(vector<Token>& tokenVector, stack<Node*>& stack) {
    if (tokenVector.begin()->token == "otherwise") 
    {
        Read(tokenVector, "otherwise", stack);
        Statement(tokenVector, stack);
        Build_tree("otherwise", 1, stack);
    }
}

void Assignment(vector<Token>& tokenVector, stack<Node*>& stack) 
{
    Name(tokenVector, stack);
    if (tokenVector.begin()->token == ":=") {

        Read(tokenVector, ":=", stack);
        Expression(tokenVector, stack);
        Build_tree("assign", 2, stack);
    }
    else
    {
        if (tokenVector.begin()->token == ":=:")
        {
            Read(tokenVector, ":=:", stack);
            Name(tokenVector, stack);
            Build_tree("swap", 2, stack);
        }
        else
        {
            exit(1);
        }
    }
}

void ForStat(vector<Token>& tokenVector, stack<Node*>& stack) 
{
    if (tokenVector.begin()->type == "identifier") 
    {
        Assignment(tokenVector, stack);
    }
    else 
    {
        Build_tree("<null>", 0, stack);
    }
}

void ForExp(vector<Token>& tokenVector, stack<Node*>& stack) 
{
    if (tokenVector.begin()->type == "identifier" || tokenVector.begin()->type == "char" || tokenVector.begin()->token == "+" || tokenVector.begin()->token == "not" || tokenVector.begin()->token == "succ" || tokenVector.begin()->token == "chr" || tokenVector.begin()->token == "ord" || tokenVector.begin()->token == "eof" || tokenVector.begin()->token == "(" || tokenVector.begin()->token == ")")
    {
        Expression(tokenVector, stack);
    }
    else 
    {
        Build_tree("true", 0, stack);
    }
}

void Expression(vector<Token>& tokenVector, stack<Node*>& stack) 
{
    Term(tokenVector, stack);
    if (tokenVector.begin()->token == "<=") 
    {
        Read(tokenVector, "<=", stack);
        Term(tokenVector, stack);
        Build_tree("<=", 2, stack);
    }
    else
    {
        if (tokenVector.begin()->token == "<") 
        {
            Read(tokenVector, "<", stack);
            Term(tokenVector, stack);
            Build_tree("<", 2, stack);
        }
        else
        {
            if (tokenVector.begin()->token == ">=")
            {
                Read(tokenVector, ">=", stack);
                Term(tokenVector, stack);
                Build_tree(">=", 2, stack);
            }
            else
            {
                if (tokenVector.begin()->token == ">")
                {
                    Read(tokenVector, ">", stack);
                    Term(tokenVector, stack);
                    Build_tree(">", 2, stack);
                }
                else
                {
                    if (tokenVector.begin()->token == "=")
                    {
                        Read(tokenVector, "=", stack);
                        Term(tokenVector, stack);
                        Build_tree("=", 2, stack);
                    }
                    else
                    {
                        if (tokenVector.begin()->token == "<>")
                        {
                            Read(tokenVector, "<>", stack);
                            Term(tokenVector, stack);
                            Build_tree("<>", 2, stack);
                        }
                    }
                }
            }
        }
    }
}

void Term(vector<Token>& tokenVector, stack<Node*>& stack) 
{
    Factor(tokenVector, stack);
    while (tokenVector.begin()->token == "+" || tokenVector.begin()->token == "-" || tokenVector.begin()->token == "or") 
    {
        if (tokenVector.begin()->token == "+") 
        {
            Read(tokenVector, "+", stack);
            Factor(tokenVector, stack);
            Build_tree("+", 2, stack);
        }
        else
        {
            if (tokenVector.begin()->token == "-") 
            {
                Read(tokenVector, "-", stack);
                Factor(tokenVector, stack);
                Build_tree("-", 2, stack);
            }
            else
            {
                if (tokenVector.begin()->token == "or") 
                {
                    Read(tokenVector, "or", stack);
                    Factor(tokenVector, stack);
                    Build_tree("or", 2, stack);
                }
            }
        }
    }
}

void Factor(vector<Token>& tokenVector, stack<Node*>& stack) 
{
    Primary(tokenVector, stack);
    while (tokenVector.begin()->token == "*" || tokenVector.begin()->token == "/" || tokenVector.begin()->token == "and" || tokenVector.begin()->token == "mod") 
    {
        if (tokenVector.begin()->token == "*") 
        {
            Read(tokenVector, "*", stack);
            Primary(tokenVector, stack);
            Build_tree("*", 2, stack);
        }
        else
        {
            if (tokenVector.begin()->token == "/")
            {
                Read(tokenVector, "/", stack);
                Primary(tokenVector, stack);
                Build_tree("/", 2, stack);
            }
            else
            {
                if (tokenVector.begin()->token == "and")
                {
                    Read(tokenVector, "and", stack);
                    Primary(tokenVector, stack);
                    Build_tree("and", 2, stack);
                }
                else
                {
                    if (tokenVector.begin()->token == "mod")
                    {
                        Read(tokenVector, "mod", stack);
                        Primary(tokenVector, stack);
                        Build_tree("mod", 2, stack);
                    }
                }
            }
        }
    }
}

void Primary(vector<Token>& tokenVector, stack<Node*>& stack) 
{
    if (tokenVector.begin()->token == "-") 
    {
        Read(tokenVector, "-", stack);
        Primary(tokenVector, stack);
        Build_tree("-", 1, stack);
    }
    else
    {
        if (tokenVector.begin()->token == "+")
        {
            Read(tokenVector, "+", stack);
            Primary(tokenVector, stack);
            Build_tree("+", 1, stack);
        }
        else
        {
            if (tokenVector.begin()->token == "not")
            {
                Read(tokenVector, "not", stack);
                Primary(tokenVector, stack);
                Build_tree("not", 1, stack);
            }
            else
            {
                if (tokenVector.begin()->token == "eof")
                {
                    Read(tokenVector, "eof", stack);
                    Build_tree("eof", 0, stack);
                }
                else
                {
                    if (tokenVector.begin()->token == "(")
                    {
                        Read(tokenVector, "(", stack);
                        Expression(tokenVector, stack);
                        Read(tokenVector, ")", stack);
                    }
                    else
                    {
                        if (tokenVector.begin()->token == "succ")
                        {
                            Read(tokenVector, "succ", stack);
                            Read(tokenVector, "(", stack);
                            Expression(tokenVector, stack);
                            Read(tokenVector, ")", stack);
                            Build_tree("succ", 1, stack);
                        }
                        else
                        {
                            if (tokenVector.begin()->token == "pred")
                            {
                                Read(tokenVector, "pred", stack);
                                Read(tokenVector, "(", stack);
                                Expression(tokenVector, stack);
                                Read(tokenVector, ")", stack);
                                Build_tree("pred", 1, stack);
                            }
                            else
                            {
                                if (tokenVector.begin()->token == "chr")
                                {
                                    Read(tokenVector, "chr", stack);
                                    Read(tokenVector, "(", stack);
                                    Expression(tokenVector, stack);
                                    Read(tokenVector, ")", stack);
                                    Build_tree("chr", 1, stack);
                                }
                                else
                                {
                                    if (tokenVector.begin()->token == "ord")
                                    {
                                        Read(tokenVector, "ord", stack);
                                        Read(tokenVector, "(", stack);
                                        Expression(tokenVector, stack);
                                        Read(tokenVector, ")", stack);
                                        Build_tree("ord", 1, stack);
                                    }
                                    else
                                    {
                                        if (tokenVector.begin()->type == "integer")
                                        {
                                            Read(tokenVector, "<integer>", stack);
                                        }
                                        else
                                        {
                                            if (tokenVector.begin()->type == "char")
                                            {
                                                Read(tokenVector, "<char>", stack);
                                            }
                                            else
                                            {
                                                Name(tokenVector, stack);
                                                if (tokenVector.begin()->token == "(")
                                                {
                                                    int x = 2;
                                                    Read(tokenVector, "(", stack);
                                                    Expression(tokenVector, stack);
                                                    while (tokenVector.begin()->token == ",")
                                                    {
                                                        Read(tokenVector, ",", stack);
                                                        Expression(tokenVector, stack);
                                                        ++x;
                                                    }
                                                    Read(tokenVector, ")", stack);
                                                    Build_tree("call", x, stack);
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void Name(vector<Token>& tokenVector, stack<Node*>& stack) 
{
    Read(tokenVector, "<identifier>", stack);
}

void Read(vector<Token>& tokenVector, string str, stack<Node*>& stack)
{
    if (str == "<integer>")
    {
        if (tokenVector.begin()->type == "integer")
        {
            Build_tree(tokenVector.begin()->token, 0, stack);
            Build_tree("<integer>", 1, stack);
        }
        else
        {
            cout << "Parse Error: Integer!\n";
            exit(1);
        }
    }
    else
    {
        if (str == "<char>")
        {
            if (tokenVector.begin()->type == "char")
            {
                Build_tree(tokenVector.begin()->token, 0, stack);
                Build_tree("<char>", 1, stack);
            }
            else
            {
                cout << "Parse Error: Char!\n";
                exit(1);
            }
        }
        else
        {
            if (str == "<identifier>")
            {
                if (tokenVector.begin()->type == "identifier")
                {
                    Build_tree(tokenVector.begin()->token, 0, stack);
                    Build_tree("<identifier>", 1, stack);
                }
                else
                {
                    cout << "Parse Error: Identifier!\n";
                    exit(1);
                }
            }
            else
            {
                if (str == "<string>")
                {
                    if (tokenVector.begin()->type == "string")
                    {
                        Build_tree(tokenVector.begin()->token, 0, stack);
                        Build_tree("<string>", 1, stack);
                    }
                    else
                    {
                        cout << "Parse Error: String!\n";
                        exit(1);
                    }
                }
                else
                {
                    if (tokenVector.begin()->token != str)
                    {
                        cout << "Error!\n";
                        exit(1);
                    }
                }
            }
        }
    }
    tokenVector.erase(tokenVector.begin());
}