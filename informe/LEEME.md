Aqui va el informe: el borrador de los capitulos 1 y 2 en la Etapa 1 y el PDF final en la Etapa 3.

ASIGNATURA: ESTRUCTURA DE DATOS

Rol QA y documentación: Cristofer Tonny Yanqui Laura

**ESTRUCTURA DE DATOS · PLANTILLA DEL INFORME · C2**

**Tux Store v2 · Informe técnico**

Evaluación por competencias C2 · NRC 42964 (lunes)

|                     |                                                                               |
|---------------------|-------------------------------------------------------------------------------|
| Asignatura          | Estructura de Datos (24UC00428)                                               |
| Docente             | Carlos del Carpio                                                             |
| NRC · Grupo         | 42964 · Grupo G                                                               |
| Servidor            | pinguino-magallenes                                                           |
| Repositorio         | <https://github.com/Dannypml/tuxstore-42964-grupo-G-/commits?author=Dannypml> |
| Versión del informe | v0.5 (E2)                                                                     |
| Periodo             | 2026-20                                                                       |

| **Integrante**               | **Usuario de GitHub** | **Rol**               | **Requisitos a cargo**                                              |
|------------------------------|-----------------------|-----------------------|---------------------------------------------------------------------|
| Danny Abel León Huamán       | Dannypml              | Líder (scrum)         | Mantiene el tablero al día, convoca las reuniones y redacta el acta |
| Juan Dennys Cayllahua Apaza  | 60703718-ui           | Dev · catálogo        | R1 y R5: lista enlazada                                             |
| Eduardo Quista Justo         | 75282429-bot          | Dev · descargas       | R2 y R3: cola de prioridad y cálculo de tiempos                     |
| Juan Carlos Chani Chullo     | 76907318-coder        | Dev · disco y archivo | R4 y R5: “pila y persistencia”                                      |
| Cristofer Tonny Yanqui Laura | Tony-Yanqui           | QA y documentación    | R7, las pruebas y el informe                                        |

**Capítulo 1 · Análisis del problema**

1.  **Descripción del problema \[E1\]**

    Tux Store es un simulador de consola que actúa como un gestor de paquetes de GNU/Linux. Nuestro equipo debe administrar el servidor "pinguino-magallanes", implementando un sistemaque utilice tres estructuras de datos dinámicas hechas desde cero como;lista enlazada, cola de prioridad y pila, todo esto para gestionar un catálogo de aplicaciones, administrar una fila de descargas considerando distintas prioridades incluyendo los tiempos y controlar el almacenamiento en disco de forma eficaz, permitiendo persistir los datos en un archivo.

<table>
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr class="odd">
<td><p><strong>QUÉ VA AQUÍ</strong></p>
<p>Con sus palabras, en un párrafo: qué hace Tux Store, quién lo usa y qué debe resolver en su servidor. (Borren este recuadro en la versión final.)</p></td>
</tr>
</tbody>
</table>

**1.2 Variables y condiciones \[E1\]**

<table>
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr class="odd">
<td><p><strong>QUÉ VA AQUÍ</strong></p>
<p>Completen la tabla con todas las variables del problema (no solo las del código). Ejemplos: velocidad, disco, reloj, segundo del pedido, MB libres, prioridad. (Borren este recuadro en la versión final.)</p></td>
</tr>
</tbody>
</table>

| **Variable**        | **Tipo en C++** | **Unidad** | **Valor inicial o rango** | **Condición o regla que la afecta** |
|---------------------|-----------------|------------|---------------------------|-------------------------------------|
| VELOCIDAD           | const int       | MB/s       | 3                         | regla 2                             |
| DISCO               | const int       | MB         | 274                       | reglas 4 y 7                        |
| reloj               | int             | segundos   | 0                         | reglas 3 y 5                        |
| Segundo del perdido | int             | segundos   | 0                         | reglas 3 y 5                        |
| MB libres           | int             | MB         | 274                       | regla 4                             |
| Prioridad           | int             | \-         | 1 a 3                     | regla 6                             |
| Estado              | int             | \-         | 0,1,2                     | regla 5                             |

