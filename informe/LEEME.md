Aqui va el informe: el borrador de los capitulos 1 y 2 en la Etapa 1 y el PDF final en la Etapa 3.

ASIGNATURA: ESTRUCTURA DE DATOS

Rol QA y documentación: Cristofer Tonny Yanqui Laura

Requisitos Funcionales

Gestión del Catálogo (Lista Enlazada): El sistema debe permitir insertar aplicaciones al final del catálogo, buscar por nombre exacto o parcial, modificar prioridades y retirar apps que estén disponibles. 

Fila de Descargas (Cola de Prioridad): Se debe encolar aplicaciones validando que existan y haya disponibilidad. El orden de salida prioriza el nivel (1 antes que 2, y 2 antes que 3) y resuelve empates mediante orden de llegada FIFO.   

Procesamiento de Instalación: El sistema desencolará el frente, calculará el tiempo de descarga, validará el espacio en disco, actualizará el reloj y apilará el bloque instalado.   Gestión de Disco (Pila): Se registrará un historial de bloques. 

Se debe permitir deshacer liberar el bloque del tope devolviendo el espacio y consultar el espacio disponible.   

Persistencia: Guardar y cargar el catálogo y el disco en el archivo tuxstore.txt cuando la fila esté vacía.
