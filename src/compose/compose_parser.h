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

#ifndef YY_YY_COMPOSE_PARSER_H_INCLUDED
# define YY_YY_COMPOSE_PARSER_H_INCLUDED
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
    IDENTIFIER = 258,
    HASH = 259,
    STRING_LITERAL = 260,
    INT_LITERAL = 261,
    TRUE_ = 262,
    FALSE_ = 263,
    FLOAT_LITERAL = 264,
    VOID_ = 265,
    BOOL_ = 266,
    CHAR_ = 267,
    BYTE_ = 268,
    SHORT_ = 269,
    USHORT_ = 270,
    INT_ = 271,
    UINT_ = 272,
    LONG_ = 273,
    ULONG_ = 274,
    HALF_ = 275,
    FLOAT_ = 276,
    DOUBLE_ = 277,
    COLOR = 278,
    VEC2 = 279,
    VEC3 = 280,
    VEC4 = 281,
    QUAT = 282,
    MAT3 = 283,
    MAT43 = 284,
    MAT4 = 285,
    HANDLE_ = 286,
    ENTITY = 287,
    STRING = 288,
    IF = 289,
    SWITCH = 290,
    CASE = 291,
    DEFAULT = 292,
    FOR = 293,
    WHILE = 294,
    DO = 295,
    BREAK = 296,
    RETURN = 297,
    COMPONENT = 298,
    COMPONENTS = 299,
    USING = 300,
    AS = 301,
    CONST_ = 302,
    THIS__ = 303,
    NONE = 304,
    ELSE = 305,
    THEN = 306,
    ADD_ASSIGN = 307,
    SUB_ASSIGN = 308,
    MUL_ASSIGN = 309,
    DIV_ASSIGN = 310,
    MOD_ASSIGN = 311,
    LSHIFT_ASSIGN = 312,
    RSHIFT_ASSIGN = 313,
    AND_ASSIGN = 314,
    XOR_ASSIGN = 315,
    OR_ASSIGN = 316,
    TRANSFORM = 317,
    OR = 318,
    AND = 319,
    EQ = 320,
    NEQ = 321,
    LTE = 322,
    GTE = 323,
    LSHIFT = 324,
    RSHIFT = 325,
    INC = 326,
    DEC = 327,
    UMINUS = 328,
    POSTINC = 329,
    POSTDEC = 330
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 49 "compose.y" /* yacc.c:1909  */

    int                 numi;
    float               numf;
    const char*         str;
    DataType            dataType;
    Ast*                pAst;
    SymTab*             pSymTab;
    const SymDataType*  pSymDataType;

#line 140 "compose_parser.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif



int yyparse (ParseData * pParseData);

#endif /* !YY_YY_COMPOSE_PARSER_H_INCLUDED  */
