/* A Bison parser, made by GNU Bison 2.7.1.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.7.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 27 "compose.y"

#include "compose/compiler.h"

#include "compose/comp_mem.h"
#define YYMALLOC COMP_ALLOC
#define YYFREE COMP_FREE

#define YYDEBUG 1
#include <stdio.h>

/* Line 371 of yacc.c  */
#line 79 "compose_parser.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "compose_parser.h".  */
#ifndef YY_YY_COMPOSE_PARSER_H_INCLUDED
# define YY_YY_COMPOSE_PARSER_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IDENTIFIER = 258,
     INT_LITERAL = 259,
     FLOAT_LITERAL = 260,
     INT = 261,
     UINT = 262,
     FLOAT = 263,
     BOOL = 264,
     CHAR = 265,
     VEC3 = 266,
     VEC4 = 267,
     MAT3 = 268,
     MAT34 = 269,
     MAT4 = 270,
     VOID = 271,
     IF = 272,
     SWITCH = 273,
     CASE = 274,
     DEFAULT = 275,
     FOR = 276,
     WHILE = 277,
     DO = 278,
     BREAK = 279,
     RETURN = 280,
     THEN = 281,
     ELSE = 282,
     OR_ASSIGN = 283,
     XOR_ASSIGN = 284,
     AND_ASSIGN = 285,
     RSHIFT_ASSIGN = 286,
     LSHIFT_ASSIGN = 287,
     MOD_ASSIGN = 288,
     DIV_ASSIGN = 289,
     MUL_ASSIGN = 290,
     SUB_ASSIGN = 291,
     ADD_ASSIGN = 292,
     OR = 293,
     AND = 294,
     NEQ = 295,
     EQ = 296,
     GTE = 297,
     LTE = 298,
     GT = 299,
     LT = 300,
     RSHIFT = 301,
     LSHIFT = 302,
     DEC = 303,
     INC = 304,
     UMINUS = 305,
     POSTDEC = 306,
     POSTINC = 307,
     SCOPE = 308
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 49 "compose.y"

    int         numi;
    float       numf;
    const char* str;
    DataType    dataType;
    Ast*        pAst;
    AstList*    pAstList;
    SymRec*     pSymRec;
    SymTab*     pSymTab;


/* Line 387 of yacc.c  */
#line 187 "compose_parser.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (ParseData * pParseData);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_COMPOSE_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */
/* Line 390 of yacc.c  */
#line 60 "compose.y"

#define YY_NO_UNISTD_H
#include "compose/compose_scanner.h"
#define YYLEX_PARAM parsedata_scanner(pParseData)

#define YYPRINT(file, type, value)   yyprint (file, type, value)
void yyprint(FILE * file, int type, YYSTYPE value);

/* Line 390 of yacc.c  */
#line 236 "compose_parser.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef __attribute__
/* This feature is available in gcc versions 2.5 and later.  */
# if (! defined __GNUC__ || __GNUC__ < 2 \
      || (__GNUC__ == 2 && __GNUC_MINOR__ < 5))
#  define __attribute__(Spec) /* empty */
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif


