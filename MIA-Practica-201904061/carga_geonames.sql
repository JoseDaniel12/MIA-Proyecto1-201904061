use prueba;

-- __________ geoname_t __________

LOAD DATA INFILE '/var/lib/mysql-files/geonames.csv' 
INTO TABLE geoname_t 
character set latin1
FIELDS TERMINATED BY ',' 
ENCLOSED BY '"'
LINES TERMINATED BY '\n'
IGNORE 1 ROWS;

SELECT COUNT(*) AS geonames_t_rows FROM geoname_t;