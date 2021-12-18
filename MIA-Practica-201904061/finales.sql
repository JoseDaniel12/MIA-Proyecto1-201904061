use prueba;

DROP TABLE IF EXISTS geoname;
DROP TABLE IF EXISTS project;
DROP TABLE IF EXISTS level_1a;
DROP TABLE IF EXISTS transaction;
DROP TABLE IF EXISTS country_code;
DROP TABLE IF EXISTS location;
DROP TABLE IF EXISTS status;
DROP TABLE IF EXISTS currenci;


\! clear

-- __________________ Creacion de las tablas unidas _____________________________

-- __________ location __________

CREATE TABLE IF NOT EXISTS location (
    location_type_code VARCHAR(255),
    location_type_name VARCHAR(255)
);

INSERT INTO location
(location_type_code, location_type_name)
SELECT DISTINCT * FROM location_t;

SELECT COUNT(*) AS location_final_rows FROM location;


-- __________ status __________

CREATE TABLE IF NOT EXISTS status (
    name_status VARCHAR(255)
);

INSERT INTO status
(name_status)
SELECT DISTINCT status FROM project_t GROUP BY status;

SELECT COUNT(*) AS status_rows FROM status;


-- __________ currenci __________

CREATE TABLE IF NOT EXISTS currenci (
    name_currency VARCHAR(255)
);

INSERT INTO currenci
(name_currency)
SELECT DISTINCT transaction_currency FROM transaction_t GROUP BY transaction_currency;

SELECT COUNT(*) AS currenci_rows FROM currenci;


-- __________ country_code __________

CREATE TABLE IF NOT EXISTS country_code (
    name VARCHAR(255),
    iso2 VARCHAR(255),
    name_name VARCHAR(255),
    name_aiddata_code INT,
    name_aiddata_name VARCHAR(255),
    name_cow_alpha VARCHAR(255),
    name_cow_numeric INT,
    name_fao_code INT,
    name_fips VARCHAR(255),
    name_geonames_id INT,
    name_imf_code INT,
    name_iso2 VARCHAR(255),
    name_iso3 VARCHAR(255),
    name_iso_numeric INT,
    name_oecd_code INT,
    name_oecd_name VARCHAR(255),
    name_un_code INT,
    name_wb_code VARCHAR(255)
);

INSERT INTO country_code
(name, iso2, name_name, name_aiddata_code, name_aiddata_name, name_cow_alpha, name_cow_numeric,
name_fao_code, name_fips, name_geonames_id, name_imf_code, name_iso2, name_iso3,name_iso_numeric, 
name_oecd_code, name_oecd_name, name_un_code, name_wb_code)
SELECT DISTINCT * FROM country_code_t;

SELECT COUNT(*) AS country_code_final_rows FROM country_code;



-- __________ geoname __________

CREATE TABLE IF NOT EXISTS geoname (
    geoname_id INT,
    place_name VARCHAR(255),
    latitude FLOAT,
    longitude FLOAT,
    location_type_code VARCHAR(255),
    location_type_name VARCHAR(255),
    gazetteer_adm_code VARCHAR(255),
    gazetteer_adm_name VARCHAR(255),
    location_class INT,
    geographic_exactness INT
);

INSERT INTO geoname
(geoname_id, place_name, latitude, longitude, location_type_code, location_type_name, 
gazetteer_adm_code, gazetteer_adm_name, location_class, geographic_exactness)
SELECT DISTINCT * FROM geoname_t;

SELECT COUNT(*) AS geoname_final_rows FROM geoname;



-- __________ project __________

CREATE TABLE IF NOT EXISTS project (
    project_id VARCHAR(255),
    is_geocoded  INT,
    project_title VARCHAR(255),
    start_actual_isodate DATE,
    end_actual_isodate DATE,
    donors VARCHAR(255),
    donors_iso3 VARCHAR(255),
    recipients VARCHAR(255),
    recipients_iso3 VARCHAR(255),
    ad_sector_codes varchar(255),
    ad_sector_names varchar(255),
    status VARCHAR(255),
    transactions_start_year VARCHAR(255),
    transactions_end_year VARCHAR(255),
    total_commitments  DECIMAL(65, 30),
    total_disbursements DECIMAL(65, 30)
);

INSERT INTO project
(project_id, is_geocoded, project_title, start_actual_isodate, end_actual_isodate, donors,
donors_iso3, recipients, recipients_iso3, ad_sector_codes, ad_sector_names, status,
transactions_start_year, transactions_end_year, total_commitments, total_disbursements)
SELECT DISTINCT * FROM project_t;

SELECT COUNT(*) AS project_final_rows FROM project;


-- __________ level_1a __________

CREATE TABLE IF NOT EXISTS level_1a (   
    project_id VARCHAR(255),
    project_location_id VARCHAR(255),
    geoname_id INT,
    transactions_start_year YEAR,
    transactions_end_year YEAR,
    even_split_commitments VARCHAR(255),
    even_split_disbursements DECIMAL(65, 30)
);

INSERT INTO level_1a
(project_id, project_location_id, geoname_id, transactions_start_year, transactions_end_year,
even_split_commitments, even_split_disbursements)
SELECT DISTINCT * FROM level_1a_t;

SELECT COUNT(*) AS level_1a_final_rows FROM level_1a;


-- __________ transaction __________

CREATE TABLE IF NOT EXISTS transaction (
    transaction_id VARCHAR(255),
    project_id VARCHAR(255),
    transaction_isodate DATE,
    transaction_year YEAR,
    transaction_value_code CHAR,
    transaction_currency VARCHAR(255),
    transaction_value DECIMAL(65, 30)
);

INSERT INTO transaction
(transaction_id, project_id, transaction_isodate, transaction_year, transaction_value_code, 
transaction_currency, transaction_value)
SELECT DISTINCT * FROM transaction_t;

SELECT COUNT(*) AS transaction_final_rows FROM transaction;
