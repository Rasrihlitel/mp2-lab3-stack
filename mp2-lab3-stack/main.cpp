#include <iostream>
#include <string>
#include "Stack.h"

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

    std::cout << "top = " << s.pop() << "\n";   // 3
    std::cout << "top = " << s.pop() << "\n";   // 2
    std::cout << "empty? " << s.IsEmpty() << "\n"; // 0

    s.clear();
    std::cout << "after clear empty? " << s.IsEmpty() << "\n"; // 1

    Stack<int> a(2);
    a.push(10);
    a.push(20);
    Stack<int> b = a;
    std::cout << "copy equal? " << (a == b) << "\n"; // 1

    Stack<int> c = std::move(a);
    std::cout << "moved top = " << c.pop() << "\n";  // 20

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