/*
 * BasicConstruction.h
 *
 *  Created on: 2014Äê10ÔÂ19ÈÕ
 *      Author: Lei Zhang
 */

#ifndef BASICCONSTRUCTION_H_
#define BASICCONSTRUCTION_H_

#include<string>
#include<iostream>
#include"Regi.h"
#include<bitset>
using namespace std;

int stringtoint(string s)
{
	int sum=0;
	for (unsigned i=0;i<s.length();i++)
	{
		sum=sum*10+s[i]-'0';
	}
	return sum;
}


void Addi(string s0,string s1,int imm){
	bitset<32> mipscmd;
	int i=(8<<26)|(reg(s1)<<21)|(reg(s0)<<16)|(imm&0x0000ffff);
	mipscmd=i;
	cout<<mipscmd;
}

void Addiu(string s0,string s1,int imm){
	bitset<32> mipscmd;
	mipscmd=(9<<26)|(reg(s1)<<21)|(reg(s0)<<16)|(imm&0x0000ffff);
	cout<<mipscmd;
}


void Andi(string s0,string s1,unsigned imm){
	bitset<32> mipscmd;
	mipscmd=(0x0c<<26)|(reg(s1)<<21)|(reg(s0)<<16)|(imm&0x0000ffff);
	cout<<mipscmd;
}


void Beq(string s0,string s1,int L){
	bitset<32> mipscmd;
	mipscmd=(4<<26)|(reg(s0)<<21)|(reg(s1)<<16)|(L&0x0000ffff);
	cout<<mipscmd;
}

void Bgez(string s0,int L){
	bitset<32> mipscmd;
	mipscmd=(1<<26)|(reg(s0)<<21)|(1<<16)|(L&0x0000ffff);
	cout<<mipscmd;
}

void	Bgezal(string s0,int L){
	bitset<32> mipscmd;
	mipscmd=(1<<26)|(reg(s0)<<21)|(17<<16)|(L&0x0000ffff);
	cout<<mipscmd;
}


void	Bgtz(string s0,int L){
	bitset<32> mipscmd;
	mipscmd=(7<<26)|(reg(s0)<<21)|(0<<16)|(L&0x0000ffff);
	cout<<mipscmd;
	}



void	Blez(string s0,int L){
	bitset<32> mipscmd;
	mipscmd=(6<<26)|(reg(s0)<<21)|(0<<16)|(L&0x0000ffff);
	cout<<mipscmd;
}


void	Bltz(string s0,int L){
	bitset<32> mipscmd;
	mipscmd=(1<<26)|(reg(s0)<<21)|(0<<16)|(L&0x0000ffff);
	cout<<mipscmd;
}
//????


void	Bltzal(string s0,int L){
	bitset<32> mipscmd;
	mipscmd=(1<<26)|(reg(s0)<<21)|(16<<16)|(L&0x0000ffff);
	cout<<mipscmd;
}


void	Bne(string s0,string s1,int L){
	bitset<32> mipscmd;
	mipscmd=(5<<26)|(reg(s0)<<21)|(reg(s1)<<16)|(L&0x0000ffff);
	cout<<mipscmd;
}

void	Lh(string s0,string s1){
	bitset<32> mipscmd;
	string str1,str2;
	int D;
	str1=s1.substr(0,s1.find('('));
	str2=s1.substr(s1.find('(')+1,s1.find(')')-s1.find('(')-1);
	D=stringtoint(str1);
	mipscmd=(0x21<<26)|(reg(str2)<<21)|(reg(s0)<<16)|(D&0x0000ffff);
	cout<<mipscmd;
}


void	Lhu(string s0,string s1){
	bitset<32> mipscmd;
	string str1,str2;
	unsigned D;
	str1=s1.substr(0,s1.find('('));
	str2=s1.substr(s1.find('(')+1,s1.find(')')-s1.find('(')-1);
	D=stringtoint(str1);
	mipscmd=(0x25<<26)|(reg(str2)<<21)|(reg(s0)<<16)|D;
	cout<<mipscmd;
}

void	Lui(string s0,int imm){
	bitset<32> mipscmd;
	mipscmd=(0x0f<<26)|(0<<21)|(reg(s0)<<16)|(imm&0x0000ffff);
	cout<<mipscmd;
}

void	Lw(string s0,string s1){
	bitset<32> mipscmd;
	string str1,str2;
	int D;
	str1=s1.substr(0,s1.find('('));
	str2=s1.substr(s1.find('(')+1,s1.find(')')-s1.find('(')-1);
	D=stringtoint(str1);
	mipscmd=(0x23<<26)|(reg(str2)<<21)|(reg(s0)<<16)|(D&0x0000ffff);
	cout<<mipscmd;
}

