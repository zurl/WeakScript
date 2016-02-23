#include<iostream>
#include"WeakScriptLex.h"
#include<string>
#include "lex.h"
using namespace std;
class Node {
public:
	virtual void visit(int x) = 0;
	virtual void del() = 0;
};
class UnitNode : public Node {
public:
	UnitNode() {}
	void visitson(int x) {}
	virtual void del() {}
};
class UnaryNode : public Node {
	Node *son;
public:
	UnaryNode(Node *_s)
		:son(_s) {}
	void visitson(int x) {
		son->visit(x);
	}
	virtual void del() {
		son->del();
		delete son;
	}
};
class BinaryNode : public Node {
	Node *left, *right;
public:
	BinaryNode(Node *_l, Node *_r)
		:left(_l), right(_r) {}
	void visitson(int x) {
		left->visit(x);
		right->visit(x);
	}
	virtual void del() {
		left->del();
		right->del();
		delete left;
		delete right;
	}
};
class TernaryNode : public Node {
	Node *left, *mid, *right;
public:
	TernaryNode(Node *_l, Node *_m, Node *_r)
		:left(_l), mid(_m), right(_r) {}
	void visitson(int x) {
		left->visit(x);
		mid->visit(x);
		right->visit(x);
	}
	virtual void del() {
		left->del();
		mid->del();
		right->del();
		delete left;
		delete mid;
		delete right;
	}
};
Lex lex("test.ws"); //bug
Node *root;
void refresh() {
	if (root == nullptr)return;
		root->del();
	delete root;
	root = 0;
}  //bug
class SubNode : public BinaryNode {
public:
	SubNode(Node *a, Node *b)
		:BinaryNode(a, b) {}
	virtual void visit(int x) {
		for (int i = 1; i <= x; i++)printf("    ");
		cout << "Sub Node" << endl;
		this->visitson(x + 1);
	}
};
class AddNode : public BinaryNode {
public:
	AddNode(Node *a, Node *b)
		:BinaryNode(a, b) {}
	virtual void visit(int x) {
		for (int i = 1; i <= x; i++)printf("    ");
		cout << "Add Node" << endl;
		this->visitson(x + 1);
	}
};
class DivNode : public BinaryNode {
public:
	DivNode(Node *a, Node *b)
		:BinaryNode(a, b) {}
	virtual void visit(int x) {
		for (int i = 1; i <= x; i++)printf("    ");
		cout << "Div Node" << endl;
		this->visitson(x + 1);
	}
};
class MulNode : public BinaryNode {
public:
	MulNode(Node *a, Node *b)
		:BinaryNode(a, b) {}
	virtual void visit(int x) {
		for (int i = 1; i <= x; i++)printf("    ");
		cout << "Mul Node" << endl;
		this->visitson(x + 1);
	}
};
class NumNode : public Node {
private:
	string num;
public:
	NumNode(string _num)
		:num(_num){}
	virtual void visit(int x) {
		for (int i = 1; i <= x; i++)printf("    ");
		cout << "Num Node :"<< num << endl;
	}
	virtual void del() {
		
	}
};
bool parseFact();
bool parseUnit(); //bug;	
bool parseSum() {
	auto savedRoot1 = root;
	if (parseFact()) {
		int flag = 1;
		while (flag) {
			flag = 0;
			auto SavedLexPos2 = lex.getNowPos();
			auto ReadinToken2 = lex.readNextToken();
			if (ReadinToken2.id == LEX_SUB) {
				auto savedRoot3 = root;
				if (parseFact()) {
					root = new SubNode(savedRoot3, root);
					flag = 1;
					continue;
				}
				else {
					refresh();
					root = savedRoot3;
				}
			}
			else {
				lex.setNowPos(SavedLexPos2);
			}
			SavedLexPos2 = lex.getNowPos();
			ReadinToken2 = lex.readNextToken();
			if (ReadinToken2.id == LEX_ADD) {
				auto savedRoot3 = root;
				if (parseFact()) {
					root = new AddNode(savedRoot3, root);
					flag = 1;
					continue;
				}
				else {
					refresh();
					root = savedRoot3;
				}
			}
			else {
				lex.setNowPos(SavedLexPos2);
			}
		}
		return 1;
	}
	else {
		refresh();
		root = savedRoot1;	
	}
	return 0;
}
bool parseFact() {
	auto savedRoot1 = root;
	if (parseUnit()) {
		int flag = 1;
		while (flag) {
			flag = 0;
			auto SavedLexPos2 = lex.getNowPos();
			auto ReadinToken2 = lex.readNextToken();
			if (ReadinToken2.id == LEX_DIV) {
				auto savedRoot3 = root;
				if (parseUnit()) {
					root = new DivNode(savedRoot3, root);
					flag = 1;
					continue;
				}
				else {
					refresh();
					root = savedRoot3;
				}
			}
			else {
				lex.setNowPos(SavedLexPos2);
			}
			SavedLexPos2 = lex.getNowPos();
			ReadinToken2 = lex.readNextToken();
			if (ReadinToken2.id == LEX_MUL) {
				auto savedRoot3 = root;
				if (parseUnit()) {
					root = new MulNode(savedRoot3, root);
					flag = 1;
					continue;
				}
				else {
					refresh();
					root = savedRoot3;
				}
			}
			else {
				lex.setNowPos(SavedLexPos2);
			}
		}
		return 1;
	}
	else {
		refresh();
		root = savedRoot1;
	}
	return 0;
}
bool parseUnit() {
	auto SavedLexPos1 = lex.getNowPos();
	auto ReadinToken1 = lex.readNextToken();
	if (ReadinToken1.id == LEX_LP) {
		auto savedRoot2 = root;
		if (parseSum()) {
			auto SavedLexPos3 = lex.getNowPos();
			auto ReadinToken3 = lex.readNextToken();
			if (ReadinToken3.id == LEX_RP) {
				return 1;
			}
			else {
				lex.setNowPos(SavedLexPos3);
			}
		}
		else {
			refresh();
			root = savedRoot2;
		}
	}
	else {
		lex.setNowPos(SavedLexPos1);
		//bug
	}
	SavedLexPos1 = lex.getNowPos();
	ReadinToken1 = lex.readNextToken();
	if (ReadinToken1.id == LEX_NUMBER) {
		root = new NumNode(ReadinToken1.name);
		return 1;
	}
	else {
		lex.setNowPos(SavedLexPos1);
	}
	return 0;
}
int main() {
	if (parseSum()) {
		root->visit(0);
		return 1;
	}
	return 0;
	//for (int i = 1; i <= 30; i++)
	//	out(lex.readNextToken());
	return 0;
}
