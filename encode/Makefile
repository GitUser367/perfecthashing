CC		= g++
FLAGS	= -Wall -O2 -Dcimg_use_png
SOURCES	= main.cpp 
OBJECTS	= main.o 
LIBRARY = ../binary/libpsh.a
INCLUDE	= -I../src/
TARGET	= ../binary/pshencode

all:	$(TARGET)

$(TARGET):	$(OBJECTS) $(LIBRARY)
		$(CC) -o $(TARGET) $(OBJECTS) $(LIBRARY) -lX11 -lpthread -lm -lpng

%.o:	%.cpp
		$(CC) $(FLAGS) $(INCLUDE) -c $<

clean:
		rm $(OBJECTS) $(TARGET)

