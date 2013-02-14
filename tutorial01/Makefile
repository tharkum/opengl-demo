CC=g++
CFLAGS=-c -Wall
LDLIBS=-lGL -lrt -lpthread -lX11
OBJECTS=$(SOURCES:.cpp=.o)
TARGET=$(shell basename `pwd`)
SOURCES=$(wildcard *.cpp)

all: $(SOURCES) $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LDLIBS)

clean:
	$(RM) $(OBJECTS) $(TARGET)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
