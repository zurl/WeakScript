#include "Regular.h"
class Lex{
private:
	string spilt(string &str, int l, int r);
	string replace(const string &str, const string &key, const string &value);
	string getStr(string str, int num);
	int _stoi(string a);
	string _itos(int a);
	string mulstr(string a, int k);
	Reg reg;
	string Defination;
	int nowRuleNumber = 0;
	int ready = 0;
public:
	/*
	Grammer Defination:
	@ ->comment
	#DEF A B //def A->B
	#REP A B n // rep A->B *n
	#RULE
	A //def a is RULE
	#END

	*/
	bool ReadFromFile(string File);
	void outDFA(string fileName);
	void outDef(string fileName);
};