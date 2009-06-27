CC		= g++
FLAGS	= -Wall -O2
SOURCES	= main.cpp 
OBJECTS	= main.o 
LIBRARY = ../binary/libpsh.a
INCLUDE	= -I../src/
TARGET	= ../binary/pshdecode

all:	$(TARGET)

$(TARGET):	$(OBJECTS) $(LIBRARY)
		$(CC) -o $(TARGET) $(OBJECTS) $(LIBRARY) -lX11 -lpthread -lm

%.o:	%.cpp
		$(CC) $(FLAGS) $(INCLUDE) -c $<

clean:
		rm $(OBJECTS) $(TARGET)

