#pragma once
#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <string>
#include "Container.h"
#include "Token.h"

class Calculator {
private:
	std::string infix;
	std::string postfix;
	Container<Token> infixContainer;
	Container<Token> postContainer;
public:
	Calculator() : infix(""), postfix("") {
		infixContainer.clear();
		postContainer.clear();
	}
	void infixToCont() {
		infixContainer.clear();
		int i = 0;
		while (i < infix.size()) {
			if (infix[i] == '(') {
				Token temp;
				temp.type = OpenBr;
				temp.str = '(';
				infixContainer.push_back(temp);
			}
			else if (infix[i] == ')') {
				Token temp;
				temp.type = CloseBr;
				temp.str = ')';
				infixContainer.push_back(temp);
			}
			else if (infix[i] >= '0' && infix[i] <= '9' || infix[i] == '.') {
				char* p;
				double val = strtod(&infix[i], &p);
				Token temp;
				temp.type = Number;
				temp.val = val;
				temp.str = infix.substr(i, p - &infix[i]);
				infixContainer.push_back(temp);
				i += p - &infix[i]; - 1;
			}
			else if (
				infix[i] == '+' ||
				infix[i] == '-' ||
				infix[i] == '*' ||
				infix[i] == '/' ||
				infix[i] == '^' ||
				infix[i] == '%'
				) {
				Token temp;
				temp.type = Operation;
				temp.str = infix[i];
				infixContainer.push_back(temp);
				++i;
			}
			else {
				i++;
			}
		}
	}
};

#endif //CALCULATOR_H