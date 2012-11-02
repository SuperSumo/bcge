COMPILER = cl
COMPFLAGS = /nologo /EHsc /c

LINKER = link
LINKFLAGS = /nologo /NODEFAULTLIB:msvcrt

INCPATH = /I"C:/Documents and Settings/uv448c/My Documents/lib/SFML-2.0-rc/include"

LIBPATH = /LIBPATH:"C:/Documents and Settings/uv448c/My Documents/lib/SFML-2.0-rc/lib"
LIBS = sfml-graphics.lib sfml-window.lib sfml-system.lib sfml-main.lib

.PHONEY = all compile clean link run, run2

all: run

compile:
	$(COMPILER) $(COMPFLAGS) $(DEFINES) $(INCPATH) main.cpp

link:
	$(LINKER) $(LINKFLAGS) $(LIBPATH) $(LIBS) main.obj /out:sfml.exe

run: clean compile link
	./sfml.exe

clean:
	rm -rf *.exe *.obj *.manifest