# heuristic-search
Proyecto 1 de búsqueda heurística para Inteligencia Artificial 1

### INTEGRANTES    	#######
Rivas Vanessa
Salcedo Andrea
Verdugo Reinaldo

### OBJETIVO    	#######
El objetivo del proyecto es aprender sobre el modelo de espacio  de  estados  y  sobre  los  diferentes algoritmos  de  búsqueda  heurística.

### ESTRUCTURA    	#######
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


### CORRIDA 			#######