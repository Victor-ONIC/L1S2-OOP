CXX = g++
TARGET = collection

# Fichiers
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:%.cpp=%.o)

# Commandes
all: $(TARGET)

$(TARGET): $(OBJECTS)
	@$(CXX) -o $@ $^
	@echo "Linking complete !"

$(OBJECTS): %.o : %.cpp
	@$(CXX) $(OPT) $(DEBUG) -c $< -o $@
	@echo "Compiled "$<" successfully !"

# Pour Linux
clean:
	@rm -f $(wildcard *.o)
	@rm -f $(TARGET)
	@echo "Removal complete !"

# Pour Windows pwsh
cleanW:
	@del /q $(wildcard *.o)
	@del /q $(TARGET).exe
	@echo "Removal complete !"
