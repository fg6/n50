#
#	 Makefile
#
CC=g++
SOURCES= n50.cpp 

INCLUDES = -Imylibs/gzstream/ 
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
	$(CC) -std=c++11 $(OBJECTS) -Lmylibs/gzstream/ -lgzstream -lz -o $@


# create *.o
.cpp.o:
	$(COMPILE) $< -o $@

clean:
	@echo -n '+++ Cleaning all object files ... '
	@rm -f $(EXECUTABLE) $(OBJECTS)
	@echo 'Done.'

