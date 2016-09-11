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
	   obj/VDisk.o

all: main

clean:
	rm obj/*.o

rebuild: clean all

main: $(OFILES) 
	$(CC) $(OFILES) -o main

obj/main.o: inc/lib/Helper.hpp \
			inc/lib/StrFunc.hpp \
			inc/lib/VecFunc.hpp \
			inc/Assembler/AbstractAssembler.hpp \
			inc/Assembler/SmallAssembler.hpp \
			inc/VirtualMachine/SmallVirtualMachine.hpp \
			inc/Computer/SmallComputer.hpp \
			src/lib/Helper.cpp \
			src/lib/StrFunc.cpp \
			src/Assembler/AbstractAssembler.cpp \
			src/Assembler/SmallAssembler.cpp \
			src/VirtualMachine/SmallVirtualMachine.cpp \
			src/Computer/SmallComputer.cpp
	$(CC) $(CFLAGS) src/main.cpp -o obj/main.o

obj/Helper.o: inc/lib/Helper.hpp src/lib/Helper.cpp
	$(CC) $(CFLAGS) src/lib/Helper.cpp -o obj/Helper.o

obj/StrFunc.o: inc/lib/StrFunc.hpp src/lib/StrFunc.cpp
	$(CC) $(CFLAGS) src/lib/StrFunc.cpp -o obj/StrFunc.o

obj/AbstractAssembler.o: inc/Assembler/AbstractAssembler.hpp src/Assembler/AbstractAssembler.cpp
	$(CC) $(CFLAGS) src/Assembler/AbstractAssembler.cpp -o obj/AbstractAssembler.o

obj/SmallAssembler.o: inc/Assembler/SmallAssembler.hpp src/Assembler/SmallAssembler.cpp
	$(CC) $(CFLAGS) src/Assembler/SmallAssembler.cpp -o obj/SmallAssembler.o

obj/SmallVirtualMachine.o: inc/VirtualMachine/SmallVirtualMachine.hpp src/VirtualMachine/SmallVirtualMachine.cpp
	$(CC) $(CFLAGS) src/VirtualMachine/SmallVirtualMachine.cpp -o obj/SmallVirtualMachine.o

obj/SmallComputer.o: inc/Computer/ScreenIO/AbstractIO.hpp \
					 obj/LinuxIO.o \
					 inc/Computer/SmallComputer.hpp \
					 src/Computer/SmallComputer.cpp \
					 obj/VDisk.o 
	$(CC) $(CFLAGS) src/Computer/SmallComputer.cpp -o obj/SmallComputer.o

obj/LinuxIO.o: inc/Computer/ScreenIO/AbstractIO.hpp \
			   inc/Computer/ScreenIO/LinuxIO.hpp \
			   src/Computer/ScreenIO/LinuxIO.cpp
	$(CC) $(CFLAGS) src/Computer/ScreenIO/LinuxIO.cpp -o obj/LinuxIO.o

obj/VDisk.o: inc/Computer/FileSystem/VDisk.hpp \
			 src/Computer/FileSystem/VDisk.cpp
	$(CC) $(CFLAGS) src/Computer/FileSystem/VDisk.cpp -o obj/VDisk.o