**1.3 Requerimientos funcionales y no funcionales \[E1\]**

| **ID** | **Requerimiento funcional**                                           | **Orden(es)**                         | **Estructura**    |
|--------|-----------------------------------------------------------------------|---------------------------------------|-------------------|
| RF1    | Agregar las apps, buscar por texto y mostrar el catalogo completo     | Agregar, buscar, info, catalogo       | Lista enlazada    |
| RF2    | Poner aplicaciones en cola segun prioridad y mostrar fila             | Intalar, fila                         | Cola de prioridad |
| RF3    | Procesar descargas, ver estado del disco, ver el historial y revertir | Procesar,espacio, historial, deshacer | Cola y pila       |
| RF4    | Cambiar la prioridad de una app y retirar del catalogo                | Prioridad, retirar                    | Lista enlazada    |
| RF5    | Persistencia en guardar y cargar datos al archivo                     | Guardar y cargar                      | Lista y pila      |

| **ID** | **Requerimiento no funcional (cómo debe comportarse)**                                                                  |
|--------|-------------------------------------------------------------------------------------------------------------------------|
| RNF1   | Ninguna entrada inválida cierra el programa                                                                             |
| RNF2   | El tiemo de descarga siempre siempre se redonde a numeros enteros con formulas de enteros.                              |
| RNF3   | El codigo debe compilar sin contenedores de la blibiota estandar(list, vector, queue, stack, map ni otros contenedores) |

**1.4 Estructuras propuestas y justificación \[E1\]**

**Para el catálogo: Se utilizo una lista enlazada simple la vimos conveniente y a**decuada porque el catálogo, ya que puede crecer y agregar apps al final, recorriendo secuencialmente para imprimir la información o buscar texto, y se necesita poder retirar o eliminar elementos de cualquier parte sin dejar espacios vacíos en la memoria.

**Para la fila de descargas: Obtamos por una cola de prioridad:** Es la mejor opción porque las aplicaciones entran desordenadas pero deben salir estrictamente bajo dos criterios de prioridad y orden de llegada (FIFO) siempre se atiende el frente de la cola.

**Para el disco: La pila es** Ideal ya que modela correctamente la operación de revertir cambios que seria el deshacer. Al instalar se guarda el registro (push) y al deshacer se quita únicamente la última instalación (pop), siguiendo la estructura LIFO (Last In, First Out).

**Capítulo 2 · Diseño de la solución**

**2.1 Estructuras y operaciones \[E1\]**

![WhatsApp Image 2026-10-28 at 11.00.00 PM](imagenes/image2.jpeg)

<table>
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr class="odd">
<td><p><strong>QUÉ VA AQUÍ</strong></p>
<p>Dibujen los tres tipos de nodos (NodoApp, NodoFila, NodoBloque) con sus campos y los punteros catalogo, frente, final y tope. Pueden dibujar a mano y fotografiar, o usar draw.io, Excalidraw o Mermaid. (Borren este recuadro en la versión final.)</p></td>
</tr>
</tbody>
</table>

| **Estructura** | **Operación**         | **Orden** | **Qué punteros cambian** |
|----------------|-----------------------|-----------|--------------------------|
| Lista          | insertar al final     | agregar   |                          |
| Lista          | eliminar              | retirar   |                          |
| Cola           | encolar con prioridad | instalar  |                          |
| Cola           | desencolar            | procesar  |                          |
| Pila           | push                  | procesar  |                          |
| Pila           | pop                   | deshacer  |                          |

**2.2 Pseudocódigo \[E1\]**

<table>
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr class="odd">
<td><p><strong>QUÉ VA AQUÍ</strong></p>
<p>Escriban el pseudocódigo de <strong>agregar app</strong> (insertar en la lista), de <strong>instalar</strong> (encolar con prioridad) y de <strong>procesar</strong> (cambiar el estado de la app, calcular los tiempos y apilar el bloque). (Borren este recuadro en la versión final.)</p></td>
</tr>
</tbody>
</table>

