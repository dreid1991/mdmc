FLAGS = -std=c++11 -Wall -O3 #-fopenmp -Wall# -O3 
CC = g++
PYLINK = -lpython2.7
MD = /home/daniel/Documents/classSim/mdmc/MD/
SHARED = /home/daniel/Documents/classSim/mdmc/

H = $(wildcard $(MD)*.h) $(wildcard $(SHARED)*.h)
SRCS = $(wildcard $(MD)*.cpp) $(wildcard $(SHARED)*.cpp)

OBJS = $(SRCS:.cpp=.cpp.o)
$(info Serial result = $(OBJS))
$(info Serial result = $(H))

main: $(OBJS) 
	$(CC) $(FLAGS) $(OBJS) -I/usr/include/python2.7 -I$(MD) -I$(SHARED) $(PYLINK) -o a.out

#main: $(SRCS) $(H)
#	g++ $(FLAGS) $(SRCS) $(H) -I/usr/include/python2.7 -I$(APATH) -lpython2.7 -o a.out
%.cpp.o: %.cpp
	$(CC) $(FLAGS) -c -o $@ $< $(PYLINK) -I/usr/include/python2.7 -I$(MD) -I$(SHARED)
clean:
	rm *.cpp.o
	rm ../*.cpp.o
