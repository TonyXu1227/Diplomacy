CXX = g++
CXXFLAGS = -std=c++17 -Wall

SRCS = adjudicate.cpp map.cpp orders.cpp

# Object formatting
OBJS = $(SRCS:.cpp=.o)

EXEC = diplo

all: $(EXEC)

# Object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Linker
$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@

# Clean up object files and executable
.PHONY: clean
clean:
	rm -f $(OBJS) $(EXEC)