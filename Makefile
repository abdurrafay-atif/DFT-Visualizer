# compiler
CC = gcc

# flags when compiling programs
IFLAGS = -MMD -MP
CFLAGS = -Wall -Werror -Iinclude $(IFLAGS)
CFLAGS_TEST = -Wall -Werror -g -Iinclude $(IFLAGS)

# directory names
APPDIR = app
BINDIR = bin
BUILDDIR = build
INCLUDEDIR = include
SRCDIR = src
TESTDIR = tests

# obtain every source / obj / .d file recursively under the src directory
SRCS = $(shell find $(SRCDIR) -name "*.c")
OBJS = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/$(SRCDIR)/%.o, $(SRCS))
DEPS = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/$(SRCDIR)/%.d, $(SRCS))

# obtain every source / obj / .d file recursively under the app directory
SRCS_APP = $(shell find $(APPDIR) -name "*.c")
OBJS_APP = $(patsubst $(APPDIR)/%.c, $(BUILDDIR)/$(APPDIR)/%.o, $(SRCS_APP))
DEPS_APP = $(patsubst $(APPDIR)/%.c, $(BUILDDIR)/$(APPDIR)/%.d, $(SRCS_APP))
BIN_APP =  $(BINDIR)/app

# obtain every source / obj / .d / binary file recursively under the test directory
SRCS_TEST = $(shell find $(TESTDIR) -name "*.c")
OBJS_TEST = $(patsubst $(TESTDIR)/%.c, $(BUILDDIR)/$(TESTDIR)/%.o, $(SRCS_TEST))
DEPS_TEST = $(patsubst $(TESTDIR)/%.c, $(BUILDDIR)/$(TESTDIR)/%.d, $(SRCS_TEST))
BINS_TEST = $(patsubst $(TESTDIR)/%.c,$(BINDIR)/$(TESTDIR)/%,$(SRCS_TEST))

# creates all binary files, both for main & for testing
all: app test

# creates binary file for the main method only
app: $(BIN_APP)

# creates binary files only for testing
# also runs all the tests
test: $(BINS_TEST) 
	@for exe in ./$(BINDIR)/$(TESTDIR)/*; do \
		leaks --atExit -- ./$${exe}; \
	done

# creates the binary file for the main method
$(BIN_APP): $(OBJS_APP) $(OBJS)
	@mkdir -p $(dir $@)
	$(CC) $^ -o $@

# create every binary file for testing
$(BINDIR)/$(TESTDIR)/%: $(BUILDDIR)/$(TESTDIR)/%.o $(OBJS)
	@mkdir -p $(dir $@)
	$(CC) $^ -o $@

# creates every object file for all C files under SRCDIR
$(BUILDDIR)/$(SRCDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# creates every object file for all C files under APPDIR
$(BUILDDIR)/$(APPDIR)/%.o: $(APPDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# creates every object file for all C files under TESTDIR
$(BUILDDIR)/$(TESTDIR)/%.o: $(TESTDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS_TEST) -c $< -o $@

# ensure every object file is linked to the appropriate header files
-include $(wildcard $(BUILDDIR)/**/*.d)

clean:
	rm -rf $(BINDIR) $(BUILDDIR)
