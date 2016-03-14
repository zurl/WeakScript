#include "common.h"
#include "parser.h"
#include<algorithm>

#define d
#ifdef d
extern Lex lex;
#else
extern Lex lex("test.ws");
#endif

extern shared_ptr<Node> root;
extern bool parseStmt();
extern void initSysFunc();

bool FileInput() {
	initSysFunc();
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


string info = "WeakScript 0.2.11 alpha on win32\nCopyright 2015-2016 zcy. All Rights Reserved\nThis project is under the MIT license: http://www.opensource.org/licenses/mit-license.php\n";
bool InterInput() {
	string code;
	initSysFunc(); 
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
			lex.reset();
			//return 0;
		}
		//saved_root = root;
	}
}

int main() {  
#ifndef d
	FileInput();
#else
	InterInput();
#endif
	return 0;
}
