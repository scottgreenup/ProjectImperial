
COMPILER=g++
LIBRARIES=-lglfw -lGLU -lGL
SRCFILE=src/Main.cpp src/App.cpp
BINFILE=main

SRCDIR=src
OUTDIR=bin

default:
	mkdir -p $(OUTDIR)
	$(COMPILER) $(LIBRARIES) $(SRCFILE) -o $(OUTDIR)/$(BINFILE)

run:
	$(OUTDIR)/$(BINFILE)