/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   430

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  74
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  11
/* YYNRULES -- Number of rules.  */
#define YYNRULES  67
/* YYNRULES -- Number of states.  */
#define YYNSTATES  129

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   308

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    57,     2,    68,     2,    56,    43,     2,
      65,    69,    54,    52,    70,    53,    62,    55,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    73,
       2,    28,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    66,     2,     2,    42,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    71,    41,    72,    58,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    44,    45,    46,    47,    48,
      49,    50,    51,    59,    60,    61,    63,    64,    67
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     8,    15,    22,    23,    26,    31,
      34,    38,    40,    43,    47,    53,    59,    67,    70,    72,
      74,    75,    77,    81,    85,    89,    93,    97,   101,   105,
     109,   113,   117,   121,   125,   129,   133,   137,   141,   145,
     149,   153,   157,   161,   165,   169,   173,   177,   181,   185,
     189,   193,   196,   199,   202,   205,   208,   211,   214,   216,
     218,   223,   225,   227,   229,   231,   233,   235
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      75,     0,    -1,    76,    -1,    75,    76,    -1,    68,     3,
      65,    77,    69,    78,    -1,    84,     3,    65,    77,    69,
      78,    -1,    -1,    84,     3,    -1,    77,    70,    84,     3,
      -1,    71,    72,    -1,    71,    79,    72,    -1,    80,    -1,
      79,    80,    -1,    84,     3,    73,    -1,    84,     3,    28,
      83,    73,    -1,    17,    65,    83,    69,    81,    -1,    17,
      65,    83,    69,    81,    27,    81,    -1,    83,    73,    -1,
      78,    -1,    80,    -1,    -1,    83,    -1,    82,    70,    83,
      -1,    65,    83,    69,    -1,    83,    52,    83,    -1,    83,
      53,    83,    -1,    83,    54,    83,    -1,    83,    55,    83,
      -1,    83,    56,    83,    -1,    83,    51,    83,    -1,    83,
      50,    83,    -1,    83,    40,    83,    -1,    83,    39,    83,
      -1,    83,    42,    83,    -1,    83,    45,    83,    -1,    83,
      44,    83,    -1,    83,    49,    83,    -1,    83,    47,    83,
      -1,    83,    48,    83,    -1,    83,    46,    83,    -1,     3,
      28,    83,    -1,     3,    38,    83,    -1,     3,    37,    83,
      -1,     3,    36,    83,    -1,     3,    35,    83,    -1,     3,
      34,    83,    -1,     3,    33,    83,    -1,     3,    32,    83,
      -1,     3,    31,    83,    -1,     3,    30,    83,    -1,     3,
      29,    83,    -1,    57,    83,    -1,    58,    83,    -1,    53,
      83,    -1,    60,    83,    -1,    59,    83,    -1,    83,    60,
      -1,    83,    59,    -1,     4,    -1,     5,    -1,     3,    65,
      82,    69,    -1,     3,    -1,     6,    -1,     7,    -1,     8,
      -1,     9,    -1,    11,    -1,    16,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   111,   111,   112,   116,   117,   121,   122,   123,   127,
     128,   132,   133,   137,   138,   140,   141,   143,   147,   148,
     152,   153,   154,   158,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   171,   172,   173,   174,   175,   176,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   190,   191,   192,   194,   195,   196,   197,   199,   200,
     202,   203,   207,   208,   209,   210,   211,   212
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER", "INT_LITERAL",
  "FLOAT_LITERAL", "INT", "UINT", "FLOAT", "BOOL", "CHAR", "VEC3", "VEC4",
  "MAT3", "MAT34", "MAT4", "VOID", "IF", "SWITCH", "CASE", "DEFAULT",
  "FOR", "WHILE", "DO", "BREAK", "RETURN", "THEN", "ELSE", "'='",
  "OR_ASSIGN", "XOR_ASSIGN", "AND_ASSIGN", "RSHIFT_ASSIGN",
  "LSHIFT_ASSIGN", "MOD_ASSIGN", "DIV_ASSIGN", "MUL_ASSIGN", "SUB_ASSIGN",
  "ADD_ASSIGN", "OR", "AND", "'|'", "'^'", "'&'", "NEQ", "EQ", "GTE",
  "LTE", "GT", "LT", "RSHIFT", "LSHIFT", "'+'", "'-'", "'*'", "'/'", "'%'",
  "'!'", "'~'", "DEC", "INC", "UMINUS", "'.'", "POSTDEC", "POSTINC", "'('",
  "'['", "SCOPE", "'#'", "')'", "','", "'{'", "'}'", "';'", "$accept",
  "def_list", "def", "param_list", "block", "stmt_list", "stmt",
  "block_or_stmt", "expr_list", "expr", "type", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,    61,   283,
     284,   285,   286,   287,   288,   289,   290,   291,   292,   293,
     294,   124,    94,    38,   295,   296,   297,   298,   299,   300,
     301,   302,    43,    45,    42,    47,    37,    33,   126,   303,
     304,   305,    46,   306,   307,    40,    91,   308,    35,    41,
      44,   123,   125,    59
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    74,    75,    75,    76,    76,    77,    77,    77,    78,
      78,    79,    79,    80,    80,    80,    80,    80,    81,    81,
      82,    82,    82,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    84,    84,    84,    84,    84,    84
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     6,     6,     0,     2,     4,     2,
       3,     1,     2,     3,     5,     5,     7,     2,     1,     1,
       0,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     2,     2,     2,     2,     2,     1,     1,
       4,     1,     1,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    62,    63,    64,    65,    66,    67,     0,     0,     2,
       0,     0,     1,     3,     0,     6,     6,     0,     0,     0,
       0,     0,     7,     0,     0,     4,     0,     5,    61,    58,
      59,     0,     0,     0,     0,     0,     0,     0,     9,     0,
      11,     0,     0,     8,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    20,     0,    53,    51,    52,
      55,    54,     0,    10,    12,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    57,    56,    17,     0,    40,    50,    49,    48,    47,
      46,    45,    44,    43,    42,    41,     0,    21,     0,    23,
      32,    31,    33,    35,    34,    39,    37,    38,    36,    30,
      29,    24,    25,    26,    27,    28,     0,    13,    60,     0,
       0,     0,    22,    18,    19,    15,    14,     0,    16
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     8,     9,    17,   123,    39,   124,   125,    96,    41,
      42
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -64
static const yytype_int16 yypact[] =
{
     159,   -64,   -64,   -64,   -64,   -64,   -64,    61,   117,   -64,
      69,     9,   -64,   -64,    10,   165,   165,   -63,    73,   -61,
       6,   165,   -64,     6,    46,   -64,    77,   -64,   158,   -64,
     -64,    16,   104,   104,   104,   104,   104,   104,   -64,    62,
     -64,   160,    79,   -64,   104,   104,   104,   104,   104,   104,
     104,   104,   104,   104,   104,   104,   104,   -64,   -30,   -30,
     -30,   -30,   220,   -64,   -64,   104,   104,   104,   104,   104,
     104,   104,   104,   104,   104,   104,   104,   104,   104,   104,
     104,   -64,   -64,   -64,   -17,   272,   272,   272,   272,   272,
     272,   272,   272,   272,   272,   272,   -10,   272,   246,   -64,
     293,   312,   329,   346,   346,   361,   361,   361,   361,   370,
     370,   -28,   -28,   -30,   -30,   -30,   104,   -64,   -64,   104,
      85,   190,   272,   -64,   -64,    56,   -64,    85,   -64
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -64,   -64,    78,    81,    38,   -64,   -14,   -42,   -64,   -32,
     131
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_int16 yytable[] =
{
      57,    58,    59,    60,    61,    62,    20,    21,    23,    21,
      40,   116,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    97,    98,    64,    78,    79,    80,    81,
      82,    81,    82,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,    28,
      29,    30,     1,     2,     3,     4,   117,     5,    25,   118,
     119,    27,     6,    31,    11,    28,    29,    30,     1,     2,
       3,     4,    14,     5,    15,    16,    22,    24,     6,    31,
      43,    56,    84,   127,   121,   128,    13,   122,    28,    29,
      30,     1,     2,     3,     4,     0,     5,    19,     0,    32,
       0,     6,    31,    33,    34,    35,    36,    28,    29,    30,
       0,    37,     0,     0,     0,    32,     0,    12,    38,    33,
      34,    35,    36,     1,     2,     3,     4,    37,     5,     0,
       0,    10,     0,     6,    63,     0,     0,     0,    32,    10,
       0,     0,    33,    34,    35,    36,    18,    18,     0,     0,
      37,     0,    26,     0,     0,     0,    24,    32,     0,     0,
       0,    33,    34,    35,    36,     1,     2,     3,     4,    37,
       5,     1,     2,     3,     4,     6,     5,     0,     0,     0,
       0,     6,     0,     0,     0,     7,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,     0,     0,    65,
      66,     0,    67,     0,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,     0,     0,    81,
      82,     0,     0,    55,     0,     0,     0,     7,     0,    65,
      66,     0,    67,    83,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,     0,     0,    81,
      82,     0,     0,     0,     0,     0,     0,     0,     0,    65,
      66,     0,    67,   126,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,     0,     0,    81,
      82,     0,     0,     0,     0,    65,    66,     0,    67,    99,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,     0,     0,    81,    82,     0,     0,     0,
       0,    65,    66,     0,    67,   120,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,     0,
       0,    81,    82,    66,     0,    67,     0,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
       0,     0,    81,    82,    67,     0,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,     0,
       0,    81,    82,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,     0,     0,    81,    82,
      -1,    -1,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,     0,     0,    81,    82,    -1,    -1,    -1,
      -1,    74,    75,    76,    77,    78,    79,    80,     0,     0,
      81,    82,    76,    77,    78,    79,    80,     0,     0,    81,
      82
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-64)))

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-1)))

