use prueba;

-- __________ transaction_t __________

LOAD DATA INFILE '/var/lib/mysql-files/transactions.csv' 
INTO TABLE transaction_t 
FIELDS TERMINATED BY ',' 
ENCLOSED BY '\"'
LINES TERMINATED BY '\n'
IGNORE 1 ROWS
(transaction_id, project_id, @transaction_isodate, transaction_year, transaction_value_code, 
transaction_currenci, transaction_value)
SET transaction_isodate = STR_TO_DATE(@transaction_isodate, '%d/%m/%Y')
;

SELECT COUNT(*) AS transaction_t_rows FROM transaction_t;