#pragma once
class Sortexamples
{
public:
	
	// BubbleSort
	static void BubbleSort(int* arr, int length);
	static void SelectionSort(int arr[], int length);
	static void InsertionSort(int arr[], int length);
	static void Merge(int arr[], int start, int end, int mid);
	static void MergeSort(int arr[], int start, int end);
	static void QuickSort(int arr[], int start, int end);

private:
	static void Merge(int arr[], int start, int end, int mid);
	static int Partition(int arr[], int start, int end);

};

