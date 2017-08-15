
MAKE = g++ -std=c++11 
SOURCE = /home/holynerd/Desktop/Projects/ElectricField/Source/
INCLUDE = /home/holynerd/Desktop/Projects/ElectricField/includes/
HEADER = /home/holynerd/Desktop/Projects/ElectricField/Header/
SHADERS = /home/holynerd/Desktop/Projects/ElectricField/Shaders/
LIB = /home/holynerd/LibsOpenGL/
LIB_LINK = -lGLEW -lglfw3 -lX11 -lXrandr -lXinerama -lXi -lXxf86vm -lXcursor -lGL -lpthread -lm -ldl

all: run
build: main

run: main
	./main

main: $(SOURCE)main.o $(SOURCE)application.o $(SOURCE)shader.o \
	$(SOURCE)charge.o $(SOURCE)electricField.o $(SOURCE)line.o $(SOURCE)range.o\
	$(HEADER)*.h  $(SHADERS)*.glsl
	$(MAKE) -o main $(SOURCE)main.o $(SOURCE)shader.o $(SOURCE)application.o \
	$(SOURCE)charge.o $(SOURCE)electricField.o $(SOURCE)line.o $(SOURCE)range.o  \
	-I$(INCLUDE) -I$(HEADER) -L$(LIB) $(LIB_LINK) 

$(SOURCE)main.o: $(SOURCE)main.cpp
	$(MAKE) -c $(SOURCE)main.cpp -o$(SOURCE)main.o \
	-I$(INCLUDE) -I$(HEADER)

$(SOURCE)application.o: $(SOURCE)application.cpp $(HEADER)application.h
	$(MAKE) -c $(SOURCE)application.cpp -o$(SOURCE)application.o \
	-I$(INCLUDE) -I$(HEADER)

$(SOURCE)shader.o: $(SOURCE)shader.cpp $(HEADER)shader.h
	$(MAKE) -c $(SOURCE)shader.cpp -o$(SOURCE)shader.o \
	-I$(INCLUDE) -I$(HEADER)

$(SOURCE)charge.o: $(SOURCE)charge.cpp $(HEADER)charge.h
	$(MAKE) -c $(SOURCE)charge.cpp -o$(SOURCE)charge.o \
	-I$(INCLUDE) -I$(HEADER)

$(SOURCE)electricField.o: $(SOURCE)electricField.cpp $(HEADER)electricField.h
	$(MAKE) -c $(SOURCE)electricField.cpp -o$(SOURCE)electricField.o \
	-I$(INCLUDE) -I$(HEADER)

$(SOURCE)line.o: $(SOURCE)line.cpp $(HEADER)line.h
	$(MAKE) -c $(SOURCE)line.cpp -o$(SOURCE)line.o \
	-I$(INCLUDE) -I$(HEADER)

$(SOURCE)range.o: $(SOURCE)range.cpp $(HEADER)range.h
	$(MAKE) -c $(SOURCE)range.cpp -o$(SOURCE)range.o \
	-I$(INCLUDE) -I$(HEADER)

clean:
	rm -f $(SOURCE)*.o
