#include<iostream>
#include<cstdio>
#include<fstream>
#include<map>
using namespace std;

//zurl virtual machine memory management 

int HEAPMEM[10000],STACKMEM[10000],PROGMEM[10000];
#define INS0E 14
#define INS1E 8
#define INS00 4
#define EXINSCNT 4
char *INS[INS00 + INS1E + INS0E] = {
	//0 ADD + E
	"ADD", "SUB", "MUL", "DIV", "MOD",
	"GT", "NGT", "LT", "NLT", "GT", "NGT",
	"AND", "OR", "NOT",
	//1 ADD + E
	"POP",
	"JP", "JPT", "JPF",
	"GETH", "SETH", "GETS", "SETS",
	//0 ADD + 0
	"PUSH","CALL", "RET", "APPLY"
};
enum INS{
	//0 ADD + E
	ADD, SUB, MUL, DIV, MOD,
	GT, NGT, LT, NLT, GT, NGT,
	AND, OR, NOT,
	//1 ADD + E
	POP,
	JP, JPT, JPF,
	GETH, SETH, GETS, SETS,
	//0 ADD + 0
	PUSH,CALL, RET, APPLY 
};

typedef unsigned int ADDRESS;
void *prog,*heap,*heaptop,*stackend;
int MEM_init(ADDRESS stackSize, ADDRESS progSize, ADDRESS heapSize){
	////wait for error
	stackend = STACKMEM;
	prog = PROGMEM;
	//heap = malloc(heapSize);
	//memset(heap, 0, heapSize);
	heap = HEAPMEM;
	return 1;
}
//block * int
//+0 next
//+1 count
ADDRESS MEM_alloc(ADDRESS size_t){
	char *ptr = (char *)heaptop;
	while (*((int*)ptr + 1) != 0 || (char *)heaptop + *((int*)ptr) - ptr <= (int)size_t + 2 * sizeof(int))
		ptr = (char *)heaptop + *((int*)ptr);
	*((int*)ptr + 1) = 1;
	*((int*)(ptr + size_t) + 2) = *((int*)ptr);
	*((int*)ptr) = ptr - (char*)heaptop + size_t + 2 * sizeof(int);
	return *((int*)ptr) + sizeof(int) * 2;
}
int _alloc_unittest(){
	MEM_init(0, 0, 0xFFFF);
	MEM_alloc(sizeof(long long));
	MEM_alloc(sizeof(long long));
	MEM_alloc(sizeof(char));
	MEM_alloc(sizeof(long long));
	MEM_alloc(sizeof(long long));
	return 1;
}
int MEM_read(){
	return 1;

}

const int _CONST_MAXSTRLEN = 1023;
void MF_READ(const char *fileName){
	
}
//virutal Machine


int VM_HOST(){
	int sTop = 0,fBase = 0;
	//main func proc
	if (funcname.find("main") == funcname.end())
		return 0;
	char *pPtr = (char *)prog + funcname["main"].second;
	int *stack = (int*)stackend,*base = (int*)stackend;
	*stack = 0; stack++; //Param Head
	*stack = 0; stack++; //Call Line Number
	while ((void*)stack != stackend){
		switch (*(char*)pPtr){
			/*
				Stack Structure Description ::

			07#	|	OPERAND  | 
				|------------|	
			06#	|     VAR    |
				|------------|
			05#	|     VAR    |
				|------------|
			04# | PROG	PTR  |// The Prog-Ptr of prog where call the func
				|------------|// eg.01#      (THE CALL INS LINE NUM)
			03# | PARAM HEAD |// The Stack-Ptr of Param Head (The first Param)
				|------------|// eg.01#
			02#	|	PARAM    |
				|------------|
			01# |	PARAM    | //
				-------------- // Stack End

				CALL PARAM_SPACE LINE
			*/  //   //
		case PUSH:
			//only interger
			stack++;
			*stack = *(int *)((char*)pPtr + 2);
		case POP:
			stack--;
		case CALL:			
			int param_space = *((char*)pPtr + 1);
			int call_line = *(int *)((char*)pPtr + 2);
			//PUSH PARAM HEAD
			stack++;
			*stack = (char*)base - (char*)stackend - param_space; 
			//PUSH call LINE
			stack++; 
			*stack = (char*)pPtr - (char*)prog; 
			//base change
			base = stack;
			//prog change (sub first)
			pPtr = (char *)prog + call_line * 6 - 6;
			break;
		case APPLY:
			//move stack Ptr
			*stack += *(int *)((char*)pPtr + 2);
			break;
		case RET:
			int ret_val_size = *(int *)((char*)pPtr + 2);
			int call_line = *base;
			int param_head = *(base - 1);
			//PROG END JUDGE
			if (param_head = 0){
				//TODO : 
				//  ending precedure
			}
			//not end

			//call line change;
			pPtr = (char *)prog + call_line * 6;
			//ret val copy
			memcpy((char *)stackend + param_head, stack - ret_val_size + 1, ret_val_size);
			//stack change;
			stack = (int * )((char *)stackend + param_head + ret_val_size);
			break;
		}
		//next ins
		pPtr += 6;
	}
	

}

