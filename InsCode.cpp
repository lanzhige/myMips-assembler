/*
 * InsCode.cpp
 *
 *  Created on: 2014Äê10ÔÂ23ÈÕ
 *      Author: Lei Zhang
 */

#include "InsCode.h"
#include<iostream>
#include "Bc.h"

InsCode::InsCode() {
	returnCode = new vector<string>();
}

InsCode::~InsCode() {
	delete returnCode;
}

//(abs)|(move)|(neg)|(negu)|(not)|(div)|(divu)|(jalr)|(mult)|(multu)
void InsCode::transInsRdRs(string s) {

	smatch m;
	regex_search(s, m, regex(insRdRs));
	string ins = m.format("$1");
	s = m.suffix().str();
	regex_search(s, m, regex(reg));
	string rd = m.format("$1");
	s = m.suffix().str();
	regex_search(s, m, regex(reg));
	string rs = m.format("$1");

	if (ins == "abs") 	 Abs(rd, rs);
	else if (ins == "move")	Move(rd,rs);
	else if (ins == "neg") 	Neg(rd,rs);
	else if (ins == "negu") Negu(rd,rs);
	else if (ins == "not") 	Not(rd,rs);
	else if (ins=="div")	Div(rd,rs);
	else if (ins=="divu")	Divu(rd,rs);
	else if (ins=="jalr")	Jalr(rd,rs);
	else if (ins=="mult")	Mult(rd,rs);
	else if (ins=="multu")	Multu(rd,rs);
}

//(rol)|(ror)|(sge)|(sgeu)|(sgt)|(sgtu)|(sle)|(sleu)|(sne)|(seq)
//|(add)|(addu)|(and)|(mul)|(nor)|(or)|(sllv)|(slt)|(sltu)|(srav)|(srlv)|(sub)|(subu)|(xor)
void InsCode::transferInsRdRsRt(string s) {

	smatch m;
	regex_search(s, m, regex(insRdRsRt));
	string ins = m.format("$1");
	s = m.suffix().str();
	regex_search(s, m, regex(reg));
	string rd = m.format("$1");
	s = m.suffix().str();
	regex_search(s, m, regex(reg));
	string rs = m.format("$1");
	s = m.suffix().str();
	regex_search(s, m, regex(reg));
	string rt = m.format("$1");

	if (ins == "rol") Rol(rd,rs,rt);
	else if (ins == "ror") 		Ror(rd,rs,rt);
	else if (ins == "sge") 		Sge(rd,rs,rt);
	else if (ins == "sgeu") 	Sgeu(rd,rs,rt);
	else if (ins == "sle") 		Sle(rd,rs,rt);
	else if (ins == "sleu") 	Sleu(rd,rs,rt);
	else if (ins == "sgt") 		Sgt(rd,rs,rt);
	else if (ins == "sgtu") 	Sgtu(rd,rs,rt);
	else if (ins == "sne") 		Sne(rd,rs,rt);
	else if (ins == "seq") 		Seq(rd,rs,rt);
	else if (ins == "add")	 	Add(rd,rs,rt);
	else if (ins == "addu") 	Addu(rd,rs,rt);
	else if (ins == "and") 		And(rd,rs,rt);
	else if (ins == "nor") 		Nor(rd,rs,rt);
	else if (ins == "or") 		Or(rd,rs,rt);
	else if (ins == "sllv") 	Sllv(rd,rs,rt);
	else if (ins == "slt") 		Slt(rd,rs,rt);
	else if (ins == "sltu") 	Sltu(rd,rs,rt);
	else if (ins == "srav") 	Srav(rd,rs,rt);
	else if (ins == "srlv")	 	Srlv(rd,rs,rt);
	else if (ins == "sub") 		Sub(rd,rs,rt);
	else if (ins == "subu") 	Subu(rd,rs,rt);
	else if (ins == "xor") 		Xor(rd,rs,rt);
}

//(nop)
void InsCode::transferInsNop(string s) {
	Nop();
}

