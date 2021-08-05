//Compilar_con: bison --no-lines --skeleton=yacc.c --defines=parser.h --output=parser.cpp parser.y
//Importaciones y codigo:
%{
    #include "scanner.h" //se importa el header del analisis semantico
    #include <iostream>
    #include "../Command.h"

    extern int yylineno;
    extern int columna;
    extern char *yytext;

    using namespace std;

    Command* resAnalizer = NULL;

    void yyerror(const char* mens) {
    	std::cout << "";
    }
%}

//Salidas del parser:
%defines "parser.h"
%output "parser.cpp"
%locations

//Tipos de tokens:
%union {
	int ival;
	float fval;
	char text[400];
	class Nodo *nodito;
}
%type<Command> command

%token DESCONOCIDO ENTERO CADENA CARACTER ID

%token EXIT MKDISK RMDISK MOUNT UNMOUNT LOGIN MKGRP RMGRP RMUSR CHMOD TOUCH CAT RM EDIT REN MKDIR CP MV FIND CHOWN
%token CHGRP POUSE EXEC REP

%token PARAM_SIZE PARAM_F PARAM_U PARAM_PATH PARAM_TYPE PARAM_DELETE PARAM_NAME PARAM_ADD PARAM_ID PARAM_FS
%token PARAM_USER PARAM_PWD PARAM_USR PARAM_GRP PARAM_UGO PARAM_R PARAM_CONT PARAM_STDIN PARAM_P
%token PARAM_DEST PARAM_RUTA PARAM_ROOT

//Precedencias:
%token IGUAL

//Gramatica:
%start command
%%

command:
	MKDISK param_declarations	{ resAnalizer = new Command(); }
	|MKDISK				{ resAnalizer = new Command(); }
;


param_declarations:
	param_declarations param_declaration	{}
	|param_declaration			{}
;

param_declaration:
	PARAM_SIZE IGUAL ENTERO		{}
	|PARAM_F IGUAL ID		{}
;

%%
