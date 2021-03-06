CC=g++
CFLAGS=-c -Wall -I./inc
OFILES=obj/main.o \
	   obj/Helper.o \
	   obj/StrFunc.o \
	   obj/AbstractAssembler.o \
	   obj/SmallAssembler.o \
	   obj/SmallVirtualMachine.o \
	   obj/SmallComputer.o \
	   obj/LinuxIO.o \
	   obj/VDisk.o \
	   obj/Fat32.o \
	   obj/SmallShell.o

all: main

clean:
	rm obj/*.o

rebuild: clean all

main: $(OFILES) 
	$(CC) $(OFILES) -o main

obj/main.o: inc/Computer/ScreenIO/LinuxIO.hpp \
			inc/Computer/SmallComputer.hpp 
	$(CC) $(CFLAGS) src/main.cpp -o obj/main.o

obj/Helper.o: inc/lib/Helper.hpp src/lib/Helper.cpp
	$(CC) $(CFLAGS) src/lib/Helper.cpp -o obj/Helper.o

obj/StrFunc.o: inc/lib/StrFunc.hpp src/lib/StrFunc.cpp
	$(CC) $(CFLAGS) src/lib/StrFunc.cpp -o obj/StrFunc.o

obj/AbstractAssembler.o: inc/Computer/Assembler/AbstractAssembler.hpp src/Computer/Assembler/AbstractAssembler.cpp
	$(CC) $(CFLAGS) src/Computer/Assembler/AbstractAssembler.cpp -o obj/AbstractAssembler.o

obj/SmallAssembler.o: inc/Computer/Assembler/AbstractAssembler.hpp \
					  inc/Computer/Assembler/SmallAssembler.hpp \
					  src/Computer/Assembler/SmallAssembler.cpp
	$(CC) $(CFLAGS) src/Computer/Assembler/SmallAssembler.cpp -o obj/SmallAssembler.o

obj/SmallVirtualMachine.o: inc/Computer/VirtualMachine/AbstractVirtualMachine.hpp \
						   inc/Computer/VirtualMachine/SmallVirtualMachine.hpp \
						   src/Computer/VirtualMachine/SmallVirtualMachine.cpp
	$(CC) $(CFLAGS) src/Computer/VirtualMachine/SmallVirtualMachine.cpp -o obj/SmallVirtualMachine.o

obj/SmallComputer.o: inc/Computer/ScreenIO/AbstractIO.hpp \
					 obj/LinuxIO.o \
					 inc/Computer/SmallComputer.hpp \
					 src/Computer/SmallComputer.cpp \
					 obj/VDisk.o \
					 obj/AbstractAssembler.o \
					 obj/SmallAssembler.o \
					 obj/SmallVirtualMachine.o \
					 obj/Fat32.o \
					 obj/SmallShell.o
	$(CC) $(CFLAGS) src/Computer/SmallComputer.cpp -o obj/SmallComputer.o

obj/LinuxIO.o: inc/Computer/ScreenIO/AbstractIO.hpp \
			   inc/Computer/ScreenIO/LinuxIO.hpp \
			   src/Computer/ScreenIO/LinuxIO.cpp
	$(CC) $(CFLAGS) src/Computer/ScreenIO/LinuxIO.cpp -o obj/LinuxIO.o

obj/VDisk.o: inc/Computer/FileSystem/VDisk.hpp \
			 src/Computer/FileSystem/VDisk.cpp
	$(CC) $(CFLAGS) src/Computer/FileSystem/VDisk.cpp -o obj/VDisk.o

obj/Fat32.o: inc/Computer/FileSystem/AbstractFileSystem.hpp \
			 inc/Computer/FileSystem/Fat32.hpp \
			 src/Computer/FileSystem/Fat32.cpp
	$(CC) $(CFLAGS) src/Computer/FileSystem/Fat32.cpp -o obj/Fat32.o

obj/SmallShell.o: inc/Computer/Shell/SmallShell.hpp \
			      src/Computer/Shell/SmallShell.cpp
	$(CC) $(CFLAGS) src/Computer/Shell/SmallShell.cpp -o obj/SmallShell.o
