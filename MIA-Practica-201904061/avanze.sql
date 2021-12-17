------------------- CONSULTAS -------------------

----------------------------------------- 1
SELECT COUNT(*) FROM (SELECT transactions_start_year FROM project WHERE transactions_start_year = '2011') AS sub;

----------------------------------------- 2
-- no me sale :(

----------------------------------------- 3
-- no me sale :(

----------------------------------------- 4
SELECT * FROM ( SELECT recipients, COUNT(*) cnt FROM project pj GROUP BY recipients ) AS sub ORDER BY cnt DESC LIMIT 5;

----------------------------------------- 5
SELECT * FROM ( SELECT recipients, COUNT(*) cnt FROM project pj GROUP BY recipients ) AS sub ORDER BY cnt ASC LIMIT 5;

----------------------------------------- 6
SELECT * FROM project WHERE 
total_disbursements -- cambiar por el costo total del proyecto
= (SELECT MAX(
total_disbursements -- cambiar por el costo total del proyecto
) FROM project);

----------------------------------------- 7
SELECT * FROM project WHERE 
total_disbursements -- cambiar por el costo total del proyecto
= (SELECT MIN(
total_disbursements -- cambiar por el costo total del proyecto
) FROM project);

----------------------------------------- 8
SELECT * FROM ( SELECT * FROM project pj ) AS sub ORDER BY 
total_disbursements -- cambiar por el costo total del proyecto
DESC LIMIT 5;

----------------------------------------- 9
SELECT SUM(
total_disbursements -- cambiar por el costo total del proyecto
) FROM project;

----------------------------------------- 10
-- esto selecciona lo que contenga RI-East Africa Public Health Laboratory Networking Project
(SELECT project_id FROM project WHERE project_title LIKE '%RI-East Africa Public Health Laboratory Networking Project%');    

-- esto selecciona el valor de la transaccion de los proyectos que contengan RI-East Africa Public Health Laboratory Networking Project
SELECT TR.transaction_value FROM transaction TR 
WHERE TR.project_id = (SELECT PJ.project_id FROM project PJ WHERE PJ.project_title LIKE '%RI-East Africa Public Health Laboratory Networking Project%');     

-- CONSULTA COMPLETA
SELECT * FROM
(
SELECT * FROM transaction TR 
WHERE TR.project_id = (SELECT PJ.project_id FROM project PJ WHERE PJ.project_title LIKE '%RI-East Africa Public Health Laboratory Networking Project%')
)
AS sub ORDER BY transaction_value DESC LIMIT 3;
                               