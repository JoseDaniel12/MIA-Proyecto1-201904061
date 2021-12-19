USE prueba;  

\! clear


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
    transactions_start_year YEAR,
    transactions_end_year YEAR,
    total_commitments  DECIMAL(65, 30),
    total_disbursements DECIMAL(65, 30)
);


-- __________ level_1a_t __________

CREATE TEMPORARY TABLE IF NOT EXISTS level_1a_t (   
    project_id VARCHAR(255),
    project_location_id VARCHAR(255),
    geoname_id INT,
    transactions_start_year YEAR,
    transactions_end_year YEAR,
    even_split_commitments DECIMAL(65, 30),
    even_split_disbursements DECIMAL(65, 30)
);


-- ______ The International Banc for Reconstruction and Develpmnet (IBDR) ______

-- __________ transaction_t __________

CREATE TEMPORARY TABLE IF NOT EXISTS transaction_t (
    transaction_id VARCHAR(255),
    project_id VARCHAR(255),
    transaction_isodate DATE,
    transaction_year YEAR,
    transaction_value_code CHAR,
    transaction_currenci VARCHAR(255),
    transaction_value DECIMAL(65, 30)
);


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


-- __________ location_t __________

CREATE TEMPORARY TABLE IF NOT EXISTS location_t (
    location_type_code VARCHAR(255),
    location_type_name VARCHAR(255)
);

