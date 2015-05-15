CC = gcc
CXX = g++
SRC = ../src/
PSVN = ../psvn/
NPUZZLE = n-puzzle/
HANOI = hanoitowers/
TOPSPIN = top-spin/
RUBIKS = rubikscube/
EXTRA = extra/
OPT = -g -Wall -O3 -Wno-unused-function -Wno-unused-variable -std=c++11
PSVNOPT =  --state_map --history_len=1
PROB = 0
ROUTE = 0
ALG = 0
SIZE = 0
all:

# Si no se ingreso ningun problema  #########################################
ifeq ($(PROB),0)
	@echo "Ingrese el problema que desea resolver"
	@echo "Opciones posibles: PROB=npuzzle / hanoi / rubiks / topspin"

## Se ingreso problemas
else

# Si no se ingreso ningun algoritmo *******************
ifeq ($(ALG),0)
		@echo "Ingrese el algoritmo que usará para resolver el problema"
		@echo "Opciones posibles: ALG= ucs / ida / a / dfid / dfucs"

## Se ingreso algoritmo
else


## Si no se ingreso un tamaño -----------
ifeq ($(SIZE),0)
			@echo "Ingrese el tamaño que usará para el problema escogido"

## Se ingreso tamaño
else 

## Si el problema escogido fue npuzzle
ifeq ($(PROB),npuzzle)

## npuzzle tamaño 4x4
ifeq ($(SIZE),4)
			make $(NPUZZLE)n-puzzle4x4.$(ALG)

## npuzzle tamaño 5x5
else ifeq ($(SIZE),5)
			make $(NPUZZLE)n-puzzle5x5.$(ALG)

## npuzzle tamaño incorrecto
else
	@echo "El tamaño ingresado no es correcto"
endif
## endif tamaño del npuzzle

endif
## endif npuzzle 

endif
## endif tamaño ----------------------------

endif
## endif algoritmo ***********************************

endif
###endif problema  ############################################################

npuzzle:
# Si no se ingreso ningun algoritmo *******************
ifeq ($(ALG),0)
		@echo "Ingrese el algoritmo que usará para resolver el problema"
		@echo "Opciones posibles: ALG= ucs / ida / a / dfid / dfucs"

## Se ingreso algoritmo
else


## Si no se ingreso un tamaño -----------
ifeq ($(SIZE),0)
			@echo "Ingrese el tamaño que usará para el problema escogido"

## Se ingreso tamaño
else 

## npuzzle tamaño incorrecto
ifeq (,$(filter 4 5,$(SIZE)))
	@echo "El tamaño ingresado no es correcto"

##
else
## npuzzle tamaño 4x4
ifeq ($(SIZE),4)
			make $(NPUZZLE)n-puzzle4x4.$(ALG)
ifneq (,$(filter ida a,$(ALG)))
	make abstractor
	make pdb ss=$(NPUZZLE)n-puzzle4x4 absname=abs1 < ../abstractions/n-puzzle4x4/weak/abstraction1.txt
	make pdb ss=$(NPUZZLE)n-puzzle4x4 absname=abs2 < ../abstractions/n-puzzle4x4/weak/abstraction2.txt
	make pdb ss=$(NPUZZLE)n-puzzle4x4 absname=abs3 < ../abstractions/n-puzzle4x4/weak/abstraction3.txt
endif

## npuzzle tamaño 5x5
else ifeq ($(SIZE),5)
			make $(NPUZZLE)n-puzzle5x5.$(ALG)
ifneq (,$(filter ida a,$(ALG)))
	make abstractor
endif

endif
##


endif
## endif tamaño del npuzzle

endif
## endif tamaño ----------------------------

endif
## endif algoritmo ***********************************

rubiks:
# Si no se ingreso ningun algoritmo *******************
ifeq ($(ALG),0)
		@echo "Ingrese el algoritmo que usará para resolver el problema"
		@echo "Opciones posibles: ALG= ucs / ida / a / dfid / dfucs"

## Se ingreso algoritmo
else


## Si no se ingreso un tamaño -----------
ifeq ($(SIZE),0)
			@echo "Ingrese el tamaño que usará para el problema escogido"

## Se ingreso tamaño
else 

## rubiks tamaño incorrecto
ifeq (,$(filter 2 3,$(SIZE)))
	@echo "El tamaño ingresado no es correcto"

##
else
## rubiks cube tamaño 3x3x3
ifeq ($(SIZE),3)
			make $(RUBIKS)rubikscube3x3.$(ALG)
ifneq (,$(filter ida a,$(ALG)))
	make abstractor
	make pdb ss=$(RUBIKS)rubikscube3x3 absname=abs1 < ../abstractions/rubikscube3x3/corners/abstraction1.txt
	make pdb ss=$(RUBIKS)rubikscube3x3 absname=abs2 < ../abstractions/rubikscube3x3/edges/abstraction1.txt
	
endif

## rubiks cube tamaño 2x2x2
else ifeq ($(SIZE),2)
			make $(RUBIKS)rubikscube2x2.$(ALG)
ifneq (,$(filter ida a,$(ALG)))
	make abstractor
endif

endif
##


endif
## endif tamaño del npuzzle

endif
## endif tamaño ----------------------------

endif
## endif algoritmo ***********************************

hanoist:
# Si no se ingreso ningun algoritmo *******************
ifeq ($(ALG),0)
		@echo "Ingrese el algoritmo que usará para resolver el problema"
		@echo "Opciones posibles: ALG= ucs / ida / a / dfid / dfucs"

## Se ingreso algoritmo
else


## Si no se ingreso un tamaño -----------
ifeq ($(SIZE),0)
			@echo "Ingrese el tamaño que usará para el problema escogido"

