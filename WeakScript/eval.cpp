#include "parser.h"

class MyExpection   {
	//Abs Class
};
class CalTypeException : public MyExpection {
public:
	CalTypeException(Value a, Value b) {

	}
	CalTypeException(Value a) {

	}
}; 
class UnexpectRunTimeException : public MyExpection{

};
class UnableAssignValueException : public MyExpection {

};
class UndefinedVariableException : public MyExpection {
public:
	UndefinedVariableException(int name) {

	}
};
class UnableCallVarException : public MyExpection {
public:
	UnableCallVarException(int name) {

	}
};
class RedefinedVariableException : public MyExpection {
public:
	RedefinedVariableException(int name) {
		
	}
};
class BreakException : public MyExpection {

};
class ContinueException : public MyExpection {
	
};
class ReturnException : public MyExpection {
private:
	Value data;
public:
	ReturnException() {
		this->data = Value();
	}
	ReturnException(Value x) {
		this->data = x;
	}
	Value getValue() {
		return this->data;
	}
};
#include<unordered_map>	
class VariableTable {
public:
	VariableTable *prev;
	map<int,Value*> table;
	VariableTable() {
		prev = nullptr;  
	}
	VariableTable(VariableTable * t) {
		prev = t;
	}
	void DefineVar( int name ) {
		auto t = table.find(name);
		if (t != table.end()) 
			throw RedefinedVariableException(name);
		this->table.emplace(name, new Value());	
	}
	Value & getVarOld( const int & name )  {
		auto t = table.find(name);
		if (t == table.end()) {
			if (prev == nullptr)
				throw UndefinedVariableException(name);	
			else
				return prev->getVar(name);
		}
		else {
			return *t->second;
		}
	}
	inline Value & getVar(const int & name) {
		auto ptr = this;
		while (ptr != nullptr) {
			auto t = ptr->table.find(name);
			if (t != ptr->table.end())return *t->second;
			ptr = ptr->prev;
		}
		//return *new Value();
		throw UndefinedVariableException(name);
	}
	~VariableTable() {
		for (auto &x : table)
			delete x.second;
	}
};


class Function {
public:
	bool mark;
	shared_ptr<FuncDefNode> data;
	Function(FuncDefNode & t) {
		data = shared_ptr<FuncDefNode>(&t);
	}
};
class Object {
public:
	bool mark;
	map<int, Value*> data;
	Object() {

	}
	void DefineVar(int name) {
		auto t = data.find(name);
		if (t != data.end())
			throw RedefinedVariableException(name);
		this->data.emplace(name, new Value());
	}
	Value & getVar(int name) {
		auto t = data.find(name);
		if (t != data.end())return *t->second;
		else throw UndefinedVariableException(name);
	}
	~Object() {
		for (auto &x : data)
			delete x.second;
	}
};

vector<Function *> FuncTable;
vector<Object *> ObjTable;
VariableTable *NowVarTable = new VariableTable();
Object * TempObject = nullptr;

string itos(long long x) {
	ostringstream os;
	os << x;
	return os.str();
}
string dtos(double x) {
	ostringstream os;
	os << x;
	return os.str();
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
		delete data.Str;
	this->type = Type::Func;
	this->data.Func = t;
}
Value::Value(Object *t) {
	if (type == Type::Str)
		delete data.Str;
	this->type = Type::Obj;
	this->data.Obj = t;
}

bool Value::isTrue() {
	//All Type::  //To Modify
	if (this->type == Type::Null)
		return false;
	if (this->type == Type::Int && this->data.Int == 0)
		return false;
	return true;
}


