## -*- Makefile -*-
##
## User: matthew
## Time: 24-Mar-2019 09:11:30
## Makefile created by Oracle Developer Studio.
##
## This file is generated automatically.
##


#### Compiler and tool definitions shared by all build targets #####
CC = gcc
BASICOPTS = -g -Wall 
CFLAGS = $(BASICOPTS)
GTKLIB =`pkg-config --cflags --libs gtk+-3.0`
PTHREAD=-pthread

# Define the target directories.
TARGETDIR=.


all: $(TARGETDIR)/gladewin $(TARGETDIR)/stacks

## Target: gladewin
OBJS_gladewin =  \
	$(TARGETDIR)/gladewin.o
OBJS_stacks = \
	$(TARGETDIR)/stacks.o
USERLIBS =   
DEPLIBS =  
LDLIBS = $(PTHREAD) $(GTKLIB) -export-dynamic


# Link or archive
$(TARGETDIR)/gladewin: $(TARGETDIR) $(OBJS_gladewin) $(DEPLIBS)
	$(LINK.c) $(CFLAGS) -o $@ $(OBJS_gladewin) $(LDLIBS)

$(TARGETDIR)/stacks: $(TARGETDIR) $(OBJS_stacks) $(DEPLIBS)
	$(LINK.c) $(CFLAGS) -o $@ $(OBJS_stacks) $(LDLIBS)

# Compile source files into .o files
$(TARGETDIR)/gladewin.o: $(TARGETDIR) gladewin.c
	$(COMPILE.c) $(CFLAGS) $(GTKLIB) -o $@ gladewin.c

$(TARGETDIR)/stacks.o: $(TARGETDIR) stacks.c
	$(COMPILE.c) $(CFLAGS) $(GTKLIB) -o $@ stacks.c


#### Clean target deletes all generated files ####
clean:
	rm -f \
		$(TARGETDIR)/gladewin \
		$(TARGETDIR)/gladewin.o \
		$(TARGETDIR)/stacks \
		$(TARGETDIR)/stacks.o
	rm -f -r $(TARGETDIR)


# Create the target directory (if needed)
$(TARGETDIR):
	mkdir -p $(TARGETDIR)


# Enable dependency checking
.KEEP_STATE:
.KEEP_STATE_FILE:.make.state.GNU-x86_64-MacOSX

