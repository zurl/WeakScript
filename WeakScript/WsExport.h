#pragma once
#include "common.h"
#include "eval.h"
using ModuleFunc = Value(*)(int argc, Value *argv);
struct ExportSysFunc {
	char * name;
	int argc;
	char ** argv;
	ModuleFunc func;
};
