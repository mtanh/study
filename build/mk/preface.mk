# This file is included at the top of all other makefiles
# It discovers the environment and sets standard variables.

COMPILER = g++
LOCAL_COMPIELR = g++
SYSTEM_INC_DIR ?= /usr/include

MAKE_DIR := $(patsubst %/,%,$(dir $(realpath $(lastword $(MAKEFILE_LIST)))))

TOP_DIR := $(patsubst %/,%,$(dir $(realpath $(MAKE_DIR))))
SRC_DIR := $(TOP_DIR)/src
INC_DIR := $(TOP_DIR)/inc

#$(info $(TOP_DIR))
#$(info $(SRC_DIR))
#$(info $(INC_DIR))
$(info $(realpath $(lastword $(MAKEFILE_LIST))))
$(info $(dir $(realpath $(lastword $(MAKEFILE_LIST)))))

OBJDIR = 