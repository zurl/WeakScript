

{
	var a=function(){return 5;};
	a();
}  

Token

type  { var ID = function ( ) { return NUMBER ; } ; ID ( ) ; }
value       a							5            a

Parser  LR

expr number + expr | number - expr
number number

1+1-2+3

progNode
AddNode
num 1  subnode
       1   addnode
		   2    3

Interpreter

printf(progNode.eval());


struct value{

int type;
union{
	int a;
	double b;
	value * ;
}
int size;

name
value
}
