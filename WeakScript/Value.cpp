#include "common.h"
#include "eval.h"
using namespace std;
extern string itos(long long x);
extern string dtos(double x);
class CalTypeException : public MyExpection {
private:
	int flag;
	Value c, d;
public:
	CalTypeException(Value a, Value b)
		:c(a), d(b), flag(1) {

	}
	CalTypeException(Value a) :c(a), flag(0) {

	}
	virtual string getErrorMessage() {
		if (flag)
			return "TypeError: unsupported operand type(s) with \"" + c.toString() + "\" and \"" + d.toString() + "\"";
		else
			return "TypeError: unsupported operand type(s) with\"" + c.toString();
	}
};


Value::Value() {

	if (type == Type::Str)
		{delete data.Str;type = Type::Null;}
	type = Type::Null;
}
Value::Value(const bool &t) {
	this->type = Type::Boolean;
	this->data.Boolean = t;
}
Value::Value(const string &t) {
	this->type = Type::Str;
	this->data.Str = new string(t);
}
Value::Value(const long long &t) {
	this->type = Type::Int;
	this->data.Int = t;
}
Value::Value(const double &t) {
	this->type = Type::Real;
	this->data.Real = t;
}

string Value::toString()const {
	switch (this->type) {
	case Type::Boolean:
		return this->data.Boolean ? "true" : "false";
	case Type::Int:
		return itos(this->data.Int);
	case Type::Real:
		return dtos(this->data.Real);
	case Type::Str:
		return *this->data.Str;
	case Type::Func:
		return "[Function]";
	case Type::Null:
		return "Null";
	case Type::Obj:
		return this->data.Obj->toString();
	}
	return "";
}

Value::Value(const Value &t) {
	switch (t.type) {
	case Type::Boolean:
		this->type = Type::Boolean;
		this->data.Boolean = t.data.Boolean;
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
	case Type::Func:
		this->type = Type::Func;
		this->data.Func = t.data.Func;
		break;
	case Type::Obj:
		this->type = Type::Obj;
		this->data.Obj = t.data.Obj;
	}
}
Value::~Value() {
	if (type == Type::Str) {
		{delete data.Str;type = Type::Null;}
	}
}
Value & Value::operator= (const Value & t) {
	if (type == Type::Str)
		{delete data.Str;type = Type::Null;}
	switch (t.type) {
	case Type::Boolean:
		this->type = Type::Boolean;
		this->data.Boolean = t.data.Boolean;
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
	case Type::Func:
		this->type = Type::Func;
		this->data.Func = t.data.Func;
		break;
	case Type::Obj:
		this->type = Type::Obj;
		this->data.Obj = t.data.Obj;
	}
	return *this;
}
Value::Value(Function *t) {
	if (type == Type::Str)
		{delete data.Str;type = Type::Null;}
	this->type = Type::Func;
	this->data.Func = t;
}
Value::Value(Object *t) {
	if (type == Type::Str)
		{delete data.Str;type = Type::Null;}
	this->type = Type::Obj;
	this->data.Obj = t;
}

bool Value::isTrue() {
	//All Type::  //To Modify
	if (this->type == Type::Null)
		return false;
	if (this->type == Type::Int && this->data.Int == 0)
		return false;
	if (this->type == Type::Boolean && this->data.Boolean == false)
		return false;
	return true;
}


