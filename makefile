CC = gcc
OBJS = RLEList.o AsciiArtTool.o
EXEC = AsciiArtTool
DEBUG_FLAG = -DNDEBUG
COMP_FLAG = -std=c99 -Wall -Werror

$(EXEC) : $(OBJS)
	$(CC) $(DEBUG_FLAG) $(OBJS) -o $@
AsciiArtTool.o : AsciiArtTool.c AsciiArtTool.h RLEList.c RLEList.h
	$(CC) -c $(DEBUG_FLAGS) $(COMP_FLAG) $*.c
RLEList.o : RLEList.c RLEList.h
	$(CC) -c $(DEBUG_FLAGS) $(COMP_FLAG) $*.c

clean:
	rm -f $(OBJS) $(EXEC)

