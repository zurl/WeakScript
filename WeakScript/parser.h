#include "eval.h"

#ifndef PARSER_H
#define PARSER_H

class Node {
public:
	virtual void visit(int x) = 0;
	virtual void del() = 0;
	virtual Value eval() = 0;
};

class UnitNode : public Node {
public:
	UnitNode();
	void visitson(int x);
	virtual void del();
};
#include "WsExport.h"
class ModuleFuncNode : public UnitNode {
public:
	ExportSysFunc * func;
	ModuleFuncNode(ExportSysFunc* x);
	virtual void visit(int x);
	virtual Value eval();
};
class SysFuncNode : public UnitNode {
public:
	SysFunc func;
	SysFuncNode(SysFunc x);
	virtual void visit(int x);
	virtual Value eval();
};
class UnaryNode : public Node {
public:
	shared_ptr<Node> son;
public:
	UnaryNode(shared_ptr<Node>  _s);
	void visitson(int x);
	virtual void del();
};
class BinaryNode : public Node {
public:
	shared_ptr<Node> left, right;
public:
	BinaryNode(shared_ptr<Node>  _l, shared_ptr<Node>  _r);
	void visitson(int x);
	virtual void del();
};
class TernaryNode : public Node {
public:
	shared_ptr<Node> left, mid, right;
public:
	TernaryNode(shared_ptr<Node> _l, shared_ptr<Node> _m, shared_ptr<Node> _r);
	void visitson(int x);
	virtual void del();
};
class QuadNode : public Node {
public:
	shared_ptr<Node> left, midleft, midright, right;
public:
	QuadNode(shared_ptr<Node> _l, shared_ptr<Node> _ml, shared_ptr<Node> _mr, shared_ptr<Node> _r);
	void visitson(int x);
	virtual void del();
};
class ValueNode : public UnitNode {
public:
	Value val;
	ValueNode(string _value);
	ValueNode(double _value);
	ValueNode(long long _value);
	ValueNode(bool  _value);
	ValueNode();
	virtual void visit(int x);
	virtual Value eval();
};

class VarDeclrsNode : public BinaryNode {
public:
	VarDeclrsNode(shared_ptr<Node> a, shared_ptr<Node> b);
	virtual void visit(int x);
	virtual Value eval();
};
class VarDeclrAssignNode : public UnaryNode {
public:
	int value;
	VarDeclrAssignNode(string _value, shared_ptr<Node> a);
	virtual void visit(int x);
	virtual Value eval();
};
class VarDeclrNode : public UnitNode {
public:
	int value;
	VarDeclrNode(string _value);
	virtual void visit(int x);
	virtual Value eval();
};
class StmtsNode : public BinaryNode {
public:
	StmtsNode(shared_ptr<Node> a, shared_ptr<Node> b);
	virtual void visit(int x);
	virtual Value eval();
}; 
class NewFuncCallNode : public BinaryNode {
public:
	NewFuncCallNode(shared_ptr<Node> a, shared_ptr<Node> b);
	virtual void visit(int x);
	virtual Value eval();
};
class ForNode : public QuadNode {
public:
	ForNode(shared_ptr<Node> a, shared_ptr<Node> b, shared_ptr<Node> c, shared_ptr<Node> d);
	virtual void visit(int x);
	virtual Value eval();
};
class WhileNode : public BinaryNode {
public:
	WhileNode(shared_ptr<Node> a, shared_ptr<Node> b);
	virtual void visit(int x);
	virtual Value eval();
};
class IfElseNode : public TernaryNode {
public:
	IfElseNode(shared_ptr<Node> a, shared_ptr<Node> b, shared_ptr<Node> c);
	virtual void visit(int x);
	virtual Value eval();
};
class IfNode : public BinaryNode {
public:
	IfNode(shared_ptr<Node> a, shared_ptr<Node> b);
	virtual void visit(int x);
	virtual Value eval();
};
class BlockNode : public UnaryNode {
public:
	BlockNode(shared_ptr<Node> a);
	virtual void visit(int x);
	virtual Value eval();
};