// Assembler
map<string,pair<int,int>> funcname;
int ASM_funcPre(char *fileName, char *tempString){
	FILE *fp = fopen(fileName, "r");
	int flag = 0,now = 0,varc;
	fscanf(fp, "%s", tempString);
	while (strcmp(".end", tempString) != 0){
		while (strcmp(".func", tempString) == 0){
			fscanf(fp, "%s%s", tempString,&varc);
			funcname.emplace(tempString,  now / 3, varc );
			fscanf(fp, "%s", tempString);
			while (tempString[0] != '.'){
				now++;
				fscanf(fp, "%s", tempString);
			}
		}
		fscanf(fp, "%s", tempString);
	}
	fclose(fp);
	return 0;
}

int ASM_main(char *fileName){
	//ASM prog 

	//Prog Info
	char tempString[_CONST_MAXSTRLEN];
	int ProgSpace = 0x500000;
	int StackSpace = 0x500000;
	int HeapSpace = 0x9000000;
	ASM_funcPre(fileName, tempString);
	FILE *fp = fopen(fileName, "r");
	fscanf(fp, "%s", tempString);
	if (strcmp(".info", tempString) == 0){
		fscanf(fp, "%s", tempString);
		while (tempString[0] != '.'){
			if (strcmp(tempString, "progsize") == 0){
				scanf("%x", &ProgSpace);
			}
			else if (strcmp(tempString, "stacksize") == 0){
				scanf("%x", &StackSpace);
			}
			else if (strcmp(tempString, "progsize") == 0){
				scanf("%x", &HeapSpace);
			}
			//	else if ()
			fscanf(fp, "%s", tempString);
		}
	}
	//init

	MEM_init(StackSpace, ProgSpace, HeapSpace);

	//Const Table
	int constTableCount, constType, constInt;
	double constDouble;
	const int _CONST_INT = 0;
	const int _CONST_DOUBLE = 1;
	const int _CONST_STR = 2;
	heaptop = heap;
	if (strcmp(".const", tempString) == 0){
		fscanf(fp, "%d", &constTableCount);
		while (constTableCount--){
			fscanf(fp, "%d", &constType);
			switch (constType){
			case _CONST_INT:
				fscanf(fp, "%d", &constInt);
				*((int*)heaptop) = constInt;
				heaptop = (void*)((int*)heaptop + 1);
				break;
			case _CONST_DOUBLE:
				fscanf(fp, "%lf", &constDouble);
				*((double*)heaptop) = constDouble;
				heaptop = (void*)((double*)heaptop + 1);
				break;
			case _CONST_STR:
				fscanf(fp, "%s", tempString);
				for (int i = 0; i <= strlen(tempString); i++){
					*((char*)heaptop) = tempString[i];
					heaptop = (void*)((char*)heaptop + 1);
				}
				break;
			}
		}
		fscanf(fp, "%s", tempString);
	}
	
	//prog
	void * progtop = prog;
	while (strcmp(".func", tempString) == 0){
		fscanf(fp, "%s%*s", tempString);//func name
		while (tempString[0] != '.'){
			for (int i = 0; i <= INS00 + INS1E + INS0E - 1; i++){
				if (strcmp(INS[i], tempString) == 0){
					//fscanf(fp, "%s", tempString);
					*((char*)progtop) = i;
					if (i >= INS0E){
						if (strcmp(INS[i], "CALL") == 0){
							fscanf(fp, "%s", tempString);
							*((char*)progtop + 1) = funcname[tempString].second;
							*((int*)((char*)progtop + 2)) = funcname[tempString].first;
						}
						else if (strcmp(INS[i], "APPLY") == 0){
							fscanf(fp, "%x", (char*)progtop + 2);
						}
						else if (strcmp(INS[i], "RET") == 0){
							fscanf(fp, "%x", (char*)progtop + 2);
						}
						else{
							//TODO
						}
					}
					else if(i < INS1E){
						fscanf(fp, "%x", (char*)progtop + 1);
						fscanf(fp, "%x", (char*)progtop + 2);
					}
					else{
						fscanf(fp, "%x", (char*)progtop + 1);						
					}
					progtop = (char*)progtop + 6;
					break;
				}
			}
			fscanf(fp, "%s", tempString);
		}
	}
	if (strcmp(".end", tempString) == 0){
		return 1;
	}
	else{
		return 0;
	}

}
void  unittest(){
	ASM_main("test.zvc");
	VM_HOST();
}

int main(){
	unittest();
}