#pragma once
#ifndef TOKEN_H
#define TOKEN_H
#include <string>

enum TokenType {
	Number,
	Operation,
	OpenBr,
	CloseBr
};

struct Token {
	TokenType type;
	std::string str;
	double val;
};

#endif //TOKEN_H