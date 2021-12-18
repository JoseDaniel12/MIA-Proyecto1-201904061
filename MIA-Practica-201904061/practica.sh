#!/usr/bin/bash

# chmod +x practica.sh, para convertir el archivo en ejecutable

cat eliminarTablas.sql crear_base_datos.sql roles.sql temporales.sql carga_country_codes.sql carga_geonames.sql carga_level_1a.sql carga_locations.sql carga_projects.sql carga_transactions.sql finales.sql | sudo mysql -u root -p