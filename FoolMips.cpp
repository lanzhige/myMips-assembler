#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <ctime>
#include <bitset>
#include "PseudoCode.h"
#include "Expression.h"
#include "InsCode.h"
#include "Label.h"
#include "StrStr.h"
#include "StrInt.h"
using namespace std;

int main() {
	clock_t start, stop, all;		//start ticks and stop ticks
	double duration;		//records the run time (seconds) of a function and the total time

	//�������
	all = start = clock();
	vector<string> program;
	char temp[256];
	ifstream readin("input.txt", ios::in);
	while (!readin.eof()) {
		readin.getline(temp, 256);
		string t = temp;
		//ȥע��
		if (t.find('#') != string::npos) {
			/*string x="$1";
			regex_replace(t,regex("(.*?)#.*"), x);*/
			t = t.substr(0, t.find("#"));
			//cout << t << endl;
		}
		if (regex_match(t, regex("[ \\t]*"))) {
			continue;
		}
		program.push_back(" " + t + " ");
	}
	stop = clock();
	duration = ((double)(stop - start)) / CLK_TCK;
	cout << "�������ȥ��ע�ͺͿ��У�\t" << duration << endl;

	//.data�ƶ���.textǰ��
	start = clock();
	vector<string>::iterator startOfText, startOfData;
	for (startOfText = program.begin(); startOfText != program.end(); ++startOfText) {
		if (regex_match(*startOfText, regex("[ \\t]+(\\.text)[ \\t]+")))
			break;
	}
	for (startOfData = program.begin(); startOfData != program.end(); ++startOfData) {
		if (regex_match(*startOfData, regex("[ \\t]+(\\.data)[ \\t]+")))
			break;
	}
	if (startOfText < startOfData) {
		vector<string> temp(startOfData, program.end());
		program.erase(startOfData, program.end());
		program.insert(program.begin(), temp.begin(), temp.end());
	}
	stop = clock();
	duration = ((double)(stop - start)) / CLK_TCK;
	cout << ".data�ƶ���.textǰ�棺\t\t" << duration << endl;

	//�궨���滻��Ĭ��ֻ����ĸ������ɣ���������Сд����..
	start = clock();
	vector<StrStr> equ;
	string matchEqu = "[ \\t]+([a-zA-Z][_?a-zA-Z0-9]*)[ \\t]+equ[ \\t]+([^ \\t]*).*";
	for (vector<string>::iterator iter = program.begin(); iter != program.end();) {
		smatch m;
		if (regex_match(*iter, m, regex(matchEqu))) {
			equ.push_back(StrStr(m.format("$1"), m.format("$2")));
			iter = program.erase(iter);
			if (iter == program.end()) break;
		}
		else ++iter;
	}
	for (vector<string>::iterator iter = program.begin(); iter != program.end(); ++iter) {
		for (vector<StrStr>::iterator itere = equ.begin(); itere != equ.end(); ++itere) {
			smatch m;
			while (regex_search(*iter, m, regex("(.*?[^a-zA-Z0-9])" + (*itere).symbol + "([^a-zA-Z0-9].*)"))) {
				*iter = m.format("$1") + (*itere).expression + m.format("$2");
			}
		}
	}
	stop = clock();
	duration = ((double)(stop - start)) / CLK_TCK;
	cout << "�궨���滻��\t\t\t" << duration << endl;


	string tomorrowLabel = "[ \\t]+((_[a-zA-Z0-9_]+)|([a-zA-Z][a-zA-Z0-9_]*))[ \\t]*:[ \\t]*";
	string hexInt = ".*\\W(-?[0-9]+[a-fA-F0-9_]*h)\\W.*";
	string OnlyHexInt = "(-?[0-9]+[a-fA-F0-9_]*h)";

	for (vector<string>::iterator iter = program.begin(); iter != program.end(); ++iter) {
		smatch m;

		if (regex_match(*iter, m, regex(tomorrowLabel))) continue;
		string rets = "";
		string ss = *iter;
		while (regex_match(ss, m, regex(hexInt))){
			regex_search(ss, m, regex(OnlyHexInt));
			string s = "";
			s=m.format("$1");
			string s1= m.prefix().str();
			string s2= m.suffix().str();
			int symbolMinus;
			int i = 0;
			if (s[0] == '-') 
			{
				symbolMinus = -1; i++;
			}
			else symbolMinus = 1;
			int ans = 0;
			while (i < s.length()-1){
				int k = 0;
				if (s[i]>='0'&&s[i] <= '9') k = s[i] - '0';
				else if (s[i] >= 'a'&&s[i]<='f') k = s[i] - 'a'+10;
				else if (s[i] >= 'A'&&s[i] <= 'F') k = s[i] - 'A'+10;
				else throw("error hex integer");
				ans= ans * 16 + k;
				i++;
			}
			ans = symbolMinus*ans;
			stringstream stemp;
			stemp << ans;
			string s3 ="";
			stemp >> s3;
			rets = rets + s1 + s3;
			ss = s2;
		}
		if (rets != "") *iter = rets+ss;
	}

	//���ʽ�����趨�Ǳ��ʽ�м�û�пո�֮��ġ��������ַ���ɵı��ʽ
	start = clock();
	string matchExpr = "(.*?)([ \\t,]+)([0-9\\+\\*\\(\\)\\^\\|%><&/~-]+)(.*)";
	for (vector<string>::iterator iter = program.begin(); iter != program.end(); ++iter) {
		smatch m;
		string temp = "";
		while (regex_match(*iter, m, regex(matchExpr))) {
			stringstream s;
			string t = m.format("$3");
			int length = t.length() - 1;
			string lost = "";
			if (t[length] == '(') {
				t = t.substr(0, length);
				lost = "(";
			}
			s << Expression(t).answer();
			temp = temp + m.format("$1") + m.format("$2") + s.str() + lost;
			*iter = m.format("$4");
		}
		*iter = temp + *iter;
	}
	stop = clock();
	duration = ((double)(stop - start)) / CLK_TCK;
	cout << "���ʽ����\t\t\t" << duration << endl;

	//��ʽָ���������ű��Լ����������ƴ���ɾ��.data��������

	start = clock();
	vector<StrInt> dataLabelTable;
	vector<string> dataTable;
	for (vector<string>::iterator iter = program.begin(); iter != program.end();)
	{
		if (((*iter).find(":") != string::npos) &&((*iter).find(".")!=string::npos) &&((*iter).find(".") > (*iter).find(":"))){
			bool formend(0);
			string s,temp,datalabel;
			datalabel = (*iter).substr(0, (*iter).find(":"));
			//cout << "label: " << datalabel<<endl;
			string formtext("");
			while (!formend&&(*iter).length()>6){
				if ((*iter).find(".formend") != string::npos) {
					formend = 1;
					if (iter != program.end()) iter = program.erase(iter); else { program.erase(iter); iter = program.end(); }
					break;
				}
				s = (*iter).substr((*iter).find("."));
				//formtype = s.substr(0, 6);
				if (s.substr(0, 7) == ".1byte "){
						s = s.substr(7);
						while (s.find(",") != string::npos){
						temp = s.substr(0, s.find(","));
						int i = atoi(temp.c_str());
						bitset<16> j = i & 0xffff;
						formtext += j.to_string();
						s = s.substr(s.find(",")+1);
					}
					int i = atoi(s.c_str());
					bitset<16> j = i & 0xffff;
					formtext += j.to_string();
				}else
				if (s.substr(0, 8) == ".asciiz "){
					temp = s.substr(8);
					while (temp.find(",") != string::npos){
						temp = temp.substr(0, temp.find(","));
						temp = temp.substr(temp.find("'")+1);
						temp = temp.substr(0, temp.find("'"));
						for (unsigned i = 0; i < temp.length(); i++){
							int asc = temp[i];
							bitset<16> j = asc & 0xff;
							formtext += j.to_string();
						}
						temp = temp.substr(s.find(",") + 1);
					}
					if (temp.find("'") != string::npos)	temp = temp.substr(temp.find("'") + 1); else {
						iter = program.erase(iter); continue;
					}
					if (temp.find("'") != string::npos) temp = temp.substr(0, temp.find("'")); else {
						iter = program.erase(iter); continue;
					}
					for (unsigned i = 0; i < temp.length(); i++){
							int asc = temp[i];
							bitset<16> j = asc & 0xff;
							formtext += j.to_string();
						}
				}else
				if (s.substr(0, 7) == ".2byte "){
					s = s.substr(7);
					while (s.find(",") != string::npos){
						temp = s.substr(0, s.find(","));
						int i = atoi(temp.c_str());
						bitset<32> j = i & 0xffffffff;
						formtext += j.to_string();
						s = s.substr(s.find(",") + 1);
					}
					int i = atoi(s.c_str());
					bitset<32> j = i & 0xffffffff;
					formtext += j.to_string();
				}
				iter = program.erase(iter);
			}
			dataLabelTable.push_back(StrInt(datalabel,formtext.length()/16));
			//cout << formtext.length() / 16 << endl;
			dataTable.push_back(formtext);
		}
		else ++iter;
	}
	
	int dataSize = 2;//������ͷ�ϵ�Jָ��
	//labelTable���������б�ŵ�λ�ã��ֽ�(16λ)Ϊ��λ
	vector<StrInt> labelTable;
	for (size_t i = 0; i < dataLabelTable.size(); i++) {
		labelTable.push_back(StrInt(dataLabelTable[i].symbol, dataSize));
		dataSize = dataSize + dataLabelTable[i].location;
	}
	stop = clock();
	duration = ((double)(stop - start)) / CLK_TCK;
	cout << "��ʽָ���\t\t\t" << duration << endl;



	//αָ���滻
	start = clock();
	string startAddr = "";
	bool end = true;
	for (vector<string>::iterator iter = program.begin(); iter != program.end(); ++iter) {
		smatch m;
		if (end && regex_match(*iter, m, regex("[ \\t]+\\.end[ \\t]+((_[a-zA-Z0-9_]+)|([a-zA-Z][a-zA-Z0-9_]*))[ \\t]+"))) {
			startAddr = m.format("$1");
			iter = program.erase(iter) - 1;
			end = false;
			continue;
		}
		PseudoCode pseudoCode;
		vector<string> temp = pseudoCode.transfer(*iter);
		iter = program.erase(iter);
		iter = program.insert(iter, temp.begin(), temp.end()) - (int)(temp.size() > 1 ? 1 : 0);
	}
	if (startAddr == "") {
		throw(string("No '.end LABEL' found."));
	}
	stop = clock();
	duration = ((double)(stop - start)) / CLK_TCK;
	cout << "αָ���滻��\t\t\t" << duration << endl;

	/*for (vector<string>::iterator iter = program.begin(); iter != program.end(); ++iter) {
		cout << *iter << endl;
	}*/
	
	
	
	//��Ŵ���
	start = clock();
	string labelDefine = "[ \\t]+((_[a-zA-Z0-9_]+)|([a-zA-Z][a-zA-Z0-9_]*))[ \\t]*:[ \\t]+";
	int line = 0;
	for (vector<string>::iterator iter = program.begin(); iter != program.end(); ++iter) {
		if ((*iter).find(".data") != string::npos || (*iter).find(".text") != string::npos)
			continue;
		smatch m;

		if (regex_match(*iter, m, regex(labelDefine))) {
			string label = m.format("$1");
			for (vector<StrInt>::iterator i = labelTable.begin(); i != labelTable.end(); i++) {
				if (*i == label)
					throw("Label \'" + (*i).symbol + "\' duplication.");
			}
			labelTable.push_back(StrInt(label, line*2 + dataSize));
			iter = program.erase(iter) - 1;
		}
		else {
			line++;
		}
	}

	//for (vector<string>::iterator iter = program.begin(); iter != program.end(); iter++)
	//	cout << *iter << endl;

	/*for (size_t i = 0; i < labelTable.size(); i++)	{
		cout << labelTable[i].symbol << "----" << labelTable[i].location << endl;
	}
	cout << "####" << startAddr << endl;*/
	Label labelManager(labelTable);

	program[0] = " j " + startAddr+" ";

	program[0] = labelManager.replace(program[0],dataSize);

	for (size_t i = 2, line = dataSize; i < program.size(); ++i, line = line + 2) {
		program[i] = labelManager.replace(program[i], line);
	}
	stop = clock();
	duration = ((double)(stop - start)) / CLK_TCK;
	cout << "��Ŵ���\t\t\t" << duration << endl;

	ofstream out("output.txt", ios::out);

	/*for (size_t i = 0; i < program.size(); i++)	{
		cout << program[i] << endl;
	}*/
	//cout << "###########################" << endl;
	InsCode inscode;
	//cout << program[0];
	inscode.transfer(program[0]);
	cout << endl;
	
	/*for (vector<string>::iterator iter = dataTable.begin(); iter != dataTable.end(); iter++){
		cout << *iter << endl;
	}*/
	string ops("");
	for (vector<string>::iterator iter = dataTable.begin(); iter != dataTable.end(); iter++){
		ops = ops + *iter;
		while (ops.length() >= 32){
			cout << ops.substr(0, 32) << endl;
			ops = ops.substr(32);
		}
	}
	while (ops.length() > 0){
		ops = ops + '0';
		if (ops.length() == 32) {
			cout << ops << endl;
			ops = "";
		}
	}

	for (vector<string>::iterator iter=program.begin()+2;iter!=program.end();iter++)
	{
		//cout <<  *iter<<"  " ;
		//�����Ҫ���ָ��������ȥ����һ��ע��
		inscode.transfer(*iter);
		cout << endl;
	}
	cout << "total time lapse :\t\t" << ((double)(clock() - all)) / CLK_TCK << endl;
	cout << "instruction number :\t\t" << program.size() << endl;
	int x;
	cin >> x;
	return 0;
}
