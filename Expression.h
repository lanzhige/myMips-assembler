/*
 *	�����޲ι��죬���ȺŸ�ֵ������ֱ���ַ������죬�ַ��������ʽ
 *	����answer�����ؼ�������Ϊint
 *	���ʽ�д��׳�string�쳣
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