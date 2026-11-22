#pragma once
#ifndef TOKEN_H
#define TOKEN_H
#include <string>

enum TokenType {
	Operation,
	Number,
	OpenBr,
	CloseBr
};

struct Token {
	TokenType type;
	double val;
	int prior;
	std::string str;
};

#endif //TOKEN_H