#include <urcu.h>
#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include <urcu/rculist.h>
#include <urcu/compiler.h>


using namespace std;

void *reader_fn(void *arg);
void *writer_fn(void *arg);

pthread_t *readers,*writers;


struct mynode {
	int value;
	struct cds_list_head node;
	struct rcu_head rcu_head;
};

struct thread_input{
	int id;
	struct mynode *node;
};

CDS_LIST_HEAD(mylist);
int nreaders,nwriters,size;

static
void free_node_rcu(struct rcu_head *head)
{
	struct mynode *node = caa_container_of(head, struct mynode, rcu_head);

	free(node);
}

int main(){
	cin>>nreaders>>nwriters>>size;
	
	readers = (pthread_t *)malloc(sizeof(pthread_t)*nreaders);
	writers = (pthread_t *)malloc(sizeof(pthread_t)*nwriters);
	
	int readers_id[nreaders],writers_id[nwriters];
	struct mynode *node,*n;

	for(int i = 0;i < size;i++){
		node = (struct mynode *)malloc(sizeof(*node));
       		if(!node){

		}
		node->value = i;
		cds_list_add_rcu(&node->node, &mylist);
	}

	for(long i = 0;i < nreaders;i++){
		readers_id[i] = i;
		readers[i] = pthread_create(&readers[i],NULL,reader_fn,&readers_id[i]);
	}
	for(long i = 0;i < nwriters;i++){
		usleep(5000);
		writers_id[i] = i;
		writers[i] = pthread_create(&writers[i],NULL,writer_fn,&writers_id[i]);
	}
	for(long i = 0;i < nreaders;i++){
		pthread_join(readers[i],NULL);
	}
	for(long i = 0;i < nwriters;i++){
		pthread_join(writers[i],NULL);
	}
	printf("Done\n");
	return 0;
}

void *reader_fn(void *arg){
	int t_id = *(int *)arg;
	printf("%d thread started reading\n",t_id);
	struct mynode *node;

//	rcu_read_lock();
		cds_list_for_each_entry(node, &mylist, node) {
			printf(" %d", node->value);
		}
//	rcu_read_unlock();
}

void *writer_fn(void *arg){
	int t_id = *(int *)arg;
	int rnd = t_id%size;
	printf("%d thread started writing\n",t_id);
	struct mynode *node,*n;

//	rcu_read_lock();
		cds_list_for_each_entry_safe(node, n, &mylist, node) {
			struct mynode *new_node;
			new_node = (struct mynode *)malloc(sizeof(*node));
			if (!new_node) {
			}
			/* Replacement node value is negated original value. */
			new_node->value = node->value;
			cds_list_replace_rcu(&node->node, &new_node->node);
			call_rcu(&node->rcu_head, free_node_rcu);
		}	
//	rcu_read_unlock();
}
