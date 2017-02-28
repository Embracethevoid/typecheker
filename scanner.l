%{
#include <iostream>
#include "AST.h"
#include "scanner.tab.h"
#include<typeinfo>
using namespace std;
#define YY_DECL extern "C" int yylex()
int line_num = 1;
#define yyval_capacity 1000

char yyval_buf[yyval_capacity]; /* When yytext is not the token value */
int yyval_index = 0;



%}

%option yylineno
%option header-file = "lex.yy.h"
%x tripleq
%%



[ \t\n]*       	{;}

class 	       { return CLASS;}
extends	       { return EXTENDS;}
return         { return RETURN; }
def            { return DEF;}
if             { return IF;}
elif           { return ELIF;}
else           { return ELSE;}
while          { return WHILE;}
True	       { return QUACKTRUE;}
False	       { return QUACKFALSE;}
\(             { return LP;}
\)	       { return RP;}
\{	       { return LB;}
\}             { return RB;}
\:             { return COLON;}
\;             { return SEMICOLON;}

\>\=           { return ATLEAST;}
\<\=           { return ATMOST;}
\.             { return DOT;}
\<             { return LESS;}
\>             { return MORE;}

\=\=           { return EQUALS;}
\=             { return GETS;}
and            { return AND;}
or             { return OR;}
not            { return NOT;}
\+             { return PLUS;}
\-             { return MINUS;}
\*             { return TIMES;}
\%             { return DIVIDE;}

\,		{ return COMMA;}
       
[0-9]+\.[0-9]+ 	{ yylval.fval = atof(yytext);return FLOAT; }
[0-9]+         	{ yylval.ival = atoi(yytext);return INT_LIT; }
[a-zA-Z_][a-zA-Z0-9_]*	{ yylval.identval = strdup(yytext);return Ident;}






["]["]["]        { BEGIN tripleq;
		   yyval_index=0;
		   yyval_buf[yyval_index] = '\0'; 
		  }
<tripleq>(([^\"])|([\"][^\"])|([\"][\"][^\"])|\n)*  {
                  strncpy(yyval_buf + yyval_index, yytext,
		  yyval_capacity - yyval_index - 1);
		  yyval_index += yyleng; 
			{return STRING_LIT;}
		  //fprintf(stderr, "Adding |%s| to buffer\n", yytext);
		  //fprintf(stderr, "Buffer is now |%s|\n", yyval_buf); 
		  }
<tripleq>["]["]["]  { yylval.sval = yyval_buf; 
                      BEGIN INITIAL; 
                      //return STRING_LIT; 
                    }

["](([\\][0btnrf"\\])|[^"\n\\])*["]   	{ yylval.sval = strdup(yytext);return STRING_LIT;}
["](([\\].)|[^"\n\\])*["]     {    
                                  return ILLEGAL;
                              }

["](([\\][^\n])|[^\n"])*\n         {  
                                return MISS; 
                              }




(\/\*([^*]|[\r\n]|(\*+([^*/]|[\r\n])))*\*+\/)|(\/\/.*) {;}


<<EOF>>         { return EOF;}

%%