<table>
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr class="odd">
<td><p>ALGORITMO instalar(app, seg)</p>
<p>SI ... ENTONCES</p>
<p>...</p>
<p>FIN SI</p>
<p>FIN</p></td>
</tr>
<tr class="even">
<td><p>ALGORITMO de Agregar app</p>
<p>INICIO</p>
<p>SI faltan datos ENTONCES</p>
<p>Mostrar "E: Uso incorrecto"</p>
<p>SINO SI mb &lt;= 0 O prioridad &lt; 1 O prioridad &gt; 3</p>
<p>Mostrar "E: Datos invalidos"</p>
<p>SINO SI buscarApp(catalogo, app) != nullptr</p>
<p>Mostrar "E: No se pudo agregar"</p>
<p>SINO</p>
<p>Crear nuevo NodoApp</p>
<p>SI catalogo == nullptr ENTONCES</p>
<p>catalogo = nuevo</p>
<p>SINO</p>
<p>p = catalogo</p>
<p>MIENTRAS p.sig != nullptr HACER</p>
<p>p = p.sig</p>
<p>FIN MIENTRAS</p>
<p>p.sig = nuevo</p>
<p>FIN SI</p>
<p>Mostrar "Agregada"</p>
<p>FIN SI</p>
<p>FIN</p></td>
</tr>
<tr class="odd">
<td><p>ALGORITMO de INSTALAR</p>
<p>INICIO</p>
<p>SI faltan app o seg ENTONCES</p>
<p>Mostrar "E: Uso incorrecto"</p>
<p>SINO SI seg no es entero O seg &lt; 0 ENTONCES</p>
<p>Mostrar "E: Tiempo invalido"</p>
<p>SINO</p>
<p>a = buscarApp(catalogo, app)</p>
<p>SI a == nullptr ENTONCES</p>
<p>Mostrar "E: La app no existe"</p>
<p>SINO SI a.estado != DISPONIBLE ENTONCES</p>
<p>Mostrar "E: App en fila o instalada"</p>
<p>SINO SI seg &lt; ultimaLlegada ENTONCES</p>
<p>Mostrar "E: El tiempo retrocede"</p>
<p>SINO</p>
<p>Crear NodoFila con app, seg y prioridad</p>
<p>SI frente == nullptr ENTONCES</p>
<p>frente = nuevo</p>
<p>final = nuevo</p>
<p>SINO SI nuevo tiene mayor prioridad</p>
<p>nuevo.sig = frente</p>
<p>frente = nuevo</p>
<p>SINO</p>
<p>p = frente</p>
<p>MIENTRAS exista p.sig Y el siguiente</p>
<p>deba atenderse antes HACER</p>
<p>p = p.sig</p>
<p>FIN MIENTRAS</p>
<p>nuevo.sig = p.sig</p>
<p>p.sig = nuevo</p>
<p>SI p == final ENTONCES</p>
<p>final = nuevo</p>
<p>FIN SI</p>
<p>FIN SI</p>
<p>a.estado = EN_FILA</p>
<p>ultimaLlegada = seg</p>
<p>Mostrar "En fila"</p>
<p>FIN SI</p>
<p>FIN SI</p>
<p>FIN</p></td>
</tr>
<tr class="even">
<td><p>ALGORITMO de PROCESAR</p>
<p>INICIO</p>
<p>SI frente == nullptr ENTONCES</p>
<p>Mostrar "La fila esta vacia"</p>
<p>SINO</p>
<p>pedido = frente</p>
<p>frente = frente.sig</p>
<p>SI frente == nullptr ENTONCES</p>
<p>final = nullptr</p>
<p>FIN SI</p>
<p>app = buscarApp(catalogo, pedido.nombre)</p>
<p>SI app.mb &gt; libre ENTONCES</p>
<p>Mostrar "E: No hay espacio suficiente"</p>
<p>app.estado = DISPONIBLE</p>
<p>SINO</p>
<p>descarga = (app.mb + VELOCIDAD - 1) / VELOCIDAD</p>
<p>app.inicio = MAX(reloj, pedido.llegada)</p>
<p>app.fin = app.inicio + descarga</p>
<p>app.espera = app.inicio - pedido.llegada</p>
<p>reloj = app.fin</p>
<p>libre = libre - app.mb</p>
<p>instalaciones = instalaciones + 1</p>
<p>mbDescargados = mbDescargados + app.mb</p>
<p>sumaEspera = sumaEspera + app.espera</p>
<p>app.estado = INSTALADA</p>
<p>Crear NodoBloque</p>
<p>bloque.nombre = app.nombre</p>
<p>bloque.mb = app.mb</p>
<p>bloque.sig = tope</p>
<p>tope = bloque</p>
<p>Mostrar descarga, inicio, fin, espera y libre</p>
<p>FIN SI</p>
<p>Eliminar pedido</p>
<p>FIN SI</p>
<p>FIN</p></td>
</tr>
</tbody>
</table>

