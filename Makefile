LIBS += -lws2_32 -lstdc++
LIBS += -static-libgcc 
RM = rm -f 
SRC += client.cpp main.cpp
OBJ = $(SRC:.cpp=.o)
BIN      = winsock_tst
CXXFLAGS = -m32 -std=c++11 -Wall
CPP      = g++.exe
CC       = gcc.exe
DLL = client.dll
all: $(BIN)

$(BIN): $(OBJ)
	$(CPP) $(OBJ)  -o $(BIN) $(LIBS)
	
client.o: client.cpp
	$(CPP) -c client.cpp -o client.o $(CXXFLAGS)
	
main.o: main.cpp
	$(CPP) -c main.cpp -o main.o $(CXXFLAGS)
				
clean: 
	${RM} $(OBJ) $(BIN) $(DLL)
	
dll: $(OBJ)
	@echo '### Here we will create separate dll and exe file ###'
	gcc -shared   -o $(DLL) client.o $(LIBS)
	$(CPP) main.o -o $(BIN) $(LIBS) -L. -lclient
.PHONY: all clean 