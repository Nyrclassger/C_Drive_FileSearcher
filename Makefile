CC = gcc
CFLAGS = -Wall -Wextra -pthread
LIBRARY_PATH = ../file_search_library

all: app

lib: $(LIBRARY_PATH)/file_search.c $(LIBRARY_PATH)/file_search.h
	$(CC) $(CFLAGS) -c $(LIBRARY_PATH)/file_search.c -o $(LIBRARY_PATH)/file_search.o
	ar rcs $(LIBRARY_PATH)/libfile_search.a $(LIBRARY_PATH)/file_search.o

app: lib main.c
	$(CC) $(CFLAGS) main.c -o file_search_app -L$(LIBRARY_PATH) -lfile_search

clean:
	rm -f $(LIBRARY_PATH)/*.o $(LIBRARY_PATH)/*.a file_search_app