class AssignNode : public BinaryNode {
public:
	AssignNode(shared_ptr<Node> a, shared_ptr<Node> b);
	virtual void visit(int x);
	virtual Value eval();
};
class ReturnNode : public UnaryNode {
public:
	ReturnNode(shared_ptr<Node> a);
	virtual void visit(int x);
	virtual Value eval();
};
class ReturnNullNode : public UnaryNode {
public:
	ReturnNullNode(shared_ptr<Node> a);
	virtual void visit(int x);
	virtual Value eval();
};
class ContinueNode : public UnitNode {
public:
	ContinueNode();
	virtual void visit(int x);
	virtual Value eval();
};
class BreakNode : public UnitNode {
public:
	BreakNode();
	virtual void visit(int x);
	virtual Value eval();
};
class FuncDefNode : public BinaryNode {
public:
	FuncDefNode(shared_ptr<Node> a, shared_ptr<Node> b);
	virtual void visit(int x);
	virtual Value eval();
	//sp
};
class ArguDefNode : public BinaryNode {
public:
	ArguDefNode(shared_ptr<Node> a, shared_ptr<Node> b);
	virtual void visit(int x);
	virtual Value eval();
};
class RevNode : public UnaryNode {
public:
	RevNode(shared_ptr<Node> a);
	virtual void visit(int x);
	virtual Value eval();
};
class NotNode : public UnaryNode {
public:
	NotNode(shared_ptr<Node> a);
	virtual void visit(int x);
	virtual Value eval();
};
class NegNode : public UnaryNode {
public:
	NegNode(shared_ptr<Node> a);
	virtual void visit(int x);
	virtual Value eval();
};
class FuncCallNode : public BinaryNode {
public:
	FuncCallNode(shared_ptr<Node> a, shared_ptr<Node> b);
	virtual void visit(int x);
	virtual Value eval();
};
class ArguNode : public BinaryNode {
public:
	ArguNode(shared_ptr<Node> a, shared_ptr<Node> b);
	virtual void visit(int x);
	virtual Value eval();
};
class ILvalue {
public:
	virtual Value & get();
	virtual string getName();
};
class ObjDefNode : public UnaryNode {
public:
	ObjDefNode(shared_ptr<Node> a);
	virtual void visit(int x);
	virtual Value eval();
}; class ForeachNode : public TernaryNode {
public:
	ForeachNode(shared_ptr<Node> a, shared_ptr<Node> b, shared_ptr<Node> c);
	virtual void visit(int x);
	virtual Value eval();
};
class JsonGroupNode : public BinaryNode {
public:
	JsonGroupNode(shared_ptr<Node> a, shared_ptr<Node> b);
	virtual void visit(int x);
	virtual Value eval();
};
class ArrayDefNode : public UnaryNode {
public:
	ArrayDefNode(shared_ptr<Node> a);
	virtual void visit(int x);
	virtual Value eval();
};
class ArrayDefGroupNode : public BinaryNode {
public:
	ArrayDefGroupNode(shared_ptr<Node> a, shared_ptr<Node> b);
	virtual void visit(int x);
	virtual Value eval();
};
class JsonNode : public BinaryNode {
public:
	JsonNode(shared_ptr<Node> a, shared_ptr<Node> b);
	virtual void visit(int x);
	virtual Value eval();
};
class SelfSubNode : public UnaryNode {
public:
	SelfSubNode(shared_ptr<Node> a);
	virtual void visit(int x);
	virtual Value eval();
};
class SelfAddNode : public UnaryNode {
public:
	SelfAddNode(shared_ptr<Node> a);
	virtual void visit(int x);
	virtual Value eval();
};
class IDNode : public UnitNode , public ILvalue {
public:
	int value;
	IDNode(string _value);
	virtual void visit(int x);
	virtual Value eval();
	virtual Value & get();
	virtual string getName();
};
class SonNode : public BinaryNode, public ILvalue {
public:
	SonNode(shared_ptr<Node> a, shared_ptr<Node> b);
	virtual void visit(int x);
	virtual Value eval();
	virtual Value & get();
	virtual string getName();
};


class OrNode : public BinaryNode {
public:
	OrNode(shared_ptr<Node> a, shared_ptr<Node> b);
	virtual void visit(int x);
	virtual Value eval();
};
class AndNode : public BinaryNode {
public:
	AndNode(shared_ptr<Node> a, shared_ptr<Node> b);
	virtual void visit(int x);
	virtual Value eval();
};
class BorNode : public BinaryNode {
public:
	BorNode(shared_ptr<Node> a, shared_ptr<Node> b);
	virtual void visit(int x);
	virtual Value eval();
};
class BandNode : public BinaryNode {
public:
	BandNode(shared_ptr<Node> a, shared_ptr<Node> b);
	virtual void visit(int x);
	virtual Value eval();
};
class NeqNode : public BinaryNode {
public:
	NeqNode(shared_ptr<Node> a, shared_ptr<Node> b);
	virtual void visit(int x);
	virtual Value eval();
};
class EqNode : public BinaryNode {
public:
	EqNode(shared_ptr<Node> a, shared_ptr<Node> b);
	virtual void visit(int x);
	virtual Value eval();
};
class NltNode : public BinaryNode {
public:
	NltNode(shared_ptr<Node> a, shared_ptr<Node> b);
	virtual void visit(int x);
	virtual Value eval();
};
class NgtNode : public BinaryNode {
public:
	NgtNode(shared_ptr<Node> a, shared_ptr<Node> b);
	virtual void visit(int x);
	virtual Value eval();
};
class LtNode : public BinaryNode {
public:
	LtNode(shared_ptr<Node> a, shared_ptr<Node> b);
	virtual void visit(int x);
	virtual Value eval();
};
class GtNode : public BinaryNode {
public:
	GtNode(shared_ptr<Node> a, shared_ptr<Node> b);
	virtual void visit(int x);
	virtual Value eval();
};
class SubNode : public BinaryNode {
public:
	SubNode(shared_ptr<Node> a, shared_ptr<Node> b);
	virtual void visit(int x);
	virtual Value eval();
};
class AddNode : public BinaryNode {
public:
	AddNode(shared_ptr<Node> a, shared_ptr<Node> b);
	virtual void visit(int x);
	virtual Value eval();
};
class ModNode : public BinaryNode {
public:
	ModNode(shared_ptr<Node> a, shared_ptr<Node> b);
	virtual void visit(int x);
	virtual Value eval();
};
class DivNode : public BinaryNode {
public:
	DivNode(shared_ptr<Node> a, shared_ptr<Node> b);
	virtual void visit(int x);
	virtual Value eval();
};
class MulNode : public BinaryNode {
public:
	MulNode(shared_ptr<Node> a, shared_ptr<Node> b);
	virtual void visit(int x);
	virtual Value eval();
};
class NullNode : public UnitNode {
public:
	NullNode();
	virtual void visit(int x);
	virtual Value eval();
};
class SimpleNode : public UnaryNode {
public:
	SimpleNode(shared_ptr<Node> a);
	virtual void visit(int x);
	virtual Value eval();
};
#endif // !PARSER_H

