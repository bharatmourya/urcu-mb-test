main: main.c
	g++ -pthread -lurcu main.c -o main

clean:
	-rm main
