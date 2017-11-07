#include "PseudoCode.h"

//(abs)|(move)|(neg)|(negu)|(not)|(div)|(divu)|(jalr)|(mult)|(multu)
void PseudoCode::transferInsRdRs(string s) {

	smatch m;
	regex_search(s, m, regex(insRdRs));
	string ins = m.format("$1");
	s = m.suffix().str();
	regex_search(s, m, regex(reg));
	string rd = m.format("$1");
	s = m.suffix().str();
	regex_search(s, m, regex(reg));
	string rs = m.format("$1");

	if (ins == "abs") {
		result.push_back("addu " + rd + ", $zero, " + rs);
		result.push_back("bgez " + rs + ", 1");
		result.push_back("sub " + rd + ", $zero, " + rs);
		//Abs(rd,rs);
	}
	else if (ins == "move") {
		result.push_back("addu " + rd + ", $zero, " + rs);
		//Move(rd,rs);
	}
	else if (ins == "neg") {
		result.push_back("sub " + rd + ", $zero, " + rs);
		//Neg(rd,rs);
	}
	else if (ins == "negu") {
		result.push_back("subu " + rd + ", $zero, " + rs);
		//Negu(rd,rs);
	}
	else if (ins == "not") {
		result.push_back("nor " + rd + ", $zero, " + rs);
		//Not(rd,rs);
	}
/*	else if (ins == "div"){
		Div(rd,rs);
	}
	else if (ins == "divu"){
		Divu(rd,rs);
	}
	else if (ins == "jalr"){
		Jalr(rd,rs);
	}
	else if (ins == "mult"){
		Mult(rd,rs);
	}
	else if (ins == "multu"){
		Multu(rd,rs);
	}*/
}

//(rol)|(ror)|(sge)|(sgeu)|(sgt)|(sgtu)|(sle)|(sleu)|(sne)|(seq)
void PseudoCode::transferInsRdRsRt(string s) {

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

	if (ins == "rol") {
		result.push_back("subu $at, $zero, " + rt);
		result.push_back("srlv $at, " + rs + ", $at");
		result.push_back("sllv " + rd + ", " + rs + ", " + rt);
		result.push_back("or " + rd + ", " + rd + ", $at");
		//Rol(rd,rs,rt);
	}
	else if (ins == "ror") {
		result.push_back("subu $at, $zero, " + rt);
		result.push_back("sllv $at, " + rs + ", $at");
		result.push_back("srlv " + rd + ", " + rs + ", " + rt);
		result.push_back("or " + rd + ", " + rd + ", $at");
		//Ror(rd,rs,rt);
	}
	else if (ins == "sge") {
		result.push_back("bne " + rt + ", " + rs + ", 2");
		result.push_back("ori " + rd + ", $zero, 1");
		result.push_back("beq $zero, $zero, 1");
		result.push_back("slt " + rd + ", " + rt + ", " + rs);
		//Sge(rd,rs,rt);
	}
	else if (ins == "sgeu") {
		result.push_back("bne " + rt + ", " + rs + ", 2");
		result.push_back("ori " + rd + ", $zero, 1");
		result.push_back("beq $zero, $zero, 1");
		result.push_back("sltu " + rd + ", " + rt + ", " + rs);
		//Sgeu(rd,rs,rt);
	}
	else if (ins == "sle") {
		result.push_back("bne " + rt + ", " + rs + ", 2");
		result.push_back("ori " + rd + ", $zero, 1");
		result.push_back("beq $zero, $zero, 1");
		result.push_back("slt " + rd + ", " + rs + ", " + rt);
		//Sle(rd,rs,rt);
	}
	else if (ins == "sleu") {
		result.push_back("bne " + rt + ", " + rs + ", 2");
		result.push_back("ori " + rd + ", $zero, 1");
		result.push_back("beq $zero, $zero, 1");
		result.push_back("sltu " + rd + ", " + rs + ", " + rt);
		//Sleu(rd,rs,rt);
	}
	else if (ins == "sgt") {
		result.push_back("slt " + rd + ", " + rt + ", " + rs);
		//Sgt(rd,rs,rt);
	}
	else if (ins == "sgtu") {
		result.push_back("sltu " + rd + ", " + rt + ", " + rs);
		//Sgtu(rd,rs,rt);
	}
	else if (ins == "sne") {
		result.push_back("beq " + rt + ", " + rs + ", 2");
		result.push_back("ori " + rd + ", $zero, 1");
		result.push_back("beq $zero, $zero, 1");
		result.push_back("ori " + rd + ", $zero, 0");
		//Sne(rd,rs,rt);
	}
	else if (ins == "seq") {
		result.push_back("beq " + rt + ", " + rs + ", 2");
		result.push_back("ori " + rd + ", $zero, 0");
		result.push_back("beq $zero, $zero, 1");
		result.push_back("ori " + rd + ", $zero, 1");
		//Seq(rd,rs,rt);
	}
}

