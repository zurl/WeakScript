WeakScript Main Language Defination

# Lex

See WeakScript.lex

which is defined in WeakScript Lex Generator Mark Language

# Type System

WeakScript is a weak-type language
Using var token as variable defination
In WeakScript, We have following 4 origin types:

str  : string 
int  : integer 64bit (long long in C++) 
real : float num 64bit(double in C++)
ref  : reference to Array/object/function;
 
We have following Type conversion rules

Cal/Ass :
int and real -> promote to real
int and real and string ->promote to string
Cond :
real\string -> Runtime ERROR;


# Syntax

stmts->stmt stmts | stmt

stmt-> exp ; | ; | Lv = exp ; | { stmts } 

exp-> exp > sum | exp < sum | exp >=sum |exp <=sum |exp == sum | exp !=sum | sum

sum-> fact + sum | fact - sum | fact 

Fact-> unit * fact_ | unit / fact_ | unit 

unit -> + unit | - unit | unit | (sum) 

Rv-> val | val (argus) | num | str 

argus -> exp , argus | exp

val -> ID | ID . val

ID -> id | id [exp]

