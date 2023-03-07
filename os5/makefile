all: main1 main2

libfirst.so: realization1.o
	gcc -shared realization1.o -o libfirst.so

libsecond.so: realization2.o
	gcc -shared realization2.o -o libsecond.so

realization1.o: realization1.c
	gcc -fPIC -c realization1.c -o realization1.o

realization2.o: realization2.c
	gcc -fPIC -c realization2.c -o realization2.o

main1: libfirst.so main1.c
	gcc main1.c -L. libfirst.so -o main1

main2: libfirst.so libsecond.so main2.c
	gcc main2.c -ldl -o main2

clean:
	rm -r *.so *.o main1 main2