//(nop)
void PseudoCode::transferInsNop(string s) {
	result.push_back("sll $zero, $zero, 0");
	//Nop();
}

//(li)
void PseudoCode::transferInsRsImm(string s) {
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
		result.push_back(string("lui $at, ") + temp);
		x=bit32&0xFFFF;
		s<<x;
		s>>temp;
		result.push_back("ori " + rd + ", $at, " + temp);
	}
}

//(bnez)|(beqz)|(beq)|
void PseudoCode::transferInsRsLabelOrImm(string s) {
	smatch m;
	regex_search(s, m, regex(insRsLabelOrImm));
	string ins = m.format("$1");
	s = m.suffix().str();
	regex_search(s, m, regex(reg));
	string rd = m.format("$1");
	s = m.suffix().str();
	regex_search(s, m, regex(labelOrImm));
	string imm = m.format("$1");

	if (ins == "bnez") {
		result.push_back("bne $zero, " + rd + ", " + imm);
	}
	else if (ins == "beqz") {
		result.push_back("beq $zero, " + rd + ", " + imm);
	}
}

//(bge)|(bgeu)|(bgt)|(bgtu)|(ble)|(bleu)|(blt)|(bltu)
void PseudoCode::transferInsRsRtLabelOrImm(string s) {

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

	if (ins == "bge") {
		result.push_back("slt $at, " + rs + ", " + rt);
		result.push_back("beq $zero, $at, " + imm);
	}
	else if (ins == "bgeu") {
		result.push_back("sltu $at, " + rs + ", " + rt);
		result.push_back("beq $zero, $at, " + imm);
	}
	else if (ins == "bgt") {
		result.push_back("slt $at, " + rt + ", " + rs);
		result.push_back("bne $zero, $at, " + imm);
	}
	else if (ins == "bgtu") {
		result.push_back("sltu $at, " + rt + ", " + rs);
		result.push_back("bne $zero, $at, " + imm);
	}
	else if (ins == "ble") {
		result.push_back("slt $at, " + rt + ", " + rs);
		result.push_back("beq $zero, $at, " + imm);
	}
	else if (ins == "bleu") {
		result.push_back("sltu $at, " + rt + ", " + rs);
		result.push_back("beq $zero, $at, " + imm);
	}
	else if (ins == "blt") {
		result.push_back("slt $at, " + rs + ", " + rt);
		result.push_back("bne $zero, $at, " + imm);
	}
	else if (ins == "bltu") {
		result.push_back("sltu $at, " + rs + ", " + rt);
		result.push_back("bne $zero, $at, " + imm);
	}
}

//(la)
void PseudoCode::transferInsRdLabelOrImmRs(string s) {

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

	if (ins == "la") {
		result.push_back("addi " + rd + ", " + rs + ", " + imm);
	}
}

//(b)
void PseudoCode::transferInsLabelOrImm(string s) {

	smatch m;
	regex_search(s, m, regex(insLabelOrImm));
	string ins = m.format("$1");
	s = m.suffix().str();
	regex_search(s, m, regex(labelOrImm));
	string imm = m.format("$1");

	if (ins == "b") {
		result.push_back("beq $zero, $zero, " + imm);
	}
}

//标号:代码，分成两行
void PseudoCode::transferLabelIns(string s) {

	smatch m;
	regex_search(s, m, regex(labelDefine));
	string ins = m.format("$1");
	s = m.suffix().str();

	result.push_back(ins + ":");
	result.push_back(s);
}

vector<string> &PseudoCode::transfer(string s) {
	result.clear();

	if (regex_match(s, regex(matchLabelIns))) {
		transferLabelIns(s);
	}
	else if (regex_match(s, regex(matchInsRdRs))) {
		transferInsRdRs(s);
	}
	else if (regex_match(s, regex(matchInsRdRsRt))) {
		transferInsRdRsRt(s);
	}
	else if (regex_match(s, regex(matchInsNop))) {
		transferInsNop(s);
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
	else {
		result.push_back(s.substr(1));
	}

	for (size_t i = 0; i < result.size(); i++) {
		result[i] = " " + result[i] + " ";
	}
	return result;
}
