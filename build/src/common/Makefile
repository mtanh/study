include ../../mk/preface.mk
include ../../mk/make-common-defs

VPATH := $(SRC_DIR)/common
SRC := $(wildcard *.cpp)

3RD_DEP_LIBS :=
3RD_LINK_LIBS :=

INNOLOGIC_LIBS := 
INNOLOGIC_DEP_LIBS :=
INNOLOGIC_LINK_LIBS :=

.PHONY: all clean

all: $(INNOLOGIX_TARGET_DIR)/exe

$(INNOLOGIX_TARGET_DIR)/exe: $(OBJ)

$(INNOLOGIX_OBJ_DIR)/%.o: %.cpp
	$(COMPILER_CPP) $@ $<

clean:
	rm -fr $(OBJ)
	