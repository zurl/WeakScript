#include "Regular.h"

const char Reg::preDef[10] = "asbldwpnt";
Reg::edge::edge() = default;
Reg::edge::edge(int _t, char _v, edge *_prev) :
t(_t), v(_v), prev(_prev){}
Reg::GraphPart::GraphPart() = default;
Reg::GraphPart::GraphPart(int _begin, int _end)
:begin(_begin), end(_end){}
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
void Reg::Graph::addEdge(int f, int t, char v){
	e[f] = new edge(t, v, e[f]);
}
int Reg::Graph::get(){
	pointCount++;
	return pointCount;
}
int Reg::Graph::now(){
	return pointCount;
}
void Reg::Graph::adjust(int a){
	pointCount = a;
}
string Reg::Graph::out(){
	ostringstream os;
	//count
	os << pointCount << " ";
	//edge
	for (int i = 0; i <= pointCount; i++){
		int cnt = 0;
		for (edge *j = e[i]; j != nullptr; j = j->prev)cnt++;
		os << cnt << " ";
		for (edge *j = e[i]; j != nullptr; j = j->prev){
			os << j->t << " ";
			os << int(j->v) << " ";
		}
	}
	//accept
	for (int i = 0; i <= pointCount; i++){
		os << acc[i] << " ";
	}
	return os.str();
}
Reg::MatchRule::MatchRule(bool _reverse, char _l, char _r) :
type(0), reverse(_reverse), l(_l), r(_r){}
Reg::MatchRule::MatchRule(bool _reverse, char _v) :
type(1), reverse(_reverse), l(_v){}
bool Reg::MatchRule::Match(const char &a){
	if (type) return reverse ^ (a == l);
	else return reverse ^ (a >= l && a <= r);
}
Reg::Reg(){
	addPreDef();
}
Reg::~Reg(){}
bool Reg::addRule(string x, int code){
	if (this->isReady)return 0;
	if (this->check(x)){
		this->toENFA(x);
		NFAs.addEdge(0, NFA.begin, 0);
		NFAs.acc[NFA.end] = code;
		this->hasRule = 1;
		return 1;
	}
	else return 0;
}
bool Reg::ready(){
	if (this->hasRule){
		this->toNFA();
		this->toDFA();
		this->isReady = 1;
		return 1;
	}
	return 0;
}
bool Reg::accept(string str, bool(*callback)(int code)){
	if (!this->isReady)return 0;
	for (unsigned k = 0; k <= str.length() - 1; k++){
		int g = k, now = 0, onacc = -1;
		while (true){
			int t = -1;
			//accept char finding
			for (edge *i = DFA.e[now]; i != nullptr; i = i->prev){
				if (acceptChar(str[g], i->v)){
					t = i->t;
					g++;
					break;
				}
			}
			//accept checking
			if (t != -1) now = t;
			else{
				if (greedy && onacc != -1){
					//greedy accept
					callback(onacc);
					if (shift){
						k = g - 1;
					}
				}
				break;
			}
			if (greedy) { if (DFA.acc[now])onacc = DFA.acc[now]; }
			else
			if (DFA.acc[now]){
				//ungreedy accept
				callback(DFA.acc[now]);
				if (shift){
					k = g - 1;
					break;
				}
			}
		}
	}
	return 0;
}
void Reg::setOpition(bool _greedy, bool _shift){
	greedy = _greedy;
	shift = _shift;
}
string Reg::outDFA(){
	return DFA.out();
}
void Reg::addPreDef(){
	//All Char
	this->checkList.emplace(-1, vector<MatchRule>{MatchRule(0, 'a', 'z'), MatchRule(0, 'A', 'Z'), MatchRule(0, '0', '9')});
	//Small Letter
	this->checkList.emplace(-2, vector<MatchRule>{MatchRule(0, 'a', 'z')});
	//Big Letter
	this->checkList.emplace(-3, vector<MatchRule>{MatchRule(0, 'A', 'Z')});
	//All Letter
	this->checkList.emplace(-4, vector<MatchRule>{MatchRule(0, 'a', 'z'), MatchRule(0, 'A', 'Z')});
	//Number
	this->checkList.emplace(-5, vector<MatchRule>{MatchRule(0, '0', '9')});
	//All Char
	this->checkList.emplace(-6, vector<MatchRule>{MatchRule(0, 1, 127)});
	//Space
	this->checkList.emplace(-7, vector<MatchRule>{MatchRule(0, ' ')});
	//n
	this->checkList.emplace(-8, vector<MatchRule>{MatchRule(0, '\n')});
	//t
	this->checkList.emplace(-9, vector<MatchRule>{MatchRule(0, '\t')});

}
bool Reg::toENFA(string &reg){
	vector<GraphPart> s; s.reserve(POINT_MAX);
	vector<ope> o; o.reserve(POINT_MAX);

	for (unsigned i = 0; i <= reg.length() - 1; i++){
		switch (reg[i]){
		case '[':
			//waiting for modifing
		case '|':
			while (!o.empty() && *(o.end() - 1) != ope::left)popStack(s, o);
			o.emplace_back(ope::or);
			break;
		case '(':
			o.emplace_back(ope::left);
			break;
		case ')':
			while (!o.empty() && *(o.end() - 1) != ope::left)popStack(s, o);
			o.pop_back();
			if (i != reg.length() - 1 && reg[i + 1] != ')' && reg[i + 1] != '+'&&reg[i + 1] != '?'&&reg[i + 1] != '*'&&reg[i + 1] != '|'){
				o.emplace_back(ope::and);
			}
			break;
		case '?':
			o.emplace_back(ope::able);
			popStack(s, o);
			if (i != reg.length() - 1 && reg[i + 1] != ')' && reg[i + 1] != '+'&&reg[i + 1] != '?'&&reg[i + 1] != '*'&&reg[i + 1] != '|'){
				o.emplace_back(ope::and);
			}
			break;
		case '*':
			o.emplace_back(ope::rep);
			popStack(s, o);
			if (i != reg.length() - 1 && reg[i + 1] != ')' && reg[i + 1] != '+'&&reg[i + 1] != '?'&&reg[i + 1] != '*'&&reg[i + 1] != '|'){
				o.emplace_back(ope::and);
			}
			break;
		case '+':
			o.emplace_back(ope::prep);
			popStack(s, o);
			if (i != reg.length() - 1 && reg[i + 1] != ')' && reg[i + 1] != '+'&&reg[i + 1] != '?'&&reg[i + 1] != '*'&&reg[i + 1] != '|'){
				o.emplace_back(ope::and);
			}
			break;
		case '\\':
			//process the preDefine chars;
			i++;
			for (int j = 0; j < preDefCount; j++){
				if (preDef[j] == reg[i]){
					reg[i] = -j - 1;
					break;
				}
			}
		default:
			s.emplace_back(addGraph(reg[i]));
			if (i != reg.length() - 1 && reg[i + 1] != ')' && reg[i + 1] != '+'&&reg[i + 1] != '?'&&reg[i + 1] != '*'&&reg[i + 1] != '|'){
				o.emplace_back(ope::and);
			}
			break;
		}

	}
	while (!o.empty())popStack(s, o);
	this->NFA = *(s.end() - 1);
	return 1;
}
bool Reg::toNFA(){
	
	able[0] = true;
	//find the points set that can arrive
	for (int k = 0; k <= NFAs.now(); k++){
		for (edge *i = NFAs.e[k]; i != nullptr; i = i->prev){
			if (i->v != 0)able[i->t] = 1;
		}
	}
	//add edge from rootPoint to the point that can reach through epsilon
	for (int k = 0; k <= NFAs.now(); k++){
		if (able[k]){
			dfsAddEdge(k, k);
		}
	}
	//recursive delete edge that are epsilon
	for (int k = 0; k <= NFAs.now(); k++){
		if (!able[k]){
			dfsDeleteEpsilonEdge(NFAs.e[k]);
			NFAs.e[k] = nullptr;
		}
	}
	//delete points that cant reach 
	for (int k = 0; k <= NFAs.now(); k++){
		for (edge *i = NFAs.e[k]; i != nullptr; i = i->prev){
			while (i->prev != nullptr && i->prev->v == 0){
				edge *t = i->prev;
				i->prev = i->prev->prev;
				delete t;
			}
		}
		while (NFAs.e[k] != nullptr && NFAs.e[k]->v == 0){
			edge *t = NFAs.e[k];
			NFAs.e[k] = NFAs.e[k]->prev;
			delete t;
		}
	}
	//compress the points set
	//there codes are need to be optimist
	int  now = -1;
	memset(fx, 0, sizeof(fx));
	memset(gx, 0, sizeof(gx));
	for (int i = 0; i <= NFAs.now(); i++){
		if (able[i] == true)
			fx[++now] = i;
	}
	for (int k = 0; k <= now; k++){
		NFAs.e[k] = NFAs.e[fx[k]];
	}
	for (int k = 0; k <= now; k++){
		NFAs.acc[k] = NFAs.acc[fx[k]];
	}
	for (int k = now; k >= 0; k--){
		gx[fx[k]] = k;
	}

	NFAs.adjust(now);
	for (int k = 0; k <= NFAs.now(); k++){
		for (edge *i = NFAs.e[k]; i != nullptr; i = i->prev){
			i->t = gx[i->t];
		}
	}
	NFA.begin = gx[0];
	return 0;
}
bool Reg::toDFA(){
	queue<pair<set<int>, int>> q;
	map<set<int>, int> m;
	m.emplace(set<int>{NFA.begin}, 0);
	q.emplace(set<int>{NFA.begin}, 0);
	while (!q.empty()){
		set<char> charSet;
		auto t = q.front();
		q.pop();
		//get the convertion set
		for (auto &i : t.first)
		for (edge *j = NFAs.e[i]; j != nullptr; j = j->prev)
			charSet.emplace(j->v);
		//get target set
		for (auto &x : charSet){
			set<int> tempSet;
			int acc = 0;
			for (auto &i : t.first)
			for (edge *j = NFAs.e[i]; j != nullptr; j = j->prev)
			if (x == j->v)tempSet.emplace(j->t);
			//checking duplicate		
			auto temp = m.find(tempSet);
			if (temp == m.end()){
				int tp = DFA.get();
				q.emplace(tempSet, tp);
				m.emplace(tempSet, tp);
				DFA.addEdge(t.second, tp, x);
			}
			else{
				DFA.addEdge(t.second, temp->second, x);
			}

		}
	}
	//accept adjustment
	memset(DFA.acc, 0, sizeof(DFA.acc));
	for (auto &x : m){
		int acc = 0;
		for (auto &y : x.first){
			if (NFAs.acc[y]){
				if (acc<NFAs.acc[y])acc=NFAs.acc[y];
			}
		}
		DFA.acc[x.second] = acc;
	}
	return 1;
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
void Reg::dfsAddEdge(int &rootPoint, int currentPoint){
	//transfer accept value
	if (NFAs.acc[currentPoint])NFAs.acc[rootPoint] = NFAs.acc[currentPoint];
	//add edge from rootPoint to the point that can reach through epsilon
	for (edge *i = NFAs.e[currentPoint]; i != nullptr; i = i->prev){
		if (i->v != 0) NFAs.addEdge(rootPoint, i->t, i->v);
		else dfsAddEdge(rootPoint, i->t);
	}
}
void Reg::dfsDeleteEpsilonEdge(edge *currentEdge){
	//recursive delete edge that are epsilon
	//not exist edge
	if (currentEdge == nullptr)return;
	//front edge
	if (currentEdge->prev != nullptr) dfsDeleteEpsilonEdge(currentEdge->prev);
	delete currentEdge;
}
void Reg::popStack(vector<GraphPart> &s, vector<ope> &o){
	//pop the first priority operator
	switch (*(o.end() - 1)){
	case ope::and:
		*(s.end() - 2) = mergeGraph(0, *(s.end() - 2), *(s.end() - 1));
		s.pop_back();
		break;
	case ope::or:
		*(s.end() - 2) = mergeGraph(1, *(s.end() - 2), *(s.end() - 1));
		s.pop_back();
		break;
	case ope::rep:
		*(s.end() - 1) = repeatGraph(0, *(s.end() - 1));
		break;
	case ope::prep:
		*(s.end() - 1) = repeatGraph(1, *(s.end() - 1));
		break;
	case ope::able:
		NFAs.addEdge((s.end() - 1)->begin, (s.end() - 1)->end, 0);
		break;
	}
	o.pop_back();
};
bool Reg::check(string &reg){
	//binary operator rule check
	for (unsigned i = 0; i <= reg.length() - 1; i++){
		if (reg[i] == '\\'&&i == reg.length() - 1)return 0;
		if (reg[i] == '\\')i += 2;
		if (i == reg.length() - 1)break;
		if (reg[i] == '|')
		if (reg[i + 1] == '|' || reg[i + 1] == '*'
			|| reg[i + 1] == '?' || reg[i + 1] == ')')return 0;
		if (reg[i] == '*' || reg[i] == '?')
		if (i == 0)return 0;
		if (reg[i] == '(')
		if (reg[i + 1] == ')' || reg[i + 1] == '|' || reg[i + 1] == '*' || reg[i + 1] == '?')return 0;
	}
	//backet match check
	int now = 0;
	for (unsigned i = 0; i <= reg.length() - 1; i++){
		if ((!i || reg[i - 1] != '\\') && reg[i] == '(')now++;
		if ((!i || reg[i - 1] != '\\') && reg[i] == ')')now--;
		if (now < 0)return 0;
	}
	if (now != 0)return 0;
	return 1;
}
Reg::GraphPart Reg::addGraph(char x){
	int begin = NFAs.get();
	int end = NFAs.get();
	NFAs.addEdge(begin, end, x);
	return GraphPart(begin, end);
}
Reg::GraphPart Reg::mergeGraph(bool plan, GraphPart &a, GraphPart &b){
	if (plan){
		//or
		int begin = NFAs.get();
		int end = NFAs.get();
		NFAs.addEdge(begin, a.begin, 0);
		NFAs.addEdge(begin, b.begin, 0);
		NFAs.addEdge(a.end, end, 0);
		NFAs.addEdge(b.end, end, 0);
		return GraphPart(begin, end);
	}
	else{
		//and
		NFAs.addEdge(a.end, b.begin, 0);
		return GraphPart(a.begin, b.end);
	}
}
Reg::GraphPart Reg::repeatGraph(bool plan, GraphPart &a){
	int begin = NFAs.get();
	int end = NFAs.get();
	//rep
	if (plan){
		//prep
		NFAs.addEdge(begin, a.begin, 0);
		NFAs.addEdge(a.end, end, 0);
		NFAs.addEdge(a.end, a.begin, 0);
		return GraphPart(begin, end);
	}
	else{
		//rep
		NFAs.addEdge(begin, a.begin, 0);
		NFAs.addEdge(a.end, end, 0);
		NFAs.addEdge(begin, end, 0);
		NFAs.addEdge(a.end, a.begin, 0);
		return GraphPart(begin, end);
	}

}
