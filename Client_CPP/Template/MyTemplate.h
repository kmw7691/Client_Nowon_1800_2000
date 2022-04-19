#pragma once

template<typename T, typename K>
class MyTemplate
{
private:
	T a;
	K b;

public:
	T ForceSum(T t,K k);
};

template<typename T, typename K>
inline T MyTemplate<T, K>::ForceSum(T t, K k)
{
	return t + (T)k;
}
