# ------------------------------------------------
#  # dirtree Makefile
#
# Author: Sathish Kumar Srinivasan
# Date  : 2024-05-16
#
# Changelog :
#   0.01 - first version
# ------------------------------------------------
TARGET = dirtree
CC = gcc
# compiling flags here
CFLAGS   = -std=gnu99 -Wall -I.
LINKER   = gcc
# linking flags here
LFLAGS   = -Wall -I.

SRCDIR = src
BINDIR = bin
OBJDIR = obj

SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm = rm -f

SRCS := $(wildcard *.c)
all:$(BINDIR)/$(TARGET)

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(LINKER) $(OBJECTS) $(LFLAGS) -o $@
	@echo "Linking complete!"

.PHONY: clean
clean:
	@$(rm) $(OBJECTS)
	@echo "Cleanup complete!"

.PHONY: remove
remove: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "Executable removed!"
