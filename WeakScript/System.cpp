#include "common.h"
#include "eval.h"
#include "parser.h"

extern shared_ptr<VariableTable> caller;
extern shared_ptr<VariableTable> NowVarTable;

extern int EncodeString(string);
extern int Sx;
extern int SSystem;
void addModuleFunc(int obj,ExportSysFunc * func) {
	auto space = NowVarTable->getVar(obj).data.Obj;

	auto name = EncodeString(func->name);
	shared_ptr<Node> arugs;
	//null;
	if (func->argc == 0)arugs = shared_ptr<Node>(new NullNode());
	//one
	else if (func->argc == 1) arugs = shared_ptr<Node>(new IDNode(func->argv[0]));
	//more
	else {
		arugs = shared_ptr<Node>(new ArguDefNode(
			shared_ptr<Node>(new IDNode(func->argv[0])),
			shared_ptr<Node>(new IDNode(func->argv[1]))));
		for (unsigned i = 2; i <= func->argc - 1; i++) {
			arugs = shared_ptr<Node>(new ArguDefNode(arugs, shared_ptr<Node>(new IDNode(func->argv[i]))));
		}
	}
	space->getVar(name).type = Value::Type::Func;
	space->getVar(name).data.Func = new Function(new FuncDefNode(arugs, shared_ptr<Node>(new ModuleFuncNode(func))));
}
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
#include "WsExport.h"

Value evalString(string str);
typedef void(*GcFunc)(int *);
typedef void(*GfFunc)(int, ExportSysFunc *);
#include <windows.h>
void initSysFunc() {
	//add system;
	GcFunc getFuncCnt; GfFunc getFunc;
	HINSTANCE hdll;
	hdll = LoadLibrary("D:\\DataBase\\VSCODE\\WeakScript\\Release\\DoublerDll.dll");
	getFuncCnt = (GcFunc)GetProcAddress(hdll, "?getFuncCnt@@YAXPAH@Z");
	getFunc = (GfFunc)GetProcAddress(hdll, "?getFunc@@YAXHPAUExportSysFunc@@@Z");
	int cnt = 0;
	getFuncCnt(&cnt);
	DWORD ttt = GetLastError();

	ExportSysFunc * tmp = new ExportSysFunc();
	getFunc(0, tmp);
	NowVarTable->defineVar(SSystem);
	NowVarTable->getVar(SSystem) = new Object();
	NowVarTable->defineVar(SNetwork);
	NowVarTable->getVar(SNetwork) = new Object();

	addModuleFunc(SSystem, tmp);

//	addSysFunc(SSystem, nname, *nv, tmp->func);
	addSysFunc(SSystem,"print", { "x" }, []() {
		// Value print(x)
		cout << NowVarTable->getVar(Sx);
		throw ReturnException();
		return Value();
	});
	addSysFunc(SSystem, "println", {}, []() {
		// Value print(x)
		cout << endl;
		throw ReturnException();
		return Value();
	});
	addSysFunc(SSystem, "eval", {"x"}, []() {
		// Value print(x)
		throw ReturnException(evalString(*NowVarTable->getVar(Sx).data.Str));
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
	addSysFunc(SNetwork, "sendHTMLHeader", {}, []() {
		cout << "SENDHTML" << "%%%%%%";
		return Value();
	});
	addSysFunc(SNetwork, "sendJSONHeader", {}, []() {
		cout  << "SENDJSON" << "%%%%%%";
		return Value();
	});
}