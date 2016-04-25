#pragma once
#include "WsExportCommon.h"


using ModuleFunc = Value(*)(int argc, Value *argv);

struct ExportSysFunc {
	char * name;	//Function Name
	int argc;		//Function arguments count
	char ** argv;	//Function argusmens name
	ModuleFunc func;//Function body.
};

__declspec(dllexport) void getFuncCnt(int * ret);
//Return the number of functions
__declspec(dllexport) void getFunc(int id, ExportSysFunc * ret);
//Return the nth function

