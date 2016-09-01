SUB_DIRS :=\
	$(SRC_DIR)/common \
	$(SRC_DIR)/dgs \
	$(SRC_DIR)/dgs/server

all:
	@for f in $(SUB_DIRS); do (echo $$f; $(MAKE) -C $$f) || exit 1; done
	
.PHONY: clean
clean:
	@for f in $(SUB_DIRS); do (echo $$f; $(MAKE) clean -C $$f) || exit 1; done
	