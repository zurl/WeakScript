#include "parser.h"
#include "eval.h"
//map<string, int> IdHashTable;
//int IdHashTableNow;

//int getNameInt(string x) {
//	auto t = IdHashTable.find(x);
//	if (t == IdHashTable.end()) {
//		IdHashTable.emplace(x, ++IdHashTableNow);
//		return IdHashTableNow;
//	}
//	else return t->second;
//}
extern int Sprototype;
extern int Sthis;
extern int S__proto__;
extern int Ssystem;
extern int Sconstructor;

shared_ptr<VariableTable> caller;
shared_ptr<VariableTable> NowVarTable(new VariableTable("Global"));
//shared_ptr<VariableTable> GlobalVarTable = NowVarTable;
shared_ptr<VariableTable> TmpVarTable = nullptr;
Object * TempObject = nullptr;
std::vector<Function *> FuncTable;
std::vector<Object *> ObjTable;

unordered_map<int, string> EncodeHashTable;
unordered_map<string, int> DecodeHashTable;
int NowEncodeNum = 0;

int EncodeString(string x) {
	auto tmp = DecodeHashTable.find(x);
	if (tmp == DecodeHashTable.end()) {
		int now = ++NowEncodeNum;
		EncodeHashTable.emplace(now, x);
		DecodeHashTable.emplace(x, now);
		return now;
	}
	else {
		return tmp->second;			
	}
}

string DecodeString(int x) {
return EncodeHashTable.find(x)->second;
}

string MyExpection::getErrorMessage() { return ""; }

ReturnException::ReturnException() {
	this->data = Value();
}
ReturnException::ReturnException(Value x) {
	this->data = x;
}
Value ReturnException::getValue() {
	return this->data;
}

class UnexpectRunTimeException : public MyExpection {
	virtual string getErrorMessage() {
		return "RunTimeError: UnexpectRunTimeException";
	}
};
class UnableTraveralException : public MyExpection {
	virtual string getErrorMessage() {
		return "UnableTraveralException";
	}
};
class UnableUseSonOperatorException : public MyExpection {
	virtual string getErrorMessage() {
		return "UnableUseSonOperatorException";
	}
};


class UnableAssignValueException : public MyExpection {
	virtual string getErrorMessage() {
		return "UnableAssignValueException";
	}
};
class UnexpectSubscriptException : public MyExpection {
	virtual string getErrorMessage() {
		return "TypeError: object can't apply subscript operatonr";
	}
};
class UnableCallVarException : public MyExpection {
public:
	UnableCallVarException(string name) {

	}
	virtual string getErrorMessage() {
		return "UnableCallVarException";
	}
};

