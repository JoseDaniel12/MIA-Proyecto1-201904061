DROP TABLE geoname_t;
DROP TABLE project_t;
DROP TABLE level_1a_t;
DROP TABLE transaction_t;
DROP TABLE country_code_t;
DROP TABLE location_t;


\! clear

CREATE DATABASE prueba;
USE prueba;  


-- __________ Tablas de la Asociación Internacional de Fomento (IDA) __________

-- __________ geoname_t __________

CREATE TEMPORARY TABLE IF NOT EXISTS geoname_t (
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

LOAD DATA INFILE '/var/lib/mysql-files/geonames.csv' 
INTO TABLE geoname_t 
FIELDS TERMINATED BY ',' 
ENCLOSED BY '\"'
LINES TERMINATED BY '\n'
IGNORE 1 ROWS;

SELECT COUNT(*) AS geonames_t_rows FROM geoname_t;


-- __________ project_t __________

CREATE TEMPORARY TABLE IF NOT EXISTS project_t (
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
    total_commitments  VARCHAR(255),
    total_disbursements VARCHAR(255)
);

LOAD DATA INFILE '/var/lib/mysql-files/projects.csv' 
INTO TABLE project_t
CHARACTER SET latin1
FIELDS TERMINATED BY ','  
ENCLOSED BY '\"'
LINES TERMINATED BY '\n'
IGNORE 1 ROWS
(project_id, is_geocoded, project_title, @start_actual_isodate, @end_actual_isodate, donors,
donors_iso3, recipients, recipients_iso3, ad_sector_codes, ad_sector_names, status,
transactions_start_year, transactions_end_year, total_commitments, total_disbursements)
SET start_actual_isodate = STR_TO_DATE(@start_actual_isodate, '%d/%m/%Y'),
    end_actual_isodate = IF (STRCMP(@end_actual_isodate,"") = 0, NULL, STR_TO_DATE(@end_actual_isodate, '%d/%m/%Y'))
;



SELECT COUNT(*) AS projects_t_rows FROM project_t;


-- __________ level_1a_t __________

CREATE TEMPORARY TABLE IF NOT EXISTS level_1a_t (   
    project_id VARCHAR(255),
    project_location_id VARCHAR(255),
    geoname_id INT,
    transactions_start_year YEAR,
    transactions_end_year YEAR,
    even_split_commitments VARCHAR(255),
    even_split_disbursements DECIMAL(65, 30)
);

LOAD DATA INFILE '/var/lib/mysql-files/level_1a.csv'
INTO TABLE level_1a_t
CHARACTER SET latin1
FIELDS TERMINATED BY ','
ENCLOSED BY '\"'
LINES TERMINATED BY '\n'
IGNORE 1 ROWS
(project_id, project_location_id, geoname_id, transactions_start_year, transactions_end_year,
even_split_commitments, @even_split_disbursements)
SET even_split_disbursements = NULLIF(@even_split_disbursements, 0.0);


SELECT COUNT(*) AS level_1a_t_rows FROM level_1a_t;



-- ______ The International Banc for Reconstruction and Develpmnet (IBDR) ______

-- __________ transaction_t __________

CREATE TEMPORARY TABLE IF NOT EXISTS transaction_t (
    transaction_id VARCHAR(255),
    project_id VARCHAR(255),
    transaction_isodate DATE,
    transaction_year YEAR,
    transaction_value_code CHAR,
    transaction_currency VARCHAR(255),
    transaction_value DECIMAL(65, 30)
);

LOAD DATA INFILE '/var/lib/mysql-files/transactions.csv' 
INTO TABLE transaction_t 
FIELDS TERMINATED BY ',' 
ENCLOSED BY '\"'
LINES TERMINATED BY '\n'
IGNORE 1 ROWS
(transaction_id, project_id, @transaction_isodate, transaction_year, transaction_value_code, 
transaction_currency, transaction_value)
SET transaction_isodate = STR_TO_DATE(@transaction_isodate, '%d/%m/%Y')
;


SELECT COUNT(*) AS transactions_t_rows FROM transaction_t;


-- __________ country_code_t __________

CREATE TEMPORARY TABLE IF NOT EXISTS country_code_t (
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

LOAD DATA INFILE '/var/lib/mysql-files/country_codes.tsv' 
INTO TABLE country_code_t
CHARACTER SET latin1
FIELDS TERMINATED BY '\t' 
ENCLOSED BY '\"'
LINES TERMINATED BY '\n'
IGNORE 1 ROWS
(name, iso2, name_name, @name_aiddata_code, name_aiddata_name, name_cow_alpha, @name_cow_numeric,
@name_fao_code, name_fips, @name_geonames_id, @name_imf_code, name_iso2, name_iso3, @name_iso_numeric, 
@name_oecd_code, name_oecd_name, @name_un_code, name_wb_code)
SET name_aiddata_code = NULLIF(@name_aiddata_code, 0),
    name_cow_numeric = NULLIF(@name_cow_numeric, 0),
    name_fao_code = NULLIF(@name_fao_code, 0),
    name_geonames_id = NULLIF(@name_geonames_id, 0),
    name_imf_code = NULLIF(@name_imf_code, 0),
    name_oecd_code = NULLIF(@name_oecd_code, 0),
    name_iso_numeric = NULLIF(@name_iso_numeric, 0),
    name_un_code = NULLIF(@name_un_code, 0)
;

SELECT COUNT(*) AS country_code_t_rows FROM country_code_t;


-- __________ location_t __________

CREATE TEMPORARY TABLE IF NOT EXISTS location_t (
    location_type_code VARCHAR(255),
    location_type_name VARCHAR(255)
);

LOAD DATA INFILE '/var/lib/mysql-files/locations.tsv'
INTO TABLE location_t
CHARACTER SET latin1
FIELDS TERMINATED BY '\t'
ENCLOSED BY '\"'
LINES TERMINATED BY '\n'
IGNORE 1 ROWS;

SELECT COUNT(*) AS locations_t_rows FROM location_t;