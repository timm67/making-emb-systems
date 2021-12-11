all : main.o flash_emul.o
	gcc -o main main.o flash_emul.o

main.o : main.c
	gcc -c main.c

flash_emul.o : flash_emul.c
	gcc -c flash_emul.c

clean:
	rm -f main main.o flash_emul.o
