#
#	 Makefile
#
CC=g++
SOURCES= n50.cpp

INCLUDES = 
LIBS =  

CFLAGS= -c  $(INCLUDES) 
COMPILE = $(CC) $(CFLAGS)

OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=$(SOURCES:.cpp=)

all: clean iprint $(SOURCES) $(EXECUTABLE) oprint

iprint:
	@echo '+++ compiling all ... '
oprint:
	@echo 'Done '

# compile source	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -lz -o $@


# create *.o
.cpp.o:
	$(COMPILE) $< -o $@

clean:
	@echo -n '+++ Cleaning all object files ... '
	@rm -f $(EXECUTABLE) $(OBJECTS)
	@echo 'Done.'