static const yytype_int8 yycheck[] =
{
      32,    33,    34,    35,    36,    37,    69,    70,    69,    70,
      24,    28,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    39,    54,    55,    56,    59,
      60,    59,    60,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,     3,
       4,     5,     6,     7,     8,     9,    73,    11,    20,    69,
      70,    23,    16,    17,     3,     3,     4,     5,     6,     7,
       8,     9,     3,    11,    65,    65,     3,    71,    16,    17,
       3,    65,     3,    27,   116,   127,     8,   119,     3,     4,
       5,     6,     7,     8,     9,    -1,    11,    16,    -1,    53,
      -1,    16,    17,    57,    58,    59,    60,     3,     4,     5,
      -1,    65,    -1,    -1,    -1,    53,    -1,     0,    72,    57,
      58,    59,    60,     6,     7,     8,     9,    65,    11,    -1,
      -1,     0,    -1,    16,    72,    -1,    -1,    -1,    53,     8,
      -1,    -1,    57,    58,    59,    60,    15,    16,    -1,    -1,
      65,    -1,    21,    -1,    -1,    -1,    71,    53,    -1,    -1,
      -1,    57,    58,    59,    60,     6,     7,     8,     9,    65,
      11,     6,     7,     8,     9,    16,    11,    -1,    -1,    -1,
      -1,    16,    -1,    -1,    -1,    68,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    -1,    -1,    39,
      40,    -1,    42,    -1,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    -1,    -1,    59,
      60,    -1,    -1,    65,    -1,    -1,    -1,    68,    -1,    39,
      40,    -1,    42,    73,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    -1,    -1,    59,
      60,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,
      40,    -1,    42,    73,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    -1,    -1,    59,
      60,    -1,    -1,    -1,    -1,    39,    40,    -1,    42,    69,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    -1,    -1,    59,    60,    -1,    -1,    -1,
      -1,    39,    40,    -1,    42,    69,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    -1,
      -1,    59,    60,    40,    -1,    42,    -1,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      -1,    -1,    59,    60,    42,    -1,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    -1,
      -1,    59,    60,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    -1,    -1,    59,    60,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    -1,    -1,    59,    60,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    -1,    -1,
      59,    60,    52,    53,    54,    55,    56,    -1,    -1,    59,
      60
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,     7,     8,     9,    11,    16,    68,    75,    76,
      84,     3,     0,    76,     3,    65,    65,    77,    84,    77,
      69,    70,     3,    69,    71,    78,    84,    78,     3,     4,
       5,    17,    53,    57,    58,    59,    60,    65,    72,    79,
      80,    83,    84,     3,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    65,    65,    83,    83,    83,
      83,    83,    83,    72,    80,    39,    40,    42,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    59,    60,    73,     3,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    82,    83,    83,    69,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    28,    73,    69,    70,
      69,    83,    83,    78,    80,    81,    73,    27,    81
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (&yylloc, pParseData, YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (YYID (N))                                                     \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (YYID (0))
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

__attribute__((__unused__))
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
#else
static unsigned
yy_location_print_ (yyo, yylocp)
    FILE *yyo;
    YYLTYPE const * const yylocp;
#endif
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += fprintf (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += fprintf (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += fprintf (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += fprintf (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += fprintf (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, &yylloc, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval, &yylloc, pParseData)
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location, pParseData); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, ParseData * pParseData)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, pParseData)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    ParseData * pParseData;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
  YYUSE (pParseData);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, ParseData * pParseData)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp, pParseData)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    ParseData * pParseData;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, pParseData);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, ParseData * pParseData)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule, pParseData)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
    ParseData * pParseData;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       , pParseData);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule, pParseData); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, ParseData * pParseData)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp, pParseData)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
    ParseData * pParseData;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (pParseData);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YYUSE (yytype);
}




