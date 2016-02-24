#include "common.h"
#include "parser.h"

extern Lex lex;
extern shared_ptr<Node> root;
extern bool parseStmt();
int main() {
	if (parseStmt()) {		
		root->visit(0);
		return 1;
	}
	return 0;
	//for (int i = 1; i <= 30; i++)
	//	out(lex.readNextToken());
	return 0;
}
