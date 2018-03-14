# SRC := src/Extensions.cpp src/Group.cpp src/Networking.cpp src/Hub.cpp src/Node.cpp src/WebSocket.cpp src/HTTPSocket.cpp src/Socket.cpp src/Epoll.cpp
SRCS=$(wildcard ./src/*.cpp)
OBJS=$(SRCS:.cpp=.o)
CPP_SHARED := -std=c++11 -O3 -I src -shared -fPIC 
CPP_OPENSSL_OSX := -L/usr/local/opt/openssl/lib -I/usr/local/opt/openssl/include
CPP_OSX := -stdlib=libc++ -mmacosx-version-min=10.7 -undefined dynamic_lookup $(CPP_OPENSSL_OSX)

default:
	make `(uname -s)`

%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(CPP_SHARED) -c $< -o $@

Linux: $(OBJS)
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(CPP_SHARED) $(OBJS) -s -o libuWS.so
	ar rcs libuWS.a $(OBJS)
Darwin:
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(CPP_SHARED) $(CPP_OSX) -o libuWS.dylib
.PHONY: install
install:
	make install`(uname -s)`
.PHONY: installLinux
installLinux:
	$(eval PREFIX ?= /usr)
	if [ -d "/usr/lib64" ]; then mkdir -p $(PREFIX)/lib64 && cp libuWS.so libuWS.a $(PREFIX)/lib64/; else mkdir -p $(PREFIX)/lib && cp libuWS.so libuWS.a $(PREFIX)/lib/; fi
	mkdir -p $(PREFIX)/include/uWS
	cp src/*.h $(PREFIX)/include/uWS/
.PHONY: installDarwin
installDarwin:
	$(eval PREFIX ?= /usr/local)
	mkdir -p $(PREFIX)/lib
	cp libuWS.dylib $(PREFIX)/lib/
	mkdir -p $(PREFIX)/include/uWS
	cp src/*.h $(PREFIX)/include/uWS/
.PHONY: clean
clean:
	rm -f libuWS.so libuWS.a 
	rm -f libuWS.dylib
.PHONY: tests
tests:
	$(CXX) $(CPP_OPENSSL_OSX) -std=c++11 -O3 tests/main.cpp -Isrc -o testsBin -lpthread -L. -luWS -lssl -lcrypto -lz -luv
