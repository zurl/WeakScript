#include "common.h"
#include "eval.h"
#include "parser.h"

extern shared_ptr<VariableTable> caller;
extern shared_ptr<VariableTable> NowVarTable;

extern int EncodeString(string);
extern int Sx;
extern int SSystem;

void addSysFunc(int obj, string nameO, vector<string> args, SysFunc func) {
	auto space = NowVarTable->getVar(obj).data.Obj;
	
	auto name = EncodeString(nameO);
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
		for (unsigned i = 2; i <= args.size() - 1; i++) {
			arugs = shared_ptr<Node>(new ArguDefNode(arugs, shared_ptr<Node>(new IDNode(args[i]))));
		}
	}
	space->getVar(name).type = Value::Type::Func;
	space->getVar(name).data.Func = new Function(new FuncDefNode(arugs, shared_ptr<Node>(new SysFuncNode(func))));
}
void initSysFunc() {
	//add system;
	NowVarTable->defineVar(SSystem);
	NowVarTable->getVar(SSystem) = new Object();

	addSysFunc(SSystem,"print", { "x" }, []() {
		// Value print(x)
		cout << NowVarTable->getVar(Sx);
		throw ReturnException();
		return Value();
	});
	addSysFunc(SSystem, "readint", {}, []() {
		long long x;
		cin >> x;
		throw ReturnException(Value((x)));
		return Value();
	});
	addSysFunc(SSystem, "readstr", {}, []() {
		string x;
		cin >> x;
		throw ReturnException(Value(x));
		return Value();
	});
	addSysFunc(SSystem, "readreal", {}, []() {
		double x;
		cin >> x;
		throw ReturnException(Value(x));
		return Value();
	});
	addSysFunc(SSystem, "showAllVars", {}, []() {
		caller->showAllVariable();
		return Value();
	});
	addSysFunc(SSystem, "exit", {}, []() {
		exit(0);
		return Value();
	});
}