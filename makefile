all: run

run: clearCodage compile
	./euclideEtendu

compile:
	gcc euclideEtendu.c -Wall -o euclideEtendu

clearCodage:
	rm -rf euclideEtendu
