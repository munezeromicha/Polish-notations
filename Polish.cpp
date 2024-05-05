#include "Polish.h"

std::string readInfix()
{   std::string infix;
    std::cout<<"enter an infix expression\n";
    std::getline(std::cin,infix);
    std::cout<<"read "<<infix<<"\n";
    return infix;
}

std::string convertToPostfix(std::string infix)
{
    /* Simplifying assumptions: 
    (1) Operands are integers from 1 to 9
    (2) Operators supported are + - * and /
    (3) Supported brackets are () [] and {}
    */
 /*Algorithm to implement: 
   
     Initialize an empty stack S
     Initialize an empty string that will be returned
     Scan the infix expression from left to right
      If you encounter an opening parenthesis ( or [  or {
        push it on the stack
      If you encounter an operand (1 - 9):
         append it to the output string
      If you encounter a closing parenthesis ) or ] or }:
         Pop each symbol from the stack up to (including) the corresponding 
         opening parenthesis, appending each popped symbol to the output string
         Discard both the opening and closing parenthesis
      If you encounter an operator + or - or * or /:
          Pop all operators with the same or higher precedence and append them to the output string
          then push the operator on the stack
      When the entire input string is read:
           Pop the remaining symbols from the stack, appending them to the output string
      Return the output string  (Which is the postfix expression)          
   */

   std::string postfix;
    std::stack<char> S;

    for (char& c : infix)
    {
        if (isdigit(c))
        {
            postfix += c;
        }
        else if (c == '(' || c == '[' || c == '{')
        {
            S.push(c);
        }
        else if (c == ')' || c == ']' || c == '}')
        {
            char opening;
            switch (c)
            {
                case ')':
                    opening = '(';
                    break;
                case ']':
                    opening = '[';
                    break;
                case '}':
                    opening = '{';
                    break;
            }
            while (!S.empty() && S.top() != opening)
            {
                postfix += S.top();
                S.pop();
            }
            S.pop(); 
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/')
        {
            int precedence_c;
            if (c == '+' || c == '-')
                precedence_c = 1;
            else
                precedence_c = 2;

            while (!S.empty() && (S.top() == '+' || S.top() == '-' || S.top() == '*' || S.top() == '/') && precedence_c <= 2)
            {
                postfix += S.top();
                S.pop();
            }
            S.push(c);
        }
    }

    while (!S.empty())
    {
        postfix += S.top();
        S.pop();
    }

    return postfix;
   
   
}

int evaluate(std::string postfix)
{
    /* This function takes as input a postfix expression
     and returns the value of that expression, obtained as follows:
     Initialize an empty stack of integers
     Scan the postfix expression from left to right:
        When you encounter an operand, push it on the stack
        When you encounter an operator, pop two operands from the stack
        and apply the operation on them, then push back the result on the
        stack.
        Once the postfix expression is entirely read, the value of the
        expression is on the stack
     
     */


    std::stack<int> S;

    for (char& c : postfix)
    {
        if (isdigit(c))
        {
            S.push(c - '0'); 
        }
        else
        {
            int operand2 = S.top();
            S.pop();
            int operand1 = S.top();
            S.pop();
            switch (c)
            {
                case '+':
                    S.push(operand1 + operand2);
                    break;
                case '-':
                    S.push(operand1 - operand2);
                    break;
                case '*':
                    S.push(operand1 * operand2);
                    break;
                case '/':
                    S.push(operand1 / operand2);
                    break;
            }
        }
    }

    return S.top();


}