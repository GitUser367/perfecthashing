CC		= g++
FLAGS	= -Wall -O2 
SOURCES	= pshgpu.cpp 
OBJECTS	= pshgpu.o 
LIBRARY = -L$(HOME)/install/lib
INCLUDE	= -I/usr/include/ -I$(HOME)/install/include -I../src/
TARGET	= ../binary/pshgpu

all:	$(TARGET)

$(TARGET):	$(OBJECTS) 
		$(CC) -o $(TARGET) $(OBJECTS) $(LIBRARY) -lX11 -lpthread -lm -lpng -lGLEW -lglut -lGL

%.o:	%.cpp
		$(CC) $(FLAGS) $(INCLUDE) -c $<

clean:
		rm $(OBJECTS) $(TARGET)

