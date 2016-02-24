#include<iostream>
#include"WeakScriptLex.h"
#include<string>
#include<memory>
#include "lex.h"
using namespace std;
class Node {
public:
	virtual void visit(int x) = 0;
	virtual void del() = 0;
	virtual
};
class UnitNode : public Node {
public:
	UnitNode() {}
	void visitson(int x) {}
	virtual void del() {}
};
class UnaryNode : public Node {
	shared_ptr<Node> son;
public:
	UnaryNode(shared_ptr<Node>  _s)
		:son(_s) {}
	void visitson(int x) {
		son->visit(x);
	}
	virtual void del() {
		son->del();
	}
};
class BinaryNode : public Node {
	shared_ptr<Node> left, right;
public:
	BinaryNode(shared_ptr<Node>  _l, shared_ptr<Node>  _r)
		:left(_l), right(_r) {}
	void visitson(int x) {
		left->visit(x);
		right->visit(x);
	}
	virtual void del() {
		left->del();
		right->del();
	}
};
class TernaryNode : public Node {
	shared_ptr<Node> left, mid, right;
public:
	TernaryNode(shared_ptr<Node> _l, shared_ptr<Node> _m, shared_ptr<Node> _r)
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
	}
};

Lex lex("test.ws");
shared_ptr<Node>  root = nullptr;
void refresh() {
	if (root == nullptr)return;
	root->del();
	root = nullptr;
}; class StmtsNode : public BinaryNode {
public:
	StmtsNode(shared_ptr<Node> a, shared_ptr<Node> b)
		:BinaryNode(a, b) {}
	virtual void visit(int x) {
		for (int i = 1; i <= x; i++)printf("    ");
		cout << "Stmts Node" << endl;
		this->visitson(x + 1);
	}
};
class ContinueNode : public UnitNode {
public:
	ContinueNode()
		:UnitNode() {}
	virtual void visit(int x) {
		for (int i = 1; i <= x; i++)printf("    ");
		cout << "Continue Node" << endl;
		this->visitson(x + 1);
	}
};
class BreakNode : public UnitNode {
public:
	BreakNode()
		:UnitNode() {}
	virtual void visit(int x) {
		for (int i = 1; i <= x; i++)printf("    ");
		cout << "Break Node" << endl;
		this->visitson(x + 1);
	}
};
class WhileNode : public BinaryNode {
public:
	WhileNode(shared_ptr<Node> a, shared_ptr<Node> b)
		:BinaryNode(a, b) {}
	virtual void visit(int x) {
		for (int i = 1; i <= x; i++)printf("    ");
		cout << "While Node" << endl;
		this->visitson(x + 1);
	}
};
class IfElseNode : public TernaryNode {
public:
	IfElseNode(shared_ptr<Node> a, shared_ptr<Node> b, shared_ptr<Node> c)
		:TernaryNode(a, b, c) {}
	virtual void visit(int x) {
		for (int i = 1; i <= x; i++)printf("    ");
		cout << "IfElse Node" << endl;
		this->visitson(x + 1);
	}
};
class IfNode : public BinaryNode {
public:
	IfNode(shared_ptr<Node> a, shared_ptr<Node> b)
		:BinaryNode(a, b) {}
	virtual void visit(int x) {
		for (int i = 1; i <= x; i++)printf("    ");
		cout << "If Node" << endl;
		this->visitson(x + 1);
	}
};
class DeclrNode : public UnitNode {
public:
	string value;
	DeclrNode(string _value)
		:UnitNode() {
		value = _value;
	}
	virtual void visit(int x) {
		for (int i = 1; i <= x; i++)printf("    ");
		cout << "Declr Node :" << value << endl;
		this->visitson(x + 1);
	}
};
class AssignNode : public BinaryNode {
public:
	AssignNode(shared_ptr<Node> a, shared_ptr<Node> b)
		:BinaryNode(a, b) {}
	virtual void visit(int x) {
		for (int i = 1; i <= x; i++)printf("    ");
		cout << "Assign Node" << endl;
		this->visitson(x + 1);
	}
};
class OrNode : public BinaryNode {
public:
	OrNode(shared_ptr<Node> a, shared_ptr<Node> b)
		:BinaryNode(a, b) {}
	virtual void visit(int x) {
		for (int i = 1; i <= x; i++)printf("    ");
		cout << "Or Node" << endl;
		this->visitson(x + 1);
	}
};
class AndNode : public BinaryNode {
public:
	AndNode(shared_ptr<Node> a, shared_ptr<Node> b)
		:BinaryNode(a, b) {}
	virtual void visit(int x) {
		for (int i = 1; i <= x; i++)printf("    ");
		cout << "And Node" << endl;
		this->visitson(x + 1);
	}
};
class NltNode : public BinaryNode {
public:
	NltNode(shared_ptr<Node> a, shared_ptr<Node> b)
		:BinaryNode(a, b) {}
	virtual void visit(int x) {
		for (int i = 1; i <= x; i++)printf("    ");
		cout << "Nlt Node" << endl;
		this->visitson(x + 1);
	}
};
class NgtNode : public BinaryNode {
public:
	NgtNode(shared_ptr<Node> a, shared_ptr<Node> b)
		:BinaryNode(a, b) {}
	virtual void visit(int x) {
		for (int i = 1; i <= x; i++)printf("    ");
		cout << "Ngt Node" << endl;
		this->visitson(x + 1);
	}
};
class LtNode : public BinaryNode {
public:
	LtNode(shared_ptr<Node> a, shared_ptr<Node> b)
		:BinaryNode(a, b) {}
	virtual void visit(int x) {
		for (int i = 1; i <= x; i++)printf("    ");
		cout << "Lt Node" << endl;
		this->visitson(x + 1);
	}
};
class GtNode : public BinaryNode {
public:
	GtNode(shared_ptr<Node> a, shared_ptr<Node> b)
		:BinaryNode(a, b) {}
	virtual void visit(int x) {
		for (int i = 1; i <= x; i++)printf("    ");
		cout << "Gt Node" << endl;
		this->visitson(x + 1);
	}
};
class NeqNode : public BinaryNode {
public:
	NeqNode(shared_ptr<Node> a, shared_ptr<Node> b)
		:BinaryNode(a, b) {}
	virtual void visit(int x) {
		for (int i = 1; i <= x; i++)printf("    ");
		cout << "Neq Node" << endl;
		this->visitson(x + 1);
	}
};
class EqNode : public BinaryNode {
public:
	EqNode(shared_ptr<Node> a, shared_ptr<Node> b)
		:BinaryNode(a, b) {}
	virtual void visit(int x) {
		for (int i = 1; i <= x; i++)printf("    ");
		cout << "Eq Node" << endl;
		this->visitson(x + 1);
	}
};
class SubNode : public BinaryNode {
public:
	SubNode(shared_ptr<Node> a, shared_ptr<Node> b)
		:BinaryNode(a, b) {}
	virtual void visit(int x) {
		for (int i = 1; i <= x; i++)printf("    ");
		cout << "Sub Node" << endl;
		this->visitson(x + 1);
	}
};
class AddNode : public BinaryNode {
public:
	AddNode(shared_ptr<Node> a, shared_ptr<Node> b)
		:BinaryNode(a, b) {}
	virtual void visit(int x) {
		for (int i = 1; i <= x; i++)printf("    ");
		cout << "Add Node" << endl;
		this->visitson(x + 1);
	}
};
class ModNode : public BinaryNode {
public:
	ModNode(shared_ptr<Node> a, shared_ptr<Node> b)
		:BinaryNode(a, b) {}
	virtual void visit(int x) {
		for (int i = 1; i <= x; i++)printf("    ");
		cout << "Mod Node" << endl;
		this->visitson(x + 1);
	}
};
class DivNode : public BinaryNode {
public:
	DivNode(shared_ptr<Node> a, shared_ptr<Node> b)
		:BinaryNode(a, b) {}
	virtual void visit(int x) {
		for (int i = 1; i <= x; i++)printf("    ");
		cout << "Div Node" << endl;
		this->visitson(x + 1);
	}
};
class MulNode : public BinaryNode {
public:
	MulNode(shared_ptr<Node> a, shared_ptr<Node> b)
		:BinaryNode(a, b) {}
	virtual void visit(int x) {
		for (int i = 1; i <= x; i++)printf("    ");
		cout << "Mul Node" << endl;
		this->visitson(x + 1);
	}
};
class RevNode : public UnaryNode {
public:
	RevNode(shared_ptr<Node> a)
		:UnaryNode(a) {}
	virtual void visit(int x) {
		for (int i = 1; i <= x; i++)printf("    ");
		cout << "Rev Node" << endl;
		this->visitson(x + 1);
	}
};
class NotNode : public UnaryNode {
public:
	NotNode(shared_ptr<Node> a)
		:UnaryNode(a) {}
	virtual void visit(int x) {
		for (int i = 1; i <= x; i++)printf("    ");
		cout << "Not Node" << endl;
		this->visitson(x + 1);
	}
};
class NegNode : public UnaryNode {
public:
	NegNode(shared_ptr<Node> a)
		:UnaryNode(a) {}
	virtual void visit(int x) {
		for (int i = 1; i <= x; i++)printf("    ");
		cout << "Neg Node" << endl;
		this->visitson(x + 1);
	}
};
class IDNode : public UnitNode {
public:
	string value;
	IDNode(string _value)
		:UnitNode() {
		value = _value;
	}
	virtual void visit(int x) {
		for (int i = 1; i <= x; i++)printf("    ");
		cout << "ID Node :" << value << endl;
		this->visitson(x + 1);
	}
};
class strNode : public UnitNode {
public:
	string value;
	strNode(string _value)
		:UnitNode() {
		value = _value;
	}
	virtual void visit(int x) {
		for (int i = 1; i <= x; i++)printf("    ");
		cout << "str Node :" << value << endl;
		this->visitson(x + 1);
	}
};
class realNode : public UnitNode {
public:
	string value;
	realNode(string _value)
		:UnitNode() {
		value = _value;
	}
	virtual void visit(int x) {
		for (int i = 1; i <= x; i++)printf("    ");
		cout << "real Node :" << value << endl;
		this->visitson(x + 1);
	}
};
class intNode : public UnitNode {
public:
	string value;
	intNode(string _value)
		:UnitNode() {
		value = _value;
	}
	virtual void visit(int x) {
		for (int i = 1; i <= x; i++)printf("    ");
		cout << "int Node :" << value << endl;
		this->visitson(x + 1);
	}
};

