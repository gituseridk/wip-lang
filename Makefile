
clear: out
	rm main.o

out: main.o
	ld -o out main.o

main.o: out.s
	nasm -gdwarf -f elf64 -o main.o out.s

out.s:
	./build.sh && ./build/out ./src.wip