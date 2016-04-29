SUBDIRS = \
 fileio \
 thread
 
all:
	@for f in $(SUBDIRS); do (echo $$f ; cd $$f && $(MAKE)) || exit 1; done
	
clean:
	@for f in $(SUBDIRS); do (echo $$f ; cd $$f && $(MAKE) clean) || exit 1; done
	
