CC = gcc
CFLAGS = -I./src/include -g
BINDIR = ./bin
SRCDIR = ./src

# Define your executables
EXECUTABLES = cat ls mkdir shell

# Default target
all: $(EXECUTABLES)

# General rule for building the executables
%: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $< -o $(BINDIR)/$@

# Specific rule for building the shell
shell: $(SRCDIR)/shell.c $(SRCDIR)/shell_builtins.c $(SRCDIR)/include/shell_builtins.h
	$(CC) $(CFLAGS) $(SRCDIR)/shell_builtins.c $(SRCDIR)/shell.c -o $(BINDIR)/shell

# Clean the build directory
.PHONY: clean
clean:
	rm -f $(addprefix $(BINDIR)/,$(EXECUTABLES))
