/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_SCANNER_TAB_H_INCLUDED
# define YY_YY_SCANNER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    EXTENDS = 258,
    CLASS = 259,
    WHILE = 260,
    IF = 261,
    ELSE = 262,
    ELIF = 263,
    RETURN = 264,
    DEF = 265,
    ENDL = 266,
    COLON = 267,
    SEMICOLON = 268,
    LP = 269,
    RP = 270,
    LB = 271,
    RB = 272,
    DOT = 273,
    COMMA = 274,
    GETS = 275,
    MISS = 276,
    ILLEGAL = 277,
    AND = 278,
    OR = 279,
    NOT = 280,
    ATMOST = 281,
    MORE = 282,
    ATLEAST = 283,
    LESS = 284,
    PLUS = 285,
    MINUS = 286,
    TIMES = 287,
    DIVIDE = 288,
    EQUALS = 289,
    NEG = 290,
    INT_LIT = 291,
    FLOAT = 292,
    STRING_LIT = 293,
    Ident = 294,
    QUACKTRUE = 295,
    QUACKFALSE = 296
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 31 "scanner.y" /* yacc.c:1909  */

	int ival;
	float fval;
	char* sval;
	char* identval;
	char* qtrue;
	char* qflase;
	//struct expr_val* expval;
    program* prog;
	basic_classes* b_classes;
	basic_class* b_class;
	class_sig* class_sign;
	extend* ex;
	statements* ss;
	methods* ms;
	class_body* cb;
	statement* stmt;
	method* mtd;
	r_expr* r_exp;
	make_ident* mk_ident;
	formal_args* f_args;
	formal_args_first* f_args_f;
	formal_args_idents* f_args_is;
	formal_args_ident* f_args_i;
	elifs*          ElIfs;
	elif*        ElIf;
	actual_args* a_args;
	r_exprs* r_exps;


#line 127 "scanner.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SCANNER_TAB_H_INCLUDED  */
