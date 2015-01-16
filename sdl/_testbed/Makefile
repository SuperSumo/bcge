COMPILER = g++
COMPFLAGS = -c

LINKER = g++

LIBS = -lGL -lGLU -lGLEW -lSDL2 -ljsoncpp

SRCS = $(wildcard *.cpp)

OUTFLAG = -o
OBJEXT = .o
OBJS := $(patsubst %.cpp,%$(OBJEXT),$(SRCS))

MAIN = sdl2.exe

.PHONEY = all clean run

all: $(MAIN)

dependencies.txt: $(SRCS)
	rm -f dependencies.txt
	$(COMPILER) $(COMPFLAGS) -MM $^ > dependencies.txt;

include dependencies.txt

$(MAIN): $(OBJS)
	$(LINKER) $(OBJS) $(LIBS) $(OUTFLAG) $(MAIN)

clean:
	rm -f $(MAIN)
	find . -name "*.o" -type f -delete

run: all
	./$(MAIN)

optirun: all
	PRIMUS_SYNC=1 optirun ./$(MAIN)

%.o : %.cpp
	$(COMPILER) $(COMPFLAGS) $< $(OUTFLAG) $@
