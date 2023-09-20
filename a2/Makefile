all: fifo sjf rr

fifo: driver.cpp Loader.cpp simulator.cpp
	g++ -std=c++20 -Wall -o fifo driver.cpp Loader.cpp simulator.cpp

sjf: driver.cpp Loader.cpp simulator.cpp
	g++ -std=c++20 -Wall -o sjf driver.cpp Loader.cpp simulator.cpp

rr: driver.cpp Loader.cpp simulator.cpp
	g++ -std=c++20 -Wall -o rr driver.cpp Loader.cpp simulator.cpp

# Clean rule
clean:
	rm -f fifo
	rm -f sjf
	rm -f rr
