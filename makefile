
COMPILER=g++
LIBRARIES=-lGLEW -lglfw -lGLU -lGL
SRCFILE=src/*.cpp
BINFILE=main

SRCDIR=src
OUTDIR=bin

default:
	mkdir -p $(OUTDIR)
	$(COMPILER) $(LIBRARIES) $(SRCFILE) -o $(OUTDIR)/$(BINFILE)

run: default
	$(OUTDIR)/$(BINFILE)
