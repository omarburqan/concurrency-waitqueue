#ifndef _WAITQUEUE_H
#define _WAITQUEUE_H

#include <iostream> 
#include <queue>


template <typename T> 
class WaitQueue{
	public:
		WaitQueue( size_t size );
		void add(T element);
		T pop();

	private:
	size_t m_size;
		std::queue<T> m_queue;
		pthread_cond_t m_cond;
		pthread_mutex_t m_lock;
};

template <typename T> 
inline WaitQueue<T>::WaitQueue( size_t size ): m_size(size) {
	pthread_mutex_init(&m_lock, NULL);
	pthread_cond_init(&m_cond, NULL);
}
template <typename T> 
inline void WaitQueue<T>::add(T element)
{
    pthread_mutex_lock(&m_lock); 

	while(m_queue.size() >= m_size)
		pthread_cond_wait(&m_cond, &m_lock); 

	m_queue.push(element);
	std::cout << "Element[" << m_queue.back() << "] push succesfuly" << std::endl;
	pthread_cond_signal(&m_cond);

	pthread_mutex_unlock(&m_lock);
}

template <typename T> 
inline T WaitQueue<T>::pop()
{ 
	pthread_mutex_lock(&m_lock);
	
	while(m_queue.empty())
		pthread_cond_wait(&m_cond, &m_lock); 

	T popElement = m_queue.front();
	m_queue.pop();
	std::cout << "Element[" << popElement << "] pop  successfuly" << std::endl;
	pthread_cond_signal(&m_cond);

	pthread_mutex_unlock(&m_lock);

	return popElement;
}


#endif //_WAITQUEUE_H //

