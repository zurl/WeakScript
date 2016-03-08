#include "parser.h"
Lex lex("test.ws");
shared_ptr<Node> root = shared_ptr<Node>(new NullNode());
extern map<string, int> IdHashTable;
extern int IdHashTableNow;
UnitNode::UnitNode() {}
void UnitNode::visitson(int x) {}
void UnitNode::del() {}
NullNode::NullNode() :UnitNode() {}
Value NullNode::eval() { return Value(); }
void NullNode::visit(int x) {
	for (int i = 1; i <= x; i++)printf("    ");
	cout << "Null Node" << endl;
	this->visitson(x + 1);
}
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
	:left(_l), midleft(_ml), midright(_mr), right(_r) {}
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

ForeachNode::ForeachNode(shared_ptr<Node> a, shared_ptr<Node> b, shared_ptr<Node> c)
	:TernaryNode(a, b, c) {}
void ForeachNode::visit(int x) {
	for (int i = 1; i <= x; i++)printf("    ");
	cout << "Foreach Node" << endl;
	this->visitson(x + 1);
}
VarDeclrsNode::VarDeclrsNode(shared_ptr<Node> a, shared_ptr<Node> b)
	:BinaryNode(a, b) {}
void VarDeclrsNode::visit(int x) {
	for (int i = 1; i <= x; i++)printf("    ");
	cout << "VarDeclrs Node" << endl;
	this->visitson(x + 1);
}
VarDeclrAssignNode::VarDeclrAssignNode(string _value, shared_ptr<Node> b)
	:UnaryNode(b) {
	auto t = IdHashTable.find(_value);
	if (t == IdHashTable.end()) {
		IdHashTable.emplace(_value, ++IdHashTableNow);
		value = IdHashTableNow;
	}
	else value = t->second;
}
void VarDeclrAssignNode::visit(int x) {
	for (int i = 1; i <= x; i++)printf("    ");
	cout << "Declrass Node :" << value << endl;
	this->visitson(x + 1);
}
VarDeclrNode::VarDeclrNode(string _value)
	:UnitNode() {
	auto t = IdHashTable.find(_value);
	if (t == IdHashTable.end()) {
		IdHashTable.emplace(_value, ++IdHashTableNow);
		value = IdHashTableNow;
	}
	else value = t->second;
}
void VarDeclrNode::visit(int x) {
	for (int i = 1; i <= x; i++)printf("    ");
	cout << "Declr Node :" << value << endl;
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
	//if (root == nullptr)return;
	root->del();
	root = shared_ptr<Node>(new NullNode());
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
} 
ArrayDefNode::ArrayDefNode(shared_ptr<Node> a)
	:UnaryNode(a) {}
void ArrayDefNode::visit(int x) {
	for (int i = 1; i <= x; i++)printf("    ");
	cout << "ArrayDef Node" << endl;
	this->visitson(x + 1);
}
ArrayDefGroupNode::ArrayDefGroupNode(shared_ptr<Node> a, shared_ptr<Node> b)
	:BinaryNode(a, b) {}
void ArrayDefGroupNode::visit(int x) {
	for (int i = 1; i <= x; i++)printf("    ");
	cout << "ArrayDefGroup Node" << endl;
	this->visitson(x + 1);
}
StmtsNode::StmtsNode(shared_ptr<Node> a, shared_ptr<Node> b)
	:BinaryNode(a, b) {}
void StmtsNode::visit(int x) {
	for (int i = 1; i <= x; i++)printf("    ");
	cout << "Stmts Node" << endl;
	this->visitson(x + 1);
}
ForNode::ForNode(shared_ptr<Node> a, shared_ptr<Node> b, shared_ptr<Node> c, shared_ptr<Node> d)
	:QuadNode(a, b, c, d) {}
