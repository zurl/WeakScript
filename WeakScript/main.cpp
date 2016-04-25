#include "common.h"
#include "Lex.h"
#include "eval.h"
#include "parser.h"
#include<algorithm>
#include <Windows.h>

extern shared_ptr<Node> root;
extern bool parseStmt();
extern void initSysFunc();

Lex * lex;



bool FileInput() {
	if (parseStmt()) {
		//root->visit(0);
		root->eval();
		return 1;
	}
	// std::out_of_range;
	// return 0;
	// for (int i = 1; i <= 30; i++)
	// out(lex.readNextToken());
	return 0;
}

extern ostream & operator<< (ostream &, const Value &);

Value evalString(string str) {
	Lex * savedLex = lex;
	lex = new Lex(0, str);
	if (parseStmt()) {
		try {
			auto x = root->eval();
			if (dynamic_pointer_cast<SimpleNode>(root) != nullptr) {
				lex = savedLex;
				return x;
			}
		}
		catch (MyExpection &e) {
			cout << e.getErrorMessage() << endl;
		}lex = savedLex;
		return Value();
	}
	else {
		cout << "Illeagl code." << endl; lex = savedLex;
		return Value();
	}
}

string info = "WeakScript 0.8.2 stable on win32\nCopyright 2015-2016 zcy. All Rights Reserved\nThis project is under the MIT license: http://www.opensource.org/licenses/mit-license.php\n";
bool InterInput() {
	string code;
	
	//lex = Lex();
	cout << info;
	while (1) {
		cout << ">>>";
		if (parseStmt()) {
			//root->visit(0);
			try {
				auto x = root->eval();
				if (dynamic_pointer_cast<SimpleNode>(root) != nullptr)
					cout << x << endl;
				//else cout << endl;
			}
			catch (MyExpection &e ) {
				cout << e.getErrorMessage()<<endl;
			}
			//if (x.type == Value::Type::Null)
			//return 1;
		}
		else {
			cout << "SyntaxError" << endl;
			lex->reset();
			//return 0;
		}
		//saved_root = root;
	}
}

extern void initConstString();
extern shared_ptr<VariableTable> NowVarTable;
void networkinit(char *begin) {
	//space;
	NowVarTable->defineVar(SHttpRequest);
	string text = string(begin);
	lex = new Lex(0,text);
	if (parseStmt()) {

		root->eval();
		delete lex;
	}
	else {
		cout << "fuck" << endl;
	}
}
int main(int argc, char *argv[]) {
	

	initConstString();
	initSysFunc();
	if (argc == 1) {
		lex = new Lex();
		InterInput();
	}
	else {
		if (argv[1][1] == 'f') {
			lex = new Lex(string(argv[2]));
		}
		else if (argv[1][1] == 'n') {
			networkinit(argv[3]);
			lex = new Lex(string(argv[2]));
		}
		FileInput();
	}
	return 0;
}
