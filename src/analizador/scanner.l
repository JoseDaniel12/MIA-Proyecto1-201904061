%{
    // Compilar_con: flex --header-file=scanner.h -o scanner.cpp scanner.l
    // Nota: el comentario multiliena no srive cuando se ejecuta el exec por lee linea por linea y
    // puede quedar imcompleto y la expresion regular no casaria

    // Importaciones y codigo:
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

comentario [#[^\n]*]
ignorados [\n|\t|\s|$]+

letra       [a-zA-Z]
digito      [0-9]
entero      ("-")?{digito}+
numero      {entero}("."{digito}+)?
id          ({letra}|{entero})({letra}|{entero}|"_")*
password    ({letra}|{entero}|[!$@+*])+
cadena      "\""[^"\""]*"\""
extension   "."{id}
diagonal    "/"
ruta        ({diagonal}{id})*({diagonal}{id}{extension})?
directorio  ({diagonal}{id})+
filen       "-file"{digito}*

%%
"~"         { return COLOCHO; }
":"         { return DOSPTS; }
"="         { return IGUAL; }

"exit"      { return EXIT; }
"mkdisk"    { return MKDISK; }
"rmdisk"    { return RMDISK; }
"fdisk"     { return FDISK; }
"mount"     { return MOUNT; }
"umount"    { return UMOUNT; }
"mkfs"      { return MKFS; }
"login"     { return LOGIN; }
"mkgrp"     { return MKGRP; }
"rmgrp"     { return RMGRP; }
"rmusr"     { return RMUSR; }
"chmod"     { return CHMOD; }
"mkfile"    { return MKFILE; }
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
"pause"     { return PAUSE; }
"rep"       { return REP; }
"mkusr"     { return MKUSR; }
"logout"    { return LOGOUT; }

"-size"     { strcpy(yylval.text, yytext); return PARAM_SIZE; }
"-f"        { strcpy(yylval.text, yytext); return PARAM_F; }
"-u"        { strcpy(yylval.text, yytext); return PARAM_U; }
"-path"     { strcpy(yylval.text, yytext); return PARAM_PATH; }
"-type"     { strcpy(yylval.text, yytext); return PARAM_TYPE; }
"-delete"   { strcpy(yylval.text, yytext); return PARAM_DELETE; }
"-name"     { strcpy(yylval.text, yytext); return PARAM_NAME; }
"-add"      { strcpy(yylval.text, yytext); return PARAM_ADD; }
"-id"       { strcpy(yylval.text, yytext); return PARAM_ID; }
"-fs"       { strcpy(yylval.text, yytext); return PARAM_FS; }
"-user"     { strcpy(yylval.text, yytext); return PARAM_USER; }
"-pwd"      { strcpy(yylval.text, yytext); return PARAM_PWD; }
"-usr"      { strcpy(yylval.text, yytext); return PARAM_USR; }
"-grp"      { strcpy(yylval.text, yytext); return PARAM_GRP; }
"-ugo"      { strcpy(yylval.text, yytext); return PARAM_UGO; }
"-r"        { strcpy(yylval.text, yytext); return PARAM_R; }
"-cont"     { strcpy(yylval.text, yytext); return PARAM_CONT; }
"-stdin"    { strcpy(yylval.text, yytext); return PARAM_STDIN; }
"-filen"    { strcpy(yylval.text, yytext); return PARAM_STDIN; }
"-p"        { strcpy(yylval.text, yytext); return PARAM_P; }
"-dest"     { strcpy(yylval.text, yytext); return PARAM_DEST; }
"-ruta"     { strcpy(yylval.text, yytext); return PARAM_RUTA; }
"-root"     { strcpy(yylval.text, yytext); return PARAM_ROOT; }

{numero}    {strcpy(yylval.text, yytext); return NUMERO;}
{cadena}    {strcpy(yylval.text, yytext); return CADENA;}
{id}        {strcpy(yylval.text, yytext); return ID;}
{ruta}      {strcpy(yylval.text, yytext); return RUTA;}
{filen}     {strcpy(yylval.text, yytext); return FILEN;}

{comentario}
{ignorados}
"#".*

[[:blank:]] {}
.           {}

%%