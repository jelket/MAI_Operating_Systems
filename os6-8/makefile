all: main node

main:
	g++ main.cpp -lzmq -o main -Wall -pedantic

node:
	g++ node.cpp -lzmq -o node -Wall -pedantic

clear:
	rm -rf main node
