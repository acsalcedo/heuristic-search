# heuristic-search
Proyecto 1 de búsqueda heurística para Inteligencia Artificial 1

### INTEGRANTES    	###############################################################

Rivas Vanessa		10-10602
Salcedo Andrea		10-10666
Verdugo Reinaldo	10-10757

### OBJETIVO    	###############################################################

El objetivo del proyecto es aprender sobre el modelo de espacio  de  estados  y  sobre  los  diferentes algoritmos  de  búsqueda  heurística.

### ESTRUCTURA    	###############################################################
Los archivos están estructurados de la siguiente manera:

** psvn 			  
Incluye todos los archivos necesarios para el funcionamiento del API psvnc2.

** problems     	  
Contiene la especificación de los problemas a resolvercon su respectiva representación en lenguaje psvn. Cada problema se encuentra en un subdirectorio. A saber:
	* Torres de Hanoi: De 4 hastas. Con 12, 14, 16 o 18 discos.
	* Cubo de Rubik: De tamaño 2x2 y 3x3.
	* n-puzzle: De tamaño 4x4 o 5x5. Con o sin costo modificado.
	* top-spin: 

** src
Donde se encuentran implementados los algoritmos de búsqueda utilizados para este proyecto. 
	a.cpp : Contiene el algoritmo A*
	dfid.cpp : Depth first iterative deepening.
	dfucs.cpp : Depth first uniform cost search.
	ida.cpp: IDA*.
	ucs.DDD: Uniform cost search con delayed duplclicate.
	heuristics.cpp: Contiene las heuristicas utilizadas para el n-puzzle haciendo uso de la distancia Manhattan.

**abstractions
Contiene las abstracciones de los problemas relajados para crear heurísticas que utilizan bases de datos de patrones (PDB)

### COMPILACION		###############################################################

Desde el directorio ** problems **, introducir mediante linea de comandos:

make <problema> ALG=<algoritmo> SIZE=<tamano>

donde:
<problema> puede ser alguno de los cuatro que nos interesa resolver: npuzzle | hanoi | rubiks | topspin
<algoritmo> puede ser: st | bfs | ucs | dfid | dfucs | a | ida
<tamano> dependerá del problema a resolver.

Nota:Los argumentos deben estar justo después del "=", sin espacios.

Ejemplos:

make npuzzle ALG=st SIZE=4
make hanoi ALG=ucs SIZE=14

Para el caso de los algoritmos informados (a o ida) existe la opción de pasar como parámetro la variable "PDB", la cual en caso de ser 1, genera automáticamente los PDB necesarios para la corrida

make npuzzle ALG=ida SIZE=4 -> Compilaría el algoritmo ida asociado al npuzzle4x4, sin generar los PDB
make npuzzle ALG=ida SIZE=4 PDB=1 -> Generaría automáticamente los PDB mediante el uso de la abstracción y los psvn .


### CORRIDA 		###############################################################

Desde el directorio ** problems **,  correr mediante linea de comando:

Para el caso de algoritmos ciegos:

./<exec>.ALG <nameStatesFile> <outputFile>



Para el caso de algoritmos informados:

./<exec>.ALG <nameStatesFile> <problem> <size> <typeHeuristic> <outputFile>