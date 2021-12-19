use prueba;

-- __________ level_1a_t __________

LOAD DATA INFILE '/var/lib/mysql-files/level_1a.csv'
INTO TABLE level_1a_t
CHARACTER SET latin1
FIELDS TERMINATED BY ','
ENCLOSED BY '"'
LINES TERMINATED BY '\n'
IGNORE 1 ROWS
(project_id, project_location_id, geoname_id, transactions_start_year, transactions_end_year,
@even_split_commitments, @even_split_disbursements)
SET even_split_commitments = NULLIF(@even_split_commitments, 0.0),
    even_split_disbursements = NULLIF(@even_split_disbursements, 0.0)
;

SELECT COUNT(*) AS level_1a_t_rows FROM level_1a_t;

