use prueba;

-- __________ project_t __________

LOAD DATA INFILE '/var/lib/mysql-files/projects.csv' 
INTO TABLE project_t
CHARACTER SET latin1
FIELDS TERMINATED BY ','  
ENCLOSED BY '\"'
LINES TERMINATED BY '\n'
IGNORE 1 ROWS
(project_id, is_geocoded, project_title, @start_actual_isodate, @end_actual_isodate, donors,
donors_iso3, recipients, recipients_iso3, ad_sector_codes, ad_sector_names, status,
transactions_start_year, transactions_end_year, @total_commitments, @total_disbursements)
SET start_actual_isodate = STR_TO_DATE(@start_actual_isodate, '%d/%m/%Y'),
    end_actual_isodate = IF (STRCMP(@end_actual_isodate,"") = 0, NULL, STR_TO_DATE(@end_actual_isodate, '%d/%m/%Y')),
    total_commitments = NULLIF(@total_commitments, 0.0),
    total_disbursements = NULLIF(@total_disbursements, 0.0)
;

SELECT COUNT(*) AS project_t_rows FROM project_t;

