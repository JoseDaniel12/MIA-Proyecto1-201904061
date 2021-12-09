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
    EXIT = 264,
    MKDISK = 265,
    RMDISK = 266,
    FDISK = 267,
    MOUNT = 268,
    UMOUNT = 269,
    MKFS = 270,
    LOGIN = 271,
    MKGRP = 272,
    RMGRP = 273,
    RMUSR = 274,
    CHMOD = 275,
    MKFILE = 276,
    CAT = 277,
    RM = 278,
    EDIT = 279,
    REN = 280,
    MKDIR = 281,
    CP = 282,
    MV = 283,
    FIND = 284,
    CHOWN = 285,
    CHGRP = 286,
    POUSE = 287,
    EXEC = 288,
    REP = 289,
    PARAM_SIZE = 290,
    PARAM_F = 291,
    PARAM_U = 292,
    PARAM_PATH = 293,
    PARAM_TYPE = 294,
    PARAM_DELETE = 295,
    PARAM_NAME = 296,
    PARAM_ADD = 297,
    PARAM_ID = 298,
    PARAM_FS = 299,
    PARAM_USER = 300,
    PARAM_PWD = 301,
    PARAM_USR = 302,
    PARAM_GRP = 303,
    PARAM_UGO = 304,
    PARAM_R = 305,
    PARAM_CONT = 306,
    PARAM_STDIN = 307,
    PARAM_P = 308,
    PARAM_DEST = 309,
    PARAM_RUTA = 310,
    PARAM_ROOT = 311,
    IGUAL = 312
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