void InsCode::transferInsEret(string s){
	Eret();
}

void InsCode::transferInsSyscall(string s){
	Syscall();
}

//(li)
void InsCode::transferInsRsImm(string s) {

	smatch m;
	regex_search(s, m, regex(insRsImm));
	string ins = m.format("$1");
	s = m.suffix().str();
	regex_search(s, m, regex(reg));
	string rd = m.format("$1");
	s = m.suffix().str();
	regex_search(s, m, regex(immediate));
	string imm = m.format("$1");

	if (ins == "li") {
		unsigned int bit32 = atoi(imm.c_str());
		int x;
		x=bit32>>16;
		stringstream s;
		string temp;
		s<<x;
		s>>temp;
		x=bit32&0xFFFF;
		s<<x;
		s>>temp;
		Li(rd,bit32);
	}
	else if (ins == "lui"){
		unsigned bit32 = atoi(imm.c_str());
		Lui(rd,bit32);
	}
}

//(bnez)|(beqz)
void InsCode::transferInsRsLabelOrImm(string s) {
	smatch m;
	regex_search(s, m, regex(insRsLabelOrImm));
	string ins = m.format("$1");
	s = m.suffix().str();
	regex_search(s, m, regex(reg));
	string rd = m.format("$1");
	s = m.suffix().str();
	regex_search(s, m, regex(labelOrImm));
	string imm = m.format("$1");

	int bit32=atoi(imm.c_str());

	if (ins == "bnez") {
		Bnez(rd,bit32);
	}
	else if (ins == "beqz") {
		Beqz(rd,bit32);
	}
	else if (ins == "bgez"){
		Bgez(rd,bit32);
	}
	else if (ins == "bgezal"){
		Bgezal(rd,bit32);
	}
	else if (ins == "bgtz"){
		Bgtz(rd,bit32);
	}
	else if (ins == "blez"){
		Blez(rd,bit32);
	}
	else if (ins == "bltz"){
		Bltz(rd,bit32);
	}
	else if (ins =="bltzal"){
		Bltzal(rd,bit32);
	}
}

//(bge)|(bgeu)|(bgt)|(bgtu)|(ble)|(bleu)|(blt)|(bltu)
//addi|addiu|andi|ori|slti|sltiu|xori|sra|srl|sll
void InsCode::transferInsRsRtLabelOrImm(string s) {

	smatch m;
	regex_search(s, m, regex(insRsRtLabelOrImm));
	string ins = m.format("$1");
	s = m.suffix().str();
	regex_search(s, m, regex(reg));
	string rs = m.format("$1");
	s = m.suffix().str();
	regex_search(s, m, regex(reg));
	string rt = m.format("$1");
	s = m.suffix().str();
	regex_search(s, m, regex(labelOrImm));
	string imm = m.format("$1");
	int bit32=atoi(imm.c_str());

	if (ins == "bge") {
		Bge(rs,rt,bit32);
	}
	else if (ins == "bgeu") {
		Bgeu(rs,rt,bit32);
	}
	else if (ins == "bgt") {
		Bgt(rs,rt,bit32);
	}
	else if (ins == "bgtu") {
		Bgtu(rs,rt,bit32);
	}
	else if (ins == "ble") {
		Ble(rs,rt,bit32);
	}
	else if (ins == "bleu") {
		Bleu(rs,rt,bit32);
	}
	else if (ins == "blt") {
		Blt(rs,rt,bit32);
	}
	else if (ins == "bltu") {
		Bltu(rs,rt,bit32);
	}
	else if (ins == "beq")
	{
		Beq(rs,rt,bit32);
	}
	else if (ins == "bne"){
		Bne(rs,rt,bit32);
	}
	else if (ins == "addi"){
		Addi(rs, rt, bit32);
	}
	else if (ins == "addiu"){
		Addiu(rs, rt, bit32);
	}
	else if (ins == "andi"){
		Andi(rs, rt, bit32);
	}
	else if (ins == "ori"){
		Ori(rs, rt, bit32);
	}
	else if (ins == "slti"){
		Slti(rs, rt, bit32);
	}
	else if (ins == "sltiu"){
		Sltiu(rs, rt, bit32);
	}
	else if (ins == "xori"){
		Xori(rs, rt, bit32);
	}
	else if (ins == "sra"){
		Sra(rs, rt, bit32);
	}
	else if (ins == "srl"){
		Srl(rs, rt, bit32);
	}
	else if (ins == "sll"){
		Sll(rs, rt, bit32);
	}
	
}

