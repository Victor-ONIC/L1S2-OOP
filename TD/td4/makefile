CXX = g++
CFLAG = -Wall -pedantic
DEBUG = -g
OPT = 
TARGET = t

SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:%.cpp=%.o)

# Commandes
all: $(TARGET)

$(TARGET): $(OBJECTS)
	@$(CXX) -o $@ $^
	@echo "Linking complete !"

$(OBJECTS): %.o : %.cpp
	@$(CXX) $(OPT) $(DEBUG) $(CFLAG) -c $< -o $@
	@echo "Compiled "$<" successfully !"

# Supprimer les fichiers objets
# Pour Linux
clean:
	@rm -f $(wildcard *.o)
	@echo "Removal complete !"
# Pour Windows PowerShell
cleanW:
	@del /q $(wildcard *.o)
	@echo "Removal complete !"

# Supprimer
# Pour Linux
cleanA:
	@rm -f $(wildcard *.o)
	@rm -f $(TARGET)
	@echo "Removal complete !"
# Pour Windows PowerShell
cleanWA:
	@del /q $(wildcard *.o)
	@del /q $(TARGET).exe
	@echo "Removal complete !"