/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (ParseData * pParseData)
#else
int
yyparse (pParseData)
    ParseData * pParseData;
#endif
#endif
{
/* The lookahead symbol.  */
int yychar;


#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
static YYSTYPE yyval_default;
# define YY_INITIAL_VALUE(Value) = Value
#endif
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc = yyloc_default;


    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);

	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
	YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 4:
/* Line 1787 of yacc.c  */
#line 116 "compose.y"
    { (yyval.pAst) = ast_create_message_def((yyvsp[(2) - (6)].str), (yyvsp[(6) - (6)].pAst), pParseData); }
    break;

  case 5:
/* Line 1787 of yacc.c  */
#line 117 "compose.y"
    { (yyval.pAst) = ast_create_function_def((yyvsp[(2) - (6)].str), (yyvsp[(1) - (6)].dataType), (yyvsp[(6) - (6)].pAst), pParseData); }
    break;

  case 6:
/* Line 1787 of yacc.c  */
#line 121 "compose.y"
    { (yyval.pSymTab) = parsedata_add_symbol(pParseData, NULL, NULL); }
    break;

  case 7:
/* Line 1787 of yacc.c  */
#line 122 "compose.y"
    { (yyval.pSymTab) = parsedata_add_symbol(pParseData, NULL, symrec_create(kSYMT_Param, (yyvsp[(1) - (2)].dataType), (yyvsp[(2) - (2)].str), NULL)); }
    break;

  case 8:
