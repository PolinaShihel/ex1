CC = gcc
OBJS = tool/main.o tool/AsciiArtTool.o RLEList.o 
EXEC = AsciiArtTool
DEST = tool
REMOTE = /home/mtm/public/2122b/ex1
DEBUG_FLAG = #now_empty
CFLAGS = -std=c99 -I/home/mtm/public/2122b/ex1 -Itool -Wall -pedantic-errors -Werror 


$(EXEC) : $(OBJS)
	$(CC) $(DEBUG_FLAG) $(OBJS) -o $@
$(DEST)/main.o : $(DEST)/main.c $(DEST)/AsciiArtTool.h $(REMOTE)/RLEList.h
$(DEST)/AsciiArtTool.o : $(DEST)/AsciiArtTool.c $(DEST)/AsciiArtTool.h $(REMOTE)/RLEList.h
RLEList.o : RLEList.c $(REMOTE)/RLEList.h

clean:
	rm -f $(OBJS) $(EXEC)

