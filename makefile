run: main
	./main

main: main.c
	$(CC) main.c -lGL -lGLU -lglut -o main

clean:
	rm main
