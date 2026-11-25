#include <iostream>
#include <string>
#include "Stack.h"
#include "Calculator.h"

int main() {
    std::setlocale(LC_CTYPE, "Russia");
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
    Stack<int> s(3);
    s.push(1);
    s.push(2);
    s.push(3);

    std::cout << "top = " << s.pop() << "\n";  
    std::cout << "top = " << s.pop() << "\n";  
    std::cout << "empty? " << s.IsEmpty() << "\n";

    s.clear();
    std::cout << "after clear empty? " << s.IsEmpty() << "\n";

    Stack<int> a(2);
    a.push(10);
    a.push(20);
    Stack<int> b = a;
    std::cout << "copy equal? " << (a == b) << "\n";

    Stack<int> c = std::move(a);
    std::cout << "moved top = " << c.pop() << "\n";

    Calculator calc;
    calc.setInfix("(1+2)*3^2-4/2");
    calc.infixToCont();
    calc.toPostFix();
    std::cout << "result = " << calc.calcPostFix() << "\n";

    try {
        Stack<int> full(1);
        full.push(1);
        full.push(2);
    }
    catch (const char* e) {
        std::cout << "ERROR: " << e << "\n";
    }

    try {
        Stack<int> empty(2);
        empty.pop();
    }
    catch (const char* e) {
        std::cout << "ERROR: " << e << "\n";
    }


    return 0;
}