#pragma once
#include<iostream>
#include<vector>
#ifndef WS_DLL_H
#define WS_DLL_H

using std::string;
using std::vector;

class Function;
class Object;
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

#endif