void	Ori(string s0,string s1,unsigned imm){
	bitset<32> mipscmd;
	mipscmd=(0x0d<<26)|(reg(s1)<<21)|(reg(s0)<<16)|(imm&0x0000ffff);
	cout<<mipscmd;
}

void	Sh(string s0,string s1){
	bitset<32> mipscmd;
	string str1,str2;
	unsigned D;
	str1=s1.substr(0,s1.find('('));
	str2=s1.substr(s1.find('(')+1,s1.find(')')-s1.find('(')-1);
	D=stringtoint(str1);
	mipscmd=(0x29<<26)|(reg(str2)<<21)|(reg(s0)<<16)|D;
	cout<<mipscmd;
}


void	Slti(string s0,string s1,int imm){
	bitset<32> mipscmd;
	mipscmd=(0x0a<<26)|(reg(s1)<<21)|(reg(s0)<<16)|(imm&0x0000ffff);
	cout<<mipscmd;
}



void	Sltiu(string s0,string s1,unsigned imm){
	bitset<32> mipscmd;
	mipscmd=(0x0b<<26)|(reg(s1)<<21)|(reg(s0)<<16)|(imm&0x0000ffff);
	cout<<mipscmd;
	}



void	Sw(string s0,string s1){
	bitset<32> mipscmd;
	string str1,str2;
	int D;
	str1=s1.substr(0,s1.find('('));
	str2=s1.substr(s1.find('(')+1,s1.find(')')-s1.find('(')-1);
	D=stringtoint(str1);
	mipscmd=(0x2B<<26)|(reg(str2)<<21)|(reg(s0)<<16)|(D&0x0000ffff);
	cout<<mipscmd;
}



void	Xori(string s0,string s1,unsigned imm){
	bitset<32> mipscmd;
	mipscmd=(0x0e<<26)|(reg(s1)<<21)|(reg(s0)<<16)|(imm&0x0000ffff);
	cout<<mipscmd;
	}


void	J(int L){
	bitset<32> mipscmd;
	mipscmd=(2<<26)|(L&0x03fffff);
	cout<<mipscmd;
	}


void	Jal(int L){
	bitset<32> mipscmd;
	mipscmd=(3<<26)|(L&0x03fffff);
	cout<<mipscmd;
	}


void	Add(string s0,string s1,string s2){
	bitset<32> mipscmd;
	mipscmd=(0<<26)|(reg(s1)<<21)|(reg(s2)<<16)|(reg(s0)<<11)|0<<6|0x20;
	cout<<mipscmd;
	}


void	Addu(string s0,string s1,string s2){
	bitset<32> mipscmd;
	mipscmd=(0<<26)|(reg(s1)<<21)|(reg(s2)<<16)|(reg(s0)<<11)|0<<6|0x21;
	cout<<mipscmd;
	}


void	And(string s0,string s1,string s2){
	bitset<32> mipscmd;
	mipscmd=(0<<26)|(reg(s1)<<21)|(reg(s2)<<16)|(reg(s0)<<11)|0<<6|0x24;
	cout<<mipscmd;
	}


void	Div(string s1,string s2){
	bitset<32> mipscmd;
	mipscmd=(0<<26)|(reg(s1)<<21)|(reg(s2)<<16)|(0<<11)|0<<6|0x1a;
	cout<<mipscmd;
	}


void	Divu(string s1,string s2){
	bitset<32> mipscmd;
	mipscmd=(0<<26)|(reg(s1)<<21)|(reg(s2)<<16)|(0<<11)|0<<6|0x1b;
	cout<<mipscmd;
	}


void	Jalr(string s1,string s2){
	bitset<32> mipscmd;
	mipscmd=(0<<26)|(reg(s1)<<21)|(0<<16)|(reg(s2)<<11)|0<<6|9;
	cout<<mipscmd;
	}


void	Jr(string s1){
	bitset<32> mipscmd;
	mipscmd=(0<<26)|(reg(s1)<<21)|(0<<16)|(0<<11)|0<<6|8;
	cout<<mipscmd;
	}

void Ei(string s1){
	bitset<32> mipscmd;
	mipscmd = (63 << 26) | (reg(s1) << 11);
	cout << mipscmd;
}

void Di(string s1){
	bitset<32> mipscmd;
	mipscmd = (62 << 26) | (reg(s1) << 16);
	cout << mipscmd;
}

void Mfcause(string s1){
	bitset<32> mipscmd;
	mipscmd = (reg(s1) << 11) | 17;
	cout << mipscmd;
}

void	Mfhi(string s1){
	bitset<32> mipscmd;
	mipscmd=(0<<26)|(0<<21)|(0<<16)|(reg(s1)<<11)|0<<6|0x10;
	cout<<mipscmd;
	}


