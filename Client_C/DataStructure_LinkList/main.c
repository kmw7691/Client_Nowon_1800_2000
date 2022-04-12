#include <stdio.h>
#include <stdlib.h>

void AddFirst(int, int), AddLast(), ShowAll();

typedef struct _Node {
	int id;
	int value;
	struct _Node* next;
}Node;

Node* head,* tail,* tmp,* tmp2;

void AddLast(int in_id, int in_value) {
	tmp = (Node*)malloc(sizeof(Node));
	if (head == NULL)
		head = tmp;
	else
		tail->next = tmp;

	tmp->id = in_id;
	tmp->value = in_value;
	tmp->next = NULL;
	tail = tmp;
}

void AddFirst(int in_id, int in_value) {
	tmp = (Node*)malloc(sizeof(Node));
	if (head == NULL)
		head = tmp;
	else
		tmp->next = head;

	tmp->id = in_id;
	tmp->value = in_value;
	head = tmp;
}

void AddAfter(int target_id,int in_id, int in_value) {
	tmp = head;
	while (tmp != NULL)
	{
		if (tmp->id == target_id) {
			tmp2 = (Node*)malloc(sizeof(Node));
			if (tmp->next != NULL) {
				tmp2->next = tmp->next;
			}
			tmp->next = tmp2;
			tmp2->id = in_id;
			tmp2->value = in_value;
			return;
		}
		tmp = tmp->next;
	}
	return;
}

int GetFirst() {
	if (head = NULL)
		return -1;
	else
		return head->value;
}

int GetLast() {
	if (tail = NULL)
		return -1;
	else
		return tail->value;
}

int Remove(int target_id) {

	int isRemoved = 0;
	tmp = head;

	if (tmp != NULL) {

		if (tmp->id == target_id)
		{
			tmp = head;
			head = tmp->next;
			free(tmp);
			isRemoved = 1;
		}

		if(tail->id == target_id){}

		while (tmp->next != NULL)
		{
			if (tmp->next->id = target_id) {
				tmp2 = tmp->next->next;
				free(tmp->next);
				isRemoved = 1;
				tmp->next = tmp2;

				if (tmp->next->next == NULL)
					tail = tmp->next;
				break;
			}
			else
				tmp = tmp->next;
		}
	}
	return isRemoved;
}

void ShowAll() {
	tmp = head;
	printf("(id, value) : ");
	while (tmp != NULL)
	{
		printf("(%d, %d)", tmp->id, tmp->value);
		tmp = tmp->next;
	}
	printf("\n");
}

int main() {
	AddLast(1, 3);
	AddLast(3, 25);
	AddLast(6, 35);
	AddLast(21, 4);
	ShowAll();

	return 0;
}