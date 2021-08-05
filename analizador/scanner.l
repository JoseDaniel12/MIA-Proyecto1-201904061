%{
    //Compilar_con: flex --header-file=scanner.h -o scanner.cpp scanner.l
    //Importaciones y codigo:
    #include <iostream>
    #include "parser.h"

    int yylex();
    void yyerror(const char *s);
    int linea=0;
    int columna = 0;
    int anterior = 0;

%}

%option case-insensitive
%option noyywrap


letra       [a-zA-Z]
entero      ("-")?[0-9]+
caracter    ({letra}|{entero})
id          {letra}({letra}|{entero}|"_")*
password    ({letra}|{entero}|[!$@+*])+
cadena      "\""[^"\""]*"\""
extension   "."{id}
diagonal    "/"
ruta        ({diagonal}{id})*({diagonal}{id}{extension})
directorio  ({diagonal}{id})+

%%
"="         { return IGUAL; }

"exit"      { return EXIT; }
"mkdisk"    { return MKDISK; }
"rmdisk"    { return RMDISK; }
"mount"     { return MOUNT; }
"unmount"   { return UNMOUNT; }
"login"     { return LOGIN; }
"mkgrp"     { return MKGRP; }
"rmgrp"     { return RMGRP; }
"rmusr"     { return RMUSR; }
"chmod"     { return CHMOD; }
"touch"     { return TOUCH; }
"cat"       { return CAT; }
"rm"        { return RM; }
"edit"      { return EDIT; }
"ren"       { return REN; }
"mkdir"     { return MKDIR; }
"cp"        { return CP; }
"mv"        { return MV; }
"find"      { return FIND; }
"chown"     { return CHOWN; }
"chgrp"     { return CHGRP; }
"pouse"     { return POUSE; }
"exec"      { return EXEC; }
"rep"       { return REP; }


"-size"     { return PARAM_SIZE; }
"-f"        { return PARAM_F; }
"-u"        { return PARAM_U; }
"-path"     { return PARAM_PATH; }
"-type"     { return PARAM_TYPE; }
"-delete"   { return PARAM_DELETE; }
"-name"     { return PARAM_NAME; }
"-add"      { return PARAM_ADD; }
"-id"       { return PARAM_ID; }
"-fs"       { return PARAM_FS; }
"-user"     { return PARAM_USER; }
"-pwd"      { return PARAM_PWD; }
"-usr"      { return PARAM_USR; }
"-grp"      { return PARAM_GRP; }
"-ugo"      { return PARAM_UGO; }
"-r"        { return PARAM_R; }
"-cont"     { return PARAM_CONT; }
"-stdin"    { return PARAM_STDIN; }
"-filen"    { return PARAM_STDIN; }
"-p"        { return PARAM_P; }
"-dest"     { return PARAM_DEST; }
"-ruta"     { return PARAM_RUTA; }
"-root"     { return PARAM_ROOT; }

{entero}    {strcpy(yylval.text, yytext); return ENTERO;}
{caracter}  {strcpy(yylval.text, yytext); return CARACTER;}
{cadena}    {strcpy(yylval.text, yytext); return CADENA;}
{id}        {strcpy(yylval.text, yytext); return ID;}
[[:blank:]] {}
.           {strcpy(yylval.text, yytext); return DESCONOCIDO; }

%%