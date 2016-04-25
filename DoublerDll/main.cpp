#include "WsExportCommon.h"
#include "WsExport.h"


__declspec(dllexport) void getModuleFuncCnt(int * ret) {
	*ret = 1;
}
__declspec(dllexport) void getFunc(int id, ExportSysFunc * ret) {
	if (id == 0) {
		//ret = new ExportSysFunc();
		ret->name = (char *)malloc(sizeof("add"));
		strcpy(ret->name, "add");
		ret->argc = 2;
		ret->argv = (char**)malloc(sizeof(char*) * 2);
		ret->argv[0] = (char *)malloc(sizeof("dddx"));
		strcpy(ret->argv[0], "dddx");
		ret->argv[1] = (char *)malloc(sizeof("ddy"));
		strcpy(ret->argv[1], "ddy");
		ret->func = [](int argc,Value * argv)->Value {
			return Value(argv[0].data.Int + argv[1].data.Int);
		};
	}
	else {
	}
}

