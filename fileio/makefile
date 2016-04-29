IDIR =/usr/include
CC = gcc
CXX = g++

MKFILEPATH := $(abspath $(lastword $(MAKEFILE_LIST)))
CURRENTDIR := $(notdir $(patsubst %/,%,$(dir $(MKFILEPATH))))

DEFINES = -D__GXX_EXPERIMENTAL_CXX0X__
COMMONFLAGS = -Wall

CFLAGS = -I$(IDIR) -I../common

BIN_FILE = $(CURRENTDIR)

ODIR = ./
LBOOSTDIR = -L/usr/lib/x86_64-linux-gnu/

LIB_BOOST_FILE_SYSTEM = $(LBOOSTDIR) -lboost_filesystem
LIB_RT = $(LBOOSTDIR) -lrt
LIB_BOOST_SYSTEM = $(LBOOSTDIR) -lboost_system
LIB_BOOST_THREAD = $(LBOOSTDIR) -lboost_thread

LIBS = $(LIB_BOOST_FILE_SYSTEM) $(LIB_RT) $(LIB_BOOST_SYSTEM) $(LIB_BOOST_THREAD) -lpthread

_DEPS = #terminate.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = $(CURRENTDIR).o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.cxx $(DEPS)
	$(CXX) -std=c++11 -c -o $@ $< $(CFLAGS) $(DEFINES) $(COMMONFLAGS)

$(BIN_FILE): $(OBJ)
	$(CXX) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(BIN_FILE)
