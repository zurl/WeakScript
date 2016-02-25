#pragma once
#include "common.h"
#include "Lex.h"
#ifndef PARSER_H
#define PARSER_H
class Value {
public:
	Value();
	Value(const string &t);
	Value(const long long &t);
	Value(const double &t);
	Value(const Value &t);
	~Value();

	Value & operator= (const Value & t);

	Value operator+ (const Value & t);
	Value operator- (const Value & t);
	Value operator* (const Value & t);
	Value operator/ (const Value & t);
	Value operator% (const Value & t);

	Value operator&& (const Value & t);
	Value operator|| (const Value & t);
	Value operator! ();

	Value operator- ();
	Value operator~ ();
	//Value operator& (const Value & t);
	//Value operator| (const Value & t);


	Value operator!= (const Value & t);
	Value operator== (const Value & t);
	Value operator> (const Value & t);
	Value operator< (const Value & t);
	Value operator>= (const Value & t);
	Value operator<= (const Value & t);

	bool isTrue();
	enum class Type {
		Null, Int, Real, Str
	};
	Type type;
	union {
		long long Int;
		double Real;
		string * Str;
	} data;
};
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
class UnaryNode : public Node {
protected:
	shared_ptr<Node> son;
public:
	UnaryNode(shared_ptr<Node>  _s);
	void visitson(int x);
	virtual void del();
};
class BinaryNode : public Node {
protected:
	shared_ptr<Node> left, right;
public:
	BinaryNode(shared_ptr<Node>  _l, shared_ptr<Node>  _r);
	void visitson(int x);
	virtual void del();
};
class TernaryNode : public Node {
protected:
	shared_ptr<Node> left, mid, right;
public:
	TernaryNode(shared_ptr<Node> _l, shared_ptr<Node> _m, shared_ptr<Node> _r);
	void visitson(int x);
	virtual void del();
};
class ValueNode : public UnitNode {
public:
	Value val;
	ValueNode(string _value);
	ValueNode(double _value);
	ValueNode(long long _value);
	virtual void visit(int x);
	virtual Value eval();
}; class StmtsNode : public BinaryNode {
public:
	StmtsNode(shared_ptr<Node> a, shared_ptr<Node> b);
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
class BlockNode : public UnaryNode {
public:
	BlockNode(shared_ptr<Node> a);
	virtual void visit(int x);
	virtual Value eval();
};
class IfNode : public BinaryNode {
public:
	IfNode(shared_ptr<Node> a, shared_ptr<Node> b);
	virtual void visit(int x);
	virtual Value eval();
};
class DeclrNode : public UnitNode {
public:
	string value;
	DeclrNode(string _value);
	virtual void visit(int x);
	virtual Value eval();
};
class AssignNode : public BinaryNode {
public:
	AssignNode(shared_ptr<Node> a, shared_ptr<Node> b);
	virtual void visit(int x);
	virtual Value eval();
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
class IDNode : public UnitNode {
public:
	string value;
	IDNode(string _value);
	virtual void visit(int x);
	virtual Value eval();
};
#endif // !PARSER_H

