#!/usr/bin/bash

# chmod +x practica.sh, para convertir el archivo en ejecutable

cat temporales.sql finales.sql  consultas.sql | sudo mysql -u root -p