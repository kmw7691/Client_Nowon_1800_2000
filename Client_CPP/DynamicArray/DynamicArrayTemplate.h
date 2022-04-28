#pragma once
template <typename T>
class DynamicArray
{
private:
	T* _data;
	int _length;
	int _capacity;
	const int DEFAULT_SIZE;

public:
	int Length();
	void Add(T item);
	int Find(T item); 
	bool IsExist(T item);            
	bool Remove(T item); 
	bool RemoveAt(int index); 
	void Delete();

	DynamicArray();
	~DynamicArray();

	T& operator[] (int index) {
		if (index > 0 &&
			index < _length) {
			throw "배열 인덱스가 허용범위를 넘어섰습니다";
		}
		return _data[index];
	}
};

template <typename T>
int DynamicArray<T>::Length() {
	return _length;
}

template<typename T>
void DynamicArray<T>::Add(T item)
{
	if (_length >= _capacity) {
		_capacity *= 2;
		T* tmp = new T[_capacity];
		for (int i = 0; i < _length; i++)
			tmp[i] = _data[i];
		delete[] _data;
		_data = new T[_capacity];
		for (int i = 0; i < _length; i++)
			_data[i] = tmp[i];
		delete[] tmp;
	}
	_data[_length] = item;
	_length++;
}

template<typename T>
int DynamicArray<T>::Find(T item)
{
	for (int i = 0; i < _length; i++)
	{
		if (_data[i] == item)
			return i;
	}
	return -1;
}

template<typename T>
bool DynamicArray<T>::IsExist(T item)
{
	for (int i = 0; i < _length; i++)
	{
		if (_data[i] == item)
			return true;
	}
	return false;
}

template<typename T>
bool DynamicArray<T>::Remove(T item)
{
	for (int i = 0; i < _length; i++)
	{
		if (_data[i] == item)
			return RemoveAt(i);
	}
	return false;
}

template<typename T>
inline bool DynamicArray<T>::RemoveAt(int index)
{
	if (index < _length) {
		for (int i = index; i < _length - 1; i++)
		{
			_data[i] = _data[i + 1];
		}
		_length--;
		return true;
	}

	return false;
}

template <typename T>
inline void DynamicArray<T>::Delete()
{
	delete[] _data;
}

template <typename T>
DynamicArray<T>::DynamicArray()
	:DEFAULT_SIZE(1)
{
	_length = 0;
	_capacity = DEFAULT_SIZE;
	_data = new int[_capacity];
}
