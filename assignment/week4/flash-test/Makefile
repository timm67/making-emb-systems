all : main.o flash_emul.o libunity.a
	gcc -o main main.o flash_emul.o libunity.a 

main.o : main.c
	gcc -c main.c

flash_emul.o : flash_emul.c
	gcc -c flash_emul.c

clean:
	rm main main.o flash_emul.o
