CC = gcc
CXX = g++
SRC = ../src/
PSVN = ../psvn/
NPUZZLE = n-puzzle/
HANOI = hanoi/
TOPSPIN = topspin/
RUBIKS = rubikscube/
EXTRA = extra/
OPT = -g -Wall -O3 -Wno-unused-function -Wno-unused-variable -std=c++11
PSVNOPT =  --state_map --no_abstraction --history_len=1

all:
	# make $(NPUZZLE)n-puzzle4x4.ucs
	# make $(NPUZZLE)n-puzzle4x4.bfs
	make $(NPUZZLE)n-puzzle4x4.ida

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

%.stBFS: %.c
	cp $(SRC)searchtree.cpp ./searchtree.cpp
	$(CXX) $(OPT) searchtree.cpp -include $< -o $@
	rm searchtree.cpp

%.stDFS: %.c
	cp $(SRC)dfsalternativo.cpp ./dfsalternativo.cpp
	$(CXX) $(OPT) dfsalternativo.cpp -include $< -o $@
	rm dfsalternativo.cpp

%.stDuplicates: %.c searchTreeWoDuplicates.cpp
	cp $(SRC)searchTreeWoDuplicates.cpp ./searchTreeWoDuplicates.cpp
	$(CXX) $(OPT) searchTreeWoDuplicates.cpp -include $< -o $@
	rm searchTreeWoDuplicates.cpp

%.ucs: %.c 
	cp $(SRC)ucs.cpp ./ucs.cpp
	cp $(PSVN)priority_queue.hpp ./priority_queue.hpp
	$(CXX) $(OPT) ucs.cpp -include $< -o $@
	rm ucs.cpp priority_queue.hpp

%.dfsID: %.c
	cp $(SRC)dfsID.cpp ./dfsID.cpp
	$(CXX) $(OPT) dfsID.cpp -include $< -o $@
	rm dfsID.cpp 

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
	cp $(PSVN)priority_queue.hpp ./priority_queue.hpp
	$(CXX) $(OPT) ida.cpp -include $< -o $@
	rm ida.cpp priority_queue.hpp heuristics.hpp 

.PHONY : clean
clean:
	rm -f *.o *.st *.stDuplicates *.ucs *.stDFS *.bfs *.dfsID *.ida *.c *.stBFS1 *~
