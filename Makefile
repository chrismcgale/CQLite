CC = gcc
CFLAGS = -Wall -Wextra -g -I./include
SRCDIR = src
OBJDIR = obj
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJ = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
TARGET = db.exe

# Windows specific commands
ifeq ($(OS),Windows_NT)
    RM = del /Q /F
    RMDIR = rmdir /Q /S
    MKDIR = mkdir
    TARGET_CLEAN = $(TARGET) $(OBJDIR)\*.o
else
    RM = rm -f
    RMDIR = rm -rf
    MKDIR = mkdir -p
    TARGET_CLEAN = $(TARGET) $(OBJDIR)/*.o
endif

# Create obj directory if it doesn't exist
$(shell $(MKDIR) $(OBJDIR) 2>NUL)

# Default target
all: $(TARGET)

# Linking
$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

# Compiling
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

# Remove all generated files
clean:
	@if exist $(TARGET) $(RM) $(TARGET)
	@if exist $(OBJDIR) $(RMDIR) $(OBJDIR)

# Remove object files only
clean-obj:
	@if exist $(OBJDIR)\*.o $(RM) $(OBJDIR)\*.o

# Rebuild everything from scratch
rebuild: clean all

# List all source files
list-src:
	@echo Source files:
	@echo $(SRCS)

# Dependencies
$(OBJDIR)/main.o: $(SRCDIR)/main.c include/input.h include/table.h include/statement.h include/meta.h include/cursor.h
$(OBJDIR)/input.o: $(SRCDIR)/input.c include/input.h
$(OBJDIR)/table.o: $(SRCDIR)/table.c include/table.h include/node.h
$(OBJDIR)/statement.o: $(SRCDIR)/statement.c include/statement.h include/table.h include/node.h
$(OBJDIR)/meta.o: $(SRCDIR)/meta.c include/meta.h include/table.h
$(OBJDIR)/cursor.o: $(SRCDIR)/cursor.c include/cursor.h include/node.h
$(OBJDIR)/node.o: $(SRCDIR)/node.c include/node.h

.PHONY: all clean clean-obj rebuild list-src