Value Value::operator++ () {
	if (this->type == Type::Int) {
		this->data.Int++;
		return *this;
	}
	if (this->type == Type::Real) {
		this->data.Real++;
		return *this;
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
	if(this->type == Type::Real)
		return Value(-this->data.Real);
	throw CalTypeException(*this);
}		
Value Value::operator+ (const Value &t) {
	//For Str
	if (this->type == Type::Str && t.type == Type::Str)
		return Value(*this->data.Str+ *t.data.Str);
	if (this->type == Type::Int && t.type == Type::Str)
		return Value(itos(this->data.Int) + *t.data.Str);
	if (this->type == Type::Real && t.type == Type::Str)
		return Value(dtos(this->data.Real) + *t.data.Str);
	if (this->type == Type::Str && t.type == Type::Int)
		return Value(itos(t.data.Int) + *this->data.Str);
	if (this->type == Type::Str && t.type == Type::Real)
		return Value(dtos(t.data.Real) + *this->data.Str);
	//For Num
	if (this->type == Type::Int && t.type == Type::Int)
		return Value(this->data.Int + t.data.Int);
	if (this->type == Type::Real && t.type == Type::Int)
		return Value(this->data.Real + t.data.Int);
	if (this->type == Type::Real && t.type == Type::Real)
		return Value(this->data.Real + t.data.Real);
	if (this->type == Type::Int  && t.type == Type::Real)
		return Value(this->data.Int + t.data.Real);
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
	throw CalTypeException(*this,t);
}

Value Value::operator&& (const Value &t) {
	if (this->type == Type::Int && t.type == Type::Int)
		return Value(this->data.Int / t.data.Int);
	throw CalTypeException(*this, t);
}
Value Value::operator|| (const Value &t){
	if (this->type == Type::Int && t.type == Type::Int)
		return Value(this->data.Int / t.data.Int);
	throw CalTypeException(*this, t);
}
Value Value::operator! () {
	if (this->type == Type::Int)
		return Value((long long)!this->data.Int);
	throw CalTypeException(*this);
}

Value Value::operator~ () {
	if (this->type == Type::Int)
		return Value(~this->data.Int);
	throw CalTypeException(*this);
}
Value Value::operator& (const Value &t){
	if (this->type == Type::Int && t.type == Type::Int)
		return Value(this->data.Int / t.data.Int);
	throw CalTypeException(*this, t);
}
Value Value::operator| (const Value &t){
	if (this->type == Type::Int && t.type == Type::Int)
		return Value(this->data.Int / t.data.Int);
	throw CalTypeException(*this, t);
}

Value Value::operator!= (const Value &t) {
	return Value((long long )!this->operator==(t).data.Int);
}
Value Value::operator== (const Value &t) {
	if (this->type != t.type)
		return Value((long long)0);
	if (this->type == Type::Int && this->data.Int == t.data.Int
		|| this->type == Type::Real && this->data.Real == t.data.Real
		|| this->type == Type::Str && *this->data.Str == *t.data.Str
		|| this->type == Type::Func && this->data.Func == t.data.Func
		|| this->type == Type::Func && this->data.Obj == t.data.Obj
		)
		return Value((long long)1);
	return Value((long long)0);
}
Value Value::operator> (const Value &t) {
	if (this->type == Type::Int && t.type == Type::Int)
		return Value((long long)(this->data.Int > t.data.Int));
	if (this->type == Type::Real && t.type == Type::Int)
		return Value((long long)(this->data.Real > t.data.Int));
	if (this->type == Type::Real && t.type == Type::Real)
		return Value((long long)(this->data.Real > t.data.Real));
	if (this->type == Type::Int  && t.type == Type::Real)
		return Value((long long)(this->data.Int > t.data.Real));
	throw CalTypeException(*this, t);
}
Value Value::operator< (const Value &t) {
	if (this->type == Type::Int && t.type == Type::Int)
		return Value((long long)(this->data.Int < t.data.Int));
	if (this->type == Type::Real && t.type == Type::Int)
		return Value((long long)(this->data.Real < t.data.Int));
	if (this->type == Type::Real && t.type == Type::Real)
		return Value((long long)(this->data.Real < t.data.Real));
	if (this->type == Type::Int  && t.type == Type::Real)
		return Value((long long)(this->data.Int < t.data.Real));
	throw CalTypeException(*this, t);
}
Value Value::operator>= (const Value &t) {
	if (this->type == Type::Int && t.type == Type::Int)
		return Value((long long)(this->data.Int >= t.data.Int));
	if (this->type == Type::Real && t.type == Type::Int)
		return Value((long long)(this->data.Real >= t.data.Int));
	if (this->type == Type::Real && t.type == Type::Real)
		return Value((long long)(this->data.Real >= t.data.Real));
	if (this->type == Type::Int  && t.type == Type::Real)
		return Value((long long)(this->data.Int >= t.data.Real));
	throw CalTypeException(*this, t);
}
Value Value::operator<= (const Value &t) {
	if (this->type == Type::Int && t.type == Type::Int)
		return Value((long long)(this->data.Int <= t.data.Int));
	if (this->type == Type::Real && t.type == Type::Int)
		return Value((long long)(this->data.Real <= t.data.Int));
	if (this->type == Type::Real && t.type == Type::Real)
		return Value((long long)(this->data.Real <= t.data.Real));
	if (this->type == Type::Int  && t.type == Type::Real)
		return Value((long long)(this->data.Int <= t.data.Real));
	throw CalTypeException(*this, t);
}
Value StmtsNode::eval() {
	left->eval();
	right->eval();
	return Value();
}
Value AddNode::eval() {
	Value t1 = left->eval();
	Value t2 = right->eval();
	return t1 + t2;
}
Value SubNode::eval() {
	Value t1 = left->eval();
	Value t2 = right->eval();
	return t1 - t2;
}
Value MulNode::eval() {
	Value t1 = left->eval();
	Value t2 = right->eval();
	return t1 * t2;
}
Value DivNode::eval() {
	Value t1 = left->eval();
	Value t2 = right->eval();
	return t1 - t2;
}
Value ModNode::eval() {
	Value t1 = left->eval();
	Value t2 = right->eval();
	return t1 % t2;
}
Value EqNode::eval() {
	Value t1 = left->eval();
	Value t2 = right->eval();
	return t1 == t2;
}
Value NeqNode::eval() {
	Value t1 = left->eval();
	Value t2 = right->eval();
	return t1 != t2;
}
Value GtNode::eval() {
	Value t1 = left->eval();
	Value t2 = right->eval();
	return t1 > t2;
}
Value NgtNode::eval() {
	Value t1 = left->eval();
	Value t2 = right->eval();
	return t1 <= t2;
}
Value LtNode::eval() {
	Value t1 = left->eval();
	Value t2 = right->eval();
	return t1 < t2;
}
Value NltNode::eval() {
	Value t1 = left->eval();
	Value t2 = right->eval();
	return t1 >= t2;
}
Value RevNode::eval() {
	return ~son->eval();
}
Value NotNode::eval() {
	return !son->eval();
}
Value ValueNode::eval() {
	return this->val;
}
Value NegNode::eval() {
	return -this->son->eval();
}
Value WhileNode::eval() {
	while (1) {
		auto t = left->eval();
		if (!t.isTrue())return Value();
		try {
			right->eval();
		}
		catch (BreakException) {
			return Value();
		}
		catch (ContinueException) {
			//Continue;
		}
	}
}
Value ForNode::eval() {
	left->eval();
	while (1) {
		auto t = midleft->eval();
		if (!t.isTrue())return Value();
		try {
			right->eval();
		}
		catch (BreakException) {
			return Value();
		}
		catch (ContinueException) {
			//Continue;
		}
		midright->eval();
	}
}
Value IfElseNode::eval() {
	if (left->eval().isTrue()) {
		mid->eval();
	}
	else {
		right->eval();
	}
	return Value();
}
Value IfNode::eval() {
	if (left->eval().isTrue()) {
		right->eval();
	}
	return Value();
}
Value ContinueNode::eval() {
	throw ContinueException();
	return Value();
}
Value ReturnNode::eval() {
	throw ReturnException(this->son->eval());
	return Value();
}
Value ReturnNullNode::eval() {
	throw ReturnException();
	return Value();
}
Value BreakNode::eval() {
	throw BreakException();
	return Value();
}
Value BlockNode::eval() {
	NowVarTable = new VariableTable(NowVarTable);
	son->eval();
	auto tmp = NowVarTable;
	NowVarTable = NowVarTable->prev;
	delete tmp;
	return Value();
}
Value AndNode::eval() {
	if (left->eval().isTrue()) {
		if (right->eval().isTrue()) {
			return Value((long long)1);
		}
	}
	return Value((long long)0);
}
Value OrNode::eval() {
	if (!left->eval().isTrue()) {
		if (!right->eval().isTrue()) {
			return Value((long long)0);
		}
	}
	return Value((long long)1);
}
Value BandNode::eval() {
	Value t1 = left->eval();
	Value t2 = right->eval();
	return t1 & t2;
}
Value BorNode::eval() {
	Value t1 = left->eval();
	Value t2 = right->eval();
	return t1 | t2;
}
Value IDNode::eval() {
	return NowVarTable->getVar(this->value);
}
extern ostream & operator<< (ostream & ,const Value & );

Value AssignNode::eval() {
	auto t = std::dynamic_pointer_cast<ILvalue>(this->left);
	if (t == nullptr)
		throw UnexpectRunTimeException();
	Value & temp = t->get();
	temp = right->eval();
	return Value();
}
Value FuncDefNode::eval() {
	FuncTable.emplace_back(new Function(*this));
	return Value(*(FuncTable.end() - 1));
}
vector<int> FuncCallTmp;
int FuncCallTmpNow;
Value FuncCallNode::eval() {
	//var check
	auto t = std::dynamic_pointer_cast<ILvalue>(this->left);
	if (t == nullptr)
		throw UnableAssignValueException();
	auto var = t->get();
	//func check;
	if (var.type != Value::Type::Func)
		//throw UnableCallVarException(((IDNode *)left.get())->value);
		throw UnexpectRunTimeException();
	//read args list & create variable;
	NowVarTable = new VariableTable(NowVarTable);
	//Argus
	//null
	FuncCallTmp = vector<int>(); FuncCallTmpNow = 0;
	auto func = var.data.Func->data;
	if (typeid(*func->left) == typeid(NullNode)) {
		//
	}
	//sigle
	else if (typeid(*func->left) == typeid(IDNode)) {
		NowVarTable->DefineVar(((IDNode *)func->left.get())->value);
		FuncCallTmp.emplace_back(((IDNode *)func->left.get())->value);
		if (typeid(*this->right) != typeid(ArguNode)) {
			NowVarTable->getVar(((IDNode *)func->left.get())->value) = this->right->eval();
		}
		else this->right->eval();
	}
	//more
	else {
		func->left->eval();
		if (typeid(*this->right) != typeid(ArguNode)) {
			NowVarTable->getVar(FuncCallTmp[FuncCallTmpNow]) = this->right->eval();
		}
		else this->right->eval();
	}
	//render;
	try {
		var.data.Func->data->right->eval();
	}
	catch (ReturnException e) {
		auto tmp = NowVarTable;
		NowVarTable = NowVarTable->prev;
		delete tmp;
		return e.getValue();
	}
	//return 
	auto tmp = NowVarTable;
	NowVarTable = NowVarTable->prev;
	delete tmp;
	return Value();
}
Value ArguDefNode::eval() {
	NowVarTable->DefineVar(((IDNode *)left.get())->value);
	FuncCallTmp.emplace_back(((IDNode *)left.get())->value);
	if (typeid(*right) == typeid(IDNode)) {
		NowVarTable->DefineVar(((IDNode *)right.get())->value);
		FuncCallTmp.emplace_back(((IDNode *)right.get())->value);
	}
	else right->eval();
	return Value();
}
Value ArguNode::eval() {
	if (typeid(*this->left) != typeid(ArguNode)) {
		FuncCallTmpNow++;
		NowVarTable->getVar(FuncCallTmp[FuncCallTmpNow-1]) = this->left->eval();
		if (FuncCallTmpNow  == FuncCallTmp.size())
			return Value();
		FuncCallTmpNow++;
		NowVarTable->getVar(FuncCallTmp[FuncCallTmpNow - 1]) = this->right->eval();
	}
	else {
		this->left->eval();
		if (FuncCallTmpNow  == FuncCallTmp.size())
			return Value();
		FuncCallTmpNow++;
		NowVarTable->getVar(FuncCallTmp[FuncCallTmpNow - 1]) = this->right->eval();
	}
	return Value();
}

SysFuncNode::SysFuncNode(SysFunc x)
	:func(x) {}
void SysFuncNode::visit(int x) {
	for (int i = 1; i <= x; i++)printf("    ");
	cout << "SysFunc Node" << endl;
	this->visitson(x + 1);
}
Value SysFuncNode::eval() {
	return func();
}
extern map<string,int> IdHashTable;
extern int IdHashTableNow;
void addSysFunc(int name,vector<int> args,SysFunc func) {
	//define var

	NowVarTable->DefineVar(name);
	shared_ptr<Node> arugs;
	//null;
	if (args.size() == 0)arugs = shared_ptr<Node>(new NullNode());
	//one
	else if (args.size() == 1) arugs = shared_ptr<Node>(new IDNode(args[0]));
	//more
	else {
		arugs = shared_ptr<Node>(new ArguDefNode(
			shared_ptr<Node>(new IDNode(args[0])),
			shared_ptr<Node>(new IDNode(args[1]))));
		for (int i = 2; i <= args.size() - 1; i++) {
			arugs = shared_ptr<Node>(new ArguDefNode(arugs, shared_ptr<Node>(new IDNode(args[i]))));
		}
	}
	NowVarTable->getVar(name).type = Value::Type::Func;
	NowVarTable->getVar(name).data.Func = new Function(*new FuncDefNode(arugs, shared_ptr<Node>(new SysFuncNode(func))));
}
Value SysPrint() {
	// Value print(x)
	cout << NowVarTable->getVar(2);
	throw ReturnException();
	return Value();
}
Value SysReadInt() {
	long long x;
	cin >> x;
	throw ReturnException(Value((x)));
	return Value();
}
Value SysReadStr() {
	string x;
	cin >> x;
	throw ReturnException(Value((x)));
	return Value();
}
Value SysReadReal() {
	double x;
	cin >> x;
	throw ReturnException(Value((x)));
	return Value();
}
void initSysFunc() {
	IdHashTable.emplace("print",1); IdHashTable.emplace("x",2);
	addSysFunc(1, {2}, SysPrint);
	IdHashTable.emplace("readint",3);
	addSysFunc(3, {}, SysReadInt);
	IdHashTable.emplace("readstr",4);
	addSysFunc(4, {}, SysReadStr);
	IdHashTable.emplace("readreal",5);
	addSysFunc(5, {}, SysReadReal);
	IdHashTableNow = 5;
}	
int getNameInt(string x) {
	auto t = IdHashTable.find(x);
	if (t == IdHashTable.end()) {
		IdHashTable.emplace(x, ++IdHashTableNow);
		return IdHashTableNow;
	}
	else return t->second;
}
Value & ILvalue::get() {
	return * new Value ();
}
Value & SonNode::get() {
	auto t = std::dynamic_pointer_cast<ILvalue>(this->left);
	if (t == nullptr)
		throw UnexpectRunTimeException();
	auto var = t->get();
	return var.data.Obj->getVar(((IDNode*)(right.get()))->value);
}
Value & IDNode::get() {
	return NowVarTable->getVar(this->value);
}
Value SonNode::eval() {
	return this->get();
	//return Value();
}
Value ObjDefNode::eval() {
	TempObject = new Object();
	this->son->eval();
	ObjTable.emplace_back(TempObject);
	return Value(TempObject);
}
Value JsonNode::eval() {
	int x = ((IDNode*)(this->left.get()))->value;
	TempObject->DefineVar(x);
	TempObject->getVar(x) = this->right->eval();
	return Value();
}
Value JsonGroupNode::eval() {
	this->left->eval();
	this->right->eval();
	return Value();
}
Value SelfAddNode::eval() {
	++dynamic_pointer_cast<ILvalue>(this->son)->get();
	return Value();
}
Value SelfSubNode::eval() {
	--dynamic_pointer_cast<ILvalue>(this->son)->get();
	return Value();
}
Value VarDeclrNode::eval() {
	NowVarTable->DefineVar(this->value);
	return Value();
}
Value VarDeclrAssignNode::eval() {
	NowVarTable->DefineVar(this->value);
	NowVarTable->getVar(this->value) = this->son->eval();
	return Value();
}
Value VarDeclrsNode::eval() {
	this->left->eval();
	this->right->eval();
	return Value();
}
