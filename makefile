all: zero five ten optional
zero: 0thread.c
	gcc -o zero 0thread.c -lm -lpthread
five: 5thread.c
	gcc -o five 5thread.c -lm -lpthread
ten: 10thread.c
	gcc -o ten 10thread.c -lm -lpthread
optional: optional.c
	gcc -o optional optional.c -lm -lpthread
clean:
	rm -f zero
	rm -f five
	rm -f ten
	rm -f optional