void	Mflo(string s1){
	bitset<32> mipscmd;
	mipscmd=(0<<26)|(0<<21)|(0<<16)|(reg(s1)<<11)|0<<6|0x12;
	cout<<mipscmd;
	}


void	Mult(string s1,string s2){
	bitset<32> mipscmd;
	mipscmd=(0<<26)|(reg(s1)<<21)|(reg(s2)<<16)|(0<<11)|0<<6|0x18;
	cout<<mipscmd;
	}


void	Multu(string s1,string s2){
	bitset<32> mipscmd;
	mipscmd=(0<<26)|(reg(s1)<<21)|(reg(s2)<<16)|(0<<11)|0<<6|0x19;
	cout<<mipscmd;
	}


void	Nor(string s0,string s1,string s2){
	bitset<32> mipscmd;
	mipscmd=(0<<26)|(reg(s1)<<21)|(reg(s2)<<16)|(reg(s0)<<11)|0<<6|0x27;
	cout<<mipscmd;
	}


void	Or(string s0,string s1,string s2){
	bitset<32> mipscmd;
	mipscmd=(0<<26)|(reg(s1)<<21)|(reg(s2)<<16)|(reg(s0)<<11)|0<<6|0x25;
	cout<<mipscmd;
	}


void	Sll(string s0,string s1,unsigned sft){
	bitset<32> mipscmd;
	mipscmd=(0<<26)|(0<<21)|(reg(s1)<<16)|(reg(s0)<<11)|(sft&0x3f)<<6|0;
	cout<<mipscmd;
	}


void Sllv(string s0,string s1,string s2){
	bitset<32> mipscmd;
	mipscmd=(0<<26)|(reg(s2)<<21)|(reg(s1)<<16)|(reg(s0)<<11)|0<<6|4;
	cout<<mipscmd;
	}


void	Slt(string s0,string s1,string s2){
	bitset<32> mipscmd;
	mipscmd=(0<<26)|(reg(s1)<<21)|(reg(s2)<<16)|(reg(s0)<<11)|0<<6|0x2a;
	cout<<mipscmd;
	}


void	Sltu(string s0,string s1,string s2){
	bitset<32> mipscmd;
	mipscmd=(0<<26)|(reg(s1)<<21)|(reg(s2)<<16)|(reg(s0)<<11)|0<<6|0x2b;
	cout<<mipscmd;
	}


void	Sra(string s0,string s1,unsigned sft){
	bitset<32> mipscmd;
	mipscmd=(0<<26)|(0<<21)|(reg(s1)<<16)|(reg(s0)<<11)|(sft&0x3f)<<6|3;
	cout<<mipscmd;
	}


void	Srav(string s0,string s1,string s2){
	bitset<32> mipscmd;
	mipscmd=(0<<26)|(reg(s2)<<21)|(reg(s1)<<16)|(reg(s0)<<11)|0<<6|7;
	cout<<mipscmd;
	}


void	Srl(string s0,string s1,unsigned sft){
	bitset<32> mipscmd;
	mipscmd=(0<<26)|(0<<21)|(reg(s1)<<16)|(reg(s0)<<11)|(sft&0x3f)<<6|2;
	cout<<mipscmd;
	}


void	Srlv(string s0,string s1,string s2){
	bitset<32> mipscmd;
	mipscmd=(0<<26)|(reg(s2)<<21)|(reg(s1)<<16)|(reg(s0)<<11)|0<<6|6;
	cout<<mipscmd;
	}


void	Sub(string s0,string s1,string s2){
	bitset<32> mipscmd;
	mipscmd=(0<<26)|(reg(s1)<<21)|(reg(s2)<<16)|(reg(s0)<<11)|0<<6|0x22;
	cout<<mipscmd;
	}


void	Subu(string s0,string s1,string s2){
	bitset<32> mipscmd;
	mipscmd=(0<<26)|(reg(s1)<<21)|(reg(s2)<<16)|(reg(s0)<<11)|0<<6|0x23;
	cout<<mipscmd;
	}


void	Syscall(){
	bitset<32> mipscmd = 0xc;
		cout<<mipscmd;
	}


void	Xor(string s0,string s1,string s2){
	bitset<32> mipscmd;
	mipscmd=(0<<26)|(reg(s1)<<21)|(reg(s2)<<16)|(reg(s0)<<11)|0<<6|0x26;
	cout<<mipscmd;
	}


void	Abs(string rd,string rs){
	Addu(rd,"$zero",rs);
	Bgez(rs,8);
	Sub(rd,"$zero",rs);
	}


void 	B(int L)
	{
	Bgez("$zero",L);
	}


void	Beqz(string rs,int L)
	{
		Beq(rs,"$zero",L);
	}


void	Bge(string rs,string rt,int L)
	{
		Slt("$at",rs,rt);
		Beq("$zero","$at",L);
	}


