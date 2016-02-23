#include "LexGenerator.h"
Lex lex;
int main() {
	lex.ReadFromFile("WeakScript.lex");
	lex.outDFA("WeakScript.dfa");
	lex.outDef("WeakScriptLex.h");
	return 0;
}