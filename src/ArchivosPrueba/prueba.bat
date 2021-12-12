MKdisk -sizE=120 -u=M -path="/home/archivos/fase2/D1.dk" -f=FF
mkdisK -sizE=120 -u=M -path="/home/archivos/fase2/D2.dk" -f=FF

#Disco1
Mkdisk -size=320 -path=/home/user/Disco1.dk -u=k 

#Disco2
Mkdisk -size=32 -path=/home/user/Disco2.dk -u=k 

#CREAR PARTICIÓN 1 EN DISCO1
fdisk -sizE=72 -path=/home/user/Disco1.dk -name=Particion1

#CREAR PARTICIÓN 1 EN DISCO2
fdisk -sizE=8 -path=/home/user/Disco2.dk -name=Particion1

#CREAR PARTICIÓN 2 EN DISCO1
fdisk -sizE=40 -path=/home/user/Disco1.dk -name=Particion2

#ELIMINACIÓN DE LA PARTICIÓN 1 DE DISCO1
fdisk -delete=fast -name=Particion1 -path="/home/user/Disco1.dk"

pause

fdisk -sizE=20 -u=M -path="/home/archivos/fase2/D1.dk" -type=P -f=FF -name="PRI1"
fdisk -path="/home/archivos/fase2/D1.dk" -sizE=10000 -f=BF -name="PRI2"
fdisk -u=M -path="/home/archivos/fase2/D1.dk" -sizE=10 -name="PRI3"

fdisk -sizE=10 -u=M -path="/home/archivos/fase2/D2.dk" -type=P -f=FF -name="PRI1"
fdisk -path="/home/archivos/fase2/D2.dk" -sizE=10000 -f=BF -name="PRI2"
fdisk -u=M -path="/home/archivos/fase2/D2.dk" -sizE=10 -name="PRI3"

#CREAR PARTICION EXTENDIDA EN DISCO1
fdisk -size=20 -u=M -path="/home/archivos/fase2/D2.dk" -name=Particion3 -type=E
fdisk -size=5 -u=M -path="/home/archivos/fase2/D2.dk" -name=logica1 -type=L
fdisk -size=5 -u=M -path="/home/archivos/fase2/D2.dk" -name=logica2 -type=L
fdisk -size=5 -u=M -path="/home/archivos/fase2/D2.dk" -name=logica3 -type=L
fdisk -size=5 -u=M -path="/home/archivos/fase2/D2.dk" -name=logica4 -type=L
fdisk -delete=FAST -name=logica1 -path="/home/archivos/fase2/D2.dk"
fdisk -delete=FAST -name=logica3 -path="/home/archivos/fase2/D2.dk"
fdisk -size=5 -u=M -f=WF -path="/home/archivos/fase2/D2.dk" -name=logica3 -type=L

mouNt -NamE="PRI1"  -path="/home/archivos/fase2/D2.dk"
moUnt -PAth="/home/archivos/fase2/D2.dk" -name="PRI2"
mouNt -path="/home/archivos/fase2/D1.dk" -NamE="PRI1"
moUnt -name="PRI2" -PAth="/home/archivos/fase2/D1.dk"

mkfs -id="vd1a" -type=Full 
Mkfs -id="vd1b" 

#Usuario de generacion es 201700308 -> 08

loGin -usr=root -pwd=123 -id="vd1a"

#Crearemos un grupo llamado "Barcelona" ,"Real Madrid" y "Atletico Madrid"

mkgrp -name="Barcelona"
mkgrp -name="Real Madrid"
mkgrp -name="Atletico Madrid"

#Crearemos 3 usuarios llamados user1, user2 y user3

Mkusr -usr="user1" -grp="Barcelona" -pwd=user1
Mkusr -usr="user2" -grp="Real Madrid" -pwd=user2
Mkusr -usr="user3" -grp="Barcelona" -pwd=user3

LogouT

#nos logueamos en la particion PRI1 con nuestro usuario root
loGin -usr=root -pwd=123 -id="vd1b"

#Crearemos un grupo llamado "Barcelona" ,"Real Madrid" y "Atletico Madrid"
mkgrp -name="Barcelona"
mkgrp -name="Real Madrid"
mkgrp -name="Atletico Madrid"

#Crearemos 3 usuarios llamados user1, user2 y user3
Mkusr -usr="user4" -grp="Barcelona" -pwd=123
Mkusr -usr="user5" -grp="Real Madrid" -pwd=123
Mkusr -usr="user6" -grp="Barcelona" -pwd=123

LogouT

pause

#Cerramos sesión e iniciamos sesión con vd1a

LogouT

loGin -usr=root -pwd=123 -id="vd1a"

#Creamos la ruta y las padres que no existan

