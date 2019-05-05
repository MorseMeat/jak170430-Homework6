# Filename	 Makefile
# Date		 05/05/2019
# Author	 Jacob Kitchens
# Email		 jak170430@utdallas.edu
# Course 	 CS 3377.502
# Version	 1.0
#	
# Description 	 Makefile for Assignment 6

CXX = g++
CFLAGS = -Wall -Wno-write-strings
CPPFLAGS = -I/scratch/perkins/include
LDFLAGS = -L/scratch/perkins/lib
LDLIBS = -lcdk -lcurses

PROJECTNAME = cs3377Assignment5
EXEC = exampleCDK.exe

OBJS = example1.o

all: $(EXEC)

clean: 
	rm -f $(OBJS) *~ $(EXEC)
	rm -f *.nfs

$(EXEC): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)

backup:
	@make clean
	@mkdir -p ~/backups; chmod 700 ~/backups
	@$(eval CURDIRNAME := $(shell basename "`pwd`"))
	@$(eval MKBKUPNAME := ~/backups/$(PROJECTNAME)-$(shell date +'%y.%m.%d-%H:%M:%S').tar.gz)
	@echo
	@echo Writing Backup file to:
	@echo
	@-tar zcfv $(MKBKUPNAME) ../$(CURDIRNAME) 2> /dev/null
	@chmod 700 $(MKBKUPNAME)
	@echo Done!
