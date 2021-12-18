use prueba;

-- __________ location_t __________

LOAD DATA INFILE '/var/lib/mysql-files/locations.tsv'
INTO TABLE location_t
CHARACTER SET latin1
FIELDS TERMINATED BY '\t'
ENCLOSED BY '\"'
LINES TERMINATED BY '\n'
IGNORE 1 ROWS;

SELECT COUNT(*) AS locations_t_rows FROM location_t;

