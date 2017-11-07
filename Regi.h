/*
 * Regi.h
 *
 *  Created on: 2014Äê10ÔÂ19ÈÕ
 *      Author: Lei Zhang
 */

#ifndef REGI_H_
#define REGI_H_

/*#include<string>
#include<iostream>
#include"Str.h"
using namespace std;

class Rs{
protected: int i;
public:
Rs(string s1):i(-1){
	if (s1>="10000"&&s1<="10111"){
			Str x(s1);
			i=x.outInt();
			cout<<i;
		}
	}
};

class Rt{
protected: int i;
public:
Rt(string s1):i(-1){
	if ((s1>="1000"&&s1<="1111")||(s1>="11000"&&s1<="11001")){
			Str x(s1);
			i=x.outInt();
			cout<<i;
		}
	}
};

class RZero{
public:
	RZero(string s1){
		if (s1=="0")
			cout<<0;
	}
};*/
#include<string>
using namespace std;

string regi[32]={
		"$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3", "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7",
		    "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7", "$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra"
};

int reg(string s)
{
	for (int i=0;i<32;i++)
	{
		if (regi[i]==s||regi[i].substr(1)==s) return i;
	}
	return -1;
}

/*string reg(int i)
{
	return
}*/

#endif /* REGI_H_ */
