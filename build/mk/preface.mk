# This file is included at the top of all other makefiles
# It discovers the environment and sets standard variables.

COMPILER ?= g++
LOCAL_COMPILER ?= g++

MKDIR ?= mkdir -p

MAKE_DIR := $(patsubst %/,%,$(dir $(realpath $(lastword $(MAKEFILE_LIST)))))

TOP_DIR := $(patsubst %/,%,$(dir $(realpath $(MAKE_DIR))))
SRC_DIR := $(TOP_DIR)/src
INC_DIR := $(TOP_DIR)/inc
TARGET_DIR := $(TOP_DIR)/target

DEBUG_MODE :=
ifeq ($(cfg),)
DEBUG_MODE := -ggdb 
endif

CPP_FLAGS := -I$(INC_DIR)

COMPILER_CPP ?= $(COMPILER) -std=c++0x $(DEBUG_MODE) -O0 -fPIC -c $(CPP_FLAGS) -o
LINK_EXE ?= $(COMPILER_CPP) $(DEBUG_MODE) -O0 -fPIC $(LINK_FLAGS) -o

#OSNAME := $(shell uname)
TARGET_OS := $(shell $(COMPILER) -dumpmachine)

NOOP := $(shell $(MKDIR) $(TARGET_DIR)/$(strip $(TARGET_OS)))
INNOLOGIX_TARGET_DIR := $(shell cd $(TARGET_DIR)/$(strip $(TARGET_OS)); pwd)
INNOLOGIX_OBJ_DIR := $(INNOLOGIX_TARGET_DIR)/obj
NOOP := $(shell $(MKDIR) $(INNOLOGIX_OBJ_DIR))

SYSTEM_INC_DIR = /usr/include
LIBEVENT_INC_DIR ?= $(SYSTEM_INC_DIR)
LIBEVENT_LIB_DIR ?= /usr/lib/$(TARGET_OS)

CPP_FLAGS := $(CPP_FLAGS) -I$(SYSTEM_INC_DIR) -I$(LIBEVENT_INC_DIR)
LINK_SO := -L$(LIBEVENT_LIB_DIR) -levent

#$(info $(LINK_SO))