//(la)
void InsCode::transferInsRdLabelOrImmRs(string s) {

	smatch m;
	regex_search(s, m, regex(insRdLabelOrImmRs));
	string ins = m.format("$1");
	s = m.suffix().str();
	regex_search(s, m, regex(reg));
	string rd = m.format("$1");
	s = m.suffix().str();
	regex_search(s, m, regex(labelOrImm));
	string imm = m.format("$1");
	s = m.suffix().str();
	regex_search(s, m, regex(reg));
	string rs = m.format("$1");
	imm=imm+"("+rs+")";

	if (ins == "la") {
		La(rd,imm);
	}
	else if (ins == "lh")
	{
		Lh(rd,imm);
	}
	else if (ins == "lhu"){
		Lhu(rd,imm);
	}
	else if (ins == "lw"){
		Lw(rd,imm);
	}
	else if (ins == "sh"){
		Sh(rd,imm);
	}
	else if (ins == "sw"){
		Sw(rd,imm);
	}
}

//(b)
void InsCode::transferInsLabelOrImm(string s) {

	smatch m;
	regex_search(s, m, regex(insLabelOrImm));
	string ins = m.format("$1");
	s = m.suffix().str();
	regex_search(s, m, regex(labelOrImm));
	string imm = m.format("$1");
	int bit32=atoi(imm.c_str());

	if (ins == "b") {
		//result.push_back("beq $zero, $zero, " + imm);
		B(bit32);
	}
	else if (ins == "j"){
		J(bit32);
	}
	else if (ins == "jal"){
		Jal(bit32);
	}
}

void InsCode::transferInsRs(string s){
	smatch m;
	regex_search(s, m, regex(insRs));
	string ins = m.format("$1");
	s = m.suffix().str();
	regex_search(s, m, regex(reg));
	string rs = m.format("$1");
	if (ins == "jr"){
		Jr(rs);
	}
	else if (ins == "mfhi"){
		Mfhi(rs);
	}
	else if (ins == "mflo"){
		Mflo(rs);
	}
	else if (ins == "ei"){
		Ei(rs);
	}
	else if (ins == "di"){
		Di(rs);
	}
	else if (ins == "mfcause"){
		Mfcause(rs);
	}
}

void InsCode::transfer(string s) {

	if (regex_match(s, regex(matchInsRdRs))) {
		transInsRdRs(s);
	}
	else if (regex_match(s, regex(matchInsRdRsRt))) {
		transferInsRdRsRt(s);
	}
	else if (regex_match(s, regex(matchInsNop))) {
		transferInsNop(s);
	}
	else if (regex_match(s, regex(matchInsEret))){
		transferInsEret(s);
	}
	else if (regex_match(s,regex(insSyscall))){
		transferInsSyscall(s);
	}
	else if (regex_match(s, regex(matchInsRsImm))) {
		transferInsRsImm(s);
	}
	else if (regex_match(s, regex(matchInsRsLabelOrImm))) {
		transferInsRsLabelOrImm(s);
	}
	else if (regex_match(s, regex(matchInsRsRtLabelOrImm))) {
		transferInsRsRtLabelOrImm(s);
	}
	else if (regex_match(s, regex(matchInsRdLabelOrImmRs))) {
		transferInsRdLabelOrImmRs(s);
	}
	else if (regex_match(s, regex(matchInsLabelOrImm))) {
		transferInsLabelOrImm(s);
	}
	else if (regex_match(s, regex(matchInsRs))){
		transferInsRs(s);
	}
}
