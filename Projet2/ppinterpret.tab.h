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

#ifndef YY_YY_PPTOC3A_TAB_H_INCLUDED
# define YY_YY_PPTOC3A_TAB_H_INCLUDED
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
    V = 258,
    I = 259,
    NFon = 260,
    NPro = 261,
    NewAr = 262,
    Sk = 263,
    T_ar = 264,
    T_boo = 265,
    T_int = 266,
    Def = 267,
    Dep = 268,
    Af = 269,
    True = 270,
    False = 271,
    Se = 272,
    If = 273,
    Th = 274,
    El = 275,
    Var = 276,
    Wh = 277,
    Do = 278,
    Pl = 279,
    Mo = 280,
    Mu = 281,
    And = 282,
    Or = 283,
    Not = 284,
    Lt = 285,
    Eq = 286,
    OPar = 287,
    CPar = 288,
    OBracket = 289,
    CBracket = 290,
    OBrace = 291,
    CBrace = 292,
    Comma = 293,
    Colon = 294,
    SpaceTab = 295
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 18 "pptoc3a.y" /* yacc.c:1909  */

		char* identity;
		int constant;
        struct Type* type;
        struct Variable* variable;
        struct Env* env;
        struct FuncDisclaimer* funcDisc;
        struct Func* function;
        struct FuncList* funcList;
        struct Ast*  ast;
	

#line 108 "pptoc3a.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PPTOC3A_TAB_H_INCLUDED  */
