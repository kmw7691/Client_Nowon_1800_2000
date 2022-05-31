#pragma once

#define INIT_SIZE 10

template<typename T>
class PriorityQueue {

public:
	PriorityQueue();
	~PriorityQueue();
	void Enqueue(const T& data);
	T& Dequeue();

private:
	T* _heap;
	int _size;
	int _capacity


};

template<typename T>
inline PriorityQueue<T>::PriorityQueue()
{
	_heap = new T(INIT_SIZE);
}

template<typename T>
inline PriorityQueue<T>::~PriorityQueue()
{
	delete _heap;
}

template<typename T>
inline void PriorityQueue<T>::Enqueue(const T& data)
{
	if (_size >= capacity) {
		_capacity = _size * 2;
		T* tmpHeap = new T(_capacity);

		for (int i = 0; i < _size; i++)
			tmpHeap[i] = _heap[i];

		delete _heap;
		_heap = new T(_capacity);

		for (int i = 0; i < _size; i++)
			_heap[i] = tmpHeap[i];
		delete tmpHeap;

		_heap[_size] = data;
	}

	_heap[_size] = data;
	_size++;

	int parent = _size / 2;
	int child = _size;

	while (_heap[parent] < _heap[child])
	{
		T tmpData = _heap[parent];
		_heap[parent] = _heap[child];		
		_heap[child] = tmpData;
		child = parent;
		parent = child / 2;
	}
}


template<typename T>
inline T& PriorityQueue<T>::Dequeue()
{
	// TODO: 여기에 return 문을 삽입합니다.
}
