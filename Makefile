
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

default: stego.out

# To create the executable file stego.out we need the object files
# bitmap_n.o, bitmap_r.o, and UI.o:
#
stego.out:  bitmap_n.o bitmap_r.o UI.o main.o
	$(CC) $(CFLAGS) bitmap_n.o bitmap_r.o UI.o main.o -o stego.out
	make clean

# To create the object file UI.o, we need the source
# files UI.cpp and UI.h:
#
main.o:  main.cpp UI.h
	$(CC) $(CFLAGS) -c main.cpp

# To create the object file UI.o, we need the source
# files UI.cpp and UI.h:
#
UI.o:  UI.cpp UI.h
	$(CC) $(CFLAGS) -c UI.cpp

# To create the object file bitmap_n.o, we need the source files
# bitmap_n.cpp and bitmap.h:
#
bitmap_n.o:  bitmap_n.cpp bitmap.h
	$(CC) $(CFLAGS) -c bitmap_n.cpp

# To create the object file bitmap_r.o, we need the source files
# bitmap_r.cpp and bitmap.h:
#
bitmap_r.o:  bitmap_r.cpp bitmap.h
	$(CC) $(CFLAGS) -c bitmap_r.cpp

# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean:
	$(RM) count *.o *~
