#pragma once
#include "WsExportCommon.h"
using ModuleFunc = Value(*)(int argc, Value *argv);
struct ExportSysFunc {
	char * name;
	int argc;
	char ** argv;
	ModuleFunc func;
};


__declspec(dllexport) void getModuleFuncCnt(int * ret);
__declspec(dllexport) void getFunc(int id, ExportSysFunc * ret);