Value Value::operator++ () {
	if (this->type == Type::Boolean) {
		this->type = Type::Int;
		this->data.Int = this->data.Boolean + 1;
		return Value();
	}
	if (this->type == Type::Int) {
		this->data.Int++;
		return Value();
	}
	if (this->type == Type::Real) {
		this->data.Real++;
		return Value();
	}
	throw CalTypeException(*this);
}
Value Value::operator-- () {
	if (this->type == Type::Int) {
		this->data.Int--;
		return *this;
	}
	if (this->type == Type::Real) {
		this->data.Real--;
		return *this;
	}
	throw CalTypeException(*this);
}
Value Value::operator- () {
	if (this->type == Type::Int)
		return Value(-this->data.Int);
	if (this->type == Type::Real)
		return Value(-this->data.Real);
	throw CalTypeException(*this);
}
string btos(bool a) {
	return a == true ? "true" : "false";
}
Value Value::operator+ (const Value &t) {

	//For Str
	if (this->type == Type::Str && t.type == Type::Boolean)
		return Value(*this->data.Str + btos(t.data.Boolean));
	if (this->type == Type::Boolean && t.type == Type::Str)
		return Value(btos(this->data.Boolean) + *t.data.Str);
	if (this->type == Type::Str && t.type == Type::Str)
		return Value(*this->data.Str + *t.data.Str);
	if (this->type == Type::Int && t.type == Type::Str)
		return Value(itos(this->data.Int) + *t.data.Str);
	if (this->type == Type::Real && t.type == Type::Str)
		return Value(dtos(this->data.Real) + *t.data.Str);
	if (this->type == Type::Str && t.type == Type::Int)
		return Value(*this->data.Str + itos(t.data.Int));
	if (this->type == Type::Str && t.type == Type::Real)
		return Value(*this->data.Str + dtos(t.data.Real));
	//For Num
	if (this->type == Type::Int && t.type == Type::Int)
		return Value(this->data.Int + t.data.Int);
	if (this->type == Type::Real && t.type == Type::Int)
		return Value(this->data.Real + t.data.Int);
	if (this->type == Type::Real && t.type == Type::Real)
		return Value(this->data.Real + t.data.Real);
	if (this->type == Type::Int  && t.type == Type::Real)
		return Value(this->data.Int + t.data.Real);
	if (this->type == Type::Real && t.type == Type::Boolean)
		return Value(this->data.Real + t.data.Boolean);
	if (this->type == Type::Int  && t.type == Type::Boolean)
		return Value(this->data.Int + t.data.Boolean);
	if (this->type == Type::Boolean && t.type == Type::Real)
		return Value(this->data.Boolean + t.data.Real);
	if (this->type == Type::Boolean  && t.type == Type::Int)
		return Value(this->data.Boolean + t.data.Int);
	throw CalTypeException(*this, t);
}
Value Value::operator- (const Value &t) {
	if (this->type == Type::Int && t.type == Type::Int)
		return Value(this->data.Int - t.data.Int);
	if (this->type == Type::Real && t.type == Type::Int)
		return Value(this->data.Real - t.data.Int);
	if (this->type == Type::Real && t.type == Type::Real)
		return Value(this->data.Real - t.data.Real);
	if (this->type == Type::Int  && t.type == Type::Real)
		return Value(this->data.Int - t.data.Real);
	if (this->type == Type::Real && t.type == Type::Boolean)
		return Value(this->data.Real - t.data.Boolean);
	if (this->type == Type::Int  && t.type == Type::Boolean)
		return Value(this->data.Int - t.data.Boolean);
	if (this->type == Type::Boolean && t.type == Type::Real)
		return Value(this->data.Boolean - t.data.Real);
	if (this->type == Type::Boolean  && t.type == Type::Int)
		return Value(this->data.Boolean - t.data.Int);
	throw CalTypeException(*this, t);
}
Value Value::operator* (const Value &t) {
	if (this->type == Type::Int && t.type == Type::Int)
		return Value(this->data.Int * t.data.Int);
	if (this->type == Type::Real && t.type == Type::Int)
		return Value(this->data.Real * t.data.Int);
	if (this->type == Type::Real && t.type == Type::Real)
		return Value(this->data.Real * t.data.Real);
	if (this->type == Type::Int  && t.type == Type::Real)
		return Value(this->data.Int * t.data.Real);
	if (this->type == Type::Real && t.type == Type::Boolean)
		return Value(this->data.Real * t.data.Boolean);
	if (this->type == Type::Int  && t.type == Type::Boolean)
		return Value(this->data.Int * t.data.Boolean);
	if (this->type == Type::Boolean && t.type == Type::Real)
		return Value(this->data.Boolean * t.data.Real);
	if (this->type == Type::Boolean  && t.type == Type::Int)
		return Value(this->data.Boolean * t.data.Int);
	throw CalTypeException(*this, t);
}
Value Value::operator/ (const Value &t) {
	if (this->type == Type::Int && t.type == Type::Int)
		return Value(this->data.Int / t.data.Int);
	if (this->type == Type::Real && t.type == Type::Int)
		return Value(this->data.Real / t.data.Int);
	if (this->type == Type::Real && t.type == Type::Real)
		return Value(this->data.Real / t.data.Real);
	if (this->type == Type::Int  && t.type == Type::Real)
		return Value(this->data.Int / t.data.Real);
	throw CalTypeException(*this, t);
}
Value Value::operator% (const Value &t) {
	if (this->type == Type::Int && t.type == Type::Int)
		return Value(this->data.Int % t.data.Int);
	throw CalTypeException(*this, t);
}

