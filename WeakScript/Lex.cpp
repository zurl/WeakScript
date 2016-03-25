#include "Lex.h"
Reg::edge::edge() = default;
Reg::edge::edge(int _t, char _v, edge *_prev) :
t(_t), v(_v), prev(_prev){}

Reg::Graph::Graph(){
	memset(acc, 0, sizeof(acc));
}
Reg::Graph::~Graph(){
	for (int i = 0; i <= pointCount; i++){
		edge *j = e[i];
		if (j == nullptr)continue;
		while (j->prev != nullptr){
			edge *t = j->prev;
			delete j;
			j = t;
		}
	}
}
Token::Token() = default;
Token::Token(const int _id, const string _name, const int _line)
:id(_id), name(_name), line(_line){}
Token::Token(const int _id)
: id(_id){}
void Reg::Graph::addEdge(int f, int t, char v){
	e[f] = new edge(t, v, e[f]);
}
int Reg::Graph::now(){
	return pointCount;
}
void Reg::Graph::set(int x){
	this->pointCount = x;
}

Reg::MatchRule::MatchRule(bool _reverse, char _l, char _r) :
type(0), reverse(_reverse), l(_l), r(_r){}
Reg::MatchRule::MatchRule(bool _reverse, char _v) :
type(1), reverse(_reverse), l(_v){}
bool Reg::MatchRule::Match(const char &a){
	if (a == '\"' || a == '\'')return 0;
	if (type) return reverse ^ (a == l);
	else return reverse ^ (a >= l && a <= r);
}


Reg::Reg(){
	addPreDef();
}
Reg::~Reg(){}
bool Reg::loadDFA(string filename){
	ifstream fin(filename);
	int n, m,  y, z;
	fin >> n;
	DFA.set(n);
	for (int i = 0; i <= n; i++){
		fin >> m;
		for (int j = 1; j <= m; j++){
			fin >> y >> z;
			DFA.addEdge(i, y, z);
		}
	}
	for (int i = 0; i <= n; i++){
		fin >> DFA.acc[i];
	}
	return 1;
}
bool Reg::accept(string str, Lex &cbk){
	//if (!this->isReady)return 0;
	for (unsigned k = 0; k <= str.length() - 1; k++){
		int g = k, now = 0, onacc = -1; string tok = "";
		while (true){
			int t = -1;
			//accept char finding
			for (edge *i = DFA.e[now]; i != nullptr; i = i->prev){
				if (acceptChar(str[g], i->v)){
					t = i->t;
					tok += str[g];
					g++;
					break;
				}
			}
			//accept checking
			if (t != -1)
				now = t;
			else{
				if (onacc != -1){
					cbk.acceptToken(onacc, tok);
					tok = "";
					k = g - 1;
				}
				else{
					//Error Doing
 					cout << "Lex Error:please check you syntax" << endl;
					return 0;
				}
				break;
			}
			if (DFA.acc[now])
				onacc = DFA.acc[now];
		}
	}
	return 1;
}
void Reg::setOpition(bool _greedy, bool _shift){
	greedy = _greedy;
	shift = _shift;
}

void Reg::addPreDef(){
	this->checkList.emplace(-6, vector<MatchRule>{MatchRule(0, 'a', 'z'), MatchRule(0, 'A', 'Z'), MatchRule(0, '0', '9')});
	//Small Letter
	this->checkList.emplace(-2, vector<MatchRule>{MatchRule(0, 'a', 'z')});
	//Big Letter
	this->checkList.emplace(-3, vector<MatchRule>{MatchRule(0, 'A', 'Z')});
	//All Letter
	this->checkList.emplace(-4, vector<MatchRule>{MatchRule(0, 'a', 'z'), MatchRule(0, 'A', 'Z')});
	//Number
	this->checkList.emplace(-5, vector<MatchRule>{MatchRule(0, '0', '9')});
	//All Char
	this->checkList.emplace(-1, vector<MatchRule>{MatchRule(0, 1, 127)});
	//Space
	this->checkList.emplace(-7, vector<MatchRule>{MatchRule(0, ' ')});
	//n
	this->checkList.emplace(-8, vector<MatchRule>{MatchRule(0, '\n')});
	//t
	this->checkList.emplace(-9, vector<MatchRule>{MatchRule(0, '\t')});
}
bool Reg::acceptChar(const char &c, const char &ruleChar){
	if (ruleChar >= 0) return c == ruleChar;
	else{
		bool result = 0;
		auto &rules = checkList[ruleChar];
		for (auto &rule : rules){
			result |= rule.Match(c);
		}
		return result;
	}
}

void Lex::reset() {
	fflush(stdin);
	tokenList.clear();
	tokenList.emplace_front(-1);
	now = tokenList.begin();
}
bool Lex::loadToken() {
	string t; Token tk;
	if (display == 0) {
		if (std::getline(fin, t)) {
			t += '\n';
			line++;
			if (!reg.accept(t, *this))return 0;
			return 1;
		}
		else {
			return 0;
		}

	}
	else if (display == 10) {
		if (std::getline(sin, t)) {
			t += '\n';
			line++;
			if (!reg.accept(t, *this))return 0;
			return 1;
		}
		else {
			return 0;
		}
	}
	else {
		if (std::getline(cin, t)) {
			t += '\n';
			line++;
			if (!reg.accept(t, *this))return 0;
			return 1;
		}
		else {
			return 0;
		}
	}
	
	return 1;
}
string retstr(string a) {
	string ret ="";
	for (int i = 1; i <= a.length() - 2; i++)ret += a[i];
	return ret;
}
void Lex::acceptToken(int id, string &name){
	if (id == LEX_SPACE || id == LEX_TAB || id == LEX_NL || id== LEX_COMMENTA || id == LEX_COMMENTB)return;
	if (id == LEX_ID  ||id ==LEX_INT || id == LEX_REAL)
		tokenList.emplace_back(id, name, line);
	else if(id == LEX_STRING)tokenList.emplace_back(id, retstr(name), line);
	else tokenList.emplace_back(id, "", line);
}
Token Lex::readNextToken(){
	now++;
	while (now == tokenList.end()){
		now--;
		if (!loadToken()){
			return Token(-1);
		}
		now++; 
	}
	auto ret = *now;
	return ret;
}
list<Token>::iterator Lex::getNowPos(){
	return now;
}
void Lex::setNowPos(list<Token>::iterator a){
	now = a;
}
Lex::Lex(string filename)
	:fin(filename), display(0)
{
	reg.loadDFA("WeakScript.dfa");
	tokenList.emplace_front(-1);
	now = tokenList.begin();
}
Lex::Lex(int a,string x)
	: display(10),sin(x)
{
	reg.loadDFA("WeakScript.dfa");
	tokenList.emplace_front(-1);
	now = tokenList.begin();
}
Lex::Lex()
: display(1)
{
	reg.loadDFA("WeakScript.dfa");
	tokenList.emplace_front(-1);
	now = tokenList.begin();
}
int SymbolTable::AcceptId(string id){
	auto x = Table.find(id);
	if (x == Table.end()){
		++now;
		Table.emplace(id, now);
		return now;
	}
	else{
		return x->second;
	}
}	