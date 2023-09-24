CXX = g++
CFLAGS = -O0 -Wall
PROG = server
CPPS = $(shell ls *.cpp)
OBJS = $(CPPS:.cpp=.o)

all: ${PROG}

${PROG}: ${OBJS}
	${CXX} -o $@ ${OBJS} ${CFLAGS}

%.o: %.cpp
	${CXX} ${CFLAGS} -c $<

clean: 
	rm -f ${PROG} ${OBJS}
