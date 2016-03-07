WeakScirpt -- A JavaScript-like Interpreter  
    
1.Introduction:  

This is a project contains WeakScirpt's Interpreter and its util  
(contains a TokenizerBuilder & a ParserGenerator )  

2.Specification:   
* `Weak-Type`  
* `Dynamic-Type`  
* `Interpreted`  
* `Running on Analysis tree`  
* `FP`
* `OOP`
* (Mark-Sweep GC)  
  
3. Expample 
A program for finding prime numbers.
<pre> 
{  
	var system;
	system.prime = func(){
		var a;var i;var j;var n;var flag;  
		for(i=2;i<=1000;i=i+1){  
			flag = 0;  
			for(j=2;j<i;j=j+1){  
				if(i % j == 0){  
					flag = 1;  
					break;  
				}  
			}  
			if(flag == 0){  
				print(i);  
				print(" ");  
			}  
		}  
	}
	system.prime();
}  
</pre>

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
  
