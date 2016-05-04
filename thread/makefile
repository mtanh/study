IDIR =-I/usr/include -I../common

ifeq ($(cfg),)
cfg := gdebug
endif

CC = gcc
CXX = g++

MKFILEPATH := $(abspath $(lastword $(MAKEFILE_LIST)))
CURRENTDIR := $(notdir $(patsubst %/,%,$(dir $(MKFILEPATH))))

DEFINES = -D__GXX_EXPERIMENTAL_CXX0X__
COMMONFLAGS = -Wall
ifeq ($(cfg), gdebug)
CXXFLAGS = -ggdb #-fPIC -pedantic -w -Wcast-align -Wno-long-long
else
CXXFLAGS = -O2 #-fPIC -pedantic -w -Wcast-align -Wno-long-long
endif
BIN_FILE = $(CURRENTDIR)

ODIR = ./
LBOOSTDIR = -L/usr/lib/x86_64-linux-gnu/

LIB_BOOST_SYSTEM = $(LBOOSTDIR) -lboost_system
LIB_BOOST_THREAD = $(LBOOSTDIR) -lboost_thread

LIBS = $(LIB_BOOST_SYSTEM) $(LIB_BOOST_THREAD) -lpthread

_DEPS =
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

#_OBJ = $(CURRENTDIR).o
_OBJ = test_main.o WorkerThread.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.cxx $(DEPS)
	$(CXX) -std=c++11 -c -o $@ $< $(CXXFLAGS) $(DEFINES) $(IDIR) $(COMMONFLAGS)

$(BIN_FILE): $(OBJ)
	$(CXX) -o $@ $^ $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(BIN_FILE)
