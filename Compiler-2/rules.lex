%{
	int lineNo=0;
	void countNewLine();
%}

%s HASH

preDir			("#include"[ \t]+.*)|("#define"[ \t]+.*)
binaryOp 		("+"|"-"|"/"|"*"|"%"|"=")
relOp 			("=="|"<"|">"|"<="|">="|"!=")
logicalOp 		("&&"|"||"|"!")
bitwiseOp		("~"|"&"|"|"|"^")
rLP				"(" 
rRP 			")"
cLP 			"{"  
cRP 			"}" 
sLP 			"[" 
sRP 			"]"
delim			(";"|",")
bitShift		("<<"|">>")
arithematic		("++"|"--")
assignment		("+="|"-="|"*="|"/="|"%="|"<<="|">>="|"&="|"^="|"|=")

lineComment		"//".*
blockComment	"/*"[^"*/"]*"*/"
string			\"([^\"]|\\.)*\"
charLit			\'([^\']|\\.)?\'

letter 	[a-zA-Z]
digit [0-9]
ws [ \n\t]
digits {digit}+
number {digits}("."{digits})?(E("+"|"-")?{digits})?

illegal {`~@#$_\':?}

reserved ("break"|"case"|"continue"|"default"|"do"|"else"|"enum"|"extern"|"for"|"goto"|"if"|"register"|"return"|"sizeof"|"struct"|"switch"|"typedef"|"union"|"void"|"volatile"|"while")

dt ("auto"|"char"|"const"|"double"|"float"|"int"|"long"|"short"|"signed"|"static"|"unsigned")

id {letter}({letter}|{digit})*

%%

{lineComment} 							{printf("< lineComment,"); ECHO; printf(" >\n");}
{blockComment}  						{printf("< blockComment,"); ECHO; printf(" >\n"); countNewLine();}
{string}			 					{printf("< string,"); ECHO; printf(" >\n"); countNewLine();}
{charLit}			 					{printf("< charLit,"); ECHO; printf(" >\n");}
{preDir}								{printf("< preDir,"); ECHO; printf(" >\n");}
{reserved}								{printf("< reserved,"); ECHO; printf(" >\n");}
{dt}									{printf("< dt,"); ECHO; printf(" >\n");}
{number}{letter}({letter}|{digit})*		{printf("Illegal identifier < "); ECHO; printf(" > at line no.%d\n",lineNo+1);}
{number}								{printf("< number,"); ECHO; printf(" >\n");}
{id}									{printf("< id,"); ECHO; printf(" >\n");}
{binaryOp}								{printf("< binaryOp,"); ECHO; printf(" >\n");}
{relOp}									{printf("< relOp,"); ECHO; printf(" >\n");}
{logicalOp}								{printf("< logicalOp,"); ECHO; printf(" >\n");}
{bitwiseOp}								{printf("< bitwiseOp,"); ECHO; printf(" >\n");}
{arithematic}							{printf("< arithematic,"); ECHO; printf(" >\n");}
{assignment}							{printf("< assignment,"); ECHO; printf(" >\n");}
{rLP}									{printf("< rLP,"); ECHO; printf(" >\n");}
{rRP}									{printf("< rRP,"); ECHO; printf(" >\n");}
{cLP}									{printf("< cLP,"); ECHO; printf(" >\n");}
{cRP}									{printf("< cRP,"); ECHO; printf(" >\n");}
{sLP}									{printf("< sLP,"); ECHO; printf(" >\n");}
{sRP}									{printf("< sRP,"); ECHO; printf(" >\n");}
{delim}									{printf("< delim,"); ECHO; printf(" >\n");}
{bitShift}								{printf("< bitShift,"); ECHO; printf(" >\n");}
"\n"									{lineNo++;}
{ws}									{}
.										{printf("Illegal symbol < "); ECHO; printf(" > at line no.%d\n",lineNo+1);}





%%
int main()
{
	yylex();
	printf("Total Lines=%d\n",lineNo);
	return 0;
}

void countNewLine()
{
	int i;
	for(i=0; i<yyleng; i++)
	{
		if(*(yytext+i)=='\n') lineNo++;
	}
}
