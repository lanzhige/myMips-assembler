#include "Expression.h"

Expression::Expression() : expr(""){
	noBlank();
}

Expression::Expression(const string expr) : expr(expr) {
	noBlank();
}

void Expression::operator = (const string expr) {
	this->expr = expr;
	noBlank();
}

int Expression::answer() {
	calculate();
	return result;
}

Expression::~Expression() {
}

void Expression::noBlank() {
	if (expr.length() == 0)
		return;

	expr = regex_replace(expr, regex("[^0-9\\+\\*\\(\\)\\^\\|%><&/~-]"), (string)"");
	expr = regex_replace(expr, regex(">>>"), (string)"A");
	expr = regex_replace(expr, regex(">>"), (string)"R");
	expr = regex_replace(expr, regex("<<"), (string)"L");
	expr = regex_replace(expr, regex("~"), (string)"-1^");
	expr = regex_replace(expr, regex("([^0-9\\)])([\\+-][0-9]+)"), (string)"$1($2)");
	expr = regex_replace(expr, regex("^[\\+-][0-9]+"), (string)"($0)");
	expr = regex_replace(expr, regex("(\\()([\\+-][0-9]+)"), (string)"$1ZERO$2");
	expr = regex_replace(expr, regex("ZERO"), (string)"0");
	
//	cout << expr << endl;
}

int Expression::calculate(int a, int b, char c) {
	switch (c) {
	case '+':
		return (a + b);
	case '-':
		return (a - b);
	case '*':
		return (a * b);
	case '/':
		return (a / b);
	case '%':
		return (a / b);
	case '&': 
		return (a & b);
	case '^': 
		return (a ^ b);
	case '|':
		return (a | b);
	case 'A':
		return (a >> b);
	case 'R':
		return ((int)(((size_t)a) >> ((size_t)b)));
	case 'L':
		return (a << b);
	}
	return 0;
}

void Expression::calculate(stack <char> &opStack, stack <int> &numStack) {
	char op;
	int numA, numB, res;

	if (opStack.empty())
		throw (string("Wrong Expression"));
	op = opStack.top();
	opStack.pop();

	if (numStack.empty())
		throw (string("Wrong Expression"));
	numB = numStack.top();
	numStack.pop();

	if (numStack.empty())
		throw (string("Wrong Expression"));
	numA = numStack.top();
	numStack.pop();

	res = calculate(numA, numB, op);
	numStack.push(res);
}

void Expression::calculate() {
	stack <char> opStack;
	stack <int> numStack;
	int length = expr.length(), index = 0;
	int num = 0;
	bool isNum = false;

	if (length == 0) {
		throw (string("Wrong Expression"));
	}

	while (index < length) {
		char ch = expr[index++];
		if (ch >= 0x30 && ch <= 0x39) {
			num = num * 10 + (ch - 0x30);
			isNum = true;
		}
		else {
			if (isNum) {
				numStack.push(num);
			}
			isNum = false;
			num = 0;

			switch (ch)	{
			case '+': case '-': {
				while (!opStack.empty() && opStack.top() != '(') {
					calculate(opStack, numStack);
				}
				opStack.push(ch);
			} break;
			case '*': case '/': case '%': {
				while (!opStack.empty() && opStack.top() != '(' && opStack.top() != '+' && opStack.top() != '-') {
					calculate(opStack, numStack);
				}
				opStack.push(ch);
			} break;
			case '&': case '^': case '|': {
				while (!opStack.empty() && opStack.top() != '(' && opStack.top() != '+' && opStack.top() != '-' &&
					opStack.top() != '*' && opStack.top() != '/' && opStack.top() != '%') {
					calculate(opStack, numStack);
				}
				opStack.push(ch);
			} break;
			case 'A': case 'R': case 'L': {
				while (!opStack.empty() && (opStack.top() == 'A' || opStack.top() == 'R' || opStack.top() == 'L')) {
					calculate(opStack, numStack);
				}
				opStack.push(ch);
			}
				break;
			case '(': {
				opStack.push(ch);
			}
				break;
			case ')': {
				while (!opStack.empty() && opStack.top() != '(') {
					calculate(opStack, numStack);
				}
				if (opStack.empty()) {
					throw (string("Unmatched Brackets"));
				}
				else {
					opStack.pop();
				}
			}
				break;
			default:
				throw (string("Undefined Character"));
				break;
			}
		}
	}
	if (isNum) {
		numStack.push(num);
	}

	while (!opStack.empty()) {
		calculate(opStack, numStack);
	}
	this->result = numStack.top();
}
