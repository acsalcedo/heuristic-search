CC = gcc
CXX = g++
OPT = -g -Wall -O3 -Wno-unused-function -Wno-unused-variable -std=c++11
PSVNOPT =  --state_map --no_abstraction --history_len=1

all:
	make n-puzzle4x4.dfsID


psvn2c_core.c:
	cp ../psvn2c_core.c ./psvn2c_core.c

psvn2c_state_map.c:
	cp ../psvn2c_state_map.c ./psvn2c_state_map.c

psvn2c_abstraction.c:
	cp ../psvn2c_abstraction.c ./psvn2c_abstraction.c

%.c: %.psvn  psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c
	../psvn2c  $(PSVNOPT) --name=$(*F)  < $< > $@ 
	rm -f ./psvn2c_core.c ./psvn2c_state_map.c ./psvn2c_abstraction.c

.PRECIOUS: %.c

%.stBFS: %.c searchtree.cpp
	$(CXX) $(OPT) searchtree.cpp -include $< -o $@

%.stDFS: %.c dfsalternativo.cpp
	$(CXX) $(OPT) dfsalternativo.cpp -include $< -o $@

%.stDuplicates: %.c searchTreeWoDuplicates.cpp
	$(CXX) $(OPT) searchTreeWoDuplicates.cpp -include $< -o $@

%.ucs: %.c ucs.cpp Node.cpp
	$(CXX) $(OPT) ucs.cpp Node.cpp -include $< -o $@

%.dfsID: %.c dfsID.cpp 
	$(CXX) $(OPT) dfsID.cpp -include $< -o $@

%.bfs: %.c bfs.cpp 
	$(CXX) $(OPT) bfs.cpp -include $< -o $@

.PHONY : clean
clean:
	rm -f *.o *.st *.stDuplicates *.ucs *.stDFS *.bfs *.dfsID psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c *~
