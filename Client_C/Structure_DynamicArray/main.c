#include <stdio.h>
#include <stdlib.h>

void Add(int item);
int Remove(int item), RemoveAt(int index);
void Clear();

const int DEFAULT_SIZE = 1;
int* data;
int count;
int capacity;
int* tmp;

int main() {

	Add(1);
	Add(3);
	Add(5);
	Add(5);
	Add(5);
	printf("is data of index 3 removed ?: %d\n", RemoveAt(3));
	printf("is data of index 3 removed ?: %d\n", RemoveAt(3));
	printf("is data of index 3 removed ?: %d\n", RemoveAt(3));

	printf("%d\n", count);
	printf("%d\n", capacity);

	Clear();
	return 0;
}

void Add(int item)
{
	if (count == 0) {
		data = (int*)malloc(DEFAULT_SIZE * sizeof(int));
		capacity = DEFAULT_SIZE;
	}
	else if (count >= capacity) {
		tmp = (int*)malloc(count * 2 * sizeof(int));
		capacity = count * 2;
		for (int i = 0; i < count; i++)
			tmp[i] = data[i];
		free(data);
		data = (int*)malloc(count * 2 * sizeof(int));
		for (int i = 0; i < count; i++)
			data[i] = tmp[i];
		free(tmp);
	}
	data[count] = item;
	count++;
}

// 해당 인덱스의 배열 요소를 지우고
// 그 뒤의 모든 요소들을 한 칸씩 당겨준다.
int RemoveAt(int index) {
	int isRemoved = 0;

	if (index < count - 1) {
		for (int i = index; i < count - 1; i++)
		{
			data[i] = data[i + 1];
		}
		count--;
		isRemoved = 1;
	}
	else if (index == count - 1) {
		count--;
		isRemoved = 1;
	}


	return isRemoved;
}

// 특정 아이템을 지우는 함수
int Remove(int item) {
	int isRemoved = 0;
	for (int i = 0; i < count; i++)
	{
		if (data[i] == item) {
			isRemoved = RemoveAt(i);
			break;
		}
	}
	return isRemoved;
}

int isExist(int item) {
	int isExist = 0;
	for (int i = 0; i < count; i++)
	{
		if (data[i] == item)
			return 1;
	}
	return 0;
}

int ShowAll() {
	for (int i = 0; i < count; i++)
		printf("%d", data[i]);
}

void Clear() {
	free(data);
	count = 0;
	capacity = 0;
}