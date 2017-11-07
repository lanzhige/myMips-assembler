/*
 *	用于存储标号表
 *	重载了==运算符比较标号是否相等
*/

#pragma once
#include <string>
using namespace std;

class StrInt {
public:
	string symbol;
	int location;

	StrInt(string symbol, int location) : symbol(symbol), location(location) {
	}

	bool operator == (const string &str) const{
		return (symbol == str);
	}
};