//Simon Tobon - 7269-4319
#pragma once

#include "tree.h"
#include "Lexical.h"

//Grammar Functions -- From Project_Grammar.docx

void Tiny(vector<Token>& tokenVector, stack<Node*>& stack);
void Consts(vector<Token>& tokenVector, stack<Node*>& stack);
void Const(vector<Token>& tokenVector, stack<Node*>& stack);
void ConstValue(vector<Token>& tokenVector, stack<Node*>& stack);
void Types(vector<Token>& tokenVector, stack<Node*>& stack);
void Type(vector<Token>& tokenVector, stack<Node*>& stack);
void LitList(vector<Token>& tokenVector, stack<Node*>& stack);
void SubProgs(vector<Token>& tokenVector, stack<Node*>& stack);
void Fcn(vector<Token>& tokenVector, stack<Node*>& stack);
void Params(vector<Token>& tokenVector, stack<Node*>& stack);
void Dclns(vector<Token>& tokenVector, stack<Node*>& stack);
void Dcln(vector<Token>& tokenVector, stack<Node*>& stack);
void Body(vector<Token>& tokenVector, stack<Node*>& stack);
void Statement(vector<Token>& tokenVector, stack<Node*>& stack);
void OutExp(vector<Token>& tokenVector, stack<Node*>& stack);
void StringNode(vector<Token>& tokenVector, stack<Node*>& stack);
int Caseclauses(vector<Token>& tokenVector, stack<Node*>& stack);
void Caseclause(vector<Token>& tokenVector, stack<Node*>& stack);
void CaseExpression(vector<Token>& tokenVector, stack<Node*>& stack);
void OtherwiseClause(vector<Token>& tokenVector, stack<Node*>& stack);
void Assignment(vector<Token>& tokenVector, stack<Node*>& stack);
void ForStat(vector<Token>& tokenVector, stack<Node*>& stack);
void ForExp(vector<Token>& tokenVector, stack<Node*>& stack);
void Expression(vector<Token>& tokenVector, stack<Node*>& stack);
void Term(vector<Token>& tokenVector, stack<Node*>& stack);
void Factor(vector<Token>& tokenVector, stack<Node*>& stack);
void Primary(vector<Token>& tokenVector, stack<Node*>& stack);
void Name(vector<Token>& tokenVector, stack<Node*>& stack);

//Helper Function
void Read(vector<Token>& tokenVector, string str, stack<Node*>& stack);