void	Bgeu(string rs,string rt,int L)
	{
		Sltu("$at",rs,rt);
		Beq("$zero","$at",L);
	}


void 	Bgt(string rs,string rt,int L)
	{
		Slt("$at",rt,rs);
		Bne("$zero","$at",L);
	}


void	 Bgtu(string rs,string rt,int L)
	{
		Sltu("$at",rt,rs);
		Bne("$zero","$at",L);
	}


void	Ble(string rs,string rt,int L)
	{
		Slt("$at",rt,rs);
		Beq("$zero","$at",L);
	}


void	Bleu(string rs,string rt,int L)
	{
		Sltu("$at",rt,rs);
		Beq("$zero","$at",L);
	}


void	Blt(string rs,string rt,int L)
	{
		Slt("$at",rs,rt);
		Bne("$zero","$at",L);
	}


void	Bltu(string rs,string rt,int L)
	{
		Sltu("$at",rs,rt);
		Bne("$zero","$at",L);
	}


void	Bnez(string rs,int L)
	{
		Bne(rs,"$zero",L);
	}


void	La(string s0,string s1){
		string str1,str2;
		int imm;
		str1=s1.substr(0,s1.find('('));
		str2=s1.substr(s1.find('(')+1,s1.find(')')-s1.find('(')-1);
		imm=stringtoint(str1);
		Addi(s0,str2,imm);
	}


void	Li(string rd,int imm)
	{
		Lui("$at",imm);
		Ori(rd,"$at",imm);
	}


void	Move(string rd, string rs){
		Add(rd,rs,"$zero");
	}


/*void	Mulo(string rd,string rs,string rt)
	{
		Mult(rs,rt);
		Mfhi("$at");
		Mflo x(rd);
		Sra(rd,rd,31);
		Beq("$at",rd,8);
	}


void	Mulou(string rd,string rs,string rt)
	{
		Mult(rs,rt);
		Mfhi("$at");
		Beq("$at",rd,8);
		Mflo(rd);
	}*/


void	Neg(string rd,string rs)
	{
		Sub(rd,"$zero",rs);
	}


void	Negu(string rd,string rs)
	{
		Subu(rd,"$zero",rs);
	}



void	Nop(){
		Sll("$zero","$zero",0);
	}

void  Eret(){
	bitset<32> mipscmd;
	mipscmd = 16 << 26;
	cout << mipscmd;
}


void	Not(string rd,string rs)
	{
		Nor(rd,rs,"$zero");
	}


void	Rem(string rd,string rs,string rt)
	{
		Bne(rt,"$zero",8);
		Div(rs,rt);
		Mfhi(rd);
	}


void	Remu(string rd,string rs,string rt)
	{
		Bne(rt,"$zero",8);
		Divu(rs,rt);
		Mfhi(rd);
	}


//without subu;;
void	Rol(string rd,string rs,string rt){
		Subu("$at","$zero",rt);
		Srlv("$at",rs,"$at");
		Sllv(rd,rs,rt);
		Or(rd,rd,"$at");
	}


void	Ror(string rd,string rs,string rt){
		Subu("$at","$zero",rt);
		Sllv("$at",rs,"$at");
		Srlv(rd,rs,rt);
		Or(rd,rd,"$at");
	}


void	Sge(string rd,string rs, string rt)
	{
		Bne(rt,rs,12);
		Ori(rd,"$zero",1);
		Beq("zero","zero",0);
		Slt(rd,rt,rs);
	}


void	Sgeu(string rd,string rs, string rt)
	{
		Bne(rt,rs,12);
		Ori(rd,"$zero",1);
		Beq("zero","zero",0);
		Sltu(rd,rt,rs);
	}


void	Sgt(string rd,string rs,string rt)
	{
		Slt(rd,rt,rs);
	}


void	Sgtu(string rd,string rs,string rt)
	{
		Sltu(rd,rt,rs);
	}


void	Sle(string rd,string rs, string rt)
	{
		Bne(rt,rs,12);
		Ori(rd,"$zero",1);
		Beq("zero","zero",8);
		Slt(rd,rs,rt);
	}


void	Sleu(string rd,string rs, string rt)
	{
		Bne(rt,rs,12);
		Ori(rd,"$zero",1);
		Beq("zero","zero",8);
		Sltu(rd,rs,rt);
	}


void	Sne(string rd,string rs, string rt)
	{
		Beq(rt,rs,12);
		Ori(rd,"$zero",1);
		Beq("zero","zero",8);
		Ori(rd,"$zero",0);
	}


void	Seq(string rd,string rs, string rt)
{
	Beq(rt,rs,12);
	Ori(rd,"$zero",0);
	Beq("zero","zero",8);
	Ori(rd,"$zero",1);
}


#endif /* BASICCONSTRUCTION_H_ */
