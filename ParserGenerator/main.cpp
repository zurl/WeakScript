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
const int MAX = 2000;
string headfile = "";
set<string> nodehash;
string nodeWords[5] = {"Unit", "Unary", "Binary","Ternary","Quad"};
void createNewNode(string name, int base) {
	string baseName = nodeWords[base];
	string tstr1 = "",tstr2="";
	int flag = 0;
	for (int i = 1; i <= base; i++) {
		if (flag == 0) {
			flag = 1;
		}
		else tstr1 += ',', tstr2 += ',';
		tstr1 += "shared_ptr<Node> ";
		tstr1 += char('a' + i - 1);
		tstr2 += char('a' + i - 1);
	}

	app(headfile, "class "+name+"Node : public " + baseName + "Node {",0);
	app(headfile, "public:",0);
	app(headfile, "    " + name + "Node(" + tstr1 + ");", 0);

	app(head, "    " + name + "Node::" + name + "Node(" + tstr1 + ")", 0);
	app(head, "	       :" + baseName + "Node(" + tstr2 + ") {}", 0);

	app(headfile, "    virtual void visit(int x) ;", 0);
	app(head, "void " + name + "Node::visit(int x) {",0);
	app(head, "    for (int i = 1; i <= x; i++)printf(\"    \");",0);
	app(head, "    cout << \"" + name + " Node\" << endl;",0);
	app(head, "    this->visitson(x + 1);",0);
	app(head, "}", 0);
	app(headfile, "    virtual Value eval() ;", 0);
	app(headfile, "};",0);
}
void createNewUnitNode(string name,string type) {
	app(headfile, "class " + name + "Node : public UnitNode {", 0);
	app(headfile, "public:", 0);
	app(headfile, "    string value;", 0);
	app(headfile, "    " + name + "Node(string _value);", 0);

	app(head, "" + name + "Node::" + name + "Node(string _value)", 0);
	app(head, "	   :UnitNode() {value = _value;}", 0);


	app(headfile, "    virtual void visit(int x) ;", 0);
	app(headfile, "    virtual Value eval() ;", 0);
	app(headfile, "};", 0);

	app(head, "void " + name + "Node::visit(int x) {", 0);
	app(head, "    for (int i = 1; i <= x; i++)printf(\"    \");", 0);
	app(head, "    cout << \"" + name + " Node :\"  << value << endl;", 0);
	app(head, "    this->visitson(x + 1);", 0);
	app(head, "}", 0);

}
void outputEnd(vector<string> data,int deep) {
	if (data[0] == "#") {
		//pass
	}
	else if (data[0] == "*") {
		//root
		string nodename = data[1], nodetype = data[2];
		if (nodehash.find(nodename) == nodehash.end()) {
			//new;
			createNewUnitNode(nodename, nodetype);

			nodehash.emplace(nodename);
		}

		if (nodename != "#")
			app(body, "root = shared_ptr<Node> (new " + nodename + "Node(" + data[3] + "));", deep + 1);
	}
	else {
		//normal
		string nodename = data[0];
		int nodenum = data[1][0] - '0';
		if (nodehash.find(nodename) == nodehash.end()) {
			//new;
			createNewNode(nodename, nodenum);
			nodehash.emplace(nodename);
		}
		int flag = 0;
		string tstr = "";
		for (int i = 1; i <= nodenum; i++) {
			if (flag == 0)flag = 1;
			else tstr += ",";
			tstr += data[i + 1];
		}
		if (nodename != "#")
			app(body, "root = shared_ptr<Node> (new " + nodename + "Node(" + tstr + "));", deep + 1);
	}
}
string itos(int a) {
	std::ostringstream os;
	os << a;
	return os.str();
}
void dfs(int x, map<int, string> rhashtable,vector<vector<string>> datas,  edge *e[MAX], int accept[], int deep, int isCir) {
	int newVarFlag1 = 0,newVarFlag2 = 0;
	for (edge *k = e[x]; k != nullptr; k = k->prev) {
		if (k->v == -1) {
			//*
			app(body, "int flag = 1;", deep);
			app(body, "while (flag) {", deep);
			app(body, "flag = 0;", deep + 1);
			dfs(k->t, rhashtable, datas, e, accept, deep + 1, 1);
			app(body, "return 1;", deep + 1);
			app(body, "}", deep);
			continue;
		}
		string name = rhashtable[k->v];
		
		if (name[0] == '%') {
			//non - terminal;
			string keystr1 = "";
			if (newVarFlag1 == 0) {
				newVarFlag1 = 1;
				keystr1 = "auto ";
			}
			string keystr2 = "";
			if (newVarFlag2 == 0) {
				newVarFlag2 = 1;
				keystr2 = "auto ";
			}
			app(body, keystr2 + "SavedLexPos" + itos(deep) + " = lex->getNowPos(); ", deep);
			app(body, keystr2 + "SavedRoot" + itos(deep) + " = root;", deep);
			app(body, keystr1 + "ReadinToken" + itos(deep) + " = lex->readNextToken();", deep);
			app(body, "if (ReadinToken" + itos(deep) + ".id == LEX_" + getBackStr(name) + ") {", deep);

			dfs(k->t, rhashtable, datas, e, accept, deep + 1, isCir);

			if (accept[k->t] != -1) {
				//create new nod;
				auto t = datas[accept[k->t]];
				outputEnd(t, deep);
				if (!isCir)app(body, "return 1;", deep +1);
				else {
					app(body, "flag = 1;", deep + 1); app(body, "continue;", deep + 1);
				}
			}
			//app(body, "}", deep);
			//app(body, "else{", deep);
			//app(body, "lex->setNowPos(SavedLexPos" + itos(deep) + ");", deep + 1);
			//app(body, "}", deep);
			app(body, "}", deep);
			//app(body, "else{", deep);
			app(body, "lex->setNowPos(SavedLexPos" + itos(deep) + ");", deep);
			app(body, "root = SavedRoot" + itos(deep) + ";", deep);
			//app(body, "}", deep);
		}
		else {
			string keystr2 = "";
			if (newVarFlag2 == 0) {
				newVarFlag2 = 1;
				keystr2 = "auto ";
			}
			//terminal
			app(body, keystr2 + "SavedLexPos" + itos(deep) + " = lex->getNowPos(); ", deep);
			app(body, keystr2 + "SavedRoot" + itos(deep) + " = root;", deep);
			app(body, "if (parse" + getBackStr(name) + "()) {", deep);

			dfs(k->t, rhashtable, datas, e, accept, deep + 1, isCir);

			if (accept[k->t] != -1) {
				//create new nod;
				auto t = datas[accept[k->t]];
				outputEnd(t, deep);
				if (!isCir)app(body, "return 1;", deep +1);
				else {
					app(body, "flag = 1;", deep + 1);
					app(body, "continue;", deep +1);
				}
			}
			app(body, "}", deep);
			//app(body, "else{", deep);
			//app(body, "refresh();", deep + 1);
			//app(body, "root = SavedRoot" + itos(deep) + ";", deep + 1);
			//app(body, "}", deep);

			app(body, "refresh();", deep );
			app(body, "lex->setNowPos(SavedLexPos" + itos(deep) + ");", deep);
			app(body, "root = SavedRoot" + itos(deep) + ";", deep );
			//app(body, "}", deep);
		}
	}
}
bool dealrule() {
	//input
	int now = 0;
	int empty = 0;
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
		if (temp == ":EMPTY") {
			empty = 1; continue;
		}
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
	for (int i = 0; i <= 900; i++)e[i] = nullptr, accept[i] = -1;
	//create graph
	for (int i = 0; i < names.size(); i++) {
		int scannow = 0;
		for (int j = 0; j < names[i].size(); j++) {
			//add edge;
			
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
			if (j == names[i].size() - 1)accept[scannow] = i;
		}
	}
	//create graph end
	app(declr, "bool parse" + rulename + "();", 0);
	app(body, "bool parse" + rulename + "(){", 0);
	dfs( 0, rhashtable, datas, e, accept, 1, 0);
	if (empty)app(body, "return 1;", 1);
	else app(body, "return 0;", 1);
	app(body, "}", 0);
}
void work() {
	string tmpStr;
	while (cin >> tmpStr) {
		if (tmpStr == ":RULE")dealrule();
	}
}
int main() {
	nodehash.emplace("Value");

	char c;
	freopen("headerfile.code", "r", stdin);
	while ((c = getchar()) != EOF)headfile += c;
	fclose(stdin);
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
	fclose(stdout);

	app(headfile, "#endif // !PARSER_H", 0);
	freopen("result.header.code", "w", stdout);
	cout << headfile << endl;

	fclose(stdout);

	return 0;
}