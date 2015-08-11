LIBS += -lws2_32 #-lstdc++
LIBS += -static-libgcc 
LIBS += -static-libstdc++
RM = rm -f 
SRC += client.cpp main.cpp
OBJ = $(SRC:.cpp=.o)
BIN      = winsock_tst.exe
CXXFLAGS = -m32 -std=c++11 -Wall
CPP      = i686-w64-mingw32-g++
CC       = i686-w64-mingw32-gcc
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
	$(CPP) -shared   -o $(DLL) client.o $(LIBS)
	$(CPP) main.o -o $(BIN)  -L. -lclient
.PHONY: all clean 
