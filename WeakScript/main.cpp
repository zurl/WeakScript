#include "common.h"
#include "parser.h"

#include<algorithm>
bool onDisplay = 0;
extern Lex lex("test.ws");
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


void InterInput() {
	initSysFunc(); 
	lex = Lex();
}

int main() {  
	FileInput();
	//InterInput();
	return 0;
}
