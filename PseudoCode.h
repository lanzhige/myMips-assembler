/* 
 *	�޲ι��졣
 *	����transfer������Ϊstringһ��ָ��
 *	����vecter<string>�����Ϊαָ����Ƕ�Ӧ�����ȥ��ָ��
 *	����Ǳ��:ָ����ʽ������ֳ����к󷵻�
 *	������������ش�СΪ1��vector����ԭ�䱾��
 */

#pragma once
#include <stdio.h>
#include <string>
#include <regex>
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

class PseudoCode {
private:
	string space = "[ \\t]+";
	string comma = "[ \\t]*,[ \\t]*";
	string sep = "[ \\t]*";

	//$1��Ų�����':' 
	//�»��߿�ͷ��������ٴ������ֻ���ĸһ������ĸ��ͷ�������
	string labelDefine = "(_[a-zA-Z0-9_]+|[a-zA-Z][a-zA-Z0-9_]*)[ \\t]*:";
	//$1�Ĵ�����'$'
	string reg = "(\\$(zero|at|[gsf]p|ra|[kv][01]|a[0-3]|t[0-9]|s[0-7]))";
	//$1��Ż���������
	string labelOrImm = "(_[a-zA-Z0-9_]+|[a-zA-Z][a-zA-Z0-9_]*|-?[0-9]+h?)";
	string immediate = "(-?[0-9]+)";

	//$1ָ����
	string insRdRs = space + "(abs|move|neg|negu|not)" + space;
	string insRdRsRt = space + "(rol|ror|sge|sgeu|sgt|sgtu|sle|sleu|sne|seq)" + space;
	string insNop = space + "(nop)" + space;
	string insSyscall = space + "(syscall)" + space;
	string insRsImm = space + "(li)" + space;
	string insRsLabelOrImm = space + "(bnez|beqz)" + space;
	string insRsRtLabelOrImm = space + "(bge|bgeu|bgt|bgtu|ble|bleu|blt|bltu)" + space;
	string insRdLabelOrImmRs = space + "(la)" + space;
	string insLabelOrImm = space + "(b)" + space;

	string matchInsRdRs =  insRdRs + reg + comma + reg + space;
	string matchInsRdRsRt =  insRdRsRt + reg + comma + reg + comma + reg + space;
	string matchInsNop =  insNop ;
	string matchInsRsImm =  insRsImm  + reg + comma + immediate + space;
	string matchInsRsLabelOrImm =  insRsLabelOrImm + reg + comma + labelOrImm + space;
	string matchInsRsRtLabelOrImm =  insRsRtLabelOrImm + reg + comma + reg + comma + labelOrImm + space;
	string matchInsRdLabelOrImmRs =  insRdLabelOrImmRs + reg + comma + labelOrImm + sep + "\\(" + sep + reg + sep + "\\)" + space;
	string matchInsLabelOrImm =  insLabelOrImm + labelOrImm + space;
	//�ṹ�Ƚ���֡�����ƥ���˱�żӴ�������
	string matchLabelIns = space + labelDefine + sep + "[a-zA-Z].*";

	vector<string> result;

	void transferInsRdRs(string);
	void transferInsRdRsRt(string);
	void transferInsNop(string);
	void transferInsSyscall(string s);
	void transferInsRsImm(string);
	void transferInsRsLabelOrImm(string);
	void transferInsRsRtLabelOrImm(string);
	void transferInsRdLabelOrImmRs(string);
	void transferInsLabelOrImm(string);
	void transferLabelIns(string);

public:
	PseudoCode() {
	}
	~PseudoCode() {
	}
	vector<string> &transfer(string);
};
