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


all: $(TARGETDIR)/gladewin $(TARGETDIR)/stacks $(TARGETDIR)/textView $(TARGETDIR)/textViewGlade

## Target: gladewin
OBJS_gladewin =  \
	$(TARGETDIR)/gladewin.o
OBJS_stacks = \
	$(TARGETDIR)/stacks.o
OBJS_textView = \
	$(TARGETDIR)/textView.o
OBJS_textViewGlade = \
	$(TARGETDIR)/textViewGlade.o
USERLIBS =   
DEPLIBS =  
LDLIBS = $(PTHREAD) $(GTKLIB) -export-dynamic


# Link or archive
$(TARGETDIR)/gladewin: $(TARGETDIR) $(OBJS_gladewin) $(DEPLIBS)
	$(LINK.c) $(CFLAGS) -o $@ $(OBJS_gladewin) $(LDLIBS)

$(TARGETDIR)/stacks: $(TARGETDIR) $(OBJS_stacks) $(DEPLIBS)
	$(LINK.c) $(CFLAGS) -o $@ $(OBJS_stacks) $(LDLIBS)

$(TARGETDIR)/textView: $(TARGETDIR) $(OBJS_textView) $(DEPLIBS)
	$(LINK.c) $(CFLAGS) -o $@ $(OBJS_textView) $(LDLIBS)
	
$(TARGETDIR)/textViewGlade: $(TARGETDIR) $(OBJS_textViewGlade) $(DEPLIBS)
	$(LINK.c) $(CFLAGS) -o $@ $(OBJS_textViewGlade) $(LDLIBS)
	
# Compile source files into .o files
$(TARGETDIR)/gladewin.o: $(TARGETDIR) gladewin.c
	$(COMPILE.c) $(CFLAGS) $(GTKLIB) -o $@ gladewin.c

$(TARGETDIR)/stacks.o: $(TARGETDIR) stacks.c
	$(COMPILE.c) $(CFLAGS) $(GTKLIB) -o $@ stacks.c

$(TARGETDIR)/textView.o: $(TARGETDIR) textView.c
	$(COMPILE.c) $(CFLAGS) $(GTKLIB) -o $@ textView.c

$(TARGETDIR)/textViewGlade.o: $(TARGETDIR) textViewGlade.c
	$(COMPILE.c) $(CFLAGS) $(GTKLIB) -o $@ textViewGlade.c
	
#### Clean target deletes all generated files ####
clean:
	rm -f \
		$(TARGETDIR)/gladewin \
		$(TARGETDIR)/gladewin.o \
		$(TARGETDIR)/stacks \
		$(TARGETDIR)/stacks.o
		$(TARGETDIR)/textView \
		$(TARGETDIR)/textView.o \
		$(TARGETDIR)/textViewGlade \
		$(TARGETDIR)/textViewGlade.o	
	rm -f -r $(TARGETDIR)


# Create the target directory (if needed)
$(TARGETDIR):
	mkdir -p $(TARGETDIR)


# Enable dependency checking
.KEEP_STATE:
.KEEP_STATE_FILE:.make.state.GNU-x86_64-MacOSX

