#include "parser.h"
Lex lex("test.ws");
shared_ptr<Node>  root = nullptr;
UnitNode::UnitNode() {}
void UnitNode::visitson(int x) {}
void UnitNode::del() {}

UnaryNode::UnaryNode(shared_ptr<Node> _s)
	:son(_s) {}
void UnaryNode::visitson(int x) {
	son->visit(x);
}
void UnaryNode::del() {
	son->del();
}

BinaryNode::BinaryNode(shared_ptr<Node> _l, shared_ptr<Node> _r)
	:left(_l), right(_r) {}
void BinaryNode::visitson(int x) {
	left->visit(x);
	right->visit(x);
}
void BinaryNode::del() {
	left->del();
	right->del();
}

TernaryNode::TernaryNode(shared_ptr<Node> _l, shared_ptr<Node>  _m, shared_ptr<Node>  _r)
	:left(_l), mid(_m), right(_r) {}
void TernaryNode::visitson(int x) {
	left->visit(x);
	mid->visit(x);
	right->visit(x);
}
void TernaryNode::del() {
	left->del();
	mid->del();
	right->del();
}
QuadNode::QuadNode(shared_ptr<Node> _l, shared_ptr<Node>  _ml, shared_ptr<Node> _mr, shared_ptr<Node>  _r)
	:left(_l), midleft(_ml),midright(_mr), right(_r) {}
void QuadNode::visitson(int x) {
	left->visit(x);
	midleft->visit(x);
	midright->visit(x);
	right->visit(x);
}
void QuadNode::del() {
	left->del();
	midleft->del();
	midright->del();
	right->del();
}
Value::Value() {
	if (type == Type::Str)
		delete data.Str;
	type = Type::Null;
}
Value::Value(const string &t) {
	if (type == Type::Str)
		delete data.Str;
	this->type = Type::Str;
	this->data.Str = new string(t);
}
Value::Value(const long long &t) {
	if (type == Type::Str)
		delete data.Str;

	this->type = Type::Int;
	this->data.Int = t;
}
Value::Value(const double &t) {
	if (type == Type::Str)
		delete data.Str;
	this->type = Type::Real;
	this->data.Real = t;
}
Value::Value(const Value &t) {
	if (type == Type::Str)
		delete data.Str;
	switch (t.type) {
	case Type::Int:
		this->type = Type::Int;
		this->data.Int = t.data.Int;
		break;
	case Type::Real:
		this->type = Type::Real;
		this->data.Real = t.data.Real;
		break;
	case Type::Str:
		this->type = Type::Str;
		this->data.Str = new string(*t.data.Str);
		break;
	case Type::Null:
		this->type = Type::Null;
		break;
	}
}
Value::~Value() {
	if (type == Type::Str)
		delete data.Str;
	type = Type::Null;
}
Value & Value::operator= (const Value & t) {
	if (type == Type::Str)
		delete data.Str;
	switch (t.type) {
	case Type::Int:
		this->type = Type::Int;
		this->data.Int = t.data.Int;
		break;
	case Type::Real:
		this->type = Type::Real;
		this->data.Real = t.data.Real;
		break;
	case Type::Str:
		this->type = Type::Str;
		this->data.Str = new string(*t.data.Str);
		break;
	case Type::Null:
		this->type = Type::Null;
		break;
	}
	return *this;
}
ostream& operator << (ostream &o, const Value& a) {
	switch (a.type) {
	case Value::Type::Int:
		cout << a.data.Int;
		break;
	case Value::Type::Real:
		cout << a.data.Real;
		break;
	case Value::Type::Str:
		cout << *a.data.Str;
		break;
	case Value::Type::Null:
		cout << "Null";
		break;
	}
	return o;
}

BlockNode::BlockNode(shared_ptr<Node> a)
	:UnaryNode(a) {}
