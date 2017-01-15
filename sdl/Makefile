COMPILER = g++
COMPFLAGS = -c

LINKER = g++

LIBS = -lGL -lGLU -lGLEW -lSDL2 -lSDL2_image -ljsoncpp

SRCS = $(wildcard *.cpp)
SRCS += $(wildcard abc/*.cpp)
SRCS += $(wildcard games/*.cpp)

OUTFLAG = -o
OBJEXT = .o
OBJS := $(patsubst %.cpp,%$(OBJEXT),$(SRCS))

MAIN = sdl2.exe
DEPS_FILE = .make.deps

.PHONEY = all clean run

all: $(MAIN)

$(DEPS_FILE): $(SRCS)
	rm -f $(DEPS_FILE)
	$(COMPILER) $(COMPFLAGS) -MM $^ > $(DEPS_FILE);

-include $(DEPS_FILE)

$(MAIN): $(OBJS)
	$(LINKER) $(OBJS) $(LIBS) $(OUTFLAG) $(MAIN)

clean:
	rm -f $(DEPS_FILE) $(MAIN)
	find . -name "*.o" -type f -delete

run: all
	./$(MAIN)

optirun: all
	PRIMUS_SYNC=1 optirun ./$(MAIN)

%.o : %.cpp
	$(COMPILER) $(COMPFLAGS) $< $(OUTFLAG) $@