mkdir -path="/home/archivos/mia/fase2" -p
mkdir -p -path="/home/archivos/mia/carpeta2" 

mkdir -path="/home/archivos/mia/carpeta2/a1"
mkdir -path="/home/archivos/mia/carpeta2/a2"
mkdir -path="/home/archivos/mia/carpeta2/a3"
mkdir -path="/home/archivos/mia/carpeta2/a4"
mkdir -path="/home/archivos/mia/carpeta2/a5"
mkdir -path="/home/archivos/mia/carpeta2/a6"
mkdir -path="/home/archivos/mia/carpeta2/a7"
mkdir -path="/home/archivos/mia/carpeta2/a8"
mkdir -path="/home/archivos/mia/carpeta2/a9"
mkdir -path="/home/archivos/mia/carpeta2/a10"
mkdir -path="/home/archivos/mia/fase2/a1"
mkdir -path="/home/archivos/mia/fase2/a2"
mkdir -path="/home/archivos/mia/fase2/a3"
mkdir -path="/home/archivos/mia/fase2/a4"
mkdir -path="/home/archivos/mia/fase2/a5"
mkdir -path="/home/archivos/mia/fase2/a6"
mkdir -path="/home/archivos/mia/fase2/a7"
mkdir -path="/home/archivos/mia/fase2/a8"
mkdir -path="/home/archivos/mia/fase2/a9"
mkdir -path="/home/archivos/mia/fase2/a10"
mkdir -path="/home/archivos/mia/fase2/a11"
mkdir -path="/home/archivos/mia/fase2/a12"
mkdir -path="/home/archivos/mia/fase2/a13"
mkdir -path="/home/archivos/mia/fase2/a14"
mkdir -path="/home/archivos/mia/fase2/a15"
mkdir -path="/home/archivos/mia/fase2/a16"
mkdir -path="/home/archivos/mia/fase2/a17"
mkdir -path="/home/archivos/mia/fase2/a18"
mkdir -path="/home/archivos/mia/fase2/a19"
mkdir -path="/home/archivos/mia/fase2/a20"
mkdir -path="/home/archivos/mia/fase2/a21"
mkdir -path="/home/archivos/mia/fase2/a22"
mkdir -path="/home/archivos/mia/fase2/a23"
mkdir -path="/home/archivos/mia/fase2/a24"
mkdir -path="/home/archivos/mia/fase2/a25"
mkdir -path="/home/archivos/mia/fase2/a26"
mkdir -path="/home/archivos/mia/fase2/a27"
mkdir -path="/home/archivos/mia/fase2/a28"
mkdir -path="/home/archivos/mia/fase2/a29"
mkdir -path="/home/archivos/mia/fase2/a30"
mkdir -path="/home/archivos/mia/fase2/a31"
mkdir -path="/home/archivos/mia/fase2/a32"
mkdir -path="/home/archivos/mia/fase2/a33"

pause

#GENERACION DE REPORTES

rep -id="vd1a" -Path="/home/user/reports/reporte_1.jpg" -name=mbr
rep -id="vd1a" -Path="/home/user/reports/disko.jpg" -name=disk

pause

#NO CREA EL ARCHIVO
mkfile -path="/home/user/Noexiste/FIFA/pEPe.txt"

mkFile -SIZE=100 -PatH="/home/archivos/mia/fase2/archivito/a.txt" -r
mkfile -path="/home/b.txt" -SIZE=100

cat -file = "/home/b.txt"

#DEBE CREAR EL archivo arch.txt en su compu o concatenar el contenido del cont como sea esta bien -----
mkfile -path=/home/c.txt -r -cont="/home/arch.txt" 
mkfile -SIZE=37 -path="/home/cal.txt" -cont="/home/user/b.txt" #Archivo b tiene que existir en la ruta

pause

logouT

loGin -usr=root -pwd=123 -id="vd1b"

#Crearemos la ruta y las padres que no existan
mkdir -path="/home/archivos/mia/fase2" -p
mkdir -p -path="/home/archivos/mia/carpeta2" 

mkdir -path="/home/archivos/mia/carpeta2/b1"
mkdir -path="/home/archivos/mia/carpeta2/b2"
mkdir -path="/home/archivos/mia/carpeta2/b3"
mkdir -path="/home/archivos/mia/carpeta2/b4"
mkdir -path="/home/archivos/mia/carpeta2/b5"
mkdir -path="/home/archivos/mia/carpeta2/b6"
mkdir -path="/home/archivos/mia/carpeta2/b7"
mkdir -path="/home/archivos/mia/carpeta2/b8"
mkdir -path="/home/archivos/mia/carpeta2/b9"
mkdir -path="/home/archivos/mia/carpeta2/b10"

logouT