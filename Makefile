# List of subdirectories containing their own Makefiles
SUBDIRS := $(wildcard src/*)

# Default target
all: $(SUBDIRS)

# For each subdirectory, run its Makefile
$(SUBDIRS):
	@echo "Making in $@"
	$(MAKE) -C $@

# Phony target to clean each subdirectory
clean:
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done

# Ensure 'clean' is not treated as a file
.PHONY: all clean $(SUBDIRS)


run-stemdump: $(SUBDIRS)
	./build/stemdump/stemdump examples/stemdump/test.txt

run-stemelf: $(SUBDIRS)
	./build/stemelf/stemelf examples/stemelf/test eps
run-stemreq: $(SUBDIRS)
	./build/stemreq/stemreq https://www.example.com hb