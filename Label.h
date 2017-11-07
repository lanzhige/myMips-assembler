/*
 *	�ñ�ű��ʼ�������뵥�䣬�����滻��Ľ��
 *	���û�б����ԭ�䷵��
 *	���û�ж�Ӧ�ı�ţ����׳�string�쳣
*/

#pragma once
#include <string>
#include <regex>
#include <vector>
#include <sstream>
#include "StrInt.h"
using namespace std;

class Label
{
private:
	string space = "[ \\t]+";
	string comma = "[ \\t]*,[ \\t]*";
	string sep = "[ \\t]*";

	string label = "(_[a-zA-Z0-9_]+|[a-zA-Z][a-zA-Z0-9_]*)";
	string reg = "(\\$(zero|at|[gsf]p|ra|[kv][01]|a[0-3]|t[0-9]|s[0-7]))";

	string insRsRtLabel = space + "(beq|bne|addi)"+ space;
	string insRsLabel =space + "(bgez|bgtz|blez|bltz|bltzal|bgezal)" + space;
	string insRtLabelRs = space + "(lw|lh|lhu|sw|sh)" + space;
	string insLabel = space + "(j|jal)"+ space;

	string matchInsRsRtLabel = insRsRtLabel + reg + comma + reg + comma + label + space;
	string matchInsRsLabel =  insRsLabel + reg + comma + label + space;
	string matchInsRtLabelRs = insRtLabelRs + reg + comma + label + sep + "\\(" + sep + reg + sep + "\\)" + space;
	string matchInsLabel = insLabel+ label + space;

	vector<StrInt> labelTable;

	string replaceCommaLabelSpace(string, int);
	string replaceCommaLabelBracket(string);
	string replaceSpaceLabelSpace(string);
	int find(string);
public:
	Label(vector<StrInt> labelTable) : labelTable(labelTable) {
	}
	~Label() {
	}
	string replace(string, int);
};