void BlockNode::visit(int x) {
	for (int i = 1; i <= x; i++)printf("    ");
	cout << "Block Node" << endl;
	this->visitson(x + 1);
}
ValueNode::ValueNode(string _value)
	:val(_value), UnitNode() {
}
ValueNode::ValueNode(double _value)
	: val(_value), UnitNode() {
}
ValueNode::ValueNode(long long _value)
	: val(_value), UnitNode() {
}
void ValueNode::visit(int x) {
	for (int i = 1; i <= x; i++)printf("    ");
	switch (val.type) {
	case Value::Type::Int:
		cout << "INT VALUE:";
		break;
	case Value::Type::Real:
		cout << "REAL VALUE:";
		break;
	case Value::Type::Str:
		cout << "STR VALUE:";
		break;
	case Value::Type::Null:
		cout << "NULL VALUE:";
		break;
	}
	cout << val << endl;
	this->visitson(x + 1);
}
void refresh() {
	if (root == nullptr)return;
	root->del();
	root = nullptr;
};
double _stod(string x) {
	istringstream is(x);
	double ret;
	is >> ret;
	return ret;
}
long long _stoi(string x) {
	istringstream is(x);
	long long ret;
	is >> ret;
	return ret;
}    StmtsNode::StmtsNode(shared_ptr<Node> a, shared_ptr<Node> b)
	:BinaryNode(a, b) {}
void StmtsNode::visit(int x) {
	for (int i = 1; i <= x; i++)printf("    ");
	cout << "Stmts Node" << endl;
	this->visitson(x + 1);
}
ContinueNode::ContinueNode()
	:UnitNode() {}
void ContinueNode::visit(int x) {
	for (int i = 1; i <= x; i++)printf("    ");
	cout << "Continue Node" << endl;
	this->visitson(x + 1);
}
BreakNode::BreakNode()
	:UnitNode() {}
void BreakNode::visit(int x) {
	for (int i = 1; i <= x; i++)printf("    ");
	cout << "Break Node" << endl;
	this->visitson(x + 1);
}
WhileNode::WhileNode(shared_ptr<Node> a, shared_ptr<Node> b)
	:BinaryNode(a, b) {}
void WhileNode::visit(int x) {
	for (int i = 1; i <= x; i++)printf("    ");
	cout << "While Node" << endl;
	this->visitson(x + 1);
}
IfElseNode::IfElseNode(shared_ptr<Node> a, shared_ptr<Node> b, shared_ptr<Node> c)
	:TernaryNode(a, b, c) {}
void IfElseNode::visit(int x) {
	for (int i = 1; i <= x; i++)printf("    ");
	cout << "IfElse Node" << endl;
	this->visitson(x + 1);
}
IfNode::IfNode(shared_ptr<Node> a, shared_ptr<Node> b)
	:BinaryNode(a, b) {}
void IfNode::visit(int x) {
	for (int i = 1; i <= x; i++)printf("    ");
	cout << "If Node" << endl;
	this->visitson(x + 1);
}
DeclrNode::DeclrNode(string _value)
	:UnitNode() {
	value = _value;
}
void DeclrNode::visit(int x) {
	for (int i = 1; i <= x; i++)printf("    ");
	cout << "Declr Node :" << value << endl;
	this->visitson(x + 1);
}
AssignNode::AssignNode(shared_ptr<Node> a, shared_ptr<Node> b)
	:BinaryNode(a, b) {}
void AssignNode::visit(int x) {
	for (int i = 1; i <= x; i++)printf("    ");
	cout << "Assign Node" << endl;
	this->visitson(x + 1);
}
OrNode::OrNode(shared_ptr<Node> a, shared_ptr<Node> b)
	:BinaryNode(a, b) {}
void OrNode::visit(int x) {
	for (int i = 1; i <= x; i++)printf("    ");
	cout << "Or Node" << endl;
	this->visitson(x + 1);
}
AndNode::AndNode(shared_ptr<Node> a, shared_ptr<Node> b)
	:BinaryNode(a, b) {}
void AndNode::visit(int x) {
	for (int i = 1; i <= x; i++)printf("    ");
	cout << "And Node" << endl;
	this->visitson(x + 1);
}
NltNode::NltNode(shared_ptr<Node> a, shared_ptr<Node> b)
	:BinaryNode(a, b) {}
void NltNode::visit(int x) {
	for (int i = 1; i <= x; i++)printf("    ");
	cout << "Nlt Node" << endl;
	this->visitson(x + 1);
}
NgtNode::NgtNode(shared_ptr<Node> a, shared_ptr<Node> b)
	:BinaryNode(a, b) {}
void NgtNode::visit(int x) {
	for (int i = 1; i <= x; i++)printf("    ");
	cout << "Ngt Node" << endl;
	this->visitson(x + 1);
}
LtNode::LtNode(shared_ptr<Node> a, shared_ptr<Node> b)
	:BinaryNode(a, b) {}
