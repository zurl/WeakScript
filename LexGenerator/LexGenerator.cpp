#include "LexGenerator.h"
string Lex::spilt(string &str, int l, int r){
	string ret = "";
	for (int i = l; i <= r; i++)
		ret += str[i];
	return ret;
}
string Lex::replace(const string &str, const string &key, const string &value){
	string ret = "";
	if (str.length() < key.length()){
		ret = str;
		return ret;
	}
	for (unsigned i = 0; i <= str.length() - key.length(); i++){
		bool result = 1;
		for (unsigned j = 0; j <= key.length() - 1; j++){
			if (str[i + j] != key[j]){
				result = 0;
				break;
			}
		}
		if (result){
			ret += value;
			i += key.length() - 1;
		}
		else{
			ret += str[i];
		}
	}
	for (unsigned i = str.length() - key.length() + 1; i <= str.length() - 1; i++)
		ret += str[i];
	return ret;
}
string Lex::getStr(string str, int num){
	int k = 0;
	str = str + " ";
	for (unsigned i = 1; i <= num; i++){
		int last = k;
		while (k < str.length() && str[k] != ' ')k++;
		if (k == str.length())return "";
		else { if (i == num)return spilt(str, last, k - 1); k++; }
	}
	return "";
}
int Lex::_stoi(string a){
	int ret = 0;
	for (unsigned i = 0; i <= a.length() - 1; i++){
		ret = ret * 10 + char(a[i] - '0');
	}
	return ret;
}
string Lex::_itos(int a){
	ostringstream of;
	of << a;
	return of.str();
}
string Lex::mulstr(string a, int k){
	string ret = "";
	for (int i = 1; i <= k; i++)
		ret += a;
	return ret;
}

bool Lex::ReadFromFile(string File){
	//reg.setOpition(1, 1);
	ifstream fin(File);
	string c;
	map<string, string> m;
	bool onRule = 0;
	Defination = "//// Weak Script Lexical Analysis Engine\n";
	Defination += "//// Lexical Defination File\n";
	Defination += "//// For c99 / c++11\n";
	while (getline(fin, c)){
		if (c==""||c[0] == '#' || c[0] == '\n')continue;
		else if (c[0] == '@'){
			if (c[1] == 'D'&&c[2] == 'E'&&c[3] == 'F'){
				m.emplace(getStr(c, 2), getStr(c, 3));
			}
			else if (c[1] == 'R'&&c[2] == 'E'&&c[3] == 'P'){
				m.emplace(getStr(c, 2), mulstr(getStr(c, 3), _stoi(getStr(c, 4))));
			}
			else if (c[1] == 'E'&&c[2] == 'N'&&c[3] == 'D'){
				if (!onRule)return 0;
				else {
					reg.ready();
					ready = 1;
					return 1;
				}
			}
			else if (c[1] == 'R'&&c[2] == 'U'&&c[3] == 'L'&&c[4] == 'E'){
				if (!onRule)onRule = 1;
				else return 0;
			}
			else return 0;
		}
		else{
			string name = getStr(c, 1);
			string rule = getStr(c, 2);
			if (!onRule)return 0;
			for (auto &x : m){
				rule = replace(rule, x.first, x.second);
			}
			reg.addRule(rule, ++nowRuleNumber);
			Defination += "const int LEX_" + name + " = " + _itos(nowRuleNumber) + " ;\n";
		}
	}
	return 0;
}
void Lex::outDFA(string fileName){
	ofstream fout(fileName);
	fout << reg.outDFA() << endl;
}
void Lex::outDef(string fileName){
	ofstream fout(fileName);
	fout << Defination << endl;
}