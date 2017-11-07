/*
 * InsCode.h
 *
 *  Created on: 2014年10月23日
 *      Author: Lei Zhang
 */

#pragma once

#include <string>
#include <regex>
#include <sstream>
#include <vector>
using namespace std;

class InsCode {
private:
	string space = "[ \\t]+";
	string comma = "[ \\t]*,[ \\t]*";
	string sep = "[ \\t]*";

	//$1标号不包括':'
	//下划线开头则后面至少存在数字或字母一个。字母开头则后方随意
	string labelDefine = "(_[a-zA-Z0-9_]+|[a-zA-Z][a-zA-Z0-9_]*)[ \\t]*:";
	//$1寄存器带'$'
	string reg = "(\\$(zero|at|[gsf]p|ra|[kv][01]|a[0-3]|t[0-9]|s[0-7]))";
	//$1标号或者立即数
	string labelOrImm = "(_[a-zA-Z0-9_]+|[a-zA-Z][a-zA-Z0-9_]*|-?[0-9]+h?)";
	string immediate = "(-?[0-9]+)";

	//$1指令名
	string insRdRs = space+"(abs|move|neg|negu|not|div|divu|jalr|mult|multu)"+space;
	string insRdRsRt = space + "(rol|ror|sge|sgeu|sgt|sgtu|sle|sleu|sne|seq|add|addu|and|mul|nor|or|sllv|slt|sltu|srav|srlv|sub|subu|xor)" + space;
	string insNop = space + "(nop)" + space;
	string insEret = space + "(eret)" + space;
	string insSyscall = space + "(syscall)" + space;
	string insRsImm = space + "(li|lui)" + space;
	string insRsLabelOrImm = space + "(bnez|beqz|bgez|bgezal|bgtz|blez|bltz|bltzal)" + space;
	string insRsRtLabelOrImm = space + "(bge|bgeu|bgt|bgtu|ble|bleu|blt|bltu|beq|bne|addi|addiu|andi|ori|slti|sltiu|xori|sra|srl|sll)" + space;
	string insRdLabelOrImmRs = space + "(la|lh|lhu|lw|sh|sw)" + space;
	string insLabelOrImm = space + "(b|jal|j)" + space;
	string insRs = space + "(jr|mfhi|mflo|ei|di|mfcause)" + space;

	string matchInsRdRs =  insRdRs + reg + comma + reg +space;
	string matchInsRdRsRt = insRdRsRt  + reg + comma + reg + comma + reg +space;
	string matchInsNop =  insNop ;
	string matchInsEret = insEret;
	string matchInsRsImm =  insRsImm  + reg + comma + immediate +space;
	string matchInsRsLabelOrImm = insRsLabelOrImm  + reg + comma + labelOrImm +space;
	string matchInsRsRtLabelOrImm = insRsRtLabelOrImm  + reg + comma + reg + comma + labelOrImm + space;
	string matchInsRdLabelOrImmRs = insRdLabelOrImmRs + reg + comma + labelOrImm + sep + "\\(" + sep + reg + sep + "\\)" +space;
	string matchInsLabelOrImm =  insLabelOrImm  + labelOrImm + space;
	string matchInsRs =  insRs  + reg + space;
	//结构比较奇怪。但是匹配了标号加代码的情况
	string matchLabelIns = space + labelDefine + sep + "[a-zA-Z].*";

	vector<string> *returnCode;

	void transInsRdRs(string);
	void transferInsRdRsRt(string);
	void transferInsNop(string);
	void transferInsEret(string);
	void transferInsSyscall(string s);
	void transferInsRsImm(string);
	void transferInsRsLabelOrImm(string);
	void transferInsRsRtLabelOrImm(string);
	void transferInsRdLabelOrImmRs(string);
	void transferInsLabelOrImm(string);
	void transferLabelIns(string);
	void transferInsRs(string);

public:
	InsCode();
	~InsCode();
	void transfer(string);
};

