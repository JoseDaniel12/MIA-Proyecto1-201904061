\! clear

CREATE DATABASE IF NOT EXISTS prueba;

use prueba;

DROP TEMPORARY TABLE IF EXISTS geoname_t;
DROP TEMPORARY TABLE IF EXISTS project_t;
DROP TEMPORARY TABLE IF EXISTS level_1a_t;
DROP TEMPORARY TABLE IF EXISTS transaction_t;
DROP TEMPORARY TABLE IF EXISTS country_code_t;
DROP TEMPORARY TABLE IF EXISTS location_t;

DROP TABLE IF EXISTS transaction;
DROP TABLE IF EXISTS level_1a;
DROP TABLE IF EXISTS project;
DROP TABLE IF EXISTS geoname;
DROP TABLE IF EXISTS country_code;
DROP TABLE IF EXISTS currenci;
DROP TABLE IF EXISTS status;
DROP TABLE IF EXISTS location;
