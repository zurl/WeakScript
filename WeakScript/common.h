#ifndef COMMMON_H
#define COMMMON_H

#include<string>
#include<iostream>
#include<fstream>
#include<map>
#include<vector>
#include<list>
#include<string>
#include<memory>
#include<sstream>
#include<set>
#include<map>
#include<functional>
#include<unordered_map>
#include "WeakScriptLex.h"
using namespace std;



class MyExpection {
	//Abs Class
public:
	virtual string getErrorMessage();
};

#endif