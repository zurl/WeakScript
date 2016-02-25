#include<memory>
#include<vector>
#include<unordered_set>
#include<queue>
#include<set>
#include<bitset>
#include<tuple>
#include<cstdlib>
#include<map>
#include<fstream>
#include<iostream>
#include<sstream>
using namespace std;

class Reg{
public:
	enum class ope{
		and, or, left, rep, able, prep
	};
	static const int POINT_MAX = 8000;
	static const char preDef[10];
	static const int preDefCount = 9;
	class edge{
	public:
		edge *prev;
		int t;
		char v;
		edge();
		edge(int _t, char _v, edge *_prev);
	};
	class GraphPart{
	public:
		int begin, end;
		GraphPart();
		GraphPart(int _begin, int _end);
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
		int get();
		int now();
		void adjust(int a);
		string out();
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
	Reg();
	~Reg();
	bool addRule(string x, int code);
	bool ready();
	bool accept(string str, bool(*callback)(int code));
	void setOpition(bool _greedy, bool _shift);
	string outDFA();
private:
	void addPreDef();
	bool toENFA(string &reg);
	bool toNFA();
	bool toDFA();
	bool acceptChar(const char &c, const char &ruleChar);
	void dfsAddEdge(int &rootPoint, int currentPoint);
	void dfsDeleteEpsilonEdge(edge *currentEdge);
	void popStack(vector<GraphPart> &s, vector<ope> &o);
	bool check(string &reg);
	GraphPart addGraph(char x);
	GraphPart mergeGraph(bool plan, GraphPart &a, GraphPart &b);
	GraphPart repeatGraph(bool plan, GraphPart &a);
	map<int, vector<MatchRule>> checkList;
	Graph NFAs, DFA;
	GraphPart NFA;
	bool greedy = 0;
	bool shift = 0;
	bool hasRule = 0;
	bool isReady = 0;
	bitset<POINT_MAX> able;
	int fx[POINT_MAX], gx[POINT_MAX];
};
/*
The Zurl Regular Engi	ne Defination

PreDefine Command

PART DEFINE


fundaments

a //match a which is not specials
\\ // match \
a|b //a or b
ab //a and b
a* //a = 0-oo
a+ //a = 1-oo
a? //a = 0-1

\p space

\b A-Z
\s a-z
\l A-Za-z
\d 0-9
\w a-zA-Z0-9
\a all character

extension grammer
wait for do

predo command

waiting to add

[abcde-f] //match all
[^abcde] //match none

@(aaaaa) = (aaaaa)?(aaaaa)?(aaaaa)?(aaaaa)?(aaaaa)?




Lex analyser Defination v1.0

= is command order
$ is comments line

key val
=lexer
name fucking
version 1
=def
_D (\d+(.\d+)?)
=rule
$hello every one fucking your mother
the code begin
dight _D
id \l\w*


*/