/* Line 1787 of yacc.c  */
#line 123 "compose.y"
    { (yyval.pSymTab) = parsedata_add_symbol(pParseData, (yyvsp[(1) - (4)].pSymTab), symrec_create(kSYMT_Param, (yyvsp[(3) - (4)].dataType), (yyvsp[(4) - (4)].str), NULL)); }
    break;

  case 9:
/* Line 1787 of yacc.c  */
#line 127 "compose.y"
    { (yyval.pAst) = ast_append(NULL, NULL, pParseData); }
    break;

  case 10:
/* Line 1787 of yacc.c  */
#line 128 "compose.y"
    { (yyval.pAst) = (yyvsp[(2) - (3)].pAst); }
    break;

  case 11:
/* Line 1787 of yacc.c  */
#line 132 "compose.y"
    { (yyval.pAst) = ast_append(NULL, (yyvsp[(1) - (1)].pAst), pParseData); }
    break;

  case 12:
/* Line 1787 of yacc.c  */
#line 133 "compose.y"
    { (yyval.pAst) = ast_append((yyvsp[(1) - (2)].pAst), (yyvsp[(2) - (2)].pAst), pParseData); }
    break;

  case 13:
/* Line 1787 of yacc.c  */
#line 137 "compose.y"
    { (yyval.pAst) = NULL; parsedata_add_local_symbol(pParseData, symrec_create(kSYMT_Local, (yyvsp[(1) - (3)].dataType), (yyvsp[(2) - (3)].str), NULL)); }
    break;

  case 14:
