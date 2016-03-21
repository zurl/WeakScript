#pragma once
#include "common.h"
#ifndef EVAL_H
#define EVAL_H

using namespace std;

class Function;
class Object;
class FuncDefNode;
class Value {

public:
	Value();
	Value(const bool &t);
	Value(const string &t);
	Value(const long long &t);
	Value(const double &t);
	Value(const Value &t);
	Value(Function *t);
	Value(Object *t);
	~Value();

	Value & operator= (const Value & t);

	Value operator+ (const Value & t);
	Value operator++ ();
	Value operator-- ();

	Value operator- (const Value & t);
	Value operator* (const Value & t);
	Value operator/ (const Value & t);
	Value operator% (const Value & t);

	Value operator&& (const Value & t);
	Value operator|| (const Value & t);
	Value operator! ();

	Value operator- ();
	Value operator~ ();
	Value operator& (const Value & t);
	Value operator| (const Value & t);


	Value operator!= (const Value & t);
	Value operator== (const Value & t);
	Value operator> (const Value & t);
	Value operator< (const Value & t);
	Value operator>= (const Value & t);
	Value operator<= (const Value & t);

	bool isTrue();
	string toString()const;
	enum class Type {
		Null, Int, Real, Str, Obj, Func, Boolean
	};
	Type type;
	union {
		bool Boolean;
		long long Int;
		double Real;
		string * Str;
		Function * Func;
		Object * Obj;
	}data;
};

class Object {
public:
	bool mark;
	unordered_map<int, Value*> data;
	Object();
	Value & __getVar(int name);
	Value & getVar(int name);
	string toString();
	~Object();
};
class VariableTable {
public:
	string name;
	shared_ptr<VariableTable> prev;
	unordered_map<int, Value*> *table;
	int isCreatePointer = 1;
	VariableTable(string _name);
	VariableTable(shared_ptr<VariableTable> t, string _name);
	void defineVar(int name);
	Value & getVarOld(const int name);
	Value & getVar(const int name);
	void showAllVariable();
	~VariableTable();
};

class ReturnException : public MyExpection {
private:
	Value data;
public:
	ReturnException();
	ReturnException(Value x);
	Value getValue();
};

class Function : public Object {
public:
	//bool mark;

	shared_ptr<VariableTable> CallerTable;
	shared_ptr<FuncDefNode> func;
	Function(FuncDefNode * t);
};


ostream & operator<< (ostream &, const Value &);
using SysFunc = Value(*)();



#endif

