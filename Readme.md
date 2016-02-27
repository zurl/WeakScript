WeakScirpt --A script-language Interpreter  
    
1.Introduction:  
This is a project contains WeakScirpt's Interpreter and its util  
(contains a TokenizerBuilder & a ParserGenerator )  
2.Specification:   
* `Weak-Type`  
* `Dynamic-Type`  
* `Interpreted`  
* `Running on Analysis tree`  
* (FP)  
* (OOP)  
* (Mark-Sweep GC)  
  
3. Expample  
{
	var a,b;
	a = 1;
	if(a == 1){
		b = 2;
	}else{
		b = 3;
	}
}


4.Grammer Reference  
(like a subset of JavaScript)  
  
Data Type:  
WeakScirpt has six Data Types:  
Null , Integer , Real , String , Function Ref , Object Ref  
Operator:  
(Priority is descending)  
* Unary - ! ~  
* * / %  
* + -  
* >= <= > < == !=  
* &&  
* ||  
* &  
* |  
* =  
Control:  
for(stmt;expr;stmt)stmt  
while(expr)stmt  
if(expr)stmt   
if(expr)stmt else stmt  
  
