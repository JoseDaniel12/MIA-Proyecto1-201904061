DROP TABLE geoname;
DROP TABLE project;
DROP TABLE level_1a;
DROP TABLE transaction;
DROP TABLE country_code;
DROP TABLE location;
DROP TABLE status;
DROP TABLE currenci;

\! clear

-- __________________ Creacion de las tablas unidas _____________________________

-- __________ location __________

CREATE TABLE IF NOT EXISTS location (
    id_location INT NOT NULL AUTO_INCREMENT,
    location_type_code VARCHAR(255),
    location_type_name VARCHAR(255),
    PRIMARY KEY (id_location)
    --PRIMARY KEY (location_type_code)
);

INSERT INTO location
(location_type_code, location_type_name)
SELECT * FROM location_t;

SELECT COUNT(*) AS location_final_rows FROM location;


-- __________ status __________

CREATE TABLE IF NOT EXISTS status (
    id_status INT NOT NULL AUTO_INCREMENT,
    name_status VARCHAR(255),
    PRIMARY KEY (id_status)
    --PRIMARY KEY (name_status)
);

INSERT INTO status
(name_status)
SELECT status FROM project_t GROUP BY status;

SELECT COUNT(*) AS status_rows FROM status;
SELECT * FROM status;


-- __________ currenci __________

CREATE TABLE IF NOT EXISTS currenci (
    id_currency INT NOT NULL AUTO_INCREMENT,
    name_currency VARCHAR(255),
    PRIMARY KEY (id_currency)
    --PRIMARY KEY (name_currency)
);

INSERT INTO currenci
(name_currency)
SELECT transaction_currency FROM transaction_t GROUP BY transaction_currency;

SELECT COUNT(*) AS currenci_rows FROM currenci;
SELECT * FROM currenci;


-- __________ country_code __________

CREATE TABLE IF NOT EXISTS country_code (
    id INT NOT NULL AUTO_INCREMENT,
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
    name_wb_code VARCHAR(255),
    PRIMARY KEY (id)
    --PRIMARY KEY (name_iso3)
);

INSERT INTO country_code
(name, iso2, name_name, name_aiddata_code, name_aiddata_name, name_cow_alpha, name_cow_numeric,
name_fao_code, name_fips, name_geonames_id, name_imf_code, name_iso2, name_iso3,name_iso_numeric, 
name_oecd_code, name_oecd_name, name_un_code, name_wb_code)
SELECT DISTINCT * FROM country_code_t;

SELECT COUNT(*) AS country_code_final_rows FROM country_code;



-- __________ geoname __________

CREATE TABLE IF NOT EXISTS geoname (
    id INT NOT NULL AUTO_INCREMENT,
    geoname_id INT,
    place_name VARCHAR(255),
    latitude FLOAT,
    longitude FLOAT,
    location_type_code VARCHAR(255),
    location_type_name VARCHAR(255),
    gazetteer_adm_code VARCHAR(255),
    gazetteer_adm_name VARCHAR(255),
    location_class INT,
    geographic_exactness INT,
    PRIMARY KEY (id)
    --PRIMARY KEY (geoname_id),
    --FOREIGN KEY (location_type_code) REFERENCES location(location_type_code)
);

INSERT INTO geoname
(geoname_id, place_name, latitude, longitude, location_type_code, location_type_name, 
gazetteer_adm_code, gazetteer_adm_name, location_class, geographic_exactness)
SELECT DISTINCT * FROM geoname_t;

SELECT COUNT(*) AS geoname_final_rows FROM geoname;



-- __________ project __________

CREATE TABLE IF NOT EXISTS project (
    id_proyecto INT NOT NULL AUTO_INCREMENT,
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
    total_disbursements VARCHAR(255),
    PRIMARY KEY (id_proyectod)
    --PRIMARY KEY (project_id),
    --FOREIGN KEY (status) REFERENCES status(name_status),
    --FOREIGN KEY (recipients_iso3) REFERENCES country_code(name_iso3)
);

INSERT INTO project
(project_id, is_geocoded, project_title, start_actual_isodate, end_actual_isodate, donors,
donors_iso3, recipients, recipients_iso3, ad_sector_codes, ad_sector_names, status,
transactions_start_year, transactions_end_year, total_commitments, total_disbursements)
SELECT * FROM project_t;

SELECT COUNT(*) AS project_final_rows FROM project;


-- __________ level_1a __________

CREATE TABLE IF NOT EXISTS level_1a (   
    id INT NOT NULL AUTO_INCREMENT,
    project_id VARCHAR(255),
    project_location_id VARCHAR(255),
    geoname_id INT,
    transactions_start_year YEAR,
    transactions_end_year YEAR,
    even_split_commitments VARCHAR(255),
    even_split_disbursements DECIMAL(65, 30),
    PRIMARY KEY (id)
    --PRIMARY KEY (project_location_id),
    --FOREIGN KEY (project_id) REFERENCES project(project_id),
    --FOREIGN KEY (geoname_id) REFERENCES geoname(geoname_id)
);

INSERT INTO level_1a
(project_id, project_location_id, geoname_id, transactions_start_year, transactions_end_year,
even_split_commitments, even_split_disbursements)
SELECT * FROM level_1a_t;

SELECT COUNT(*) AS level_1a_final_rows FROM level_1a;


-- __________ transaction __________

CREATE TABLE IF NOT EXISTS transaction (
    id INT NOT NULL AUTO_INCREMENT,
    transaction_id VARCHAR(255),
    project_id VARCHAR(255),
    transaction_isodate DATE,
    transaction_year YEAR,
    transaction_value_code CHAR,
    transaction_currency VARCHAR(255),
    transaction_value DECIMAL(65, 30),
    PRIMARY KEY (id)
    --PRIMARY KEY (transaction_id),
    --FOREIGN KEY (project_id) REFERENCES project(project_id),
    --FOREIGN KEY (transaction_currency) REFERENCES currenci(name_currency)
);

INSERT INTO transaction
(transaction_id, project_id, transaction_isodate, transaction_year, transaction_value_code, 
transaction_currency, transaction_value)
SELECT * FROM transaction_t;

SELECT COUNT(*) AS transaction_final_rows FROM transaction;
