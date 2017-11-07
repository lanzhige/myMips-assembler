/*
 * 用于存储宏定义替换的字符串对
 */

#pragma once
#include <string>
using namespace std;

class StrStr {
public:
	string symbol;
	string expression;

	StrStr(string symbol, string expression) : symbol(symbol), expression(expression) {
	}
};