/* Line 1787 of yacc.c  */
#line 138 "compose.y"
    { (yyval.pAst) = NULL; parsedata_add_local_symbol(pParseData, symrec_create(kSYMT_Local, (yyvsp[(1) - (5)].dataType), (yyvsp[(2) - (5)].str), (yyvsp[(4) - (5)].pAst))); }
    break;

  case 15:
/* Line 1787 of yacc.c  */
#line 140 "compose.y"
    { (yyval.pAst) = NULL; }
    break;

  case 16:
/* Line 1787 of yacc.c  */
#line 141 "compose.y"
    { (yyval.pAst) = NULL; }
    break;

  case 17:
/* Line 1787 of yacc.c  */
#line 143 "compose.y"
    { (yyval.pAst) = (yyvsp[(1) - (2)].pAst); }
    break;

  case 20:
/* Line 1787 of yacc.c  */
#line 152 "compose.y"
    { (yyval.pAst) = ast_append(NULL, NULL, pParseData); }
    break;

  case 21:
/* Line 1787 of yacc.c  */
#line 153 "compose.y"
    { (yyval.pAst) = ast_append(NULL, (yyvsp[(1) - (1)].pAst),   pParseData); }
    break;

  case 22:
/* Line 1787 of yacc.c  */
#line 154 "compose.y"
    { (yyval.pAst) = ast_append((yyvsp[(1) - (3)].pAst),   (yyvsp[(3) - (3)].pAst),   pParseData); }
    break;

  case 23:
/* Line 1787 of yacc.c  */
#line 158 "compose.y"
    { (yyval.pAst) = (yyvsp[(2) - (3)].pAst); }
    break;

  case 24:
/* Line 1787 of yacc.c  */
#line 160 "compose.y"
    { (yyval.pAst) = ast_create_binary_op(kAST_Add,    (yyvsp[(1) - (3)].pAst), (yyvsp[(3) - (3)].pAst), pParseData); }
    break;

  case 25:
/* Line 1787 of yacc.c  */
#line 161 "compose.y"
    { (yyval.pAst) = ast_create_binary_op(kAST_Sub,    (yyvsp[(1) - (3)].pAst), (yyvsp[(3) - (3)].pAst), pParseData); }
    break;

  case 26:
/* Line 1787 of yacc.c  */
#line 162 "compose.y"
    { (yyval.pAst) = ast_create_binary_op(kAST_Mul,    (yyvsp[(1) - (3)].pAst), (yyvsp[(3) - (3)].pAst), pParseData); }
    break;

  case 27:
/* Line 1787 of yacc.c  */
#line 163 "compose.y"
    { (yyval.pAst) = ast_create_binary_op(kAST_Div,    (yyvsp[(1) - (3)].pAst), (yyvsp[(3) - (3)].pAst), pParseData); }
    break;

  case 28:
/* Line 1787 of yacc.c  */
#line 164 "compose.y"
    { (yyval.pAst) = ast_create_binary_op(kAST_Mod,    (yyvsp[(1) - (3)].pAst), (yyvsp[(3) - (3)].pAst), pParseData); }
    break;

  case 29:
/* Line 1787 of yacc.c  */
#line 165 "compose.y"
    { (yyval.pAst) = ast_create_binary_op(kAST_LShift, (yyvsp[(1) - (3)].pAst), (yyvsp[(3) - (3)].pAst), pParseData); }
    break;

  case 30:
/* Line 1787 of yacc.c  */
#line 166 "compose.y"
    { (yyval.pAst) = ast_create_binary_op(kAST_RShift, (yyvsp[(1) - (3)].pAst), (yyvsp[(3) - (3)].pAst), pParseData); }
    break;

  case 31:
/* Line 1787 of yacc.c  */
#line 167 "compose.y"
    { (yyval.pAst) = ast_create_binary_op(kAST_And,    (yyvsp[(1) - (3)].pAst), (yyvsp[(3) - (3)].pAst), pParseData); }
    break;

  case 32:
