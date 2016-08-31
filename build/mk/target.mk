include $(MAKE_DIR)/make-common-defs

SUB_DIRS := $(SRC_DIR)/dgs/server
$(info $(SUB_DIRS))

all:
	@for f in $(SUB_DIRS); do (echo $$f; cd $$f && $(MAKE)) || exit 1; done