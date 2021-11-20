/* A Bison parser, made by GNU Bison 3.7.6.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    DESCONOCIDO = 258,             /* DESCONOCIDO  */
    NUMERO = 259,                  /* NUMERO  */
    CADENA = 260,                  /* CADENA  */
    ID = 261,                      /* ID  */
    RUTA = 262,                    /* RUTA  */
    EXIT = 263,                    /* EXIT  */
    MKDISK = 264,                  /* MKDISK  */
    RMDISK = 265,                  /* RMDISK  */
    FDISK = 266,                   /* FDISK  */
    MOUNT = 267,                   /* MOUNT  */
    UMOUNT = 268,                  /* UMOUNT  */
    MKFS = 269,                    /* MKFS  */
    LOGIN = 270,                   /* LOGIN  */
    MKGRP = 271,                   /* MKGRP  */
    RMGRP = 272,                   /* RMGRP  */
    RMUSR = 273,                   /* RMUSR  */
    CHMOD = 274,                   /* CHMOD  */
    TOUCH = 275,                   /* TOUCH  */
    CAT = 276,                     /* CAT  */
    RM = 277,                      /* RM  */
    EDIT = 278,                    /* EDIT  */
    REN = 279,                     /* REN  */
    MKDIR = 280,                   /* MKDIR  */
    CP = 281,                      /* CP  */
    MV = 282,                      /* MV  */
    FIND = 283,                    /* FIND  */
    CHOWN = 284,                   /* CHOWN  */
    CHGRP = 285,                   /* CHGRP  */
    POUSE = 286,                   /* POUSE  */
    EXEC = 287,                    /* EXEC  */
    REP = 288,                     /* REP  */
    PARAM_SIZE = 289,              /* PARAM_SIZE  */
    PARAM_F = 290,                 /* PARAM_F  */
    PARAM_U = 291,                 /* PARAM_U  */
    PARAM_PATH = 292,              /* PARAM_PATH  */
    PARAM_TYPE = 293,              /* PARAM_TYPE  */
    PARAM_DELETE = 294,            /* PARAM_DELETE  */
    PARAM_NAME = 295,              /* PARAM_NAME  */
    PARAM_ADD = 296,               /* PARAM_ADD  */
    PARAM_ID = 297,                /* PARAM_ID  */
    PARAM_FS = 298,                /* PARAM_FS  */
    PARAM_USER = 299,              /* PARAM_USER  */
    PARAM_PWD = 300,               /* PARAM_PWD  */
    PARAM_USR = 301,               /* PARAM_USR  */
    PARAM_GRP = 302,               /* PARAM_GRP  */
    PARAM_UGO = 303,               /* PARAM_UGO  */
    PARAM_R = 304,                 /* PARAM_R  */
    PARAM_CONT = 305,              /* PARAM_CONT  */
    PARAM_STDIN = 306,             /* PARAM_STDIN  */
    PARAM_P = 307,                 /* PARAM_P  */
    PARAM_DEST = 308,              /* PARAM_DEST  */
    PARAM_RUTA = 309,              /* PARAM_RUTA  */
    PARAM_ROOT = 310,              /* PARAM_ROOT  */
    IGUAL = 311                    /* IGUAL  */
  };
  typedef enum yytokentype yytoken_kind_t;
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
