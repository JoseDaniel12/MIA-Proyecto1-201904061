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
    NUMERO = 259,
    CADENA = 260,
    ID = 261,
    RUTA = 262,
    FILEN = 263,
    COLOCHO = 264,
    DOSPTS = 265,
    EXIT = 266,
    MKDISK = 267,
    RMDISK = 268,
    FDISK = 269,
    MOUNT = 270,
    UMOUNT = 271,
    MKFS = 272,
    LOGIN = 273,
    MKGRP = 274,
    RMGRP = 275,
    RMUSR = 276,
    CHMOD = 277,
    MKFILE = 278,
    CAT = 279,
    RM = 280,
    EDIT = 281,
    REN = 282,
    MKDIR = 283,
    CP = 284,
    MV = 285,
    FIND = 286,
    CHOWN = 287,
    CHGRP = 288,
    POUSE = 289,
    EXEC = 290,
    REP = 291,
    MKUSR = 292,
    LOGOUT = 293,
    PARAM_SIZE = 294,
    PARAM_F = 295,
    PARAM_U = 296,
    PARAM_PATH = 297,
    PARAM_TYPE = 298,
    PARAM_DELETE = 299,
    PARAM_NAME = 300,
    PARAM_ADD = 301,
    PARAM_ID = 302,
    PARAM_FS = 303,
    PARAM_USER = 304,
    PARAM_PWD = 305,
    PARAM_USR = 306,
    PARAM_GRP = 307,
    PARAM_UGO = 308,
    PARAM_CONT = 309,
    PARAM_STDIN = 310,
    PARAM_P = 311,
    PARAM_DEST = 312,
    PARAM_RUTA = 313,
    PARAM_ROOT = 314,
    PAUSE = 315,
    IGUAL = 316
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{

	char text[400];


};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
