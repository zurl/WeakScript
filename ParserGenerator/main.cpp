#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<map>
#include<set>
#include<vector>
#include<sstream>
using std::cin;
using std::cout;
using std::string;
using std::vector;
using std::map;
using std::set;
using std::endl;

struct edge {
	int t, v;
	edge *prev;
	edge() {}
	edge(int _t,int _v,edge *_prev)
		:t(_t),v(_v),prev(_prev){}
};
string head = "";
string declr = "";
string body = "";
string tail = ""; 
string getBackStr(string str) {
	string ret = "";
	for (int i = 1; i <= str.length() - 1; i++)
		ret += str[i];
	return ret;
}
void app(string &x, string y, int tabs) {
	for (int i = 1; i <= tabs; i++)x += "    ";
	x += y + "\n";
}
const int MAX = 1000;

set<string> nodehash;
string nodeWords[5] = {"Unit", "Unary", "Binary","Tr"};
void createNewNode(string name, int base) {
	string baseName = nodeWords[base];
	string tstr1 = "",tstr2="";
	int flag = 0;
	for (int i = 1; i <= base; i++) {
		if (flag == 0) {
			flag = 1;
		}
		else tstr1 += ',', tstr2 += ',';
		tstr1 += "Node *";
		tstr1 += char('a' + i - 1);
		tstr2 += char('a' + i - 1);
	}

	app(head, "class "+name+"Node : public " + baseName + "Node {",0);
	app(head, "public:",0);
	app(head, "    " + name + "Node(" + tstr2 + ")",0);
	app(head, "	       :" + baseName + "Node("+tstr1+") {}",0);
	app(head, "    virtual void visit(int x) {",0);
	app(head, "        for (int i = 1; i <= x; i++)printf("    ");",0);
	app(head, "        cout << \"" + name + " Node\" << endl;",0);
	app(head, "        this->visitson(x + 1);",0);
	app(head, "    }",0);
	app(head, "};",0);
}
string itos(int a) {
	std::ostringstream os;
	os << a;
	return os.str();
}
void dfs(int x, map<int, string> rhashtable,vector<vector<string>> datas,  edge *e[MAX], int accept[], int deep, int isCir) {
	for (edge *k = e[x]; k != nullptr; k = k->prev) {
		if (k->v == -1) {
			//*
			app(body, "int flag = 1;", deep);
			app(body, "while (flag) {", deep);
			app(body, "flag = 0;", deep + 1);
			dfs(k->t, rhashtable, datas, e, accept, deep + 1, 1);
			app(body, "}", deep);
			continue;
		}
		string name = rhashtable[k->v];
		if (name[0] == '%') {
			//non - terminal;

			app(body, "auto SavedLexPos" + itos(deep) + " = lex.getNowPos(); ", deep);
			app(body, "auto ReadinToken" + itos(deep) + " = lex.readNextToken();", deep);
			app(body, "if (ReadinToken" + itos(deep) + ".id == LEX_" + getBackStr(name) + ") {", deep);

			dfs(k->t, rhashtable, datas, e, accept, deep + 1, isCir);

			if (accept[k->v]) {
				//create new nod;
				auto t = datas[accept[k->v]];
				string nodename = t[0];
				int nodenum = t[1][0] - '0';
				if (nodehash.find(nodename) == nodehash.end()) {
					//new;
					createNewNode(nodename, nodenum);
				}
				int flag = 0;
				string tstr = "";
				for (int i = 1; i <= nodenum; i++) {
					if (flag == 0)flag = 1;
					else tstr += ",";
					tstr += t[i + 1];
				}
				app(body, "root = new "+ nodename+"Node("+tstr+");",deep+1);
			}
			app(body, "}", deep);
			app(body, "else{", deep);
			app(body, "lex.setNowPos(SavedLexPos" + itos(deep) + ");", deep + 1);
			app(body, "}", deep);
		}
		else {
			//terminal
			app(body, "auto savedRoot" + itos(deep) + " = root;", deep);
			app(body, "if (parse" + getBackStr(name) + "()) {", deep);

			dfs(k->t, rhashtable, datas, e, accept, deep + 1, isCir);

			if (accept[k->v]) {
				//create new nod;
				auto t = datas[k->v];
				string nodename = t[0];
				int nodenum = t[1][0] - '0';
				if (nodehash.find(nodename) == nodehash.end()) {
					//new;
					createNewNode(nodename, nodenum);
				}
				int flag = 0;
				string tstr = "";
				for (int i = 1; i <= nodenum; i++) {
					if (flag == 0)flag = 1;
					else tstr += ",";
					tstr += t[i + 1];
				}
				app(body, "root = new " + nodename + "Node(" + tstr + ");", deep + 1);
			}
			app(body, "}", deep);
			app(body, "else{", deep);
			app(body, "refresh();", deep + 1);
			app(body, "root = savedRoot" + itos(deep) + ";", deep + 1);
			app(body, "}", deep);
		}
	}
}
bool dealrule() {
	//input
	int now = 0;
	map<int, string> rhashtable;
	map<string, int> hashtable;
	vector<vector<int>> names;
	vector<vector<string>> datas;
	int accept[MAX];
	string rulename, temp, temp2, temp3;
	edge *e[MAX];
	cin >> rulename; rulename = getBackStr(rulename);
	while (cin >> temp) {
		if (temp == ":RULEEND")break;
		if (temp != "|") {
			cout << "error" << endl;
			//error
			return 0;
		}
		datas.emplace_back();
		names.emplace_back();
		while (cin >> temp2) {
			if (temp2 == "@") {
				while (cin >> temp3) {
					if (temp3 == "@")break;
					(datas.end() - 1)->emplace_back(temp3);
				}
				break;
			}
			if (temp2 == "*") {
				//for L-RECURSIVE
				(names.end() - 1)->emplace_back(-1);
			}
			else {
				auto t = hashtable.find(temp2);
				if (t == hashtable.end()) {
					//new
					hashtable.emplace(temp2,++now);
					rhashtable.emplace(now, temp2);
					(names.end()-1)->emplace_back(now);
				}
				else {
					//old
					(names.end() - 1)->emplace_back(t->second);
				}
			}
		}
	}
	//input end;
	//init
	int nowedge = 0;
	for (int i = 0; i <= 900; i++)e[i] = nullptr, accept[i] = 0;
	//create graph
	for (int i = 0; i < names.size(); i++) {
		int scannow = 0;
		for (int j = 0; j < names[i].size(); j++) {
			//add edge;
			if (j == names[i].size() - 1)accept[names[i][j]] = i;
			int flag = 0;
			for (edge * k = e[scannow]; k != nullptr; k = k->prev) {
				if (k->v == names[i][j]) {
					//found;
					scannow = k->t;
					flag = 1;
					break;
				}
			}
			if (flag == 0) {
				//add new edge
				cout << "new edge to" << nowedge + 1 << "from" << scannow << "value" << names[i][j] << endl;
				e[scannow] = new edge(++nowedge, names[i][j], e[scannow]);
				scannow = nowedge;
			}
		}
	}
	//create graph end
	app(declr, "bool parse" + rulename + "();", 0);
	app(body, "bool parse" + rulename + "(){", 0);
	dfs( 0, rhashtable, datas, e, accept, 1, 0);
	app(body, "}", 0);
}
void work() {
	string tmpStr;
	while (cin >> tmpStr) {
		if (tmpStr == ":RULE")dealrule();
	}
}
int main() {
	char c;
	freopen("header.code", "r", stdin);
	while ((c = getchar()) != EOF)head += c;
	fclose(stdin);
	freopen("tail.code", "r", stdin);
	while ((c = getchar()) != EOF)tail += c;
	fclose(stdin);
	//This is the bloddy fucking shit

	freopen("test.gma", "r", stdin);
	work();
	freopen("result.code", "w", stdout);
	cout << head << endl;
	cout << declr << endl;
	cout << body << endl;
	cout << tail << endl;
	return 0;
}