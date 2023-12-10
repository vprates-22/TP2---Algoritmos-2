# Makefile

# Compiler options
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Source files
BNB := $(wildcard src/TP_bnb/*.cpp) $(wildcard src/*.cpp)
TAT := $(wildcard src/TP_tat/*.cpp) $(wildcard src/*.cpp)
CHR := $(wildcard src/TP_chr/*.cpp) $(wildcard src/*.cpp)

# Object files
BNB_OBJS := $(BNB:.cpp=.o)
TAT_OBJS := $(TAT:.cpp=.o)
CHR_OBJS := $(CHR:.cpp=.o)

HEADER := -I./include

# Target executable
BTARGET := bin/bnb
TTARGET := bin/tat
CTARGET := bin/chr

all: $(BTARGET) $(TTARGET) $(CTARGET) 
	rm -f $(BNB_OBJS)
	rm -f $(TAT_OBJS)
	rm -f $(CHR_OBJS)

$(BTARGET): $(BNB_OBJS) 
	$(CXX) $(CXXFLAGS) $(HEADER) -o $@ $^

$(TTARGET): $(TAT_OBJS)
	$(CXX) $(CXXFLAGS) $(HEADER) -o $@ $^
	
$(CTARGET): $(CHR_OBJS) 
	$(CXX) $(CXXFLAGS) $(HEADER) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(HEADER) -c $< -o $@

clean:
	rm -f $(BNB_OBJS) $(TAT_OBJS) $(BTARGET) $(TTARGET) $(CTARGET)