bool parseStmts();
bool parseStmt();
bool parseExpr();
bool parseAndExpr();
bool parseCompExpr();
bool parseSum();
bool parseFact();
bool parseValueGroup();
bool parseValue();
bool parseLValue();

bool parseStmts() {
	auto SavedLexPos1 = lex.getNowPos();
	auto SavedRoot1 = root;
	if (parseStmt()) {
		auto SavedLexPos2 = lex.getNowPos();
		auto SavedRoot2 = root;
		if (parseStmts()) {
			root = shared_ptr<Node>(new StmtsNode(SavedRoot2, root));
			return 1;
		}
		refresh();
		lex.setNowPos(SavedLexPos2);
		root = SavedRoot2;
		return 1;
	}
	refresh();
	lex.setNowPos(SavedLexPos1);
	root = SavedRoot1;
	return 0;
}
bool parseStmt() {
	auto SavedLexPos1 = lex.getNowPos();
	auto SavedRoot1 = root;
	auto ReadinToken1 = lex.readNextToken();
	if (ReadinToken1.id == LEX_CONTINUE) {
		auto SavedLexPos2 = lex.getNowPos();
		auto SavedRoot2 = root;
		auto ReadinToken2 = lex.readNextToken();
		if (ReadinToken2.id == LEX_SEMI) {
			root = shared_ptr<Node>(new ContinueNode());
			return 1;
		}
		lex.setNowPos(SavedLexPos2);
		root = SavedRoot2;
	}
	lex.setNowPos(SavedLexPos1);
	root = SavedRoot1;
	SavedLexPos1 = lex.getNowPos();
	SavedRoot1 = root;
	ReadinToken1 = lex.readNextToken();
	if (ReadinToken1.id == LEX_BREAK) {
		auto SavedLexPos2 = lex.getNowPos();
		auto SavedRoot2 = root;
		auto ReadinToken2 = lex.readNextToken();
		if (ReadinToken2.id == LEX_SEMI) {
			root = shared_ptr<Node>(new BreakNode());
			return 1;
		}
		lex.setNowPos(SavedLexPos2);
		root = SavedRoot2;
	}
	lex.setNowPos(SavedLexPos1);
	root = SavedRoot1;
	SavedLexPos1 = lex.getNowPos();
	SavedRoot1 = root;
	ReadinToken1 = lex.readNextToken();
	if (ReadinToken1.id == LEX_WHILE) {
		auto SavedLexPos2 = lex.getNowPos();
		auto SavedRoot2 = root;
		auto ReadinToken2 = lex.readNextToken();
		if (ReadinToken2.id == LEX_LP) {
			auto SavedLexPos3 = lex.getNowPos();
			auto SavedRoot3 = root;
			if (parseExpr()) {
				auto SavedLexPos4 = lex.getNowPos();
				auto SavedRoot4 = root;
				auto ReadinToken4 = lex.readNextToken();
				if (ReadinToken4.id == LEX_RP) {
					auto SavedLexPos5 = lex.getNowPos();
					auto SavedRoot5 = root;
					if (parseStmt()) {
						root = shared_ptr<Node>(new WhileNode(SavedRoot4, root));
						return 1;
					}
					refresh();
					lex.setNowPos(SavedLexPos5);
					root = SavedRoot5;
				}
				lex.setNowPos(SavedLexPos4);
				root = SavedRoot4;
			}
			refresh();
			lex.setNowPos(SavedLexPos3);
			root = SavedRoot3;
		}
		lex.setNowPos(SavedLexPos2);
		root = SavedRoot2;
	}
	lex.setNowPos(SavedLexPos1);
	root = SavedRoot1;
	SavedLexPos1 = lex.getNowPos();
	SavedRoot1 = root;
	ReadinToken1 = lex.readNextToken();
	if (ReadinToken1.id == LEX_IF) {
		auto SavedLexPos2 = lex.getNowPos();
		auto SavedRoot2 = root;
		auto ReadinToken2 = lex.readNextToken();
		if (ReadinToken2.id == LEX_LP) {
			auto SavedLexPos3 = lex.getNowPos();
			auto SavedRoot3 = root;
			if (parseExpr()) {
				auto SavedLexPos4 = lex.getNowPos();
				auto SavedRoot4 = root;
				auto ReadinToken4 = lex.readNextToken();
				if (ReadinToken4.id == LEX_RP) {
					auto SavedLexPos5 = lex.getNowPos();
					auto SavedRoot5 = root;
					if (parseStmt()) {
						auto SavedLexPos6 = lex.getNowPos();
						auto SavedRoot6 = root;
						auto ReadinToken6 = lex.readNextToken();
						if (ReadinToken6.id == LEX_ELSE) {
							auto SavedLexPos7 = lex.getNowPos();
							auto SavedRoot7 = root;
							if (parseStmt()) {
								root = shared_ptr<Node>(new IfElseNode(SavedRoot4, SavedRoot6, root));
								return 1;
							}
							refresh();
							lex.setNowPos(SavedLexPos7);
							root = SavedRoot7;
						}
						lex.setNowPos(SavedLexPos6);
						root = SavedRoot6;
						root = shared_ptr<Node>(new IfNode(SavedRoot4, root));
						return 1;
					}
					refresh();
					lex.setNowPos(SavedLexPos5);
					root = SavedRoot5;
				}
				lex.setNowPos(SavedLexPos4);
				root = SavedRoot4;
			}
			refresh();
			lex.setNowPos(SavedLexPos3);
			root = SavedRoot3;
		}
		lex.setNowPos(SavedLexPos2);
		root = SavedRoot2;
	}
	lex.setNowPos(SavedLexPos1);
	root = SavedRoot1;
	SavedLexPos1 = lex.getNowPos();
	SavedRoot1 = root;
	ReadinToken1 = lex.readNextToken();
	if (ReadinToken1.id == LEX_LCB) {
		auto SavedLexPos2 = lex.getNowPos();
		auto SavedRoot2 = root;
		if (parseStmts()) {
			auto SavedLexPos3 = lex.getNowPos();
			auto SavedRoot3 = root;
			auto ReadinToken3 = lex.readNextToken();
			if (ReadinToken3.id == LEX_RCB) {
				return 1;
			}
			lex.setNowPos(SavedLexPos3);
			root = SavedRoot3;
		}
		refresh();
		lex.setNowPos(SavedLexPos2);
		root = SavedRoot2;
	}
	lex.setNowPos(SavedLexPos1);
	root = SavedRoot1;
	SavedLexPos1 = lex.getNowPos();
	SavedRoot1 = root;
	ReadinToken1 = lex.readNextToken();
	if (ReadinToken1.id == LEX_VAR) {
		auto SavedLexPos2 = lex.getNowPos();
		auto SavedRoot2 = root;
		auto ReadinToken2 = lex.readNextToken();
		if (ReadinToken2.id == LEX_ID) {
			auto SavedLexPos3 = lex.getNowPos();
			auto SavedRoot3 = root;
			auto ReadinToken3 = lex.readNextToken();
			if (ReadinToken3.id == LEX_SEMI) {
				root = shared_ptr<Node>(new DeclrNode(ReadinToken2.name));
				return 1;
			}
			lex.setNowPos(SavedLexPos3);
			root = SavedRoot3;
		}
		lex.setNowPos(SavedLexPos2);
		root = SavedRoot2;
	}
	lex.setNowPos(SavedLexPos1);
	root = SavedRoot1;
	SavedLexPos1 = lex.getNowPos();
	SavedRoot1 = root;
	ReadinToken1 = lex.readNextToken();
	if (ReadinToken1.id == LEX_SEMI) {
		return 1;
	}
	lex.setNowPos(SavedLexPos1);
	root = SavedRoot1;
	SavedLexPos1 = lex.getNowPos();
	SavedRoot1 = root;
	if (parseExpr()) {
		auto SavedLexPos2 = lex.getNowPos();
		auto SavedRoot2 = root;
		auto ReadinToken2 = lex.readNextToken();
		if (ReadinToken2.id == LEX_SEMI) {
			return 1;
		}
		lex.setNowPos(SavedLexPos2);
		root = SavedRoot2;
	}
	refresh();
	lex.setNowPos(SavedLexPos1);
	root = SavedRoot1;
	SavedLexPos1 = lex.getNowPos();
	SavedRoot1 = root;
	if (parseLValue()) {
		auto SavedLexPos2 = lex.getNowPos();
		auto SavedRoot2 = root;
		auto ReadinToken2 = lex.readNextToken();
		if (ReadinToken2.id == LEX_ASSIGN) {
			auto SavedLexPos3 = lex.getNowPos();
			auto SavedRoot3 = root;
			if (parseExpr()) {
				auto SavedLexPos4 = lex.getNowPos();
				auto SavedRoot4 = root;
				auto ReadinToken4 = lex.readNextToken();
				if (ReadinToken4.id == LEX_SEMI) {
					root = shared_ptr<Node>(new AssignNode(SavedRoot3, root));
					return 1;
				}
				lex.setNowPos(SavedLexPos4);
				root = SavedRoot4;
			}
			refresh();
			lex.setNowPos(SavedLexPos3);
			root = SavedRoot3;
		}
		lex.setNowPos(SavedLexPos2);
		root = SavedRoot2;
	}
	refresh();
	lex.setNowPos(SavedLexPos1);
	root = SavedRoot1;
	return 0;
}
bool parseExpr() {
	auto SavedLexPos1 = lex.getNowPos();
	auto SavedRoot1 = root;
	if (parseAndExpr()) {
		int flag = 1;
		while (flag) {
			flag = 0;
			auto SavedLexPos3 = lex.getNowPos();
			auto SavedRoot3 = root;
			auto ReadinToken3 = lex.readNextToken();
			if (ReadinToken3.id == LEX_OR) {
				auto SavedLexPos4 = lex.getNowPos();
				auto SavedRoot4 = root;
				if (parseAndExpr()) {
					root = shared_ptr<Node>(new OrNode(SavedRoot4, root));
					flag = 1;
					continue;
				}
				refresh();
				lex.setNowPos(SavedLexPos4);
				root = SavedRoot4;
			}
			lex.setNowPos(SavedLexPos3);
			root = SavedRoot3;
			return 1;
		}
	}
	refresh();
	lex.setNowPos(SavedLexPos1);
	root = SavedRoot1;
	return 0;
}
bool parseAndExpr() {
	auto SavedLexPos1 = lex.getNowPos();
	auto SavedRoot1 = root;
	if (parseCompExpr()) {
		int flag = 1;
		while (flag) {
			flag = 0;
			auto SavedLexPos3 = lex.getNowPos();
			auto SavedRoot3 = root;
			auto ReadinToken3 = lex.readNextToken();
			if (ReadinToken3.id == LEX_AND) {
				auto SavedLexPos4 = lex.getNowPos();
				auto SavedRoot4 = root;
				if (parseCompExpr()) {
					root = shared_ptr<Node>(new AndNode(SavedRoot4, root));
					flag = 1;
					continue;
				}
				refresh();
				lex.setNowPos(SavedLexPos4);
				root = SavedRoot4;
			}
			lex.setNowPos(SavedLexPos3);
			root = SavedRoot3;
			return 1;
		}
	}
	refresh();
	lex.setNowPos(SavedLexPos1);
	root = SavedRoot1;
	return 0;
}
bool parseCompExpr() {
	auto SavedLexPos1 = lex.getNowPos();
	auto SavedRoot1 = root;
	if (parseSum()) {
		int flag = 1;
		while (flag) {
			flag = 0;
			auto SavedLexPos3 = lex.getNowPos();
			auto SavedRoot3 = root;
			auto ReadinToken3 = lex.readNextToken();
			if (ReadinToken3.id == LEX_NLT) {
				auto SavedLexPos4 = lex.getNowPos();
				auto SavedRoot4 = root;
				if (parseSum()) {
					root = shared_ptr<Node>(new NltNode(SavedRoot4, root));
					flag = 1;
					continue;
				}
				refresh();
				lex.setNowPos(SavedLexPos4);
				root = SavedRoot4;
			}
			lex.setNowPos(SavedLexPos3);
			root = SavedRoot3;
			SavedLexPos3 = lex.getNowPos();
			SavedRoot3 = root;
			ReadinToken3 = lex.readNextToken();
			if (ReadinToken3.id == LEX_NGT) {
				auto SavedLexPos4 = lex.getNowPos();
				auto SavedRoot4 = root;
				if (parseSum()) {
					root = shared_ptr<Node>(new NgtNode(SavedRoot4, root));
					flag = 1;
					continue;
				}
				refresh();
				lex.setNowPos(SavedLexPos4);
				root = SavedRoot4;
			}
			lex.setNowPos(SavedLexPos3);
			root = SavedRoot3;
			SavedLexPos3 = lex.getNowPos();
			SavedRoot3 = root;
			ReadinToken3 = lex.readNextToken();
			if (ReadinToken3.id == LEX_LT) {
				auto SavedLexPos4 = lex.getNowPos();
				auto SavedRoot4 = root;
				if (parseSum()) {
					root = shared_ptr<Node>(new LtNode(SavedRoot4, root));
					flag = 1;
					continue;
				}
				refresh();
				lex.setNowPos(SavedLexPos4);
				root = SavedRoot4;
			}
			lex.setNowPos(SavedLexPos3);
			root = SavedRoot3;
			SavedLexPos3 = lex.getNowPos();
			SavedRoot3 = root;
			ReadinToken3 = lex.readNextToken();
			if (ReadinToken3.id == LEX_GT) {
				auto SavedLexPos4 = lex.getNowPos();
				auto SavedRoot4 = root;
				if (parseSum()) {
					root = shared_ptr<Node>(new GtNode(SavedRoot4, root));
					flag = 1;
					continue;
				}
				refresh();
				lex.setNowPos(SavedLexPos4);
				root = SavedRoot4;
			}
			lex.setNowPos(SavedLexPos3);
			root = SavedRoot3;
			SavedLexPos3 = lex.getNowPos();
			SavedRoot3 = root;
			ReadinToken3 = lex.readNextToken();
			if (ReadinToken3.id == LEX_NEQ) {
				auto SavedLexPos4 = lex.getNowPos();
				auto SavedRoot4 = root;
				if (parseSum()) {
					root = shared_ptr<Node>(new NeqNode(SavedRoot4, root));
					flag = 1;
					continue;
				}
				refresh();
				lex.setNowPos(SavedLexPos4);
				root = SavedRoot4;
			}
			lex.setNowPos(SavedLexPos3);
			root = SavedRoot3;
			SavedLexPos3 = lex.getNowPos();
			SavedRoot3 = root;
			ReadinToken3 = lex.readNextToken();
			if (ReadinToken3.id == LEX_EQ) {
				auto SavedLexPos4 = lex.getNowPos();
				auto SavedRoot4 = root;
				if (parseSum()) {
					root = shared_ptr<Node>(new EqNode(SavedRoot4, root));
					flag = 1;
					continue;
				}
				refresh();
				lex.setNowPos(SavedLexPos4);
				root = SavedRoot4;
			}
			lex.setNowPos(SavedLexPos3);
			root = SavedRoot3;
			return 1;
		}
	}
	refresh();
	lex.setNowPos(SavedLexPos1);
	root = SavedRoot1;
	return 0;
}
bool parseSum() {
	auto SavedLexPos1 = lex.getNowPos();
	auto SavedRoot1 = root;
	if (parseFact()) {
		int flag = 1;
		while (flag) {
			flag = 0;
			auto SavedLexPos3 = lex.getNowPos();
			auto SavedRoot3 = root;
			auto ReadinToken3 = lex.readNextToken();
			if (ReadinToken3.id == LEX_SUB) {
				auto SavedLexPos4 = lex.getNowPos();
				auto SavedRoot4 = root;
				if (parseFact()) {
					root = shared_ptr<Node>(new SubNode(SavedRoot4, root));
					flag = 1;
					continue;
				}
				refresh();
				lex.setNowPos(SavedLexPos4);
				root = SavedRoot4;
			}
			lex.setNowPos(SavedLexPos3);
			root = SavedRoot3;
			SavedLexPos3 = lex.getNowPos();
			SavedRoot3 = root;
			ReadinToken3 = lex.readNextToken();
			if (ReadinToken3.id == LEX_ADD) {
				auto SavedLexPos4 = lex.getNowPos();
				auto SavedRoot4 = root;
				if (parseFact()) {
					root = shared_ptr<Node>(new AddNode(SavedRoot4, root));
					flag = 1;
					continue;
				}
				refresh();
				lex.setNowPos(SavedLexPos4);
				root = SavedRoot4;
			}
			lex.setNowPos(SavedLexPos3);
			root = SavedRoot3;
			return 1;
		}
	}
	refresh();
	lex.setNowPos(SavedLexPos1);
	root = SavedRoot1;
	return 0;
}
bool parseFact() {
	auto SavedLexPos1 = lex.getNowPos();
	auto SavedRoot1 = root;
	if (parseValueGroup()) {
		int flag = 1;
		while (flag) {
			flag = 0;
			auto SavedLexPos3 = lex.getNowPos();
			auto SavedRoot3 = root;
			auto ReadinToken3 = lex.readNextToken();
			if (ReadinToken3.id == LEX_MOD) {
				auto SavedLexPos4 = lex.getNowPos();
				auto SavedRoot4 = root;
				if (parseValueGroup()) {
					root = shared_ptr<Node>(new ModNode(SavedRoot4, root));
					flag = 1;
					continue;
				}
				refresh();
				lex.setNowPos(SavedLexPos4);
				root = SavedRoot4;
			}
			lex.setNowPos(SavedLexPos3);
			root = SavedRoot3;
			SavedLexPos3 = lex.getNowPos();
			SavedRoot3 = root;
			ReadinToken3 = lex.readNextToken();
			if (ReadinToken3.id == LEX_DIV) {
				auto SavedLexPos4 = lex.getNowPos();
				auto SavedRoot4 = root;
				if (parseValueGroup()) {
					root = shared_ptr<Node>(new DivNode(SavedRoot4, root));
					flag = 1;
					continue;
				}
				refresh();
				lex.setNowPos(SavedLexPos4);
				root = SavedRoot4;
			}
			lex.setNowPos(SavedLexPos3);
			root = SavedRoot3;
			SavedLexPos3 = lex.getNowPos();
			SavedRoot3 = root;
			ReadinToken3 = lex.readNextToken();
			if (ReadinToken3.id == LEX_MUL) {
				auto SavedLexPos4 = lex.getNowPos();
				auto SavedRoot4 = root;
				if (parseValueGroup()) {
					root = shared_ptr<Node>(new MulNode(SavedRoot4, root));
					flag = 1;
					continue;
				}
				refresh();
				lex.setNowPos(SavedLexPos4);
				root = SavedRoot4;
			}
			lex.setNowPos(SavedLexPos3);
			root = SavedRoot3;
			return 1;
		}
	}
	refresh();
	lex.setNowPos(SavedLexPos1);
	root = SavedRoot1;
	return 0;
}
bool parseValueGroup() {
	auto SavedLexPos1 = lex.getNowPos();
	auto SavedRoot1 = root;
	auto ReadinToken1 = lex.readNextToken();
	if (ReadinToken1.id == LEX_LP) {
		auto SavedLexPos2 = lex.getNowPos();
		auto SavedRoot2 = root;
		if (parseExpr()) {
			auto SavedLexPos3 = lex.getNowPos();
			auto SavedRoot3 = root;
			auto ReadinToken3 = lex.readNextToken();
			if (ReadinToken3.id == LEX_RP) {
				return 1;
			}
			lex.setNowPos(SavedLexPos3);
			root = SavedRoot3;
		}
		refresh();
		lex.setNowPos(SavedLexPos2);
		root = SavedRoot2;
	}
	lex.setNowPos(SavedLexPos1);
	root = SavedRoot1;
	SavedLexPos1 = lex.getNowPos();
	SavedRoot1 = root;
	ReadinToken1 = lex.readNextToken();
	if (ReadinToken1.id == LEX_REV) {
		auto SavedLexPos2 = lex.getNowPos();
		auto SavedRoot2 = root;
		if (parseValue()) {
			root = shared_ptr<Node>(new RevNode(root));
			return 1;
		}
		refresh();
		lex.setNowPos(SavedLexPos2);
		root = SavedRoot2;
	}
	lex.setNowPos(SavedLexPos1);
	root = SavedRoot1;
	SavedLexPos1 = lex.getNowPos();
	SavedRoot1 = root;
	ReadinToken1 = lex.readNextToken();
	if (ReadinToken1.id == LEX_NOT) {
		auto SavedLexPos2 = lex.getNowPos();
		auto SavedRoot2 = root;
		if (parseValue()) {
			root = shared_ptr<Node>(new NotNode(root));
			return 1;
		}
		refresh();
		lex.setNowPos(SavedLexPos2);
		root = SavedRoot2;
	}
	lex.setNowPos(SavedLexPos1);
	root = SavedRoot1;
	SavedLexPos1 = lex.getNowPos();
	SavedRoot1 = root;
	ReadinToken1 = lex.readNextToken();
	if (ReadinToken1.id == LEX_SUB) {
		auto SavedLexPos2 = lex.getNowPos();
		auto SavedRoot2 = root;
		if (parseValue()) {
			root = shared_ptr<Node>(new NegNode(root));
			return 1;
		}
		refresh();
		lex.setNowPos(SavedLexPos2);
		root = SavedRoot2;
	}
	lex.setNowPos(SavedLexPos1);
	root = SavedRoot1;
	SavedLexPos1 = lex.getNowPos();
	SavedRoot1 = root;
	if (parseValue()) {
		return 1;
	}
	refresh();
	lex.setNowPos(SavedLexPos1);
	root = SavedRoot1;
	return 0;
}
bool parseValue() {
	auto SavedLexPos1 = lex.getNowPos();
	auto SavedRoot1 = root;
	auto ReadinToken1 = lex.readNextToken();
	if (ReadinToken1.id == LEX_ID) {
		root = shared_ptr<Node>(new IDNode(ReadinToken1.name));
		return 1;
	}
	lex.setNowPos(SavedLexPos1);
	root = SavedRoot1;
	SavedLexPos1 = lex.getNowPos();
	SavedRoot1 = root;
	ReadinToken1 = lex.readNextToken();
	if (ReadinToken1.id == LEX_STRING) {
		root = shared_ptr<Node>(new strNode(ReadinToken1.name));
		return 1;
	}
	lex.setNowPos(SavedLexPos1);
	root = SavedRoot1;
	SavedLexPos1 = lex.getNowPos();
	SavedRoot1 = root;
	ReadinToken1 = lex.readNextToken();
	if (ReadinToken1.id == LEX_REAL) {
		root = shared_ptr<Node>(new realNode(ReadinToken1.name));
		return 1;
	}
	lex.setNowPos(SavedLexPos1);
	root = SavedRoot1;
	SavedLexPos1 = lex.getNowPos();
	SavedRoot1 = root;
	ReadinToken1 = lex.readNextToken();
	if (ReadinToken1.id == LEX_INT) {
		root = shared_ptr<Node>(new intNode(ReadinToken1.name));
		return 1;
	}
	lex.setNowPos(SavedLexPos1);
	root = SavedRoot1;
	return 0;
}
bool parseLValue() {
	auto SavedLexPos1 = lex.getNowPos();
	auto SavedRoot1 = root;
	auto ReadinToken1 = lex.readNextToken();
	if (ReadinToken1.id == LEX_ID) {
		root = shared_ptr<Node>(new IDNode(ReadinToken1.name));
		return 1;
	}
	lex.setNowPos(SavedLexPos1);
	root = SavedRoot1;
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

