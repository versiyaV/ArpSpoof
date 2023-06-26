INCLUDE_PATH = arp-spoof/
CPP_FLAGS = -Wall -Wextra -O2 -std=c++17
PTHREAD = -pthread

M_OBJS = bin/models/scanner.o bin/models/arp.o bin/models/host.o bin/models/interface.o bin/controller/controller.o bin/view/string_view.o bin/view/thread_view.o bin/view/socket_view.o bin/view/mac_view.o

all: bin/main

clean:
	rm -rf bin/

bin/main: main.cpp $(M_OBJS) 
	g++ $^ -o $@ $(CPP_FLAGS) $(PTHREAD)

bin/models/scanner.o: models/scanner.cpp
	mkdir -p bin/models
	g++ $^ -c -o $@ $(CPP_FLAGS)

bin/models/arp.o: models/arp.cpp
	mkdir -p bin/models
	g++ $^ -c -o $@ $(CPP_FLAGS) $(PTHREAD)

bin/models/host.o: models/host.cpp
	mkdir -p bin/models
	g++ $^ -c -o $@ $(CPP_FLAGS)

bin/models/interface.o: models/interface.cpp
	mkdir -p bin/models
	g++ $^ -c -o $@ $(CPP_FLAGS)

bin/controller/controller.o: controller/controller.cpp
	mkdir -p bin/controller
	g++ $^ -c -o $@ $(CPP_FLAGS)

bin/view/string_view.o: view/string_view.cpp
	mkdir -p bin/view/
	g++ $^ -c -o $@ $(CPP_FLAGS)

bin/view/thread_view.o: view/thread_view.cpp
	mkdir -p bin/view/
	g++ $^ -c -o $@ $(CPP_FLAGS)

bin/view/socket_view.o: view/socket_view.cpp
	mkdir -p bin/view/
	g++ $^ -c -o $@ $(CPP_FLAGS)

bin/view/mac_view.o: view/mac_view.cpp
	mkdir -p bin/view/
	g++ $^ -c -o $@ $(CPP_FLAGS)