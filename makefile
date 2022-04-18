CC = gcc
OBJS = RLEList.o AsciiArtTool.o main.o
EXE_NAME = AsciiArtTool
DEBUG_FLAG = -DNDEBUG
COMP_FLAG = -std=c99 -Wall -Werror

$(EXE_NAME) : $(OBJS)
	$(CC) $(DEBUG_FLAG) $(OBJS) -o $@
main.o : main.c AsciiArtTool.o
	$(CC) -c $(DEBUG_FLAGS) $(COMP_FLAG) $*.c
AsciiArtTool.o : AsciiArtTool.c AsciiArtTool.h RLEList.o
	$(CC) -c $(DEBUG_FLAGS) $(COMP_FLAG) $*.c
RLEList.o : RLEList.c RLEList.h
	$(CC) -c $(DEBUG_FLAGS) $(COMP_FLAG) $*.c

clean:
	rm -f $(OBJS) $(EXEC)

