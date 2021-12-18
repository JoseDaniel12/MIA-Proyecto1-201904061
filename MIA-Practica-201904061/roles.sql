USE prueba;

DROP USER IF EXISTS 'jefe'@'localhost';
DROP USER IF EXISTS 'trabajdor'@'localhost';

CREATE ROLE IF NOT EXISTS administrador;
CREATE ROLE IF NOT EXISTS empleado;

GRANT ALL PRIVILEGES ON * . * TO administrador;
GRANT SELECT ON * . * TO empleado;

CREATE USER IF NOT EXISTS 'jefe' IDENTIFIED BY 'Jefe!12345';
CREATE USER IF NOT EXISTS 'trabajdor' IDENTIFIED BY 'Empleado!12345';

GRANT administrador TO 'jefe';
GRANT empleado TO 'trabajdor';

FLUSH PRIVILEGES;