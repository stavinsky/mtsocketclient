LIBS += -lws2_32
LIBS += -static-libgcc 
RM = rm -f 
CPP += client.cpp main.cpp
OBJ += client.o main.o
BIN      = winsock_tst
CXXFLAGS = $(CXXINCS) -m32 -std=c++11
CFLAGS   = $(INCS) -m32 -std=c++11
CPP      = g++.exe
CC       = gcc.exe

all: $(BIN)

$(BIN): $(OBJ)
	$(CPP) $(OBJ) $(LIBS) -o $(BIN)
	
client.o: client.cpp
	$(CPP) -c client.cpp -o client.o $(CXXFLAGS)
	
main.o: main.cpp
	$(CPP) -c main.cpp -o main.o $(CXXFLAGS)
				
clean: 
	${RM} $(OBJ) $(BIN)
	
.PHONY: all clean 