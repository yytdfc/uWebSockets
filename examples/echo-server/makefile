SRCS=$(wildcard ./*.cpp)
EXES=$(SRCS:.cpp=)
CXX = g++
CXX_FLAG = -std=c++11
LD_FLAGS = -luWS -lpthread -lcrypto -lssl -lz

all: $(EXES)

%: %.cpp
	$(CXX) $(CXX_FLAG) $< $(LD_FLAGS) -o $@



