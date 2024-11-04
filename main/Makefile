all: main.o kit-config.o in-out.o
	gcc main.o kit-config.o in-out.o -o teste

main.o: main.c 
	gcc -c main.c 

kit-config.o: kit-config.c 
	gcc -c kit-config.c 

in-out.o: in-out.c 
	gcc -c in-out.c 

clean:
	rm *.o
