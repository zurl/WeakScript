#include "common.h"

int Sprototype;
int Sthis;
int S__proto__;
int SSystem;
int Sconstructor;
int Sx;
int SHttpRequest;
int SNetwork;
extern int EncodeString(string);
void initConstString() {
	S__proto__ = EncodeString("__proto__");
	Sprototype = EncodeString("prototype");
	Sthis = EncodeString("this");
	Sconstructor = EncodeString("constructor");
	SSystem = EncodeString("System");
	Sx = EncodeString("x");
	SHttpRequest = EncodeString("HttpRequest"); 
	SNetwork = EncodeString("Network");
}