class BreakException : public MyExpection {
	virtual string getErrorMessage() {
		return "SyntaxError: 'break' outside loop";
	}
};
class ContinueException : public MyExpection {
	virtual string getErrorMessage() {
		return "SyntaxError: 'continue' outside loop";
	}
};

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
	return t1 / t2;
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
Value ForeachNode::eval() {
	//to modify
	auto varname = dynamic_pointer_cast<IDNode>(this->left)->value;
	NowVarTable->defineVar(varname);
	auto datavar = dynamic_pointer_cast<ILvalue>(this->mid)->get();
	if (datavar.type == Value::Type::Obj) {
		for (auto & x : datavar.data.Obj->data) {
			NowVarTable->getVar(varname) = DecodeString( x.first );
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
		return Value();
	}
	else if (datavar.type == Value::Type::Str) {
		//todo;
	}
	else {
		throw UnableTraveralException();
	}
	return Value();
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
	NowVarTable = shared_ptr<VariableTable>(new VariableTable(NowVarTable, "Anonymous Code Block;"));
	son->eval();
	auto tmp = NowVarTable;
	NowVarTable = NowVarTable->prev;
	//delete tmp;
	return Value();
}
Value AndNode::eval() {
	if (left->eval().isTrue()) {
		if (right->eval().isTrue()) {
			return Value(true);
		}
	}
	return Value(false);
}
Value OrNode::eval() {
	if (!left->eval().isTrue()) {
		if (!right->eval().isTrue()) {
			return Value(false);
		}
	}
	return Value(true);
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

Value AssignNode::eval() {
	auto t = std::dynamic_pointer_cast<ILvalue>(this->left);
	if (t == nullptr)
		throw UnableAssignValueException();
	Value & temp = t->get();
	temp = right->eval();
	return Value();
}
Value FuncDefNode::eval() {
	FuncTable.emplace_back(new Function(new FuncDefNode(this->left, this->right)));
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
		throw UnableCallVarException(t->getName());
	//read args list & create variable;

	auto func = var.data.Func->func;
	TmpVarTable = shared_ptr<VariableTable>(new VariableTable(var.data.Func->CallerTable,t->getName()));


	//Argus
	//null
	FuncCallTmp = vector<int>(); FuncCallTmpNow = 0;
	
	if (typeid(*func->left) == typeid(NullNode)) {
		//
	}
	//sigle
	else if (typeid(*func->left) == typeid(IDNode)) {
		TmpVarTable->defineVar(((IDNode *)func->left.get())->value);
		FuncCallTmp.emplace_back(((IDNode *)func->left.get())->value);
		if (typeid(*this->right) != typeid(ArguNode)) {
			TmpVarTable->getVar(((IDNode *)func->left.get())->value) = this->right->eval();
		}
		else this->right->eval();
	}
	//more
	else {
		func->left->eval();
		if (typeid(*this->right) != typeid(ArguNode)) {
			TmpVarTable->getVar(FuncCallTmp[FuncCallTmpNow]) = this->right->eval();
		}
		else this->right->eval();
	}
	//render;

	//switch var table
	caller = NowVarTable;
		auto SavedVarTable = NowVarTable;
	NowVarTable = TmpVarTable;
	
	try {
		var.data.Func->func->right->eval();
	}
	catch (ReturnException e) {
		auto tmp = NowVarTable;
		NowVarTable = SavedVarTable;
		//delete tmp;
		return e.getValue();
	}
	//return 
	auto tmp = NowVarTable;
	NowVarTable = SavedVarTable;
	//delete tmp;
	return Value();
}
Value ArguDefNode::eval() {
	TmpVarTable->defineVar(dynamic_pointer_cast<IDNode>(left)->value);
	FuncCallTmp.emplace_back(dynamic_pointer_cast<IDNode>(left)->value);
	if (typeid(*right) == typeid(IDNode)) {
		TmpVarTable->defineVar(dynamic_pointer_cast<IDNode>(right)->value);
		FuncCallTmp.emplace_back(dynamic_pointer_cast<IDNode>(right)->value);
	}
	else right->eval();
	return Value();
}
Value ArguNode::eval() {
	if (typeid(*this->left) != typeid(ArguNode)) {
		FuncCallTmpNow++;
		TmpVarTable->getVar(FuncCallTmp[FuncCallTmpNow - 1]) = this->left->eval();
		if (FuncCallTmpNow == FuncCallTmp.size())
			return Value();
		FuncCallTmpNow++;
		TmpVarTable->getVar(FuncCallTmp[FuncCallTmpNow - 1]) = this->right->eval();
	}
	else {
		this->left->eval();
		if (FuncCallTmpNow == FuncCallTmp.size())
			return Value();
		FuncCallTmpNow++;
		TmpVarTable->getVar(FuncCallTmp[FuncCallTmpNow - 1]) = this->right->eval();
	}
	return Value();
}

ModuleFuncNode::ModuleFuncNode(ExportSysFunc * x)
	:func(x) {}
void ModuleFuncNode::visit(int x) {
	for (int i = 1; i <= x; i++)printf("    ");
	cout << "ModuleFuncNode Node" << endl;
	this->visitson(x + 1);
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
Value & ILvalue::get() {
	return *new Value();
}
string ILvalue::getName() {
	return "";
}
Value & SonNode::get() {
	auto t = std::dynamic_pointer_cast<ILvalue>(this->left);
	if (t == nullptr)
		throw UnexpectRunTimeException();
	auto var = t->get();
	if (var.type != Value::Type::Obj && var.type != Value::Type::Func)
		throw UnableUseSonOperatorException();
	auto r = std::dynamic_pointer_cast<IDNode>(this->right);
	if (r == nullptr) {
		//subscript
		auto ret = this->right->eval();
		if (ret.type == Value::Type::Int) {
			return var.type == Value::Type::Obj?var.data.Obj->getVar(-(int)ret.data.Int): var.data.Func->getVar(-(int)ret.data.Int);
		}
		else if (ret.type == Value::Type::Str) {
			return var.type == Value::Type::Obj ? var.data.Obj->getVar(EncodeString(*ret.data.Str)) : var.data.Func->getVar(-(int)ret.data.Int);
		}
		else {
			throw UnexpectSubscriptException();
		}
	}
	else {
		//object
		return var.data.Obj->getVar(r->value);
	}

}

string SonNode::getName() {
	return dynamic_pointer_cast<ILvalue>(this->left)->getName() +"."+ dynamic_pointer_cast<ILvalue>(this->right)->getName();
}

Value & IDNode::get() {
	return NowVarTable->getVar(this->value);
}

string IDNode::getName() {
	return DecodeString(this->value);
}
Value SonNode::eval() {
	return this->get();
	//return Value();
}

Value ObjDefNode::eval() {
	auto SavedTempObject = TempObject;
	TempObject = new Object();
	this->son->eval();
	ObjTable.emplace_back(TempObject);
	auto ret = Value(TempObject);
	TempObject = SavedTempObject;
	return ret;
}
int TempArrayIndex;
Value ArrayDefNode::eval() {
	auto SavedTempObject = TempObject;
	TempObject = new Object();
	auto SavedArrayIndex = TempArrayIndex;
	TempArrayIndex = -1;
	if (dynamic_pointer_cast<ArrayDefGroupNode>(this->son) != nullptr) {
		this->son->eval();
	}
	else if (dynamic_pointer_cast<NullNode>(this->son) != nullptr){
	
	}
	else {
		++TempArrayIndex;
		TempObject->getVar(-TempArrayIndex) = this->son->eval();
	}
 	//ObjTable.emplace_back(TempObject);
	auto ret = TempObject;
	TempObject = SavedTempObject;
	TempArrayIndex = SavedArrayIndex;
	return Value(ret);
}

Value ArrayDefGroupNode::eval() {


	if (dynamic_pointer_cast<ArrayDefGroupNode>(this->left) == nullptr) {
		++TempArrayIndex;
		TempObject->getVar(-TempArrayIndex) = this->left->eval();
	}
	else {
		this->left->eval();
	}
	++TempArrayIndex;
	TempObject->getVar(-TempArrayIndex) = this->right->eval();
	return Value();
}

Value JsonNode::eval() {
	auto x = dynamic_pointer_cast<IDNode>(this->left)->value;
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
	NowVarTable->defineVar(this->value);
	return Value();
}
Value VarDeclrAssignNode::eval() {
	NowVarTable->defineVar(this->value);
	NowVarTable->getVar(this->value) = this->son->eval();
	return Value();
}
Value VarDeclrsNode::eval() {
	this->left->eval();
	this->right->eval();
	return Value();
}
Value SimpleNode::eval() {
	return this->son->eval();
}
Value NewFuncCallNode::eval() {
	//var check

	auto FuncNamePtr = std::dynamic_pointer_cast<ILvalue>(this->left);
	if (FuncNamePtr == nullptr)
		throw UnableAssignValueException();

	auto func = FuncNamePtr->get();
	//func check;
	if (func.type != Value::Type::Func)
		//throw UnableCallVarException(((IDNode *)left.get())->value);
		throw UnableCallVarException(FuncNamePtr->getName());
	//read args list & create variable;

	//auto func = var.data.Func->func;
	TmpVarTable = shared_ptr<VariableTable>(new VariableTable(func.data.Func->CallerTable, FuncNamePtr->getName()));


	//Argus
	//null
	FuncCallTmp = vector<int>(); FuncCallTmpNow = 0;

	auto funcPtr = func.data.Func->func;
	if (typeid(*funcPtr->left) == typeid(NullNode)) {
		//
	}
	//sigle
	else if (typeid(*funcPtr->left) == typeid(IDNode)) {
		TmpVarTable->defineVar(((IDNode *)funcPtr->left.get())->value);
		FuncCallTmp.emplace_back(((IDNode *)funcPtr->left.get())->value);
		if (typeid(*this->right) != typeid(ArguNode)) {
			TmpVarTable->getVar(((IDNode *)funcPtr->left.get())->value) = this->right->eval();
		}
		else this->right->eval();
	}
	//more
	else {
		funcPtr->left->eval();
		if (typeid(*this->right) != typeid(ArguNode)) {
			TmpVarTable->getVar(FuncCallTmp[FuncCallTmpNow]) = this->right->eval();
		}
		else this->right->eval();
	}
	//render;

	//switch var table
	caller = NowVarTable;
	auto SavedVarTable = NowVarTable;
	NowVarTable = TmpVarTable;
	NowVarTable->defineVar(Sthis);
	NowVarTable->getVar(Sthis)= new Object();
	auto & tmpThis = NowVarTable->getVar(Sthis);
	tmpThis.data.Obj->getVar(S__proto__) = func.data.Func->getVar(Sprototype);
	tmpThis.data.Obj->getVar(Sconstructor) = func.data.Func;
	try {
		funcPtr->right->eval();
	}
	catch (ReturnException e) {
		auto ttmp =  Value(NowVarTable->getVar(Sthis));
		auto tmp = NowVarTable;
		NowVarTable = SavedVarTable;
		//delete tmp;
		//return e.getValue();
		return ttmp;
	}
	//return 
	auto ttmp = Value(NowVarTable->getVar(Sthis));
	auto tmp = NowVarTable;
	NowVarTable = SavedVarTable;
	//delete tmp;
	//return Value();
	return ttmp;
}

Value ModuleFuncNode::eval() {
	Value * argv = (Value *)malloc(sizeof(Value) * func->argc);
	for (int i = 0; i <= func->argc - 1; i++)
		argv[i] = NowVarTable->getVar(EncodeString(func->argv[i]));
	Value ret = func->func(func->argc,argv);
	throw ReturnException(ret);
	return Value();
}