void ForNode::visit(int x) {
	for (int i = 1; i <= x; i++)printf("    ");
	cout << "For Node" << endl;
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
BlockNode::BlockNode(shared_ptr<Node> a)
	:UnaryNode(a) {}
void BlockNode::visit(int x) {
	for (int i = 1; i <= x; i++)printf("    ");
	cout << "Block Node" << endl;
	this->visitson(x + 1);
}
AssignNode::AssignNode(shared_ptr<Node> a, shared_ptr<Node> b)
	:BinaryNode(a, b) {}
void AssignNode::visit(int x) {
	for (int i = 1; i <= x; i++)printf("    ");
	cout << "Assign Node" << endl;
	this->visitson(x + 1);
}
ReturnNode::ReturnNode(shared_ptr<Node> a)
	:UnaryNode(a) {}
void ReturnNode::visit(int x) {
	for (int i = 1; i <= x; i++)printf("    ");
	cout << "Return Node" << endl;
	this->visitson(x + 1);
}
ReturnNullNode::ReturnNullNode(shared_ptr<Node> a)
	:UnaryNode(a) {}
void ReturnNullNode::visit(int x) {
	for (int i = 1; i <= x; i++)printf("    ");
	cout << "ReturnNull Node" << endl;
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
FuncDefNode::FuncDefNode(shared_ptr<Node> a, shared_ptr<Node> b)
	:BinaryNode(a, b) {}
void FuncDefNode::visit(int x) {
	for (int i = 1; i <= x; i++)printf("    ");
	cout << "FuncDef Node" << endl;
	this->visitson(x + 1);
}
ArguDefNode::ArguDefNode(shared_ptr<Node> a, shared_ptr<Node> b)
	:BinaryNode(a, b) {}
void ArguDefNode::visit(int x) {
	for (int i = 1; i <= x; i++)printf("    ");
	cout << "ArguDef Node" << endl;
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
FuncCallNode::FuncCallNode(shared_ptr<Node> a, shared_ptr<Node> b)
	:BinaryNode(a, b) {}
void FuncCallNode::visit(int x) {
	for (int i = 1; i <= x; i++)printf("    ");
	cout << "FuncCall Node" << endl;
	this->visitson(x + 1);
}
ArguNode::ArguNode(shared_ptr<Node> a, shared_ptr<Node> b)
	:BinaryNode(a, b) {}
void ArguNode::visit(int x) {
	for (int i = 1; i <= x; i++)printf("    ");
	cout << "Argu Node" << endl;
	this->visitson(x + 1);
}
IDNode::IDNode(string _value)
	:UnitNode() {
	auto t = IdHashTable.find(_value);
	if (t == IdHashTable.end()) {
		IdHashTable.emplace(_value, ++IdHashTableNow);
		value = IdHashTableNow;
	}
	else value = t->second;		
}
IDNode::IDNode(int _value)
	:UnitNode() {
	value = _value;
}
void IDNode::visit(int x) {
	for (int i = 1; i <= x; i++)printf("    ");
	cout << "ID Node :" << value << endl;
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
BorNode::BorNode(shared_ptr<Node> a, shared_ptr<Node> b)
	:BinaryNode(a, b) {}
void BorNode::visit(int x) {
	for (int i = 1; i <= x; i++)printf("    ");
	cout << "Bor Node" << endl;
	this->visitson(x + 1);
}
BandNode::BandNode(shared_ptr<Node> a, shared_ptr<Node> b)
	:BinaryNode(a, b) {}
void BandNode::visit(int x) {
	for (int i = 1; i <= x; i++)printf("    ");
	cout << "Band Node" << endl;
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
SonNode::SonNode(shared_ptr<Node> a, shared_ptr<Node> b)
	:BinaryNode(a, b) {}
void SonNode::visit(int x) {
	for (int i = 1; i <= x; i++)printf("    ");
	cout << "Son Node" << endl;
	this->visitson(x + 1);
}
JsonGroupNode::JsonGroupNode(shared_ptr<Node> a, shared_ptr<Node> b)
	:BinaryNode(a, b) {}
void JsonGroupNode::visit(int x) {
	for (int i = 1; i <= x; i++)printf("    ");
	cout << "JsonGroup Node" << endl;
	this->visitson(x + 1);
} 
SelfSubNode::SelfSubNode(shared_ptr<Node> a)
	: UnaryNode(a) {}
void SelfSubNode::visit(int x) {
	for (int i = 1; i <= x; i++)printf("    ");
	cout << "SelfSub Node" << endl;
	this->visitson(x + 1);
}
SelfAddNode::SelfAddNode(shared_ptr<Node> a)
	:UnaryNode(a) {}
void SelfAddNode::visit(int x) {
	for (int i = 1; i <= x; i++)printf("    ");
	cout << "SelfAdd Node" << endl;
	this->visitson(x + 1);
}
JsonNode::JsonNode(shared_ptr<Node> a, shared_ptr<Node> b)
	:BinaryNode(a, b) {}
void JsonNode::visit(int x) {
	for (int i = 1; i <= x; i++)printf("    ");
	cout << "Json Node" << endl;
	this->visitson(x + 1);
}
ObjDefNode::ObjDefNode(shared_ptr<Node> a)
	:UnaryNode(a) {}
void ObjDefNode::visit(int x) {
	for (int i = 1; i <= x; i++)printf("    ");
	cout << "ObjDefNode Node" << endl;
	this->visitson(x + 1);
}
bool parseStmts();
bool parseStmt();
bool parseStmtBase();
bool parseFuncDef();
bool parseArguDef();
bool parseValueGroup();
bool parseValue();
bool parseArgu();
bool parseLValue();
bool parseExpr();
bool parseIDBase();
bool parseAndExpr();
bool parseBorExpr();
bool parseBandExpr();
bool parseEqCompExpr();
bool parseCompExpr();
bool parseSum();
bool parseFact(); 
bool parseObjDef();
bool parseJSON();
bool parseVarDecl();
bool parseVarDeclBase();
bool parseRvalue();
bool parseSonExpr();
bool parseArrayDefGroup();
bool parseArrayDef();

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
	if (parseStmtBase()) {
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
	auto ReadinToken1 = lex.readNextToken();
	if (ReadinToken1.id == LEX_FOR) {
		auto SavedLexPos2 = lex.getNowPos();
		auto SavedRoot2 = root;
		auto ReadinToken2 = lex.readNextToken();
		if (ReadinToken2.id == LEX_LP) {
			auto SavedLexPos3 = lex.getNowPos();
			auto SavedRoot3 = root;
			auto ReadinToken3 = lex.readNextToken();
			if (ReadinToken3.id == LEX_VAR) {
				auto SavedLexPos4 = lex.getNowPos();
				auto SavedRoot4 = root;
				if (parseIDBase()) {
					auto SavedLexPos5 = lex.getNowPos();
					auto SavedRoot5 = root;
					auto ReadinToken5 = lex.readNextToken();
					if (ReadinToken5.id == LEX_IN) {
						auto SavedLexPos6 = lex.getNowPos();
						auto SavedRoot6 = root;
						if (parseLValue()) {
							auto SavedLexPos7 = lex.getNowPos();
							auto SavedRoot7 = root;
							auto ReadinToken7 = lex.readNextToken();
							if (ReadinToken7.id == LEX_RP) {
								auto SavedLexPos8 = lex.getNowPos();
								auto SavedRoot8 = root;
								if (parseStmt()) {
									root = shared_ptr<Node>(new ForeachNode(SavedRoot5, SavedRoot7, root));
									return 1;
								}
								refresh();
								lex.setNowPos(SavedLexPos8);
								root = SavedRoot8;
							}
							lex.setNowPos(SavedLexPos7);
							root = SavedRoot7;
						}
						refresh();
						lex.setNowPos(SavedLexPos6);
						root = SavedRoot6;
					}
					lex.setNowPos(SavedLexPos5);
					root = SavedRoot5;
				}
				refresh();
				lex.setNowPos(SavedLexPos4);
				root = SavedRoot4;
			}
			lex.setNowPos(SavedLexPos3);
			root = SavedRoot3;
			SavedLexPos3 = lex.getNowPos();
			SavedRoot3 = root;
			if (parseStmtBase()) {
				auto SavedLexPos4 = lex.getNowPos();
				auto SavedRoot4 = root;
				auto ReadinToken4 = lex.readNextToken();
				if (ReadinToken4.id == LEX_SEMI) {
					auto SavedLexPos5 = lex.getNowPos();
					auto SavedRoot5 = root;
					if (parseExpr()) {
						auto SavedLexPos6 = lex.getNowPos();
						auto SavedRoot6 = root;
						auto ReadinToken6 = lex.readNextToken();
						if (ReadinToken6.id == LEX_SEMI) {
							auto SavedLexPos7 = lex.getNowPos();
							auto SavedRoot7 = root;
							if (parseStmtBase()) {
								auto SavedLexPos8 = lex.getNowPos();
								auto SavedRoot8 = root;
								auto ReadinToken8 = lex.readNextToken();
								if (ReadinToken8.id == LEX_RP) {
									auto SavedLexPos9 = lex.getNowPos();
									auto SavedRoot9 = root;
									if (parseStmt()) {
										root = shared_ptr<Node>(new ForNode(SavedRoot4, SavedRoot6, SavedRoot8, root));
										return 1;
									}
									refresh();
									lex.setNowPos(SavedLexPos9);
									root = SavedRoot9;
								}
								lex.setNowPos(SavedLexPos8);
								root = SavedRoot8;
							}
							refresh();
							lex.setNowPos(SavedLexPos7);
							root = SavedRoot7;
						}
						lex.setNowPos(SavedLexPos6);
						root = SavedRoot6;
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
	return 0;
}
bool parseJSONGroup() {
	auto SavedLexPos1 = lex.getNowPos();
	auto SavedRoot1 = root;
	if (parseJSON()) {
		int flag = 1;
		while (flag) {
			flag = 0;
			auto SavedLexPos3 = lex.getNowPos();
			auto SavedRoot3 = root;
			auto ReadinToken3 = lex.readNextToken();
			if (ReadinToken3.id == LEX_COM) {
				auto SavedLexPos4 = lex.getNowPos();
				auto SavedRoot4 = root;
				if (parseJSON()) {
					root = shared_ptr<Node>(new JsonGroupNode(SavedRoot4, root));
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
bool parseJSON() {
	auto SavedLexPos1 = lex.getNowPos();
	auto SavedRoot1 = root;
	if (parseIDBase()) {
		auto SavedLexPos2 = lex.getNowPos();
		auto SavedRoot2 = root;
		auto ReadinToken2 = lex.readNextToken();
		if (ReadinToken2.id == LEX_COL) {
			auto SavedLexPos3 = lex.getNowPos();
			auto SavedRoot3 = root;
			if (parseValue()) {
				root = shared_ptr<Node>(new JsonNode(SavedRoot2, root));
				return 1;
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
bool parseObjDef() {
	auto SavedLexPos1 = lex.getNowPos();
	auto SavedRoot1 = root;
	auto ReadinToken1 = lex.readNextToken();
	if (ReadinToken1.id == LEX_LCB) {
		auto SavedLexPos2 = lex.getNowPos();
		auto SavedRoot2 = root;
		if (parseJSONGroup()) {
			auto SavedLexPos3 = lex.getNowPos();
			auto SavedRoot3 = root;
			auto ReadinToken3 = lex.readNextToken();
			if (ReadinToken3.id == LEX_RCB) {
				root = shared_ptr<Node>(new ObjDefNode(root));
				return 1;
			}
			lex.setNowPos(SavedLexPos3);
			root = SavedRoot3;
		}
		refresh();
		lex.setNowPos(SavedLexPos2);
		root = SavedRoot2;
		SavedLexPos2 = lex.getNowPos();
		SavedRoot2 = root;
		auto ReadinToken2 = lex.readNextToken();
		if (ReadinToken2.id == LEX_RCB) {
			root = shared_ptr<Node>(new ObjDefNode(shared_ptr<Node>(new NullNode())));
			return 1;
		}
		lex.setNowPos(SavedLexPos2);
		root = SavedRoot2;
	}
	lex.setNowPos(SavedLexPos1);
	root = SavedRoot1;
	return 0;
}
bool parseStmtBase() {
	auto SavedLexPos1 = lex.getNowPos();
	auto SavedRoot1 = root;
	auto ReadinToken1 = lex.readNextToken();
	if (ReadinToken1.id == LEX_VAR) {
		auto SavedLexPos2 = lex.getNowPos();
		auto SavedRoot2 = root;
		if (parseVarDecl()) {
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
	if (ReadinToken1.id == LEX_SSUB) {
		auto SavedLexPos2 = lex.getNowPos();
		auto SavedRoot2 = root;
		if (parseLValue()) {
			root = shared_ptr<Node>(new SelfSubNode(root));
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
	if (ReadinToken1.id == LEX_SADD) {
		auto SavedLexPos2 = lex.getNowPos();
		auto SavedRoot2 = root;
		if (parseLValue()) {
			root = shared_ptr<Node>(new SelfAddNode(root));
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
	if (parseLValue()) {
		auto SavedLexPos2 = lex.getNowPos();
		auto SavedRoot2 = root;
		auto ReadinToken2 = lex.readNextToken();
		if (ReadinToken2.id == LEX_SSUB) {
			root = shared_ptr<Node>(new SelfSubNode(root));
			return 1;
		}
		lex.setNowPos(SavedLexPos2);
		root = SavedRoot2;
		SavedLexPos2 = lex.getNowPos();
		SavedRoot2 = root;
		ReadinToken2 = lex.readNextToken();
		if (ReadinToken2.id == LEX_SADD) {
			root = shared_ptr<Node>(new SelfAddNode(root));
			return 1;
		}
		lex.setNowPos(SavedLexPos2);
		root = SavedRoot2;
		SavedLexPos2 = lex.getNowPos();
		SavedRoot2 = root;
		ReadinToken2 = lex.readNextToken();
		if (ReadinToken2.id == LEX_ASSIGN) {
			auto SavedLexPos3 = lex.getNowPos();
			auto SavedRoot3 = root;
			if (parseRvalue()) {
				root = shared_ptr<Node>(new AssignNode(SavedRoot3, root));
				return 1;
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
	SavedLexPos1 = lex.getNowPos();
	SavedRoot1 = root;
	ReadinToken1 = lex.readNextToken();
	if (ReadinToken1.id == LEX_RETURN) {
		auto SavedLexPos2 = lex.getNowPos();
		auto SavedRoot2 = root;
		if (parseRvalue()) {
			root = shared_ptr<Node>(new ReturnNode(root));
			return 1;
		}
		refresh();
		lex.setNowPos(SavedLexPos2);
		root = SavedRoot2;
		root = shared_ptr<Node>(new ReturnNullNode(root));
		return 1;
	}
	lex.setNowPos(SavedLexPos1);
	root = SavedRoot1;
	SavedLexPos1 = lex.getNowPos();
	SavedRoot1 = root;
	ReadinToken1 = lex.readNextToken();
	if (ReadinToken1.id == LEX_CONTINUE) {
		root = shared_ptr<Node>(new ContinueNode());
		return 1;
	}
	lex.setNowPos(SavedLexPos1);
	root = SavedRoot1;
	SavedLexPos1 = lex.getNowPos();
	SavedRoot1 = root;
	ReadinToken1 = lex.readNextToken();
	if (ReadinToken1.id == LEX_BREAK) {
		root = shared_ptr<Node>(new BreakNode());
		return 1;
	}
	lex.setNowPos(SavedLexPos1);
	root = SavedRoot1;
	SavedLexPos1 = lex.getNowPos();
	SavedRoot1 = root;
	if (parseRvalue()) {
		return 1;
	}
	refresh();
	lex.setNowPos(SavedLexPos1);
	root = SavedRoot1;
	return 1;
}
bool parseRvalue() {
	auto SavedLexPos1 = lex.getNowPos();
	auto SavedRoot1 = root;
	if (parseArrayDef()) {
		return 1;
	}
	refresh();
	lex.setNowPos(SavedLexPos1);
	root = SavedRoot1;
	SavedLexPos1 = lex.getNowPos();
	SavedRoot1 = root;
	if (parseObjDef()) {
		return 1;
	}
	refresh();
	lex.setNowPos(SavedLexPos1);
	root = SavedRoot1;
	SavedLexPos1 = lex.getNowPos();
	SavedRoot1 = root;
	if (parseFuncDef()) {
		return 1;
	}
	refresh();
	lex.setNowPos(SavedLexPos1);
	root = SavedRoot1;
	SavedLexPos1 = lex.getNowPos();
	SavedRoot1 = root;
	if (parseExpr()) {
		return 1;
	}
	refresh();
	lex.setNowPos(SavedLexPos1);
	root = SavedRoot1;
	return 0;
}bool parseArrayDef() {
	auto SavedLexPos1 = lex.getNowPos();
	auto SavedRoot1 = root;
	auto ReadinToken1 = lex.readNextToken();
	if (ReadinToken1.id == LEX_LSB) {
		auto SavedLexPos2 = lex.getNowPos();
		auto SavedRoot2 = root;
		auto ReadinToken2 = lex.readNextToken();
		if (ReadinToken2.id == LEX_RSB) {
			root = shared_ptr<Node>(new ArrayDefNode(shared_ptr<Node>(new NullNode()))); return 1;
		}
		lex.setNowPos(SavedLexPos2);
		root = SavedRoot2;
		SavedLexPos2 = lex.getNowPos();
		SavedRoot2 = root;
		if (parseArrayDefGroup()) {
			auto SavedLexPos3 = lex.getNowPos();
			auto SavedRoot3 = root;
			auto ReadinToken3 = lex.readNextToken();
			if (ReadinToken3.id == LEX_RSB) {
				root = shared_ptr<Node>(new ArrayDefNode(root));

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
	return 0;
}
bool parseArrayDefGroup() {
	auto SavedLexPos1 = lex.getNowPos();
	auto SavedRoot1 = root;
	if (parseRvalue()) {
		int flag = 1;
		while (flag) {
			flag = 0;
			auto SavedLexPos3 = lex.getNowPos();
			auto SavedRoot3 = root;
			auto ReadinToken3 = lex.readNextToken();
			if (ReadinToken3.id == LEX_COM) {
				auto SavedLexPos4 = lex.getNowPos();
				auto SavedRoot4 = root;
				if (parseRvalue()) {
					root = shared_ptr<Node>(new ArrayDefGroupNode(SavedRoot4, root));
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
bool parseVarDecl() {
	auto SavedLexPos1 = lex.getNowPos();
	auto SavedRoot1 = root;
	if (parseVarDeclBase()) {
		int flag = 1;
		while (flag) {
			flag = 0;
			auto SavedLexPos3 = lex.getNowPos();
			auto SavedRoot3 = root;
			auto ReadinToken3 = lex.readNextToken();
			if (ReadinToken3.id == LEX_COM) {
				auto SavedLexPos4 = lex.getNowPos();
				auto SavedRoot4 = root;
				if (parseVarDeclBase()) {
					root = shared_ptr<Node>(new VarDeclrsNode(SavedRoot3, root));
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
bool parseVarDeclBase() {
	auto SavedLexPos1 = lex.getNowPos();
	auto SavedRoot1 = root;
	auto ReadinToken1 = lex.readNextToken();
	if (ReadinToken1.id == LEX_ID) {
		auto SavedLexPos2 = lex.getNowPos();
		auto SavedRoot2 = root;
		auto ReadinToken2 = lex.readNextToken();
		if (ReadinToken2.id == LEX_ASSIGN) {
			auto SavedLexPos3 = lex.getNowPos();
			auto SavedRoot3 = root;
			if (parseRvalue()) {
				root = shared_ptr<Node>(new VarDeclrAssignNode(ReadinToken1.name, root));
				return 1;
			}
			refresh();
			lex.setNowPos(SavedLexPos3);
			root = SavedRoot3;
		}
		lex.setNowPos(SavedLexPos2);
		root = SavedRoot2;
		root = shared_ptr<Node>(new VarDeclrNode(ReadinToken1.name));
		return 1;
	}
	lex.setNowPos(SavedLexPos1);
	root = SavedRoot1;
	return 0;
}
bool parseFuncDef() {
	auto SavedLexPos1 = lex.getNowPos();
	auto SavedRoot1 = root;
	auto ReadinToken1 = lex.readNextToken();
	if (ReadinToken1.id == LEX_FUNC) {
		auto SavedLexPos2 = lex.getNowPos();
		auto SavedRoot2 = root;
		auto ReadinToken2 = lex.readNextToken();
		if (ReadinToken2.id == LEX_LP) {
			auto SavedLexPos3 = lex.getNowPos();
			auto SavedRoot3 = root;
			if (parseArguDef()) {
				auto SavedLexPos4 = lex.getNowPos();
				auto SavedRoot4 = root;
				auto ReadinToken4 = lex.readNextToken();
				if (ReadinToken4.id == LEX_RP) {
					auto SavedLexPos5 = lex.getNowPos();
					auto SavedRoot5 = root;
					auto ReadinToken5 = lex.readNextToken();
					if (ReadinToken5.id == LEX_LCB) {
						auto SavedLexPos6 = lex.getNowPos();
						auto SavedRoot6 = root;
						if (parseStmts()) {
							auto SavedLexPos7 = lex.getNowPos();
							auto SavedRoot7 = root;
							auto ReadinToken7 = lex.readNextToken();
							if (ReadinToken7.id == LEX_RCB) {
								root = shared_ptr<Node>(new FuncDefNode(SavedRoot4, root));
								return 1;
							}
							lex.setNowPos(SavedLexPos7);
							root = SavedRoot7;
						}
						refresh();
						lex.setNowPos(SavedLexPos6);
						root = SavedRoot6;
					}
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
	return 0;
}

bool parseArguDef() {
	auto SavedLexPos1 = lex.getNowPos();
	auto SavedRoot1 = root;
	if (parseLValue()) {
		int flag = 1;
		while (flag) {
			flag = 0;
			auto SavedLexPos3 = lex.getNowPos();
			auto SavedRoot3 = root;
			auto ReadinToken3 = lex.readNextToken();
			if (ReadinToken3.id == LEX_COM) {
				auto SavedLexPos4 = lex.getNowPos();
				auto SavedRoot4 = root;
				if (parseLValue()) {
					root = shared_ptr<Node>(new ArguDefNode(SavedRoot4, root));
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
	refresh();
	return 1;
}
bool parseValueGroup() {
	auto SavedLexPos1 = lex.getNowPos();
	auto SavedRoot1 = root;
	auto ReadinToken1 = lex.readNextToken();
	if (ReadinToken1.id == LEX_LP) {
		auto SavedLexPos2 = lex.getNowPos();
		auto SavedRoot2 = root;
		if (parseRvalue()) {
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
	if (parseLValue()) {
		auto SavedLexPos2 = lex.getNowPos();
		auto SavedRoot2 = root;
		auto ReadinToken2 = lex.readNextToken();
		if (ReadinToken2.id == LEX_LP) {
			auto SavedLexPos3 = lex.getNowPos();
			auto SavedRoot3 = root;
			if (parseArgu()) {
				auto SavedLexPos4 = lex.getNowPos();
				auto SavedRoot4 = root;
				auto ReadinToken4 = lex.readNextToken();
				if (ReadinToken4.id == LEX_RP) {
					root = shared_ptr<Node>(new FuncCallNode(SavedRoot2, root));
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
		return 1;
	}
	refresh();
	lex.setNowPos(SavedLexPos1);
	root = SavedRoot1;
	SavedLexPos1 = lex.getNowPos();
	SavedRoot1 = root;
	auto ReadinToken1 = lex.readNextToken();
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
bool parseArgu() {
	auto SavedLexPos1 = lex.getNowPos();
	auto SavedRoot1 = root;
	if (parseRvalue()) {
		int flag = 1;
		while (flag) {
			flag = 0;
			auto SavedLexPos3 = lex.getNowPos();
			auto SavedRoot3 = root;
			auto ReadinToken3 = lex.readNextToken();
			if (ReadinToken3.id == LEX_COM) {
				auto SavedLexPos4 = lex.getNowPos();
				auto SavedRoot4 = root;
				if (parseRvalue()) {
					root = shared_ptr<Node>(new ArguNode(SavedRoot4, root));
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
	refresh();


	return 1;
}

bool parseLValue() {
	auto SavedLexPos1 = lex.getNowPos();
	auto SavedRoot1 = root;
	if (parseIDBase()) {
		int flag = 1;
		while (flag) {
			flag = 0;
			auto SavedLexPos3 = lex.getNowPos();
			auto SavedRoot3 = root;
			if (parseSonExpr()) {
				root = shared_ptr<Node>(new SonNode(SavedRoot3, root));
				flag = 1;
				continue;
			}
			refresh();
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
bool parseSonExpr() {
	auto SavedLexPos1 = lex.getNowPos();
	auto SavedRoot1 = root;
	auto ReadinToken1 = lex.readNextToken();
	if (ReadinToken1.id == LEX_LSB) {
		auto SavedLexPos2 = lex.getNowPos();
		auto SavedRoot2 = root;
		if (parseExpr()) {
			auto SavedLexPos3 = lex.getNowPos();
			auto SavedRoot3 = root;
			auto ReadinToken3 = lex.readNextToken();
			if (ReadinToken3.id == LEX_RSB) {
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
	if (ReadinToken1.id == LEX_POT) {
		auto SavedLexPos2 = lex.getNowPos();
		auto SavedRoot2 = root;
		if (parseIDBase()) {
			return 1;
		}
		refresh();
		lex.setNowPos(SavedLexPos2);
		root = SavedRoot2;
	}
	lex.setNowPos(SavedLexPos1);
	root = SavedRoot1;
	return 0;
}
bool parseIDBase() {
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
	if (parseBorExpr()) {
		int flag = 1;
		while (flag) {
			flag = 0;
			auto SavedLexPos3 = lex.getNowPos();
			auto SavedRoot3 = root;
			auto ReadinToken3 = lex.readNextToken();
			if (ReadinToken3.id == LEX_AND) {
				auto SavedLexPos4 = lex.getNowPos();
				auto SavedRoot4 = root;
				if (parseBorExpr()) {
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
bool parseBorExpr() {
	auto SavedLexPos1 = lex.getNowPos();
	auto SavedRoot1 = root;
	if (parseBandExpr()) {
		int flag = 1;
		while (flag) {
			flag = 0;
			auto SavedLexPos3 = lex.getNowPos();
			auto SavedRoot3 = root;
			auto ReadinToken3 = lex.readNextToken();
			if (ReadinToken3.id == LEX_BOR) {
				auto SavedLexPos4 = lex.getNowPos();
				auto SavedRoot4 = root;
				if (parseBandExpr()) {
					root = shared_ptr<Node>(new BorNode(SavedRoot4, root));
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
bool parseBandExpr() {
	auto SavedLexPos1 = lex.getNowPos();
	auto SavedRoot1 = root;
	if (parseEqCompExpr()) {
		int flag = 1;
		while (flag) {
			flag = 0;
			auto SavedLexPos3 = lex.getNowPos();
			auto SavedRoot3 = root;
			auto ReadinToken3 = lex.readNextToken();
			if (ReadinToken3.id == LEX_BAND) {
				auto SavedLexPos4 = lex.getNowPos();
				auto SavedRoot4 = root;
				if (parseEqCompExpr()) {
					root = shared_ptr<Node>(new BandNode(SavedRoot4, root));
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
bool parseEqCompExpr() {
	auto SavedLexPos1 = lex.getNowPos();
	auto SavedRoot1 = root;
	if (parseCompExpr()) {
		int flag = 1;
		while (flag) {
			flag = 0;
			auto SavedLexPos3 = lex.getNowPos();
			auto SavedRoot3 = root;
			auto ReadinToken3 = lex.readNextToken();
			if (ReadinToken3.id == LEX_NEQ) {
				auto SavedLexPos4 = lex.getNowPos();
				auto SavedRoot4 = root;
				if (parseCompExpr()) {
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
				if (parseCompExpr()) {
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


