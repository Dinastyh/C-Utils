#!/bin/make
SRC_DIR   := src

help:
	@echo "Makefile options:"
	@echo "  clean  : remove generated files"
	@echo "  cp     : compile_commands.json"

cp: compile_commands.json

compile_commands.json: $(shell find $(SRC_DIR) -name *.[ch])
	@python3 -m compiledb 

.PHONY: clean  cp 
clean:
	$(RM) compile_commands.json
