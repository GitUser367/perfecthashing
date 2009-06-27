CC		= g++
FLAGS	= -Wall -O2
SOURCES	= psh.cpp math_tools.cpp
OBJECTS	= psh.o math_tools.o 
TARGET	= ../binary/libpsh.a

all:	$(TARGET)

$(TARGET):	$(OBJECTS)
		ar cqs $(TARGET) $(OBJECTS)

%.o:	%.cpp %.h
		$(CC) $(FLAGS) -c $<

clean:
		rm -f $(OBJECTS) $(TARGET)