## Se ingreso tamaño
else 

## Torres de Hanoi
ifeq ($(SIZE),12)
			make $(HANOI)towersofhanoi4-12.$(ALG)

## rubiks cube tamaño 3x3x3
else ifeq ($(SIZE),14)
			make $(HANOI)towersofhanoi4-14.$(ALG)

else ifeq ($(SIZE),16)
			make $(HANOI)towersofhanoi4-16.$(ALG)

else ifeq ($(SIZE),18)
			make $(HANOI)towersofhanoi4-18.$(ALG)

## rubiks cube tamaño incorrecto
else
	@echo "El tamaño ingresado no es correcto"
endif
## endif tamaño del rubiks cube

endif
## endif tamaño ----------------------------

endif
## endif algoritmo ***********************************

topspin:
ifeq ($(ALG),0)
		@echo "Ingrese el algoritmo que usará para resolver el problema"
		@echo "Opciones posibles: ALG= ucs / ida / a / dfid / dfucs"

## Se ingreso algoritmo
else


## Si no se ingreso un tamaño -----------
ifeq ($(SIZE),0)
			@echo "Ingrese el tamaño que usará para el problema TopSpin"

## Se ingreso tamaño
else 

## TopSpin 12
ifeq ($(SIZE),12)
			make $(TOPSPIN)topspin12-4.$(ALG)

## TopSpin 14
else ifeq ($(SIZE),14)
			make $(TOPSPIN)topspin14-4.$(ALG)

else ifeq ($(SIZE),16)
			make $(TOPSPIN)topspin16-4.$(ALG)

else ifeq ($(SIZE),17)
			make $(TOPSPIN)topspin17-4.$(ALG)

## rubiks cube tamaño incorrecto
else
	@echo "El tamaño ingresado no es correcto"
endif
## endif tamaño del rubiks cube

endif
## endif tamaño ----------------------------

endif
## endif algoritmo ***********************************

psvn2c_core.c:
	cp $(PSVN)psvn2c_core.c ./psvn2c_core.c

psvn2c_state_map.c:
	cp $(PSVN)psvn2c_state_map.c ./psvn2c_state_map.c

psvn2c_abstraction.c:
	cp $(PSVN)psvn2c_abstraction.c ./psvn2c_abstraction.c

%.c: %.psvn  psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c
	$(PSVN)psvn2c  $(PSVNOPT) --name=$(*F)  < $< > $@ 
	rm -f ./psvn2c_core.c ./psvn2c_state_map.c ./psvn2c_abstraction.c

.PRECIOUS: %.c

%.st: %.c
	cp $(SRC)st.cpp ./st.cpp
	$(CXX) $(OPT) st.cpp -include $< -o $@
	rm st.cpp

%.ucs: %.c 
	cp $(SRC)ucs.cpp ./ucs.cpp
	cp $(PSVN)priority_queue.hpp ./priority_queue.hpp
	$(CXX) $(OPT) ucs.cpp -include $< -o $@
	rm ucs.cpp priority_queue.hpp

%.dfid: %.c
	cp $(SRC)dfid.cpp ./dfid.cpp
	$(CXX) $(OPT) dfid.cpp -include $< -o $@
	rm dfid.cpp 

%.bfs: %.c
	cp $(SRC)bfs.cpp ./bfs.cpp
	$(CXX) $(OPT) bfs.cpp -include $< -o $@
	rm bfs.cpp


%.dfucs: %.c
	cp $(SRC)dfucs.cpp ./dfucs.cpp
	$(CXX) $(OPT) dfucs.cpp -include $< -o $@
	rm dfucs.cpp

%.ida: %.c
	cp $(SRC)ida.cpp ./ida.cpp
	cp $(SRC)heuristics.hpp ./heuristics.hpp 
	$(CXX) $(OPT) ida.cpp -include $< -o $@
	rm ida.cpp heuristics.hpp 

%.a: %.c
	cp $(SRC)a.cpp ./a.cpp
	cp $(SRC)heuristics.hpp ./heuristics.hpp 
	cp $(PSVN)priority_queue.hpp ./priority_queue.hpp
	$(CXX) $(OPT) a.cpp -include $< -o $@
	rm a.cpp priority_queue.hpp heuristics.hpp 

%.distSummary: %.c
	cp $(PSVN)priority_queue.hpp ./priority_queue.hpp
	cp $(SRC)distSummary.cpp ./distSummary.cpp
	$(CXX) $(OPT) distSummary.cpp -include $< -o $@
	rm -f priority_queue.hpp distSummary.cpp

abstractor: 
	cp $(PSVN)psvn.hpp ./psvn.hpp
	cp $(PSVN)psvn.cpp ./psvn.cpp 
	cp $(SRC)abstractor.cpp ./abstractor.cpp
	$(CXX) $(OPT) abstractor.cpp psvn.cpp -o $@
	rm -f psvn.cpp psvn.hpp abstractor.cpp 

.PRECIOUS: $(absname).abst
.PRECIOUS: $(absname).state_map

.PHONY: pdb
pdb: abstractor
	#rm -f $(absname).abst $(absname).c $(absname).distSummary $(absname).dist $(absname).psvn $(absname).state_map
ifeq ($(strip $(wildcard $(absname).txt)),)
	./abstractor $(ss).psvn $(absname)
else
	./abstractor $(ss).psvn $(absname) < $(absname).txt
endif
	make $(absname).distSummary
	./$(absname).distSummary $(absname).state_map

.PHONY : clean
clean:
	rm -f *.o *.a *.st *.stDuplicates *.distSummary *.st *.state_map abstractor *.ucs *.bfs *.dfsID *.ida *.c psvn2c_abstraction.c *.psvn *.abst absname.state_map absname.c*~