**2.3 Diagramas de flujo \[E2\]**


<table>
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr class="odd">
<td><p><strong>QUÉ VA AQUÍ</strong></p>
<p>Diagrama de flujo de instalar y de procesar, con todas sus validaciones y errores. (Borren este recuadro en la versión final.)</p></td>
</tr>
</tbody>
</table>

**2.4 Traza a mano de la secuencia oficial \[E1\]**

<table>
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr class="odd">
<td><p><strong>QUÉ VA AQUÍ</strong></p>
<p>Tracen las órdenes 3 a 16 de su ficha sin ejecutar el programa. Después de cada orden de fila anoten la fila completa. En la Etapa 2 comparen con la salida del programa y expliquen cualquier diferencia. (Borren este recuadro en la versión final.)</p></td>
</tr>
</tbody>
</table>

| **\#** | **App**  | **Prior.** | **Pedida** | **MB** | **Descarga** | **Inicio** | **Fin** | **Espera** | **Libres** |
|--------|----------|------------|------------|--------|--------------|------------|---------|------------|------------|
|        | fail2ban |            |            |        |              |            |         |            |            |
|        | nginx    |            |            |        |              |            |         |            |            |
|        | python3  |            |            |        |              |            |         |            |            |
|        | firefox  |            |            |        |              |            |         |            |            |
|        |          |            |            |        |              |            |         |            |            |
|        |          |            |            |        |              |            |         |            |            |
|        |          |            |            |        |              |            |         |            |            |

Fila después de la orden 6: \_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_ · después de la orden 12: \_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_

**2.5 Justificación del diseño \[E2\]**

<table>
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr class="odd">
<td><p><strong>QUÉ VA AQUÍ</strong></p>
<p>Decisiones que tomaron (por ejemplo, cómo validan el segundo, cómo agregan los bloques al fondo al cargar) y por qué. (Borren este recuadro en la versión final.)</p></td>
</tr>
</tbody>
</table>

**Capítulo 3 · Desarrollo de la solución**

**3.1 Código fuente comentado \[E3\]**

<table>
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr class="odd">
<td><p><strong>QUÉ VA AQUÍ</strong></p>
<p>No peguen todo el programa (va en el ZIP). Muestren los fragmentos clave de cada requisito, comentados, y quién los escribió (con el enlace al commit). (Borren este recuadro en la versión final.)</p></td>
</tr>
</tbody>
</table>

**3.2 Estructuras de control utilizadas \[E3\]**

| **Fragmento (requisito)**    | **Estructura de control** | **Para qué se usa** | **Condición de parada** |
|------------------------------|---------------------------|---------------------|-------------------------|
| Recorrido del catálogo (R1)  | for / while               |                     | p == nullptr            |
| Inserción con prioridad (R2) | while                     |                     |                         |
| Lectura de tuxstore.txt (R6) | while                     |                     |                         |
|                              | if / else if              |                     | —                       |

**3.3 Costo de las operaciones \[E3\]**

