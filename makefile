
COMPILER=g++
LIBRARIES=-lglfw -lGLU -lGL
SRCFILE=main.cpp
BINFILE=main

SRCDIR=src
OUTDIR=bin

default:
	mkdir -p $(OUTDIR)
	$(COMPILER) $(LIBRARIES) $(SRCDIR)/$(SRCFILE) -o $(OUTDIR)/$(BINFILE)