Value Value::operator&& (const Value &t) {
	if (this->type == Type::Int && t.type == Type::Int && this->data.Int != 0 && t.data.Int != 0
		&& this->type == Type::Boolean && t.type == Type::Int && this->data.Boolean != 0 && t.data.Int != 0
		&& this->type == Type::Int && t.type == Type::Boolean && this->data.Int != 0 && t.data.Boolean != 0)
		return Value(true);
	return Value(false);
}
Value Value::operator|| (const Value &t) {
	if (this->type == Type::Int && t.type == Type::Int && this->data.Int == 0 && t.data.Int == 0
		|| this->type == Type::Boolean && t.type == Type::Int && this->data.Boolean == 0 && t.data.Int == 0
		|| this->type == Type::Int && t.type == Type::Boolean && this->data.Int == 0 && t.data.Boolean == 0)
		return Value(false);
	return Value(true);
}
Value Value::operator! () {
	if (this->type == Type::Int)
		return Value(!this->data.Int);
	if (this->type == Type::Boolean)
		return Value(!this->data.Boolean);
	throw CalTypeException(*this);
}

Value Value::operator~ () {
	if (this->type == Type::Int)
		return Value(~this->data.Int);
	throw CalTypeException(*this);
}
Value Value::operator& (const Value &t) {
	if (this->type == Type::Int && t.type == Type::Int)
		return Value(this->data.Int & t.data.Int);
	throw CalTypeException(*this, t);
}
Value Value::operator| (const Value &t) {
	if (this->type == Type::Int && t.type == Type::Int)
		return Value(this->data.Int | t.data.Int);
	throw CalTypeException(*this, t);
}

Value Value::operator!= (const Value &t) {
	return Value(!this->operator==(t).data.Int);
}
Value Value::operator== (const Value &t) {
	if (this->type != t.type)
		return Value(false);
	if (this->type == Type::Int && this->data.Int == t.data.Int
		|| this->type == Type::Real && this->data.Real == t.data.Real
		|| this->type == Type::Str && *this->data.Str == *t.data.Str
		|| this->type == Type::Func && this->data.Func == t.data.Func
		|| this->type == Type::Func && this->data.Obj == t.data.Obj
		)
		return Value(true);
	return Value(false);
}
Value Value::operator> (const Value &t) {
	if (this->type == Type::Int && t.type == Type::Int)
		return Value((this->data.Int > t.data.Int));
	if (this->type == Type::Real && t.type == Type::Int)
		return Value((this->data.Real > t.data.Int));
	if (this->type == Type::Real && t.type == Type::Real)
		return Value((this->data.Real > t.data.Real));
	if (this->type == Type::Int  && t.type == Type::Real)
		return Value((this->data.Int > t.data.Real));
	throw CalTypeException(*this, t);
}
Value Value::operator< (const Value &t) {
	if (this->type == Type::Int && t.type == Type::Int)
		return Value((this->data.Int < t.data.Int));
	if (this->type == Type::Real && t.type == Type::Int)
		return Value((this->data.Real < t.data.Int));
	if (this->type == Type::Real && t.type == Type::Real)
		return Value((this->data.Real < t.data.Real));
	if (this->type == Type::Int  && t.type == Type::Real)
		return Value((this->data.Int < t.data.Real));
	throw CalTypeException(*this, t);
}
Value Value::operator>= (const Value &t) {
	if (this->type == Type::Int && t.type == Type::Int)
		return Value((this->data.Int >= t.data.Int));
	if (this->type == Type::Real && t.type == Type::Int)
		return Value((this->data.Real >= t.data.Int));
	if (this->type == Type::Real && t.type == Type::Real)
		return Value((this->data.Real >= t.data.Real));
	if (this->type == Type::Int  && t.type == Type::Real)
		return Value((this->data.Int >= t.data.Real));
	throw CalTypeException(*this, t);
}
Value Value::operator<= (const Value &t) {
	if (this->type == Type::Int && t.type == Type::Int)
		return Value((this->data.Int <= t.data.Int));
	if (this->type == Type::Real && t.type == Type::Int)
		return Value((this->data.Real <= t.data.Int));
	if (this->type == Type::Real && t.type == Type::Real)
		return Value((this->data.Real <= t.data.Real));
	if (this->type == Type::Int  && t.type == Type::Real)
		return Value((this->data.Int <= t.data.Real));
	throw CalTypeException(*this, t);
}