/* Line 1787 of yacc.c  */
#line 168 "compose.y"
    { (yyval.pAst) = ast_create_binary_op(kAST_Or,     (yyvsp[(1) - (3)].pAst), (yyvsp[(3) - (3)].pAst), pParseData); }
    break;

  case 33:
/* Line 1787 of yacc.c  */
#line 169 "compose.y"
    { (yyval.pAst) = ast_create_binary_op(kAST_XOr,    (yyvsp[(1) - (3)].pAst), (yyvsp[(3) - (3)].pAst), pParseData); }
    break;

  case 34:
/* Line 1787 of yacc.c  */
#line 171 "compose.y"
    { (yyval.pAst) = ast_create_binary_op(kAST_Eq,  (yyvsp[(1) - (3)].pAst), (yyvsp[(3) - (3)].pAst), pParseData); }
    break;

  case 35:
/* Line 1787 of yacc.c  */
#line 172 "compose.y"
    { (yyval.pAst) = ast_create_binary_op(kAST_NEq, (yyvsp[(1) - (3)].pAst), (yyvsp[(3) - (3)].pAst), pParseData); }
    break;

  case 36:
/* Line 1787 of yacc.c  */
#line 173 "compose.y"
    { (yyval.pAst) = ast_create_binary_op(kAST_LT,  (yyvsp[(1) - (3)].pAst), (yyvsp[(3) - (3)].pAst), pParseData); }
    break;

  case 37:
/* Line 1787 of yacc.c  */
#line 174 "compose.y"
    { (yyval.pAst) = ast_create_binary_op(kAST_LTE, (yyvsp[(1) - (3)].pAst), (yyvsp[(3) - (3)].pAst), pParseData); }
    break;

  case 38:
/* Line 1787 of yacc.c  */
#line 175 "compose.y"
    { (yyval.pAst) = ast_create_binary_op(kAST_GT,  (yyvsp[(1) - (3)].pAst), (yyvsp[(3) - (3)].pAst), pParseData); }
    break;

  case 39:
/* Line 1787 of yacc.c  */
#line 176 "compose.y"
    { (yyval.pAst) = ast_create_binary_op(kAST_GTE, (yyvsp[(1) - (3)].pAst), (yyvsp[(3) - (3)].pAst), pParseData); }
    break;

  case 40:
/* Line 1787 of yacc.c  */
#line 178 "compose.y"
    { (yyval.pAst) = ast_create_assign_op(kAST_Assign,       (yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].pAst), pParseData); }
    break;

  case 41:
/* Line 1787 of yacc.c  */
#line 179 "compose.y"
    { (yyval.pAst) = ast_create_assign_op(kAST_AddAssign,    (yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].pAst), pParseData); }
    break;

  case 42:
/* Line 1787 of yacc.c  */
#line 180 "compose.y"
    { (yyval.pAst) = ast_create_assign_op(kAST_SubAssign,    (yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].pAst), pParseData); }
    break;

  case 43:
/* Line 1787 of yacc.c  */
#line 181 "compose.y"
    { (yyval.pAst) = ast_create_assign_op(kAST_MulAssign,    (yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].pAst), pParseData); }
    break;

  case 44:
/* Line 1787 of yacc.c  */
#line 182 "compose.y"
    { (yyval.pAst) = ast_create_assign_op(kAST_DivAssign,    (yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].pAst), pParseData); }
    break;

  case 45:
/* Line 1787 of yacc.c  */
#line 183 "compose.y"
    { (yyval.pAst) = ast_create_assign_op(kAST_ModAssign,    (yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].pAst), pParseData); }
    break;

  case 46:
/* Line 1787 of yacc.c  */
#line 184 "compose.y"
    { (yyval.pAst) = ast_create_assign_op(kAST_LShiftAssign, (yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].pAst), pParseData); }
    break;

  case 47:
/* Line 1787 of yacc.c  */
#line 185 "compose.y"
    { (yyval.pAst) = ast_create_assign_op(kAST_RShiftAssign, (yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].pAst), pParseData); }
    break;

  case 48:
