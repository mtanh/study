include ../../../mk/preface.mk
include ../../../mk/make-common-defs

VPATH := $(SRC_DIR)/common:$(SRC_DIR)/dgs:$(SRC_DIR)/dgs/server
#VPATH := $(SRC_DIR)/dgs/server:$(SRC_DIR)/common:$(SRC_DIR)/dgs

SRC := $(wildcard *.cpp) $(wildcard ../*.cpp) $(wildcard ../../common/*.cpp)
#OBJ := $(subst .cpp,.o,$(notdir $(SRC)))
#OBJ := $(addprefix $(INNOLOGIX_OBJ_DIR)/,$(OBJ))

#$(info OBJ: $(OBJ))

3RD_DEP_LIBS := /usr/lib/libpthread.so /usr/local/lib/libevent.so
3RD_LINK_LIBS := -L/usr/local/lib -levent -lpthread

INNOLOGIC_LIBS := 
INNOLOGIC_DEP_LIBS :=
INNOLOGIC_LINK_LIBS :=

all: $(INNOLOGIX_TARGET_DIR)/dgsServer

$(INNOLOGIX_TARGET_DIR)/dgsServer: $(OBJ) $(3RD_DEP_LIBS) $(INNOLOGIC_DEP_LIBS)
	$(LINK_EXE) $@ $(OBJ) $(3RD_LINK_LIBS) $(INNOLOGIC_LINK_LIBS) 
	
$(INNOLOGIX_OBJ_DIR)/%.o: %.cpp
	$(COMPILER_CPP) $@ $<

clean:
	rm -fr $(OBJ)
	rm -fr $(INNOLOGIX_TARGET_DIR)/dgsServer
	