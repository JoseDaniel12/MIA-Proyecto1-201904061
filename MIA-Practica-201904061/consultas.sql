USE prueba;  

\! clear

-- ____________________________ CONSULTAS ____________________________

--   ____________________________ 1 ____________________________
-- ¿Cunatos proyectos inciaron en 2011?

SELECT 
COUNT(*) AS proyectos_iniciados_en_2011
FROM (
    SELECT transactions_start_year
    FROM project 
    WHERE transactions_start_year = 2011
) AS RES;



--   ____________________________ 2 ____________________________
-- ¿ Cuál es el proyecto de mayor duracioón?

SELECT 
project_title, 
DATEDIFF(project.end_actual_isodate, project.start_actual_isodate) AS duracion_en_dias
FROM project 
ORDER BY duracion_en_dias DESC 
LIMIT 1;


--   ____________________________ 3 ____________________________
-- ¿ Cuál es el proyecto de nenor duracioón?

SELECT 
project_title AS proyecto_de_menor_duracion, 
DATEDIFF(project.end_actual_isodate, project.start_actual_isodate) AS duracion 
FROM project 
WHERE project.end_actual_isodate IS NOT NULL AND project.start_actual_isodate IS NOT NULL 
ORDER BY duracion 
LIMIT 1;


--   ____________________________ 4 ____________________________
-- Top 5 de paises con mas proyectos asignados

SELECT 
country_code.name AS top_5_pasises_con_mas_poryectos,
COUNT(*) AS num_proyectos
FROM project
INNER JOIN country_code
ON project.id_country_code = country_code.id_country_code
GROUP BY country_code.name 
ORDER BY num_proyectos DESC
LIMIT 5;


--   ____________________________ 5 ____________________________
-- Top 5 de paises con menos proyectos asignados

SELECT 
country_code.name AS top_5_pasises_con_mas_poryectos,
COUNT(*) AS num_proyectos
FROM project
INNER JOIN country_code
ON project.id_country_code = country_code.id_country_code
GROUP BY country_code.name 
ORDER BY num_proyectos
LIMIT 5;

--   ____________________________ 6 ____________________________
-- ¿Cuál es el proyecto con mas costo?

SELECT
project.project_title AS proyecto_mas_costoso,
ROUND(project.total_commitments, 2) AS costo
FROM project
ORDER BY costo DESC
LIMIT 1;


--   ____________________________ 7 ____________________________
-- ¿Cuál es el proyecto con menos costo?

SELECT
project.project_title AS proyecto_menos_cotoso,
ROUND(project.total_commitments, 2) AS costo
FROM project
WHERE project.total_commitments IS NOT NULL
ORDER BY costo
LIMIT 1;


--   ____________________________ 8 ____________________________
-- Top 5 de proyectos mas costos

SELECT
project.project_title AS proyectos_mas_costos,
ROUND(project.total_commitments, 2) AS costos
FROM project
WHERE project.total_commitments IS NOT NULL
ORDER BY costos DESC
LIMIT 5;


--   ____________________________ 9 ____________________________
-- Costo de todos los proyectos

SELECT
ROUND(SUM(project.total_commitments), 2) AS costo_todos_los_proyectos
FROM project;


--   ____________________________ 10 ____________________________
-- Top 3 de las Transacciones mas costas de RI-East Africa Public Health Laboratory Networking Project

SELECT
project.project_title AS organizacion_solicitada,
ROUND(transaction.transaction_value, 2) AS cotos_mas_elevados
FROM project INNER JOIN transaction
ON project.id_project = transaction.id_project
WHERE project.project_title LIKE '%RI-East Africa Public Health Laboratory Networking Project%'
ORDER BY cotos_mas_elevados DESC
LIMIT 3;

