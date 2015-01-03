COMPILER = g++
COMPFLAGS = -c

LINKER = g++
LINKFLAGS =

INCLUDES = -I"/home/dgleason/dev/lib/jsoncpp-src-0.5.0/include/"
INCLUDES += -I"/home/dgleason/dev/lib/glm/"
INCLUDES += -I"/home/dgleason/dev/lib/glew-1.11.0/include"

LIBPATH = -L"/home/dgleason/dev/lib/jsoncpp-src-0.5.0/libs/linux-gcc-4.8/"
LIBS = -lGL -lGLU -lGLEW -lSDL2 -ljson_linux-gcc-4.8_libmt

SRCS = $(wildcard *.cpp)
SRCS += $(wildcard abc/*.cpp)
SRCS += $(wildcard games/*.cpp)
# SRCS += $(wildcard instances/*.cpp)
# SRCS += $(wildcard objects/*.cpp)

OUTFLAG = -o
OBJEXT = .o
OBJS := $(patsubst %.cpp,%$(OBJEXT),$(SRCS))

MAIN = sdl2.exe

.PHONEY = all clean run

dependencies.txt: $(SRCS)
	rm -f dependencies.txt
	$(COMPILER) $(COMPFLAGS) $(INCLUDES) -MM $^ > dependencies.txt;

include dependencies.txt

all: $(MAIN)

$(MAIN): $(OBJS)
	$(LINKER) $(LINKFLAGS) $(LIBPATH) $(OBJS) $(LIBS) $(OUTFLAG) $(MAIN)

clean:
	rm -rf $(MAIN) $(OBJS)

run: all
	./$(MAIN)

optirun: all
	PRIMUS_SYNC=1 optirun ./$(MAIN)

%.o : %.cpp
	$(COMPILER) $(COMPFLAGS) $(INCLUDES) $< $(OUTFLAG) $@
