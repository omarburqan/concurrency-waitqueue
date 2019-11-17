#include "wait_queue.cpp"

#define NUM_OF_THREADS 10
#define QUEUE_SIZE 5
void* push_thread(void* queue)
{
	WaitQueue <int> *wait_queue = (WaitQueue<int> *) queue;	
	for(int i = 0 ; i < NUM_OF_THREADS/2 ; ++i )
		wait_queue->add(i);
	return NULL;
}

void* pop_thread(void* queue)
{
	WaitQueue <int> *wait_queue = (WaitQueue<int> *) queue;
	for( int i = 0 ; i < NUM_OF_THREADS/2 ; ++i )
		wait_queue->pop(); 
	return NULL;
}


int main()
{
	pthread_t push_threads[NUM_OF_THREADS];
	pthread_t pop_threads[NUM_OF_THREADS];
	size_t i;

	WaitQueue<int> queue(QUEUE_SIZE);

	for( i = 0 ; i < NUM_OF_THREADS ; ++i)
		pthread_create(&push_threads[i], NULL, push_thread, &queue);

	for( i = 0 ; i < NUM_OF_THREADS ; ++i)	
		pthread_create(&pop_threads[i], NULL, pop_thread, &queue);

	for( i = 0 ; i < NUM_OF_THREADS ; ++i)
		pthread_join(push_threads[i], NULL);

	for( i = 0;  i < NUM_OF_THREADS ; ++i)
		pthread_join(pop_threads[i], NULL);
	
	
	return 0;
}

