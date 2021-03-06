#WeakScript Lexical Analysis Engine
#Version 1.1 beta
#Powered By zurl

#The Definations are as following:
#@DEF A B //define a->b
#@REP A B C //define a->b(repeat c)
#@RULE ... @END //the defination block ,direct rules
#@TOKEN ... @END //the special ID 
##... are comments;
#\a -> [A-Za-z0-9]	\d -> [0-9]
#\b -> [A-Z]		\s -> [a-z]
#\l -> [A-Za-z]	    \p -> space
#\n -> \n			\t -> \t

#WeakScript Lex 
#Version 1.2 Stable

@DEF SLT a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|_|$
@DEF NNN 1|2|3|4|5|6|7|8|9|0

@RULE

#id

ID (SLT|\b)(SLT|\b|\d)*

#token 

IF if
ELSE else
FOR for
VAR var
RETURN return
FUNC function
WHILE while
BREAK break
CONTINUE continue
IN in
NEW new
NULL null
TRUE true
FALSE false
OF of
IMPORT import


#control symbol 

SEMI ;
LSB \[
RSB \]
LP \(
RP \)
LCB {
RCB }
COM ,
POT .
COL :

#operatror

SADD \+\+
SSUB \-\-
ADD \+
SUB \-
MUL \*
DIV \/
MOD \%
EQ ==
ASSIGN =
NEQ !=
GT >
NGT <=
LT <
NLT >=
AND &&
OR \|\|
REV ~
NOT !
BOR \|
BAND \&

#value

INT (NNN)+
REAL -?(NUM)+.(NUM)+

STRING (\"|\')\a*(\"|\')

#useless symbol

SPACE \p
NL \n
TAB \t
COMMENTA //\a*\n
COMMENTB /\*\a*\*/

@END