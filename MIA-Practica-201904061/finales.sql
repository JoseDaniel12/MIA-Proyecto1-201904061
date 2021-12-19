USE prueba;

-- __________________ Creacion de las tablas unidas _____________________________

-- __________ location __________

CREATE TABLE IF NOT EXISTS location (
    id_location INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    location_type_code VARCHAR(255),
    location_type_name VARCHAR(255)
);

INSERT INTO location
(location_type_code, location_type_name)
SELECT DISTINCT * FROM location_t;

SELECT COUNT(*) AS location_final_rows FROM location;


-- __________ status __________

CREATE TABLE IF NOT EXISTS status (
    id_status INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    name_status VARCHAR(255)
);

INSERT INTO status
(name_status)
SELECT DISTINCT status FROM project_t GROUP BY status;

SELECT COUNT(*) AS status_rows FROM status;


-- __________ currenci __________

CREATE TABLE IF NOT EXISTS currenci (
    id_currenci INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    name_currenci VARCHAR(255)
);

INSERT INTO currenci
(name_currenci)
SELECT DISTINCT transaction_currenci FROM transaction_t GROUP BY transaction_currenci;

SELECT COUNT(*) AS currenci_rows FROM currenci;


-- __________ country_code __________

CREATE TABLE IF NOT EXISTS country_code (
    id_country_code INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
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
    id_geoname INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    geoname_id INT,
    place_name VARCHAR(255),
    latitude FLOAT,
    longitude FLOAT,
    id_location INT,
    gazetteer_adm_code VARCHAR(255),
    gazetteer_adm_name VARCHAR(255),
    location_class INT,
    geographic_exactness INT,
    FOREIGN KEY (id_location) REFERENCES location(id_location)
);

INSERT INTO geoname
(geoname_id, place_name, latitude, longitude, id_location, 
gazetteer_adm_code, gazetteer_adm_name, location_class, geographic_exactness)
SELECT DISTINCT 
geoname_t.geoname_id,
geoname_t.place_name,
geoname_t.latitude,
geoname_t.longitude, 
location.id_location,
geoname_t.gazetteer_adm_code,
geoname_t.gazetteer_adm_name,
geoname_t.location_class,
geoname_t.geographic_exactness
FROM geoname_t 
INNER JOIN location
ON geoname_t.location_type_code = location.location_type_code 
AND geoname_t.location_type_name = location.location_type_name;

SELECT COUNT(*) AS geoname_final_rows FROM geoname;



-- __________ project __________

CREATE TABLE IF NOT EXISTS project (
    id_project INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    project_id VARCHAR(255),
    is_geocoded  INT,
    project_title VARCHAR(255),
    start_actual_isodate DATE,
    end_actual_isodate DATE,
    donors VARCHAR(255),
    donors_iso3 VARCHAR(255),
    #recipients VARCHAR(255),
    id_country_code INT,
    recipients_iso3 VARCHAR(255),
    ad_sector_codes varchar(255),
    ad_sector_names varchar(255),
    #status VARCHAR(255),
    id_status INT,
    transactions_start_year YEAR,
    transactions_end_year YEAR,
    total_commitments  DECIMAL(65, 30),
    total_disbursements DECIMAL(65, 30),
    FOREIGN KEY (id_country_code) REFERENCES country_code(id_country_code),
    FOREIGN KEY (id_status) REFERENCES status(id_status)
);

INSERT INTO project
(project_id, is_geocoded, project_title, start_actual_isodate, end_actual_isodate, donors,
donors_iso3, id_country_code, recipients_iso3, ad_sector_codes, ad_sector_names, id_status,
transactions_start_year, transactions_end_year, total_commitments, total_disbursements)
SELECT DISTINCT 
project_id, 
is_geocoded, 
project_title, 
start_actual_isodate, 
end_actual_isodate, 
donors,
donors_iso3, 
country_code.id_country_code, 
recipients_iso3, 
ad_sector_codes, 
ad_sector_names, 
status.id_status,
transactions_start_year, 
transactions_end_year, 
total_commitments, 
total_disbursements
FROM project_t 
LEFT JOIN country_code
ON project_t.recipients = country_code.name
LEFT JOIN status
ON project_t.status = status.name_status;

SELECT COUNT(*) AS project_final_rows FROM project;


-- __________ level_1a __________

CREATE TABLE IF NOT EXISTS level_1a (  
    id_level_1a INT NOT NULL AUTO_INCREMENT PRIMARY KEY, 
    #project_id VARCHAR(255),
    id_project INT,
    project_location_id VARCHAR(255),
    #geoname_id INT,
    id_geoname INT,
    transactions_start_year YEAR,
    transactions_end_year YEAR,
    even_split_commitments DECIMAL(65, 30),
    even_split_disbursements DECIMAL(65, 30),
    FOREIGN KEY (id_geoname) REFERENCES geoname(id_geoname),
    FOREIGN KEY (id_project) REFERENCES project(id_project)
);

INSERT INTO level_1a
(id_project, project_location_id, id_geoname, transactions_start_year, transactions_end_year,
even_split_commitments, even_split_disbursements)
SELECT DISTINCT
    project.id_project, 
    level_1a_t.project_location_id, 
    geoname.id_geoname, 
    level_1a_t.transactions_start_year, 
    level_1a_t.transactions_end_year,
    level_1a_t.even_split_commitments,
    level_1a_t.even_split_disbursements
FROM level_1a_t 
INNER JOIN geoname
ON level_1a_t.geoname_id = geoname.geoname_id
INNER JOIN project
ON level_1a_t.project_id = project.project_id;

SELECT COUNT(*) AS level_1a_final_rows FROM level_1a;


-- __________ transaction __________

CREATE TABLE IF NOT EXISTS transaction (
    id_transaction INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    transaction_id VARCHAR(255),
    #project_id VARCHAR(255),
    id_project INT,
    transaction_isodate DATE,
    transaction_year YEAR,
    transaction_value_code CHAR,
    #transaction_currenci VARCHAR(255),
    id_currenci INT,
    transaction_value DECIMAL(65, 30),
    FOREIGN KEY (id_project) REFERENCES project(id_project),
    FOREIGN KEY (id_currenci) REFERENCES currenci(id_currenci)
);

INSERT INTO transaction
(transaction_id, id_project, transaction_isodate, transaction_year, transaction_value_code, 
id_currenci, transaction_value)
SELECT DISTINCT
transaction_t .transaction_id, 
project.id_project, 
transaction_t.transaction_isodate, 
transaction_t.transaction_year, 
transaction_t.transaction_value_code, 
currenci.id_currenci, 
transaction_t.transaction_value
FROM transaction_t
INNER JOIN project
ON transaction_t.project_id = project.project_id
INNER JOIN currenci
ON transaction_t.transaction_currenci = currenci.name_currenci;

SELECT COUNT(*) AS transaction_final_rows FROM transaction;

