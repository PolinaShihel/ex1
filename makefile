CC = gcc
OBJS = RLEList.o AsciiArtTool.o main.o
EXEC = AsciiArtTool
DEBUG_FLAG = -DNDEBUG
COMP_FLAG =  gcc -std=c99 -o AsciiArtTool -I/home/mtm/public/2122b/ex1 -Itool -Wall -pedantic-errors -Werror -DNDEBUG *.c tool/*.c

$(EXEC) : $(OBJS)
	$(CC) $(DEBUG_FLAG) $(OBJS) -o $@
main.o : main.c AsciiArtTool.o
	$(CC) $(DEBUG_FLAGS) $(COMP_FLAG) $*.c
AsciiArtTool.o : AsciiArtTool.c AsciiArtTool.h RLEList.o
	$(CC) $(DEBUG_FLAGS) $(COMP_FLAG) $*.c
RLEList.o : RLEList.c RLEList.h
	$(CC) $(DEBUG_FLAGS) $(COMP_FLAG) $*.c

clean:
	rm -f $(OBJS) $(EXEC)

