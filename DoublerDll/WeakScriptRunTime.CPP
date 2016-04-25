#include "WsExportCommon.h"

Value::Value() {

	if (type == Type::Str)
	{
		delete data.Str; type = Type::Null;
	}
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
		{delete data.Str; type = Type::Null; }
	}
}
Value & Value::operator= (const Value & t) {
	if (type == Type::Str)
	{
		delete data.Str; type = Type::Null;
	}
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
