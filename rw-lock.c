#include <chrono>  // for time
#include <mutex>   // for std::mutex
#include <shared_mutex> // for reader-writer lock
#include <urcu.h>  // for urcu-mb
#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include <urcu/rculist.h>
#include <urcu/compiler.h>
#include <stdio.h>
#include <queue>
using namespace std;

void *reader_fn(void *arg);
void *writer_fn(void *arg);

pthread_t *readers,*writers;

long int nreaders,nwriters,size,nthreads;
bool flag_rcu;
mutex writer_mtx;
shared_timed_mutex shrd_mtx;

vector<int> myqueue;

int main(){
	readers = (pthread_t *)malloc(sizeof(pthread_t)*1000);
	writers = (pthread_t *)malloc(sizeof(pthread_t)*1000);
	long int *readers_id,*writers_id;
	scanf("%ld %ld %ld %ld",&nreaders,&nwriters,&size,&nthreads);	
	readers_id = (long int *)malloc(sizeof(long int)*1000);
	writers_id = (long int *)malloc(sizeof(long int)*1000);
	struct mynode *node,*n;

	for(int i = 0;i < size;i++){
		myqueue.push_back(i);
	}

	auto start = std::chrono::high_resolution_clock::now();
	long int cr=0,cw=0,flg = 0 ; // flg is set means writer else reader
	for(long i = 0;i < nthreads;i++){		
		readers_id[i] = i;
		pthread_create(&readers[i],NULL,reader_fn,&readers_id[i]);
		cr++;
	}

	for(int j = nthreads;j < 2*nthreads;j++){
		writers_id[j] = j;
		pthread_create(&writers[j],NULL,writer_fn,&writers_id[j]);	
		cw++;	
	}
	
	for(long i = 0;i < nthreads;i++){
		pthread_join(readers[i],NULL);
	}
	for(long i = nthreads;i < 2*nthreads;i++){
		pthread_join(writers[i],NULL);
	}
	auto finish = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> elapsed = finish - start;
	std::cout << "Elapsed time: " << elapsed.count() << " s\n";
	return 0;
}

void *reader_fn(void *arg){
	
	long int t_id = *(long *)arg;
	for(int i = 0;i < nreaders;i++){
		shared_lock<shared_timed_mutex> lock(shrd_mtx);
		for(int i : myqueue){
			int temp = i;
		}
	}
}

void *writer_fn(void *arg){
	int t_id = *(int *)arg;
	struct mynode *node,*n;
	for(int i = 0; i < nwriters;i++){
		unique_lock<shared_timed_mutex> lock(shrd_mtx);
		for(auto it = myqueue.begin(); it != myqueue.end();it++){
			if(*it == i % size){
				*it = i%size;	
			}
		}
		
	}	
}
