INC_DIR:=./inc
SRC_DIR:=./src
SRCS:=$(wildcard ./src/*.cc) 
OBJS:=$(patsubst %.cc, %.o, $(SRCS))
LIBS:= -lpthread

CXX:=g++

CXXFLAGS:= -std=c++11

EXE:=./bin/main.exe

$(EXE) : $(OBJS)
	$(CXX) -o $(EXE) $(OBJS) $(CXXFLAGS)

clean:
	rm -rf $(EXE)
	rm -rf $(OBJS)
