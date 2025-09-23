CXX = g++
CXXFLAGS = -std=c++11 -pedantic-errors -Wall -Wextra -g -Wswitch-enum
TARGET = envelop
SRC = EnvelopManager.cpp utils.cpp Envelop.cpp FixedExpenses.cpp main.cpp 

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
