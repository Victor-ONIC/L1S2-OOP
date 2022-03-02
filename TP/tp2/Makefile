CXX = g++
TARGET = collection

# Fichiers
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:%.cpp=%.o)

# Commandes
all: $(TARGET)

$(OBJECTS): %.o : %.cpp
	@$(CXX) -c $< -o $@
	@echo "Compiled "$<" successfully !"

$(TARGET): $(OBJECTS)
	@$(CXX) -o $@ $^
	@echo "Linking complete !"

clean:
	@rm -f $(wildcard *.o)
	@rm -f $(TARGET)
	@echo "Removal complete !"
