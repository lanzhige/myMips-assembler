/*
 * Str.h
 *
 *  Created on: 2014��10��19��
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
