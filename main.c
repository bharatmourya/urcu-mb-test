#include <urcu-bp.h>
#include <pthread.h>
#include <iostream>

using namespace std;

void *reader_fn(void *arg);
void *writer_fn(void *arg);

int main(){
	int nreaders,nwriters;
	cin>>nreaders>>nwriters;

	pthread_t readers[nreaders],writers[nwriters];
	int readers_id[nreaders],writers_id[nwriters];
	
	for(int i = 0;i < nreaders;i++){
		readers_id[i] = i;
		readers[i] = pthread_create(&readers[i],NULL,reader_fn,&readers_id[i]);
	}
	for(int i = 0;i < nwriters;i++){
		writers_id[i] = i;
		writers[i] = pthread_create(&writers[i],NULL,writer_fn,&writers_id[i]);
	}
	for(int i = 0;i < nreaders;i++){
		pthread_join(readers[i],NULL);
	}
	for(int i = 0;i < nwriters;i++){
		pthread_join(writers[i],NULL);
	}
	printf("Done\n");
	return 0;
}

void *reader_fn(void *arg){
	int t_id = *(int *)arg;

	printf("%d thread started reading\n",t_id);
}

void *writer_fn(void *arg){
	int t_id = *(int *)arg;

	printf("%d thread started writing\n",t_id);
}
