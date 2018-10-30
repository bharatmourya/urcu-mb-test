main: main.c
	g++ -std=c++14 -pthread  test-sysmem.c -lurcu -o test
	g++ -std=c++14 -pthread  rw-lock.c -lurcu -o rwlock
	g++ -std=c++14 -pthread  mutex.c -lurcu -o mutex
clean:
	-rm test rwlock mutex
