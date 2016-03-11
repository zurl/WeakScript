#include "common.h"
#include "parser.h"

extern Lex lex;
extern shared_ptr<Node> root;
extern bool parseStmt();
extern void initSysFunc();
int main() {  
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
