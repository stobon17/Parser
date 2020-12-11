#include "Lexical.h"
#include <unordered_set>

std::vector<Token> LexVec(std::string file) 
{
    //Vector to return
    std::vector<Token> outputVec;

    ifstream input;

    input.open(file);

    if (!input) 
    {
        std::cout << "Failed to open file!" << std::endl;
        exit(0);
    }
    //File to string -- https://stackoverflow.com/a/19922123/9442554
    stringstream strStream;
    strStream << input.rdbuf();
    string fileToString = strStream.str();

    for (int i = 0; i < fileToString.length(); i = i + 1) 
    {
        //Comment Handling
        if (fileToString.at(i) == '#') 
        {
            while (fileToString.at(i) != '\n') 
            {
                fileToString.erase(i - 1, 1);
            }
            fileToString.erase(i - 1, 1);
        }


        if (fileToString.at(i) == '}') 
        {
            fileToString.insert(i + 1, " ");
            fileToString.insert(i, " ");
            i = i + 2;
        }
        else if (fileToString.at(i) == '{')
        {
            fileToString.insert(i + 1, " ");
            fileToString.insert(i, " ");
            i = i + 2;
        }
        else if (fileToString.at(i) == ';')
        {
            fileToString.insert(i + 1, " ");
            fileToString.insert(i, " ");
            i = i + 2;
        }
        else if (fileToString.at(i) == ',')
        {
            fileToString.insert(i + 1, " ");
            fileToString.insert(i, " ");
            i = i + 2;
        }
        else if (fileToString.at(i) == '(')
        {
            fileToString.insert(i + 1, " ");
            fileToString.insert(i, " ");
            i = i + 2;
        }
        else if (fileToString.at(i) == ')')
        {
            fileToString.insert(i + 1, " ");
            fileToString.insert(i, " ");
            i = i + 2;
        }
        else if (fileToString.at(i) == '+')
        {
            fileToString.insert(i + 1, " ");
            fileToString.insert(i, " ");
            i = i + 2;
        }
        else if (fileToString.at(i) == '-')
        {
            fileToString.insert(i + 1, " ");
            fileToString.insert(i, " ");
            i = i + 2;
        }
        else if (fileToString.at(i) == '*')
        {
            fileToString.insert(i + 1, " ");
            fileToString.insert(i, " ");
            i = i + 2;
        }
        else if (fileToString.at(i) == '/')
        {
            fileToString.insert(i + 1, " ");
            fileToString.insert(i, " ");
            i = i + 2;
        }
        else if (fileToString.at(i) == '\"')
        {
            fileToString.insert(i + 1, " ");
            fileToString.insert(i, " ");
            i = i + 2;
        }

        //Token handling - 
        //char tokens, i.e., :=:
        else
        {
            if (fileToString.at(i) == ':') 
            {
                //=:
                if (fileToString.at(i - 1) == '=') 
                {
                    fileToString.insert(i + 1, " ");
                    i = i + 2;
                }
                //:=
                else if (fileToString.at(i + 1) == '=') 
                {
                    fileToString.insert(i, " ");
                    i = i + 1;
                }
                //:
                else 
                {
                    fileToString.insert(i + 1, " ");
                    fileToString.insert(i, " ");
                    i = i + 2;
                }

            }
            //. and ..
            else
            {
                if (fileToString.at(i) == '.')
                {
                    //..
                    if (fileToString.at(i + 1) == '.')
                    {
                        fileToString.insert(i, " ");
                        i = i + 2;
                        fileToString.insert(i + 1, " ");
                        i = i + 2;
                    }
                    //.
                    else
                    {
                        fileToString.insert(i + 1, " ");
                        fileToString.insert(i, " ");
                        i = i + 2;
                    }
                }
            }
        }
        // < <> <=
        if (fileToString.at(i) == '<' || fileToString.at(i) == '>') 
        {
            fileToString.insert(i, " ");
            i = i + 1;
            if (fileToString.at(i + 1) != '=' && fileToString.at(i + 1) != '>') 
            {
                fileToString.insert(i + 1, " ");
                i = i + 2;
            }
        }
        else
        {
            if (fileToString.at(i) == '=')
            {
                if (fileToString.at(i - 1) != '<' && fileToString.at(i - 1) != '>' && fileToString.at(i - 1) != ':')
                {
                    fileToString.insert(i, " ");
                    i = i + 1;
                    if (fileToString.at(i + 1) != ':')
                    {
                        fileToString.insert(i + 1, " ");
                        i++;
                    }
                }
                else
                {
                    if (fileToString.at(i + 1) != ':')
                    {
                        fileToString.insert(i + 1, " ");
                        i = i + 2;
                    }
                }
            }
        }

    }

    string p_token;
    string final("");
    std::stringstream inputStringStream(fileToString);
    inputStringStream >> p_token;


    //From Project_Lex.doc
    bool keywordsBool = true;

    //store keywords for classification of tokens
    unordered_set<std::string> keywords({ "program","var","const","type","function","return","begin","end","output","if","then","else","while","do",
                                          "case","of","otherwise","repeat","for","until","loop","pool","exit","read","succ","pred","chr","ord","eof",
                                          ":=:", ":=", "..", "<=", "<>", "<", ">=", ">", "=", "mod","and","or","not",":",";",".",",","+","-","*","/",
                                          "{","}","(",")" });

    //Convert characters to tokens, and check they are valid, then add to the ouput vector.
    while (!inputStringStream.fail()) 
    {
        if (p_token == "{") 
        {
            while (p_token != "}") 
            {
                inputStringStream >> p_token;
            }
            inputStringStream >> p_token;
        }

        bool isVar = false;
        bool isStr = false;
        Token currentToken;
        currentToken.type = "";

        regex int_regex("[0-9]");

        //Variable
        if (p_token == "var") 
        {
            isVar = true;
        }
        //String
        if (!isStr && p_token == "\"") 
        {
            isStr = true;
        }
        if (!isStr) 
        {

            bool isInt = true;
            for (int i = 0; i < p_token.length(); i = i + 1) 
            {
                //Integer (0-9)
                if (!regex_match(p_token, int_regex))
                {
                    isInt = false;
                }
            }
            if (isInt) 
            {
                currentToken.type = "integer";
            }
            else if (p_token.at(0) == '\'') 
            {
                currentToken.type = "char";
            }

            else if (keywordsBool == false)
            {
                currentToken.type = "identifier";
            }
            else if (!(keywords.find(p_token) != keywords.end()))
            {
                currentToken.type = "identifier";
            }
        }
        else 
        {
            currentToken.token = p_token;
            outputVec.push_back(currentToken);
            final = p_token;
            currentToken.type = "";
            inputStringStream >> p_token;
            string tokenBuf = p_token;

            while (p_token != "\"") 
            {
                tokenBuf = tokenBuf + " " + p_token;
                inputStringStream >> p_token;
            }

            currentToken.token = tokenBuf;
            currentToken.type = "string";
        }

        currentToken.token = p_token;
        outputVec.push_back(currentToken);
        final = p_token;
        currentToken.type = "";
        inputStringStream >> p_token;
    }
    return outputVec;
}