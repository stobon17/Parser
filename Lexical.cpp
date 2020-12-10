#include "Lexical.h"

std::vector<Token> LexVec(std::string file) 
{
    //Vector to return
    std::vector<Token> outputVec;

    string working;
    string last = "";
    
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

}