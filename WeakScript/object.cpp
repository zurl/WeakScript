#include "eval.h"
#include "parser.h"
extern int S__proto__;
extern string DecodeString(int);
class UndefinedVariableException : public MyExpection {
private:
	string name;
public:
	UndefinedVariableException() {
		name = "";
	}
	UndefinedVariableException(int _name)
		:name(DecodeString(_name)) {

	}
	virtual string getErrorMessage() {
		return "NameError: name \"" + name + "\" is not defined";
	}

};

class RedefinedVariableException : public MyExpection {
public:
private:
	string name;
public:
	RedefinedVariableException(int _name)
		:name(DecodeString(_name)) {

	}
	virtual string getErrorMessage() {
		return "NameError: name \"" + name + "\" has been defined";
	}

};

Object::Object() {

}
Value & Object::__getVar(int name) {
	auto t = data.find(name);
	if (t != data.end())return *t->second;
	else {
		auto pro = data.find(S__proto__);
		if (pro == data.end() || pro->second->type != Value::Type::Obj)
			throw UndefinedVariableException();
		else
			return pro->second->data.Obj->__getVar(name);
	}
}
Value & Object::getVar(int name) {
	try {
		return this->__getVar(name);
	}
	catch (UndefinedVariableException) {
		data.emplace(name, new Value());
		return this->__getVar(name);
	}
}
string Object::toString() {


	if (data.find(0) != data.end()) {
		//Array
		string str = "[\n";
		bool flag = 0;

		int min = 1;
		for (auto &x : data) {
			if (x.first <= min) min = x.first;
		}

		for (int i = 0; i >= min; i--) {
			if (flag == 0) {
				flag = 1;
			}
			else {
				str += ",";
			}
			auto temp = data.find(i);
			if ( temp != data.end()) {
				str += temp->second->toString();
			}
			else {
				str += "Null";
			}
			
		}
		return str + "]";
	}
	else {
		string str = "{\n";
		bool flag = 0;

		for (auto &x : data) {
			if (x.first <= 0) continue;
			str += DecodeString(x.first) + " : " + x.second->toString();
			if (flag = 1) str += ",\n";
			else { flag = 1; str += "\n"; }
		}
		return str + "}";
	}

}
Object::~Object() {
	for (auto &x : data)
		delete x.second;
}

VariableTable::VariableTable(string _name) :name(_name) {
	table = new unordered_map<int, Value*>();
	prev = nullptr;
}
VariableTable::VariableTable(shared_ptr<VariableTable> t, string _name) : name(_name) {
	table = new unordered_map<int, Value*>();
	prev = t;
}
void VariableTable::defineVar(int name) {
	auto t = table->find(name);
	if (t != table->end())
		throw RedefinedVariableException(name);
	this->table->emplace(name, new Value());
}
Value & VariableTable::getVarOld(const int name) {
	auto t = table->find(name);
	if (t == table->end()) {
		if (prev == nullptr)
			throw UndefinedVariableException(name);
		else
			return prev->getVar(name);
	}
	else {
		return *t->second;
	}
}
inline Value & VariableTable::getVar(const int name) {
	auto ptr = this;
	while (ptr != nullptr) {
		auto t = ptr->table->find(name);
		if (t != ptr->table->end())return *t->second;
		ptr = ptr->prev.get();
	}
	//return *new Value();
	throw UndefinedVariableException(name);
}
void VariableTable::showAllVariable() {
	if (this->prev != nullptr)
		this->prev->showAllVariable();
	cout << "At : " << this->name << endl;
	for (auto &x : *table) {
		cout << "    " << x.first << " : " << (*x.second).toString() << endl;
	}
}
VariableTable::~VariableTable() {
	for (auto &x : *table)
		delete x.second;
}

extern shared_ptr<VariableTable> NowVarTable;

Function::Function(FuncDefNode * t)
	:Object() {
	CallerTable = NowVarTable;
	func = shared_ptr<FuncDefNode>(t);
}