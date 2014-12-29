CC=g++
CCFLAGS= -I. -Iglm -Iinclude 
SRC=$(wildcard src/*.cpp)
OBJ=$(addprefix obj/,$(notdir $(SRC:.cpp=.o)))
LIBS=-lSDL2
lightswitch: $(OBJ)
	@echo "Generating $@ with dependencies $^"
	$(CC) -g -o $@ $^ $(LIBS)

obj/%.o: src/%.cpp
	@echo "Generating $@ with first prerequisite $<"
	$(CC) $(CCFLAGS) -g -Wall -c -o $@ $<