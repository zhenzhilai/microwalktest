.PHONY : clean

CFLAGS=-O0 -fPIC -g -std=c99 -I./src/common -I./src/kyber512 $(EXTRAFLAGS)
LDFLAGS=-shared

SOURCES=$(shell echo src/*.c)
OBJECTS=$(SOURCES:.c=.o)

TARGET=libexample.so

all: $(TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET)

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)
