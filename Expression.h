/*
 *	可以无参构造，其后等号赋值，或者直接字符串构造，字符串即表达式
 *	调用answer，返回计算结果，为int
 *	表达式有错抛出string异常
 */

#pragma once
#include <stack>
#include <string>
#include <regex>
#include <iostream>
using namespace std;

class Expression {
private:
	string expr;
	int result;
	void calculate();
	int calculate(int, int, char);
	void calculate(stack <char> &, stack <int> &);
	void noBlank();

public:
	Expression(void);
	~Expression(void);
	Expression(const string);
	void operator = (const string);
	int answer();
};