/* Line 1787 of yacc.c  */
#line 186 "compose.y"
    { (yyval.pAst) = ast_create_assign_op(kAST_AndAssign,    (yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].pAst), pParseData); }
    break;

  case 49:
/* Line 1787 of yacc.c  */
#line 187 "compose.y"
    { (yyval.pAst) = ast_create_assign_op(kAST_XorAssign,    (yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].pAst), pParseData); }
    break;

  case 50:
/* Line 1787 of yacc.c  */
#line 188 "compose.y"
    { (yyval.pAst) = ast_create_assign_op(kAST_OrAssign,     (yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].pAst), pParseData); }
    break;

  case 51:
/* Line 1787 of yacc.c  */
#line 190 "compose.y"
    { (yyval.pAst) = ast_create_unary_op(kAST_Not,        (yyvsp[(2) - (2)].pAst), pParseData); }
    break;

  case 52:
/* Line 1787 of yacc.c  */
#line 191 "compose.y"
    { (yyval.pAst) = ast_create_unary_op(kAST_Complement, (yyvsp[(2) - (2)].pAst), pParseData); }
    break;

  case 53:
/* Line 1787 of yacc.c  */
#line 192 "compose.y"
    { (yyval.pAst) = ast_create_unary_op(kAST_Complement, (yyvsp[(2) - (2)].pAst), pParseData); }
    break;

  case 54:
/* Line 1787 of yacc.c  */
#line 194 "compose.y"
    { (yyval.pAst) = ast_create_unary_op(kAST_PreInc, (yyvsp[(2) - (2)].pAst), pParseData); }
    break;

  case 55:
/* Line 1787 of yacc.c  */
#line 195 "compose.y"
    { (yyval.pAst) = ast_create_unary_op(kAST_PreDec, (yyvsp[(2) - (2)].pAst), pParseData); }
    break;

  case 56:
/* Line 1787 of yacc.c  */
#line 196 "compose.y"
    { (yyval.pAst) = ast_create_unary_op(kAST_PostInc, (yyvsp[(1) - (2)].pAst), pParseData); }
    break;

  case 57:
/* Line 1787 of yacc.c  */
#line 197 "compose.y"
    { (yyval.pAst) = ast_create_unary_op(kAST_PostDec, (yyvsp[(1) - (2)].pAst), pParseData); }
    break;

  case 58:
/* Line 1787 of yacc.c  */
#line 199 "compose.y"
    { (yyval.pAst) = ast_create_int_literal((yyvsp[(1) - (1)].numi), pParseData); }
    break;

  case 59:
/* Line 1787 of yacc.c  */
#line 200 "compose.y"
    { (yyval.pAst) = ast_create_float_literal((yyvsp[(1) - (1)].numf), pParseData); }
    break;

  case 60:
/* Line 1787 of yacc.c  */
#line 202 "compose.y"
    { (yyval.pAst) = ast_create_function_call((yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].pAst), pParseData); }
    break;

  case 61:
/* Line 1787 of yacc.c  */
#line 203 "compose.y"
    { (yyval.pAst) = ast_create_symbol_ref((yyvsp[(1) - (1)].str), pParseData); }
    break;


/* Line 1787 of yacc.c  */
#line 2069 "compose_parser.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (&yylloc, pParseData, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (&yylloc, pParseData, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, &yylloc, pParseData);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp, pParseData);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, pParseData, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, pParseData);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp, pParseData);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2050 of yacc.c  */
#line 215 "compose.y"



static void yyprint (FILE * file, int type, YYSTYPE value)
{
    if (type < 128)
    {
        fprintf(file, "'%c'", type);
    }
    else
    {
        switch(type)
        {
        case IDENTIFIER:
            fprintf(file, "\"%s\"", value.str);
            break;
        case INT_LITERAL:
            fprintf(file, "%d", value.numi);
            break;
        case FLOAT_LITERAL:
            fprintf(file, "%f", value.numf);
            break;
        default:
            fprintf(file, "** yyprint unknown: %d", type);
            break;
        }
    }
}

