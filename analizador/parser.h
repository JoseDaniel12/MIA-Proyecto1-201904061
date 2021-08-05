/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
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
    DESCONOCIDO = 258,
    ENTERO = 259,
    CADENA = 260,
    CARACTER = 261,
    ID = 262,
    EXIT = 263,
    MKDISK = 264,
    RMDISK = 265,
    MOUNT = 266,
    UNMOUNT = 267,
    LOGIN = 268,
    MKGRP = 269,
    RMGRP = 270,
    RMUSR = 271,
    CHMOD = 272,
    TOUCH = 273,
    CAT = 274,
    RM = 275,
    EDIT = 276,
    REN = 277,
    MKDIR = 278,
    CP = 279,
    MV = 280,
    FIND = 281,
    CHOWN = 282,
    CHGRP = 283,
    POUSE = 284,
    EXEC = 285,
    REP = 286,
    PARAM_SIZE = 287,
    PARAM_F = 288,
    PARAM_U = 289,
    PARAM_PATH = 290,
    PARAM_TYPE = 291,
    PARAM_DELETE = 292,
    PARAM_NAME = 293,
    PARAM_ADD = 294,
    PARAM_ID = 295,
    PARAM_FS = 296,
    PARAM_USER = 297,
    PARAM_PWD = 298,
    PARAM_USR = 299,
    PARAM_GRP = 300,
    PARAM_UGO = 301,
    PARAM_R = 302,
    PARAM_CONT = 303,
    PARAM_STDIN = 304,
    PARAM_P = 305,
    PARAM_DEST = 306,
    PARAM_RUTA = 307,
    PARAM_ROOT = 308,
    IGUAL = 309
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{

	int ival;
	float fval;
	char text[400];
	class Nodo *nodito;


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


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
