
CC=g++
STD=-std=c++11
LIBS=-lGLEW -lglfw -lGLU -lGL

ERRORFLAGS=-Wall -Wextra  -Wparentheses -Wfloat-equal -Wshadow -Wmissing-field-initializers -Wmissing-declarations -Wpadded -Winline
PEDANTIC=-pedantic
FLAGS=$(ERRORFLAGS) $(PEDANTIC)

SRCFILES=src/*.cpp
SRCDIR=src

OUTDIR=bin
OUTFILE=main

default: setup debug

setup:
	mkdir -p $(OUTDIR)

debug:
	clang -g3 $(STD) $(FLAGS) $(LIBS) $(SRCFILES) -o $(OUTDIR)/debug

release-debug:
	$(CC) -O3 -g3 $(STD) $(FLAGS) $(LIBS) $(SRCFILES) -o $(OUTDIR)/release-debug

release:
	$(CC) -O3 $(STD) $(FLAGS) $(LIBS) $(SRCFILES) -o $(OUTDIR)/release

run: default
	$(OUTDIR)/$(BINFILE)

