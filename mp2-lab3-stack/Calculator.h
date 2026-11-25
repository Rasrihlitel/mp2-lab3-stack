#pragma once
#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <string>
#include <cstdlib>
#include <cmath>
#include "Container.h"
#include "Token.h"
#include "Stack.h"

class Calculator {
private:
	std::string infix;
	std::string postfix;
	Container<Token> infixContainer;
	Container<Token> postfixContainer;
	Stack<Token> oper;
	Stack<double> num;
public:
	Calculator() : infix(""), postfix("") {
		infixContainer.clear();
		postfixContainer.clear();
	}

	void setInfix(const std::string& inf) {
		std::string str = '(' + inf + ')';
		infix = str;
	}

	void infixToCont() {
		infixContainer.clear();
		int i = 0;
		while (i < infix.size()) {
			if (infix[i] == '(') {
				Token temp{};
				temp.prior = 0;
				temp.str = "(";
				temp.type = OpenBr;
				infixContainer.push_back(temp);
				i++;
			}
			else if (infix[i] == ')') {
				Token temp{};
				temp.prior = 0;
				temp.str = ")";
				temp.type = CloseBr;
				infixContainer.push_back(temp);
				i++;
			}
			else if ((infix[i] - '0' <= 9 && infix[i] - '0' >= 0) || infix[i] == '.') {
				char* p;
				double val = std::strtod(&infix[i], &p);
				if (p == &infix[i]) throw "Некорректная запись числа";
				Token temp{};
				temp.val = val;
				temp.type = Number;
				temp.str = infix.substr(i, p - &infix[i]);
				infixContainer.push_back(temp);
				i += p - &infix[i];
			}
			else if (
				infix[i] == '+' ||
				infix[i] == '-' ||
				infix[i] == '*' ||
				infix[i] == '/' ||
				infix[i] == '^'
				) {
				int prior = 0;
				switch (infix[i]) {
					case '+': prior = 1; break;
					case '-': prior = 1; break;
					case '*': prior = 2; break;
					case '/': prior = 2; break;
					case '^': prior = 3; break;
					default: break;
				}
				Token temp{};
				temp.prior = prior;
				temp.str = infix[i];
				temp.type = Operation;
				infixContainer.push_back(temp);
				i++;
			}
			else {
				i++;
			}
		}
	}

	void toPostFix() {
		oper.clear();
		postfixContainer.clear();
		for (int i = 0; i < infixContainer.getSize(); i++) {
			if (infixContainer[i].type == OpenBr) {
				oper.push(infixContainer[i]);
			}
			else if (infixContainer[i].type == CloseBr) {
				while (!oper.IsEmpty() && oper.top().type != OpenBr) {
					postfixContainer.push_back(oper.pop());
				}
				if (oper.IsEmpty()) throw "Неправильно расставлены скобки";
				oper.pop();
			}
			else if (infixContainer[i].type == Number) {
				postfixContainer.push_back(infixContainer[i]);
			}
			else if (infixContainer[i].type == Operation) {
				while (infixContainer[i].prior <= oper.top().prior) {
					postfixContainer.push_back(oper.pop());
				}
				oper.push(infixContainer[i]);
			}
		}
	}

	double calcPostFix() {
		num.clear();
		for (int i = 0; i < postfixContainer.getSize(); i++) {
			if (postfixContainer[i].type == Number) {
				num.push(postfixContainer[i].val);
			}
			else if (postfixContainer[i].type == Operation) {
				double right = num.pop();
				double left = num.pop();
				double res = 0;
				if (postfixContainer[i].str == "+") res = left + right;
				if (postfixContainer[i].str == "-") res = left - right;
				if (postfixContainer[i].str == "*") res = left * right;
				if (postfixContainer[i].str == "/") res = left / right;
				if (postfixContainer[i].str == "^") res = pow(left, right);
				num.push(res);
			}
		}
		if (num.IsEmpty() || num.getTopId() != 0) {
			throw "Неверно написано арифметическое выражение";
		}
		return num.pop();
	}

	double calculate() {
		oper.clear();
		num.clear();
		for (int i = 0; i < infixContainer.getSize(); i++) {
			if (infixContainer[i].type == OpenBr) {
				oper.push(infixContainer[i]);
			}
			else if (infixContainer[i].type == Number) {
				num.push(infixContainer[i].val);
			}
			else if (infixContainer[i].type == CloseBr) {
				while (oper.top().type != OpenBr) {
					double right = num.pop();
					double left = num.pop();
					Token c = oper.pop();
					double res = 0;
					if (c.str == "+") res = left + right;
					if (c.str == "-") res = left - right;
					if (c.str == "*") res = left * right;
					if (c.str == "/") res = left / right;
					if (c.str == "^") res = pow(left, right);
					num.push(res);
				}
				oper.pop();
			}
			else if (infixContainer[i].type == Operation) {
				Stack<Token> temp;
				while (infixContainer[i].prior <= oper.top().prior) {
					temp.push(oper.pop());
				}
				oper.push(infixContainer[i]);
				while (!temp.IsEmpty()) {
					oper.push(temp.pop());
				}
			}
		}
		return num.pop();
	}

};

#endif //CALCULATOR_H