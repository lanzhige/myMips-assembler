/*
 * Str.cpp
 *
 *  Created on: 2014Äê10ÔÂ19ÈÕ
 *      Author: Lei Zhang
 */

#include "Str.h"

Str::Str(int ii):i(ii) {
	// TODO Auto-generated constructor stub

}
Str::Str(string s):i(0){
	for (unsigned j=0;j<s.length();j++)
	{
		if (s[j]=='1') i+=1<<(s.length()-1-j);
	}
}

int Str::outInt()
{
	return i;
}


Str::~Str() {
	// TODO Auto-generated destructor stub
}