| **Operación**      | **Nodos que recorre (peor caso)** | **Explicación breve** |
|--------------------|-----------------------------------|-----------------------|
| agregar (al final) | n (apps del catálogo)             |                       |
| instalar (encolar) |                                   |                       |
| procesar           |                                   |                       |
| deshacer           | 1                                 |                       |
| retirar            |                                   |                       |

**3.4 Capturas de validación y pruebas \[E3\]**

<table>
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr class="odd">
<td><p><strong>QUÉ VA AQUÍ</strong></p>
<p>Capturas de la ejecución de su secuencia oficial (o el enlace a pruebas/salida.txt) y la tabla de PRUEBAS.md con resultado esperado y obtenido, incluidas las entradas inválidas. (Borren este recuadro en la versión final.)</p></td>
</tr>
</tbody>
</table>

**3.5 Manual de usuario \[E3\]**

<table>
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr class="odd">
<td><p><strong>QUÉ VA AQUÍ</strong></p>
<p>Cómo compilar y ejecutar, las órdenes con un ejemplo de cada una, los mensajes de error y cómo guardar y cargar. Escríbanlo para alguien que nunca usó Linux. (Borren este recuadro en la versión final.)</p></td>
</tr>
</tbody>
</table>

**Capítulo 4 · Evidencias del trabajo en equipo**

**4.1 Repositorio y tablero \[E1 → E3\]**

<table>
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr class="odd">
<td><p><strong>QUÉ VA AQUÍ</strong></p>
<p>Enlace al repositorio y al tablero de GitHub Projects. Captura del tablero al final de cada etapa. (Borren este recuadro en la versión final.)</p></td>
</tr>
</tbody>
</table>

**4.2 Commits, ramas y fusiones \[E2 → E3\]**

<table>
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr class="odd">
<td><p><strong>QUÉ VA AQUÍ</strong></p>
<p>Captura de Insights → Contributors y de la lista de pull requests (quién abrió, quién revisó, cuándo se unió). (Borren este recuadro en la versión final.)</p></td>
</tr>
</tbody>
</table>

| **Integrante** | **Commits** | **Pull requests abiertos** | **Revisiones hechas** | **Requisitos o partes que escribió** |
|----------------|-------------|----------------------------|-----------------------|--------------------------------------|
|                |             |                            |                       |                                      |
|                |             |                            |                       |                                      |
|                |             |                            |                       |                                      |
|                |             |                            |                       |                                      |
|                |             |                            |                       |                                      |

**4.3 Plan de trabajo, roles y cronograma \[E1 → E3\]**

| **Tarea** | **Responsable** | **Fecha planificada** | **Fecha real** | **Estado** |
|-----------|-----------------|-----------------------|----------------|------------|
|           |                 |                       |                |            |
|           |                 |                       |                |            |
|           |                 |                       |                |            |

**4.4 Actas de reuniones \[E1 → E3\]**

<table>
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr class="odd">
<td><p><strong>QUÉ VA AQUÍ</strong></p>
<p>Copien o enlacen las actas de ACUERDOS.md: fecha, asistentes, acuerdos y responsables. Si un acuerdo cambió, expliquen por qué. (Borren este recuadro en la versión final.)</p></td>
</tr>
</tbody>
</table>

**4.5 Reflexión del equipo \[E3\]**

<table>
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr class="odd">
<td><p><strong>QUÉ VA AQUÍ</strong></p>
<p>Qué funcionó, qué conflicto tuvieron y cómo lo resolvieron, y qué harían distinto. (Borren este recuadro en la versión final.)</p></td>
</tr>
</tbody>
</table>

**Uso de IA y referencias**

<table>
<colgroup>
<col style="width: 100%" />
</colgroup>
<tbody>
<tr class="odd">
<td><p><strong>QUÉ VA AQUÍ</strong></p>
<p>Resumen de IA.md y las fuentes que consultaron. (Borren este recuadro en la versión final.)</p></td>
</tr>
</tbody>
</table>
