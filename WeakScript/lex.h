#include "common.h"
class Lex;
class Reg{
public:
	Reg();
	~Reg();
	bool Reg::accept(string str, Lex &cbk);
	bool loadDFA(string filename);
	//bool accept(string str, Lex *cbk);
	void setOpition(bool _greedy, bool _shift);
private:

	static const int POINT_MAX = 5000;
	static const int preDefCount = 7;

	class edge{
	public:
		edge *prev;
		int t;
		char v;
		edge();
		edge(int _t, char _v, edge *_prev);
	};
	class Graph{
	private:
		int pointCount = 0;
	public:
		edge *e[POINT_MAX];
		int acc[POINT_MAX];
		Graph();
		~Graph();
		void addEdge(int f, int t, char v);
		int now();
		void set(int x);
	};
	class MatchRule{
		bool type = 0;
		bool reverse = 0;
		char l = 0;
		char r = 0;
	public:
		MatchRule(bool _reverse, char _l, char _r);
		MatchRule(bool _reverse, char _v);
		bool Match(const char &a);
	};
	bool acceptChar(const char &c, const char &ruleChar);
	void addPreDef();
	map<int, vector<MatchRule>> checkList;
	Graph DFA;
	bool greedy = 0;
	bool shift = 0;
	bool isReady = 0;
}; 
class Token{
public:
	int id;
	string name;
	int line;
	Token();
	Token(const int _id);
	Token(const int _id, const string _name, const int _line);
};
class Lex{
private:
	Reg reg;
	ifstream fin;
	int line = 0;
	list<Token> tokenList;
	list<Token>::iterator now = tokenList.begin();
	bool loadToken();
public:
	void reset();
	bool display;
	void acceptToken(int id, string &name);
	Token readNextToken();
	//Token readInNextToken();
	list<Token>::iterator getNowPos();
	void setNowPos(list<Token>::iterator a);
	Lex(string filename);
	Lex();
};

class SymbolTable{
private:
	map<string, int> Table;
	int now = 0;
public:
	int AcceptId(string id);
};