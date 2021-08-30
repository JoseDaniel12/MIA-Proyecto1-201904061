//Compilar_con: bison --no-lines --skeleton=yacc.c --defines=parser.h --output=parser.cpp parser.y
//Importaciones y codigo:
%{
    #include "scanner.h" //se importa el header del analisis semantico
    #include <bits/stdc++.h>
    #include <iostream>
    #include <string>
    #include <vector>
    #include "../comandos/Command.h"
    #include "../comandos/Mkdisk.h"
    #include "../comandos/Rmdisk.h"
    #include "../comandos/Fdisk.h"
    #include "../comandos/Mount.h"
    #include "../comandos/Umount.h"
    #include "../comandos/Mkfs.h"
    #include "../comandos/Param.h"
    #include "../comandos/Rep.h"

    extern int yylineno;
    extern int columna;
    extern char *yytext;

    using namespace std;

    Command* resAnalizer = NULL;
    vector<Param> paramVector;
    string paramValue;
    string paramName;

    void yyerror(const char* mens) {
    	std::cout << "";
    }

    string toUpper(string s) {
    	string res = "";
	for (int i = 0; i < s.length(); i++) {
		res += toupper(s[i]);
	}
	return res;
    }
%}

//Tipos de tokens:
%union {
	char text[400];
}

%token<text> DESCONOCIDO NUMERO CADENA ID RUTA

%token<text> EXIT MKDISK RMDISK FDISK MOUNT UMOUNT MKFS LOGIN MKGRP RMGRP RMUSR CHMOD TOUCH CAT
%token<text> RM EDIT REN MKDIR CP MV FIND CHOWN CHGRP POUSE EXEC REP

%token<text> PARAM_SIZE PARAM_F PARAM_U PARAM_PATH PARAM_TYPE PARAM_DELETE PARAM_NAME PARAM_ADD PARAM_ID PARAM_FS
%token<text> PARAM_USER PARAM_PWD PARAM_USR PARAM_GRP PARAM_UGO PARAM_R PARAM_CONT PARAM_STDIN PARAM_P
%token<text> PARAM_DEST PARAM_RUTA PARAM_ROOT


//Precedencias:
%left IGUAL

//Gramatica:
%start command
%%

command:
	MKDISK params_declaration	{ resAnalizer = new Mkdisk(paramVector); paramVector.clear(); }
	|RMDISK params_declaration	{ resAnalizer = new Rmdisk(paramVector); paramVector.clear(); }
	|FDISK params_declaration	{ resAnalizer = new Fdisk(paramVector); paramVector.clear(); }
	|MOUNT params_declaration	{ resAnalizer = new Mount(paramVector); paramVector.clear(); }
	|UMOUNT params_declaration	{ resAnalizer = new Umount(paramVector); paramVector.clear(); }
	|MKFS params_declaration	{ resAnalizer = new Mkfs(paramVector); paramVector.clear(); }
	|REP params_declaration		{ resAnalizer = new Rep(paramVector); paramVector.clear(); }
	|EXIT				{}

;

params_declaration:
	params_declaration param_declaration	{}
	|param_declaration			{}
;

param_declaration:
	param_name IGUAL param_value	{ paramVector.push_back(*new Param(toUpper(paramName), paramValue)); }
;

param_name:
	PARAM_SIZE  	{ paramName = $1; }
	|PARAM_U	{ paramName = $1; }
	|PARAM_F	{ paramName = $1; }
	|PARAM_PATH	{ paramName = $1; }
	|PARAM_TYPE	{ paramName = $1; }
	|PARAM_DELETE	{ paramName = $1; }
	|PARAM_NAME	{ paramName = $1; }
	|PARAM_ADD	{ paramName = $1; }
	|PARAM_ID	{ paramName = $1; }
	|PARAM_FS	{ paramName = $1; }
	|PARAM_USER	{ paramName = $1; }
	|PARAM_PWD	{ paramName = $1; }
	|PARAM_USR	{ paramName = $1; }
	|PARAM_GRP	{ paramName = $1; }
	|PARAM_UGO	{ paramName = $1; }
	|PARAM_R	{ paramName = $1; }
	|PARAM_CONT	{ paramName = $1; }
	|PARAM_STDIN	{ paramName = $1; }
	|PARAM_P	{ paramName = $1; }
	|PARAM_DEST	{ paramName = $1; }
	|PARAM_RUTA	{ paramName = $1; }
	|PARAM_ROOT	{ paramName = $1; }
;

param_value:
	NUMERO	{ paramValue = $1; }
	|RUTA	{ paramValue = $1; }
	|ID	{ paramValue = $1; }
	|CADENA	{ paramValue = $1; }
;

%%
