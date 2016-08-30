VPATH=src/common src/dgs src/dgs/server
CC:=gcc
CXX:=g++
OUTDIR=bin
OBJDIR=obj
MAKELIB=-ggdb -pthread
CXXFLAGS=-I ./inc

ALL_SRCS=$(SRCS) $(OTHER_SRCS)
OBJS=$(addprefix $(OBJDIR)/,$(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(ALL_SRCS))))

SRCS=\
	lognew.cpp \
	dgsserver.cpp \
	dgsapi.cpp

OTHER_SRCS=

.PHONY: all
all: $(ALL_SRCS) $(OBJS) $(OBJDIR)/lognew.o $(OUTDIR)/dgsServer

$(OUTDIR)/dgsServer: $(OBJS)
	$(CXX) $(MAKELIB) -o $@ $^

obj/lognew.o: lognew.cpp
	$(CXX) $(CXXFLAGS) -c $<

obj/dgsserver.o: dgsserver.cpp
	$(CXX) $(CXXFLAGS) -c $<

obj/dgsapi.o: dgsapi.cpp
	$(CXX) $(CXXFLAGS) -c $<

.PHONY: clean
clean:
	rm -rf $(OBJDIR)/*.o $(OUTDIR)/dgsServer

