/*
 *	���ڴ洢��ű�
 *	������==������Ƚϱ���Ƿ����
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