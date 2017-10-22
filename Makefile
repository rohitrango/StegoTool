
# Typing 'make' or 'make main' will create the executable file.
#

# define some Makefile variables for the compiler and compiler flags
# to use Makefile variables later in the Makefile: $()
#
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
#
# for C++ define  CC = g++
CC = g++
CFLAGS  = -g -Wall
OBJ = obj
APP = stego

default: $(APP).exe

# To create the executable file stego.out we need the object files
# bitmap_n.o, bitmap_r.o, and UI.o:
#
$(APP).exe:  dirs bitmap_n.o bitmap_r.o UI.o main.o
	$(CC) $(CFLAGS) $(OBJ)/bitmap_n.o $(OBJ)/bitmap_r.o $(OBJ)/UI.o $(OBJ)/main.o -o $(APP).exe

# To create the object files, we need the output directories
dirs:
	mkdir -p $(OBJ)

# To create the object file UI.o, we need the source
# files UI.cpp and UI.h:
#
main.o:  main.cpp UI.h
	$(CC) $(CFLAGS) -c main.cpp -o $(OBJ)/main.o

# To create the object file UI.o, we need the source
# files UI.cpp and UI.h:
#
UI.o:  UI.cpp UI.h
	$(CC) $(CFLAGS) -c UI.cpp -o $(OBJ)/UI.o

# To create the object file bitmap_n.o, we need the source files
# bitmap_n.cpp and bitmap.h:
#
bitmap_n.o:  bitmap_n.cpp bitmap.h
	$(CC) $(CFLAGS) -c bitmap_n.cpp -o $(OBJ)/bitmap_n.o

# To create the object file bitmap_r.o, we need the source files
# bitmap_r.cpp and bitmap.h:
#
bitmap_r.o:  bitmap_r.cpp bitmap.h
	$(CC) $(CFLAGS) -c bitmap_r.cpp -o $(OBJ)/bitmap_r.o

# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean:
	$(RM) bin/*.o *~ $(APP).exe
