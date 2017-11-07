/*
 * Str.h
 *
 *  Created on: 2014Äê10ÔÂ19ÈÕ
 *      Author: Lei Zhang
 */

#ifndef STR_H_
#define STR_H_
#include<string>
using namespace std;

class Str {
protected:
	int i;
public:
	Str(int ii);
	Str(string s);
	int outInt();
	virtual ~Str();
};


#endif /* STR_H_ */
