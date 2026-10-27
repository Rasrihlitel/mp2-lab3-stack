#include <iostream>
#include <string>
#include "Stack.h"

int main() {
    std::string str = "(a + b) - )c * k)";
    Stack<char> stack(str.size());
    bool res = true;

    for (int i = 0; i < str.size(); i++) {
        if (str[i] == '(') {
            stack.push('(');
        }
        else if (str[i] == ')') {
            if (stack.IsEmpty()) { 
                res = false;
                break;
            }
            stack.pop();
        }
    }

    if (!stack.IsEmpty()) res = false;   
    return 0;
}