void LtNode::visit(int x) {
	for (int i = 1; i <= x; i++)printf("    ");
	cout << "Lt Node" << endl;
	this->visitson(x + 1);
}
GtNode::GtNode(shared_ptr<Node> a, shared_ptr<Node> b)
	:BinaryNode(a, b) {}
void GtNode::visit(int x) {
	for (int i = 1; i <= x; i++)printf("    ");
	cout << "Gt Node" << endl;
	this->visitson(x + 1);
}
NeqNode::NeqNode(shared_ptr<Node> a, shared_ptr<Node> b)
	:BinaryNode(a, b) {}
void NeqNode::visit(int x) {
	for (int i = 1; i <= x; i++)printf("    ");
	cout << "Neq Node" << endl;
	this->visitson(x + 1);
}
EqNode::EqNode(shared_ptr<Node> a, shared_ptr<Node> b)
	:BinaryNode(a, b) {}
void EqNode::visit(int x) {
	for (int i = 1; i <= x; i++)printf("    ");
	cout << "Eq Node" << endl;
	this->visitson(x + 1);
}
SubNode::SubNode(shared_ptr<Node> a, shared_ptr<Node> b)
	:BinaryNode(a, b) {}
void SubNode::visit(int x) {
	for (int i = 1; i <= x; i++)printf("    ");
	cout << "Sub Node" << endl;
	this->visitson(x + 1);
}
AddNode::AddNode(shared_ptr<Node> a, shared_ptr<Node> b)
	:BinaryNode(a, b) {}
void AddNode::visit(int x) {
	for (int i = 1; i <= x; i++)printf("    ");
	cout << "Add Node" << endl;
	this->visitson(x + 1);
}
ModNode::ModNode(shared_ptr<Node> a, shared_ptr<Node> b)
	:BinaryNode(a, b) {}
void ModNode::visit(int x) {
	for (int i = 1; i <= x; i++)printf("    ");
	cout << "Mod Node" << endl;
	this->visitson(x + 1);
}
DivNode::DivNode(shared_ptr<Node> a, shared_ptr<Node> b)
	:BinaryNode(a, b) {}
void DivNode::visit(int x) {
	for (int i = 1; i <= x; i++)printf("    ");
	cout << "Div Node" << endl;
	this->visitson(x + 1);
}
MulNode::MulNode(shared_ptr<Node> a, shared_ptr<Node> b)
	:BinaryNode(a, b) {}
void MulNode::visit(int x) {
	for (int i = 1; i <= x; i++)printf("    ");
	cout << "Mul Node" << endl;
	this->visitson(x + 1);
}
RevNode::RevNode(shared_ptr<Node> a)
	:UnaryNode(a) {}
void RevNode::visit(int x) {
	for (int i = 1; i <= x; i++)printf("    ");
	cout << "Rev Node" << endl;
	this->visitson(x + 1);
}
NotNode::NotNode(shared_ptr<Node> a)
	:UnaryNode(a) {}
void NotNode::visit(int x) {
	for (int i = 1; i <= x; i++)printf("    ");
	cout << "Not Node" << endl;
	this->visitson(x + 1);
}
NegNode::NegNode(shared_ptr<Node> a)
	:UnaryNode(a) {}
void NegNode::visit(int x) {
	for (int i = 1; i <= x; i++)printf("    ");
	cout << "Neg Node" << endl;
	this->visitson(x + 1);
}
IDNode::IDNode(string _value)
	:UnitNode() {
	value = _value;
}
void IDNode::visit(int x) {
	for (int i = 1; i <= x; i++)printf("    ");
	cout << "ID Node :" << value << endl;
	this->visitson(x + 1);
}

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
				root = shared_ptr<Node>(new BlockNode(root));
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
		root = shared_ptr<Node>(new ValueNode(ReadinToken1.name));
		return 1;
	}
	lex.setNowPos(SavedLexPos1);
	root = SavedRoot1;
	SavedLexPos1 = lex.getNowPos();
	SavedRoot1 = root;
	ReadinToken1 = lex.readNextToken();
	if (ReadinToken1.id == LEX_REAL) {
		root = shared_ptr<Node>(new ValueNode(_stod(ReadinToken1.name)));
		return 1;
	}
	lex.setNowPos(SavedLexPos1);
	root = SavedRoot1;
	SavedLexPos1 = lex.getNowPos();
	SavedRoot1 = root;
	ReadinToken1 = lex.readNextToken();
	if (ReadinToken1.id == LEX_INT) {
		root = shared_ptr<Node>(new ValueNode(_stoi(ReadinToken1.name)));
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


