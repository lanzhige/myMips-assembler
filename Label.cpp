#include "Label.h"
#include<iostream>

string Label::replace(string s, int currentByte) {

	if (regex_match(s, regex(matchInsRsRtLabel))) {
		return replaceCommaLabelSpace(s, currentByte);
	}
	if (regex_match(s, regex(matchInsRsLabel))) {
		return replaceCommaLabelSpace(s, currentByte);
	}
	if (regex_match(s, regex(matchInsRtLabelRs))) {
		return replaceCommaLabelBracket(s);
	}
	if (regex_match(s, regex(matchInsLabel))) {
		return replaceSpaceLabelSpace(s);
	}
	return s;
}

int Label::find(string s) {
	for (vector<StrInt>::iterator iter = labelTable.begin(); iter != labelTable.end(); iter++) {
		if (*iter == s) {
			return (*iter).location;
		}
	}
	throw(string("Label \'" + s + "\' NOT found."));
}

string Label::replaceCommaLabelSpace(string s, int currentByte) {
	smatch m;
	regex_match(s, m, regex("(.*?" + comma + ")" + label + "(" + space + ")"));
	string matchedLabel = m.format("$2");
	stringstream stream;
	stream << ((find(matchedLabel) - currentByte - 2) / 2);
	return m.format("$1") + stream.str() + m.format("$3");
}

string Label::replaceCommaLabelBracket(string s) {
	smatch m;
	regex_match(s, m, regex("(.*?" + comma + ")" + label + "(" + sep + "\\(.*)"));
	string matchedLabel = m.format("$2");
	stringstream stream;
	stream << find(matchedLabel);
	return m.format("$1") + stream.str() + m.format("$3");
}

string Label::replaceSpaceLabelSpace(string s) {
	smatch m;
	regex_match(s, m, regex("(.*?" + space + ")" + label + "(" + space + ")"));
	string matchedLabel = m.format("$2");
	stringstream stream;
	stream << find(matchedLabel);
	return m.format("$1") + stream.str() + m.format("$3");
}