use prueba;

-- __________ country_code_t __________

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