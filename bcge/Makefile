COMPILER = g++
COMPFLAGS = -c -std=c++11

LINKER = g++
LINKFLAGS = -std=c++11

INCLUDES = -I"/home/dgleason/dev/lib/SFML-2.1/include"
INCLUDES += -I"/home/dgleason/dev/lib/glm/"
INCLUDES += -I"/home/dgleason/dev/lib/glew-1.11.0/include"

LIBPATH = -L"/home/dgleason/dev/lib/SFML-2.1/lib"
LIBPATH += -L"/usr/lib64"
LIBS = -lsfml-window -lsfml-system -lGL -lGLU -lGLEW

SRCS = $(wildcard *.cpp)
SRCS += $(wildcard abc/*.cpp)
# SRCS += $(wildcard instances/*.cpp)
# SRCS += $(wildcard objects/*.cpp)

OUTFLAG = -o
OBJEXT = .o
OBJS := $(patsubst %.cpp,%$(OBJEXT),$(SRCS))

MAIN = bcge2.exe

.PHONEY = all clean run

all: $(MAIN)

$(MAIN): $(OBJS)
	$(LINKER) $(LINKFLAGS) $(LIBPATH) $(OBJS) $(LIBS) $(OUTFLAG) $(MAIN)

clean:
	rm -rf $(MAIN) $(OBJS)

run: all
	LD_LIBRARY_PATH=/home/dgleason/dev/lib/glew-1.11.0/lib/ ./$(MAIN)

optirun: all
	LD_LIBRARY_PATH=/home/dgleason/dev/lib/glew-1.11.0/lib/ optirun ./$(MAIN)

%.o : %.cpp
	$(COMPILER) $(COMPFLAGS) $(INCLUDES) $< $(OUTFLAG) $@
